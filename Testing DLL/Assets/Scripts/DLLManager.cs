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
	public static extern bool SendPosition(float x, float y);

	public bool sendingSuccess;
	
	// IP and Port variables for inspector
	public List<int> IP;
    public int port = 0;

	// Use this for initialization
	void Start()
	{
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
		if (SendPosition(transform.position.x, transform.position.y))
		{
			sendingSuccess = true;
		}
		else
		{
			sendingSuccess = false;

		}
	}
}
