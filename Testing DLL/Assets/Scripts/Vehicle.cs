using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Vehicle : MonoBehaviour {

	// attributes
	public Vector3 velocity;
	public Vector3 position;
	public Vector3 direction;
	public float speed = 5;
    GameObject background;

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

        // direction calculator
		direction = Vector3.ClampMagnitude(direction, 1);

		if (!Up && !Down || Up && Down)
			direction.y = 0;
		if (!Right && !Left || Right && Left)
			direction.x = 0;

        // update the velocity and position
		velocity = direction * speed * Time.deltaTime;

        // checks to see if we should change the camera position
        if (transform.position.x - GetComponent<BoxCollider2D>().bounds.size.x > minX && transform.position.x + GetComponent<BoxCollider2D>().bounds.size.x < maxX)
            position.x += velocity.x;
        if (transform.position.y - GetComponent<BoxCollider2D>().bounds.size.y > minY && transform.position.y + GetComponent<BoxCollider2D>().bounds.size.y < maxY)
            position.y += velocity.y;

        transform.position = position;

        // only face if a button is being pressed
        if (Up || Down || Right || Left)
            transform.up = direction;
	}
}
