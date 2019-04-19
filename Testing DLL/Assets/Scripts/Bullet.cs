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


    // sets how far the bullet can go
    GameObject background;
    float minX;
    float minY;
    float maxX;
    float maxY;

    float offset = 5f;

    // Start is called before the first frame update
    void Start()
    {
        position = transform.position;
        velocity = Vector3.zero;

        background = GameObject.Find("Background");
        minX = background.GetComponent<Background>().minX;
        minY = background.GetComponent<Background>().minY;
        maxX = background.GetComponent<Background>().maxX;
        maxY = background.GetComponent<Background>().maxY;
    }

    // Update is called once per frame
    void Update()
    {
        // update the velocity and position, with a check to make sure we should
        velocity = direction * speed * Time.deltaTime;
        position += velocity;
        transform.position = position;
        transform.up = direction;

        if (transform.position.x > maxX + offset || transform.position.x < minX - offset || transform.position.y > maxY + offset || transform.position.y < minY - offset)
            Destroy(gameObject);
    }
}
