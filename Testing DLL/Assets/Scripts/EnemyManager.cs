using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.IO;
using UnityEngine;
using UnityEngine.Diagnostics;
using System;

public class EnemyManager : MonoBehaviour
{
    // Method to receive the enemy information
    [DllImport("TestCPPLibrary", EntryPoint = "EnemyPositionCheck")]
    public static extern bool EnemyPositionCheck(IntPtr enemyStruct);

    List<GameObject> enemies;
    GameObject enemyPref;
    DLLManager dllManager;

    // Start is called before the first frame update
    void Start()
    {
        dllManager = GameObject.Find("Network Manager").GetComponent<DLLManager>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
