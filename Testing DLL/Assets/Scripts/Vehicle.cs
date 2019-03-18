using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Vehicle : MonoBehaviour {

	// attributes
	public Vector3 velocity;
	public Vector3 position;
	public Vector3 direction;
	public float speed = 5;

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
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (Up)
			direction.y += 1;
		if (Down)
			direction.y -= 1;
		if (Right)
			direction.x += 1;
		if (Left)
			direction.x -= 1;

		direction = Vector3.ClampMagnitude(direction, 1);

		if (!Up && !Down || Up && Down)
			direction.y = 0;
		if (!Right && !Left || Right && Left)
			direction.x = 0;

		velocity = direction * speed * Time.deltaTime;
		position += velocity;

		transform.position = position;
	}
}
