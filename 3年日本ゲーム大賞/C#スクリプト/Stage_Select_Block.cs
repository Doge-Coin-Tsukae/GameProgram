using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stage_Select_Block : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 Rot;
        Rot = this.gameObject.transform.localEulerAngles;
        Rot.y += 0.1f;
        this.gameObject.transform.localEulerAngles = Rot;
    }
}
