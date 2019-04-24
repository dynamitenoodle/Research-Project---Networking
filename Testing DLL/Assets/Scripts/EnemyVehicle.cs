using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyVehicle : MonoBehaviour
{
    // attributes
    public int playerID;
    public Vector3 position;
    public float cannonAngle;
    public bool firing;

    // Update is called once per frame
    void Update()
    {
        transform.position = position;
    }
}
