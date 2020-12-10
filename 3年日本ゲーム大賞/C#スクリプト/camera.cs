using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class camera : MonoBehaviour
{
    public GameObject GC_Player;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 pos;
        pos.x = GC_Player.GetComponent<Player>().transform.position.x - 0.0f;
        pos.y = GC_Player.GetComponent<Player>().transform.position.y + 2.0f;
        pos.z = GC_Player.GetComponent<Player>().transform.position.z - 13.0f;
        transform.position = pos;
    }
}
