using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class freez : MonoBehaviour
{
    public int FreezTime = 3;
    public GameObject target;
    //Rigidbody f_Rigidbody;
    // Start is called before the first frame update
    void Start()
    {
        Invoke("Hoge", FreezTime);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    void Hoge()
    {
        Debug.Log("実行された");
        Transform myTransform = this.transform;
        Vector3 freez_pos = myTransform.position;
        Instantiate(target, freez_pos, Quaternion.identity);
        Destroy(this.gameObject);
        //f_Rigidbody.constraints = RigidbodyConstraints.FreezePosition;
    }
}
