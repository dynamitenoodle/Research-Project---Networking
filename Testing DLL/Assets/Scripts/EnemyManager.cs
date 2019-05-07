using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.IO;
using UnityEngine;
using UnityEngine.Diagnostics;
using System;
using System.Threading;

public class EnemyManager : MonoBehaviour
{
	// Method to receive the enemy information
	[DllImport("TestCPPLibrary", EntryPoint = "PacketCheck")]
	public static extern bool PacketCheck();
	[DllImport("TestCPPLibrary", EntryPoint = "PacketGet")]
	public static extern IntPtr PacketGet();

	// Enemies
	List<GameObject> enemies;
    public GameObject enemyPref;
	DLLManager.PlayerPacket receivedPacket;

	DLLManager dllManager;
	Player player;

	// Start is called before the first frame update
	void Start()
    {
        dllManager = GameObject.Find("Network Manager").GetComponent<DLLManager>();
		player = GameObject.Find("Player").GetComponent<Player>();
    }

    // Update is called once per frame
    void Update()
    {
		// Check to see if theres a new packet
        while(PacketCheck())
		{
			// get the size of the struct
			IntPtr receivedPtr = PacketGet(); // Pops the packet off the queue of them
			Marshal.PtrToStructure(receivedPtr, receivedPacket);

			Debug.Log("ID Received : " + receivedPacket.id);

			// ensure that it's not our id
			if (receivedPacket.id != dllManager.id)
			{
				// Check to see if we should update an enemy
				bool newEnemy = true;
				foreach (GameObject enemy in enemies)
				{
					if (enemy.GetComponent<EnemyVehicle>().playerID == receivedPacket.id)
					{
						newEnemy = false;
						enemy.GetComponent<EnemyVehicle>().SetInformation(receivedPacket);
					}
				}

				// if we have a new enemy to generate
				if (newEnemy)
				{
					GameObject enemy = Instantiate(enemyPref);
					enemy.GetComponent<EnemyVehicle>().SetInformation(receivedPacket);
					enemies.Add(enemy);
				}
			}

			//free the pointer
			Marshal.FreeHGlobal(receivedPtr);
		}
    }
}
