using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class viewCamera : MonoBehaviour
{
    public GameObject player;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        Vector3 pos;
        pos.x = player.GetComponent<Player>().transform.position.x - 0.0f;
        pos.y = player.GetComponent<Player>().transform.position.y + 5.0f;
        pos.z = player.GetComponent<Player>().transform.position.z - 40.0f;
        transform.position = pos;
    }
}
