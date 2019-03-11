using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.IO;
using UnityEngine;

public class DLLManager : MonoBehaviour {

	// Straight From the c++ Dll (unmanaged)

	[DllImport("TestCPPLibrary", EntryPoint = "TestDivide")]
	public static extern float TestDivide(float a, float b);

	[DllImport("TestCPPLibrary", EntryPoint = "TestMultiply")]
	public static extern float TestMultiply(float a, float b);

	[DllImport("TestCPPLibrary", EntryPoint = "Connect")]
	public static extern bool Connect(int ip0, int ip1, int ip2, int ip3, int port);

	// Use this for initialization
	void Start()
	{
		float divideResult = TestDivide(25, 5);
		float multiplyResult = TestMultiply(10, 5);

		// Print it out to the console
		Debug.Log(divideResult);
		Debug.Log(multiplyResult);

		// Write the result into a file, so we can even see it working in a build
		using (StreamWriter writer = new StreamWriter("debugNumbers.txt", true))
		{
			writer.WriteLine(divideResult);
			writer.WriteLine(multiplyResult);
		}

		// Testing the connection
		if(Connect(127, 0, 0, 1, 45000))
        {
            using (StreamWriter writer = new StreamWriter("debugNumbers.txt", true))
            {
                writer.WriteLine("Success");
            }
            Debug.Log("Connection Successful");
        }
        else
        {
            using (StreamWriter writer = new StreamWriter("debugNumbers.txt", true))
            {
                writer.WriteLine("Failed");
            }
            Debug.Log("Connection Failed");
        }
	}

	// Update is called once per frame
	void Update()
	{

	}
}
