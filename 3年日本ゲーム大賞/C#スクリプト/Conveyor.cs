using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Conveyor : MonoBehaviour
{

    //ベルトコンベアが動いているか
    public bool IsOn = false;

    //ベルトコンベアの速度
    public float DriveSpeed = 3.0f;

    //現在のベルトコンベアの速度
    public float CurrentSpeed { get { return currentspeed; } }

    //ベルトコンベアの進行方向
    public Vector3 DriveDirection = Vector3.forward;

    //ベルトコンベアが押す力（加速力）
    [SerializeField] private float forcePower = 50f;

    
    private float currentspeed = 0.0f;
    private List<Rigidbody> rigidbodies = new List<Rigidbody>();


    // Start is called before the first frame update
    void Start()
    {
        //方向の正規化
        DriveDirection = DriveDirection.normalized;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        //IsOnがtrueならDriveSpeedを返す。falseなら0を返す。
        currentspeed = IsOn ? DriveSpeed : 0;

        //消滅したオブジェクトは除去する
        rigidbodies.RemoveAll(r => r == null);

        foreach(var r in rigidbodies)
        {
            //物体の移動速度のベルトコンベア方向の成分だけを取り出す。
            var objectspeed = Vector3.Dot(r.velocity, DriveDirection);

            //目標値以下なら加速する。
            if(objectspeed<Mathf.Abs(DriveSpeed))
            {
                r.AddForce(DriveDirection * forcePower, ForceMode.Acceleration);
            }
        }
    }

    //オブジェクトがベルトコンベアに触れたとき
    void OnCollisionEnter(Collision collision)
    {
        var rigidBody = collision.gameObject.GetComponent<Rigidbody>();

        //コンクリートが触れたとき、X軸の固定のみ外す。
        if (collision.gameObject.name == "ConcreteBlock(Clone)" || collision.gameObject.name == "Ladder(Clone)")
        {
            rigidBody.constraints = RigidbodyConstraints.None;

            rigidBody.constraints = RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;

            
        }


        rigidbodies.Add(rigidBody);
        
        
    }

    //オブジェクトがベルトコンベアから離れたとき 
    void OnCollisionExit(Collision collision)
    {
        var rigidBody = collision.gameObject.GetComponent<Rigidbody>();

        //コンクリートなら離れるとき、X座標の制限を戻す
        if (collision.gameObject.name == "ConcreteBlock(Clone)" || collision.gameObject.name == "Ladder(Clone)")
        {
            rigidBody.constraints = RigidbodyConstraints.FreezePositionX | RigidbodyConstraints.FreezePositionZ | RigidbodyConstraints.FreezeRotation;
        }
        rigidbodies.Remove(rigidBody);

    }



}
