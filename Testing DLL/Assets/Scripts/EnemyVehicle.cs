using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyVehicle : MonoBehaviour
{
    // attributes
    [HideInInspector] public int playerID;
    [HideInInspector] public Vector3 position;
    [HideInInspector] public float cannonAngle;
	[HideInInspector] public bool firing;
	public GameObject bulletPrefab;
	GameObject cannon;
	bool firedShot;

	void Start()
	{
		cannon = transform.GetChild(0).gameObject;
		cannon.transform.parent = null;
		firedShot = false;
	}

	// Update is called once per frame
	void Update()
    {
		// updates information
        transform.position = position;
		cannon.transform.rotation = Quaternion.Euler(new Vector3(0, 0, cannonAngle));
		cannon.transform.position = transform.position;

		// sees if the enemy should shoot a bullet
		if (firing && !firedShot)
		{
			GameObject tempBullet = Instantiate(bulletPrefab);
			tempBullet.transform.position = cannon.transform.GetChild(0).transform.position;
			tempBullet.GetComponent<Bullet>().direction = Vector3.Normalize(tempBullet.transform.position - cannon.transform.position);
			firedShot = true;
		}
		// resets the bool for firing
		else if (!firing && firedShot)
		{
			firedShot = false;
		}
	}

	// Sets the values of the enemy
	public void SetInformation(DLLManager.PlayerPacket receivedPacket)
	{
		playerID = receivedPacket.id;
		position = new Vector3(receivedPacket.xPos, receivedPacket.yPos, position.z);
		cannonAngle = receivedPacket.cannonAngle;
		firing = receivedPacket.firing;
	}
}
