using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.IO;
using UnityEngine;

public class DLLManager : MonoBehaviour {

	// Straight From the c++ Dll (unmanaged)
	[DllImport("TestCPPLibrary", EntryPoint = "Connect")]
	public static extern bool Connect(int ip0, int ip1, int ip2, int ip3, int port);
	[DllImport("TestCPPLibrary", EntryPoint = "ReceiveInformation")]
	public static extern bool ReceiveInformation();
	[DllImport("TestCPPLibrary", EntryPoint = "SendPosition")]
	public static extern bool SendPosition(int x1, int x2, int y1, int y2);

	public bool sendingSuccess;

    GameObject player;
	
	// IP and Port variables for inspector
	public List<int> IP;
    public int port = 0;

	// Use this for initialization
	void Start()
	{
        player = GameObject.Find("Player");

		// Testing the connection
		if(Connect(IP[0], IP[1], IP[2], IP[3], port))
        {
            Debug.Log("Connection Successful");

			// attempt to start the receiving thread
			if (ReceiveInformation())
			{
				Debug.Log("Receive thread successfully started");
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
        // Create the X variables
        int x1 = (int)player.transform.position.x;
        float xDecimal = Mathf.Repeat(player.transform.position.x, 1.0f) * 1000;
        int x2 = (int)xDecimal;
        //Debug.Log("X2: " + x2);

        // Create the Y variables
        int y1 = (int)player.transform.position.y;
        float yDecimal = Mathf.Repeat(player.transform.position.y, 1.0f) * 1000;
        int y2 = (int)yDecimal;
        //Debug.Log("Y2: " + y2);

        if (SendPosition(x1, x2, y1, y2))
        {
			sendingSuccess = true;
		}
		else
		{
			sendingSuccess = false;
		}
	}
}
