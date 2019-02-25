using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.IO;
using UnityEngine;

public class TestScript : MonoBehaviour {

	// Straight From the c++ Dll (unmanaged)

	[DllImport("TestCPPLibrary", EntryPoint = "TestDivide")]
	public static extern float TestDivide(float a, float b);

    [DllImport("TestCPPLibrary", EntryPoint = "TestMultiply")]
    public static extern float TestMultiply(float a, float b);


    [DllImport("TestCPPLibrary", EntryPoint = "TestString")]
    public static extern string TestString();

    // Use this for initialization
    void Start()
    {
        float divideResult = TestDivide(25, 5);
        float multiplyResult = TestMultiply(10, 5);

		// Print it out to the console
		Debug.Log(divideResult);
		Debug.Log(multiplyResult);
        Debug.Log(TestString());

        // Write the result into a file, so we can even see it working in a build
        using (StreamWriter writer = new StreamWriter("debug.txt", true))
        {
            writer.WriteLine(divideResult);
            writer.WriteLine(multiplyResult);
        }
	}

    // Update is called once per frame
    void Update()
    {

    }
}
