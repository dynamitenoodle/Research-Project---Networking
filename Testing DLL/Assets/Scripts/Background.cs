using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Background : MonoBehaviour
{
    // attributes
    public GameObject block;
    List<GameObject> backgroundBlocks;
    Sprite blockSprite;
    float sizeX;
    float sizeY;

    // sets how far the blocks will go
    public float minX;
    public float minY;
    public float maxX;
    public float maxY;

    // Start is called before the first frame update
    void Start()
    {
        backgroundBlocks = new List<GameObject>();
        blockSprite = block.GetComponent<SpriteRenderer>().sprite;
        sizeX = blockSprite.bounds.size.x;
        sizeY = blockSprite.bounds.size.y;
        Debug.Log(sizeX);

        GenerateBackgroundBlocks();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    // Generates the background of the stage
    void GenerateBackgroundBlocks()
    {
        for (float x = minX; x <= maxX; x++)
        {
            for (float y = minY; y <= maxY; y++)
            {
                GameObject tempBlock = Instantiate(block);
                tempBlock.transform.parent = gameObject.transform;
                tempBlock.transform.position = new Vector3(x /*- (sizeX / 2)*/, y /*- (sizeY / 2)*/, 0);
                backgroundBlocks.Add(tempBlock);
            }
        }
    }
}
