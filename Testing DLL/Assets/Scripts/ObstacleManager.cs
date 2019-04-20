using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObstacleManager : MonoBehaviour
{
    Background background;
    public GameObject obstaclePref;
    List<GameObject> obstacles;

    // The bounds
    float minX;
    float minY;
    float maxX;
    float maxY;

    float offset = 1.5f;

    // Start is called before the first frame update
    void Start()
    {
        // Sets the background information
        background = GameObject.Find("Background").GetComponent<Background>();
        minX = background.minX;
        minY = background.minY;
        maxX = background.maxX;
        maxY = background.maxY;

        obstacles = new List<GameObject>();

        #region Outside Wall Generation
        // Generate walls
        for (int i = 0; i < 4; i++)
            obstacles.Add(Instantiate(obstaclePref));

        // Top Wall
        obstacles[0].transform.position = new Vector3(0, maxY + offset);
        obstacles[0].transform.localScale = new Vector3(Mathf.Abs(minX) + Mathf.Abs(maxX) + (offset * 4), 1, 1);

        // Bottom Wall
        obstacles[1].transform.position = new Vector3(0, minY - offset);
        obstacles[1].transform.localScale = new Vector3(Mathf.Abs(minX) + Mathf.Abs(maxX) + (offset * 4), 1, 1);

        // Right Wall
        obstacles[2].transform.position = new Vector3(maxX + offset, 0);
        obstacles[2].transform.localScale = new Vector3(1, Mathf.Abs(minY) + Mathf.Abs(maxY) + (offset * 4), 1);

        // Left Wall
        obstacles[3].transform.position = new Vector3(minX - offset, 0);
        obstacles[3].transform.localScale = new Vector3(1, Mathf.Abs(minY) + Mathf.Abs(maxY) + (offset * 4), 1);
        #endregion

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
