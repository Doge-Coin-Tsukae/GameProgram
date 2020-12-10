using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rift : MonoBehaviour
{

    public float Rotato;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.Rotate(new Vector3(0, 0, Rotato));
    }

    void OnCollisionEnter(Collision collision)
    {
        collision.gameObject.transform.parent = this.gameObject.transform;
    }

    private void OnCollisionStay(Collision collision)
    {
        Vector3 Rot = collision.gameObject.transform.localEulerAngles;
        Rot.x = 0;
        Rot.z = 0;
        collision.transform.eulerAngles = Rot;

        
    }

    void OnCollisionExit(Collision collision)
    {
        Vector3 Rot = collision.gameObject.transform.localEulerAngles;
        Rot.x = 0;
        Rot.z = 0;
        collision.transform.eulerAngles = Rot;
        collision.transform.parent = null;
    }
}
