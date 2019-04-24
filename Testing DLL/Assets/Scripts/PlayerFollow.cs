using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerFollow : MonoBehaviour
{
    // attributes
    Camera cam;
    GameObject player;
    Vector3 playerDirection;
    GameObject background;

    // The extents
    float cameraXExtent;
    float cameraYExtent;

    // sets how camera can go, from background
    float minX;
    float minY;
    float maxX;
    float maxY;

    public float maxCameraSpeed = 0.5f;
    public float chaseDistance = 1f;
    Vector3 direction;
    Vector3 velocity;

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player");
        background = GameObject.Find("Background");
        minX = background.GetComponent<Background>().minX;
        minY = background.GetComponent<Background>().minY;
        maxX = background.GetComponent<Background>().maxX;
        maxY = background.GetComponent<Background>().maxY;

        cam = GetComponent<Camera>();
        float height = 2f * cam.orthographicSize;
        float width = height * cam.aspect;
        cameraXExtent = width / 2;
        cameraYExtent = height / 2;

        direction = Vector3.zero;
        velocity = Vector3.zero;
    }

    // Update is called once per frame
    void Update()
    {
        playerDirection = player.GetComponent<Player>().direction;
        float xPos = player.transform.position.x;
        float yPos = player.transform.position.y;

        // checks to see if we should change the camera position
        if (xPos < minX + cameraXExtent)
            xPos = minX + cameraXExtent;
        if (xPos > maxX - cameraXExtent)
            xPos = maxX - cameraXExtent;

        if (yPos < minY + cameraYExtent)
            yPos = minY + cameraYExtent;
        if (yPos > maxY - cameraYExtent)
            yPos = maxY - cameraYExtent;

        // gets the position that the camera wants to chase
        Vector3 wantedPosition = new Vector3(xPos, yPos, transform.position.z);
        // x = r * Math.cos(a+b), y = r * Math.sin(a+b)
        Vector3 dirVector = new Vector3(-Mathf.Sin(Mathf.Deg2Rad * player.GetComponent<Player>().cannonAngle), Mathf.Cos(Mathf.Deg2Rad * player.GetComponent<Player>().cannonAngle), 0);
        Debug.Log("Angle: " + player.GetComponent<Player>().cannonAngle);
        Debug.Log("Direction: " + dirVector);
        wantedPosition += (dirVector * 3f);

        // Quick seeking
        if (Vector2.Distance(transform.position, wantedPosition) > chaseDistance)
        {
            // does the magic to make it flow nicely
            direction = (wantedPosition - transform.position).normalized;
            velocity += direction * maxCameraSpeed * Time.deltaTime;
            velocity = Vector3.ClampMagnitude(velocity, maxCameraSpeed);
            
            transform.position += velocity;
        }
        else
        {
            velocity *= .95f;
            transform.position += velocity;
        }
    }
}
