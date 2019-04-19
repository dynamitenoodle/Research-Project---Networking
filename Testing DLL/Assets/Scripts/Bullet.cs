using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{
    // attributes
    public float speed;
    Vector3 velocity;
    Vector3 position;
    [HideInInspector] public Vector3 direction;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // update the velocity and position, with a check to make sure we should
        velocity = direction * speed * Time.deltaTime;
        position += velocity;
        transform.position = position;
        transform.up = direction;

        if (transform.position.x > 25 || transform.position.x < -25 || transform.position.y > 25 || transform.position.y < -25)
            Destroy(gameObject);
    }
}
