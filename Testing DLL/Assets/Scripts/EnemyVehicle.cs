using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyVehicle : MonoBehaviour
{
    // attributes
    public int playerID;
    public Vector3 position;

    // Update is called once per frame
    void Update()
    {
        transform.position = position;
    }
}
