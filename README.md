# Research-Project---Networking
To run the server, open the solution and run (Server is named Network Manager)
    Then enter your IP (open cmd, run ipconfig, then use the IPv4 code) (IP for local build to work is 127 0 0 1, with port 45000)
    Ex.
    Ethernet adapter Ethernet 3:

   Connection-specific DNS Suffix  . : igm.rit.edu.
   Link-local IPv6 Address . . . . . : fe80::ed81:7b11:e8d7:cc3a%20
   ****IPv4 Address. . . . . . . . . . . : 129.21.23.36****
   Subnet Mask . . . . . . . . . . . : 255.255.255.0
   Default Gateway . . . . . . . . . : 129.21.23.254

    D:\Profiles\crg5646>

    Then enter a port (Pick between 10000-50000 for safety)
        Also ensure the port is open if your firewall is blocking it (create rules for the port inbound and outbound)
    
    The server will now be running

To run the client, either run the build for local (if the IP you choose was 127.0.0.1 with port 45000)
    or Open Unity, click on the Network Manager in the hierarchy and change the IP and Port there.
    Then simply run the Unity game, and if all is well it should run.

On the serverside, it should be printing "Sending pos" repeatedly, meaning it is both receiving and returning the packets being sent it.
If you would like to see the Debug, check out the "Receive_Debug.txt" and "DLL_Debug.txt" in the top of the Unity file structure.
