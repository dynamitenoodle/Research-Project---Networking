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

    float lifeTime;
    public float lifeTimeMax = 10f;
    int bounces = 0;
    public int bouncesMax = 3;

    List<GameObject> obstacles;

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

        obstacles = new List<GameObject>();
        foreach(GameObject obstacle in GameObject.FindGameObjectsWithTag("Obstacle"))
        {
            obstacles.Add(obstacle);
        }
        transform.parent = null;
    }

    // Update is called once per frame
    void Update()
    {
        // update the velocity and position, with a check to make sure we should
        velocity = direction * speed * Time.deltaTime;
        position += velocity;
        transform.position = position;
        transform.up = direction;

        if ((transform.position.x > maxX + offset || transform.position.x < minX - offset || transform.position.y > maxY + offset || transform.position.y < minY - offset) || lifeTime > lifeTimeMax || bounces > bouncesMax)
            Destroy(gameObject);

        lifeTime += Time.deltaTime;

        foreach(GameObject obs in obstacles)
        {
            CheckCollisionSide();
        }
    }

    void CheckCollisionSide()
    {
        RaycastHit2D[] myRayHits = Physics2D.RaycastAll(transform.position, direction);

        foreach (RaycastHit2D myRayHit in myRayHits)
        {
            // Make sure it's an obstacle
            if (myRayHit.transform.tag == "Obstacle")
            {
                // Make sure it's THE obstacle
                if (myRayHit.transform.gameObject.GetComponent<BoxCollider2D>().Distance(GetComponent<BoxCollider2D>()).isOverlapped)
                {
                    bounces++;
                    Vector3 rayNormal = myRayHit.transform.TransformDirection(myRayHit.normal);

                    //you hit the top plane
                    if (rayNormal == myRayHit.transform.up)
                    {
                        direction.y = -direction.y;
                    }

                    //you hit the bottom plane
                    if (rayNormal == -myRayHit.transform.up)
                    {
                        direction.y = -direction.y;
                    }

                    // hit right
                    if (rayNormal == myRayHit.transform.right)
                    {
                        direction.x = -direction.x;
                    }

                    //hit left
                    if (rayNormal == -myRayHit.transform.right)
                    {
                        direction.x = -direction.x;
                    }
                }
            }
        }
    }
}
