using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player_MoveBlock : MonoBehaviour
{
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    void OnCollisionEnter(Collision col)
    {
        if (col.gameObject.tag == "MoveBlock")
        {
            transform.SetParent(col.transform);
        }
    }

    void OnCollisionExit(Collision col)
    {
        if (col.gameObject.tag == "MoveBlock")
        {
            transform.SetParent(null);
        }
    }
}
