# Research-Project---Networking
"OLD VERSION OF README"
We'll be creating a generic UDP Server to Client connection that will be able to interface with a DLL that can then be added to any project and allow use of the networking structure we create.

Step 1: Setup Server to Client Connection
    -Ensure that we can have structs sent between client and server
Step 2: Create a framework in which generic packets can be saved and stored in select memory allocations
    -Create a system in which you are able to save certain variable types as other variable types and your able to read and write with them
    -Server has no idea of what information it's told from the client
    -Developer Client is able to send a command id that's randomized and is connected to a certain payload
    -Server saves the payload to an external txt or otherwise, able to call upon that information when Player Client sends information
    -Client creates random ID with a payload that's been predefined
Step 3: Ensure that multiple client connections work with framework
Step 4: Create a DLL that is able to use client's commands to interface with the server instance
Step 5: Create a DLL that is able to use servers's commands to interface with the client instances
Step 6: Create a project that can utilize the DLL


https://stackoverflow.com/questions/32991274/return-string-from-c-dll-export-function-called-from-c-sharp
