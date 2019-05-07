using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.IO;
using UnityEngine;
using UnityEngine.Diagnostics;
using System;

public class DLLManager : MonoBehaviour {

	// Straight From the c++ Dll (unmanaged)
	[DllImport("TestCPPLibrary", EntryPoint = "Connect")]
	public static extern bool Connect(int ip0, int ip1, int ip2, int ip3, int port);
	[DllImport("TestCPPLibrary", EntryPoint = "ReceiveInformation")]
	public static extern bool ReceiveInformation();
	[DllImport("TestCPPLibrary", EntryPoint = "SendPosition")]
	public static extern bool SendPosition(IntPtr num);

	public bool sendingSuccess;

    GameObject player;
    [HideInInspector] public int id;
	
	// IP and Port variables for inspector
	public List<int> IP;
    public int port = 0;

    // struct for sending stuff
    [HideInInspector] public struct PlayerPacket
    {
        public int id;
        public float xPos;
        public float yPos;
        public float cannonAngle;
        public bool firing;
    }

	// Use this for initialization
	void Start()
	{
        player = GameObject.Find("Player");

		// Testing the connection
		if(Connect(IP[0], IP[1], IP[2], IP[3], port))
        {
            //Debug.Log("Connection Successful");

			// attempt to start the receiving thread
			if (ReceiveInformation())
			{
				//Debug.Log("Receive thread successfully started");
			}
			else
			{
				Debug.Log("Receive thread : failure on start");
			}
        }
        else
        {
            Debug.Log("Connection Failed");
        }
	}

	// Update is called once per frame
	void Update()
	{
        // Create the struct packet
        PlayerPacket pack = new PlayerPacket();
        pack.xPos = player.transform.position.x;
        pack.yPos = player.transform.position.y;
        pack.cannonAngle = player.GetComponent<Player>().cannonAngle;
        pack.firing = player.GetComponent<Player>().firing;
        if (pack.firing)
            player.GetComponent<Player>().firing = false;

        // get the size of the struct
        int size = Marshal.SizeOf(pack);

        //initialize a pointer with the apropriate size
        IntPtr ptr = Marshal.AllocHGlobal(size);
        Marshal.StructureToPtr(pack, ptr, true);

        // send the pointer
        if (SendPosition(ptr))
        {
			sendingSuccess = true;
		}
		else
		{
			sendingSuccess = false;
		}

        //free the pointer
        Marshal.FreeHGlobal(ptr);
    }
}
