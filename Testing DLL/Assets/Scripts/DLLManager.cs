using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.IO;
using UnityEngine;

public class DLLManager : MonoBehaviour {

	// Straight From the c++ Dll (unmanaged)
	[DllImport("TestCPPLibrary", EntryPoint = "Connect")]
	public static extern bool Connect(int ip0, int ip1, int ip2, int ip3, int port);

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
        }
        else
        {
            Debug.Log("Connection Failed");
        }
	}

	// Update is called once per frame
	void Update()
	{

	}
}
