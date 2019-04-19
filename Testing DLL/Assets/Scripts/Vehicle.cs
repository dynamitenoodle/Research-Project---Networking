using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Vehicle : MonoBehaviour {

	// attributes
	Vector3 velocity;
	Vector3 position;
	[HideInInspector] public Vector3 direction;
	public float speed = 5;
    GameObject background;
    GameObject cannon;
    Camera cam;

    // shooting
    public GameObject bulletPrefab;
    float shotTimer;
    public float shotTimerMax = 1f;

    // sets how far the player can go
    float minX;
    float minY;
    float maxX;
    float maxY;

    // properties
    bool Up { get { return Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow); } }
	bool Down { get { return Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.DownArrow); } }
	bool Right { get { return Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow); } }
	bool Left { get { return Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow); } }

	// Use this for initialization
	void Start ()
	{
		velocity = Vector3.zero;
		position = transform.position;
		direction = Vector3.zero;

        background = GameObject.Find("Background");
        minX = background.GetComponent<Background>().minX;
        minY = background.GetComponent<Background>().minY;
        maxX = background.GetComponent<Background>().maxX;
        maxY = background.GetComponent<Background>().maxY;

        cannon = transform.GetChild(0).gameObject;
        cannon.transform.parent = null;
        cam = GameObject.Find("Main Camera").GetComponent<Camera>();

        shotTimer = shotTimerMax;
    }
	
	// Update is called once per frame
	void Update ()
	{
        // Check input
		if (Up)
			direction.y += 1;
		if (Down)
			direction.y -= 1;
		if (Right)
			direction.x += 1;
		if (Left)
			direction.x -= 1;

        // only face if a button is being pressed
        if (Up || Down || Right || Left)
            transform.up = direction;

        // direction calculator
        direction = Vector3.ClampMagnitude(direction, 1);

        // Checks to see if we should move if the direction at all
        if (transform.position.x < minX && Left)
            direction.x = 0;
        if (transform.position.x > maxX && Right)
            direction.x = 0;
        if (transform.position.y < minY && Down)
            direction.y = 0;
        if (transform.position.y > maxY && Up)
            direction.y = 0;

        // Checks to make sure no double input presses
        if (!Up && !Down || Up && Down)
			direction.y = 0;
		if (!Right && !Left || Right && Left)
			direction.x = 0;

        // update the velocity and position, with a check to make sure we should
        velocity = direction * speed * Time.deltaTime;
        position += velocity;

        transform.position = position;

        direction = Vector3.zero;

        // Calculate Cannon angle
        CannonUpdate();

        // Shooting Method
        if (shotTimer >= shotTimerMax)
        {
            if (Input.GetMouseButtonDown(0))
            {
                GameObject tempBullet = Instantiate(bulletPrefab);
                tempBullet.transform.position = cannon.transform.GetChild(0).transform.position;
                tempBullet.GetComponent<Bullet>().direction = Vector3.Normalize(tempBullet.transform.position - cannon.transform.position);
                shotTimer = 0;
            }
        }
        else
            shotTimer += Time.deltaTime;
    }

    void CannonUpdate()
    {
        Vector3 mouse_pos = Input.mousePosition;
        mouse_pos.z = 10; //The distance between the camera and object
        Vector3 object_pos = cam.WorldToScreenPoint(cannon.transform.position);
        mouse_pos.x = mouse_pos.x - object_pos.x;
        mouse_pos.y = mouse_pos.y - object_pos.y;
        float angle = Mathf.Atan2(mouse_pos.y, mouse_pos.x) * Mathf.Rad2Deg;
        cannon.transform.rotation = Quaternion.Euler(new Vector3(0, 0, angle - 90f));
        cannon.transform.position = transform.position;
    }
}
