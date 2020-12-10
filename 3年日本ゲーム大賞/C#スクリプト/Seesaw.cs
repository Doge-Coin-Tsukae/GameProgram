using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Seesaw : MonoBehaviour
{

    public float leftRotate = 20.0f;
    public float rightRotate = 340.0f;
    float tmpRotate_z;

    Quaternion quaternion;

    // Start is called before the first frame update
    void Start()
    {
        //シーソーの傾き具合
        //leftRotate = 30.0f;
        //rightRotate = 330.0f;

        //tmpRotate = this.transform.rotation.z;

        quaternion = this.transform.rotation;
        tmpRotate_z = quaternion.eulerAngles.z;

        Debug.Log(tmpRotate_z);
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log(tmpRotate_z);
        quaternion = this.transform.rotation;
        tmpRotate_z = quaternion.eulerAngles.z;

        //指定した角度を超えたら範囲指定の角度に戻す。左側は20度
        if (tmpRotate_z > leftRotate && tmpRotate_z < leftRotate + 70.0f) 
        {
            Debug.Log("1");
            this.transform.rotation = Quaternion.Euler(0.0f, 0.0f, leftRotate);
        }

        //指定した角度を超えたら範囲指定の角度に戻す。右側は340度(-20度)
        if (tmpRotate_z < rightRotate && tmpRotate_z > rightRotate - 70.0f) 
        {
            this.transform.rotation = Quaternion.Euler(0.0f, 0.0f, rightRotate);
        }
    }
}
