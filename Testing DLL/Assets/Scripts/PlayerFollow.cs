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
    }

    // Update is called once per frame
    void Update()
    {
        playerDirection = player.GetComponent<Vehicle>().direction;
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

        transform.position = new Vector3(xPos, yPos, transform.position.z);
    }
}
