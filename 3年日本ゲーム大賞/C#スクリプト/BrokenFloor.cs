using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BrokenFloor : MonoBehaviour
{

    public float  second;
    int count;


    void Start()
    {
        count = 0;
    }

    void Update()
    {
        
    }

    void OnCollisionEnter(Collision other)
    {
        if (other.gameObject.tag == "Player" || other.gameObject.tag == "concrete")
        {
            StartCoroutine("DestroyTime");
        }
    }

    void OnTriggerExit(Collider other)
    {//Playerの当たり判定が離れた時に”Rotate”をストップ
        if (other.gameObject.tag == "Player")
        {
            StopCoroutine("DestroyTime");
        }
    }


    IEnumerator DestroyTime()
    {
        yield return new WaitForSeconds(second);
        Destroy(this.gameObject);
    }
}
