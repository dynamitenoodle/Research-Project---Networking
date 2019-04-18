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
	}
}
