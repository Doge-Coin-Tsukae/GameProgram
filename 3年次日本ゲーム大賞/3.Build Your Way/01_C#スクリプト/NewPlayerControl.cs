using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NewPlayerControll : MonoBehaviour
{

    //基本操作関連
    float jump;      //ジャンプの強さ
    private Vector3 speed;
    private bool jumpflag;
    public Rigidbody rb;


    //発射機能関連

    public GameObject inc;
    public GameObject ol;

    // bullet prefab
    public GameObject concrete;
    public GameObject concrete2;
    public GameObject water;
    public GameObject water2;

    // 弾丸発射点
    public Transform muzzle, muzzle2;

    // 弾丸の速度
    public float concrete_speed = 1000;

    private int count = 0;

    private Vector3 moveDirection;


    // Start is called before the first frame update
    void Start()
    {
        //ジャンプ関連関数の初期化
        rb = GetComponent<Rigidbody>();
        jumpflag = false;
    }

    // Update is called once per frame
    void Update()
    {
        //ジャンプ関連変数宣言
        Transform transform = this.transform;
        Vector3 Pos = transform.position;
        Vector3 Rot = this.gameObject.transform.localEulerAngles;
        speed = rb.velocity;

        //移動
        if (Input.GetKey(KeyCode.A))
        {
            Rot.y = -90;
            Pos.x -= 0.05f;
        }

        if (Input.GetKey(KeyCode.D))
        {
            Rot.y = 90;
            Pos.x += 0.05f;
        }

        //ジャンプ処理
        if (Input.GetKeyDown(KeyCode.Space))
        {
            if (jumpflag == false)
            {
                rb.AddForce(0, 400, 0);
                jumpflag = true;
            }
        }
        transform.position = Pos;
        transform.eulerAngles = Rot;


        count++;
        //スペースを押したら
        if (Input.GetKeyDown(KeyCode.Z) && (inc.GetComponent<ItemNumController>().GetMode() == 1) && (ol.GetComponent<overlap>().IsNotOverlap() == true))
        {

            count = 0;
            // 弾丸の複製
            GameObject concretes = Instantiate(concrete) as GameObject;

            Vector3 force;

            force = this.gameObject.transform.forward * concrete_speed;

            // Rigidbodyに力を加えて発射
            concretes.GetComponent<Rigidbody>().AddForce(force);

            // 弾丸の位置を調整
            concretes.transform.position = muzzle.position;

        }

        //スペースを押したら
        if (Input.GetKeyDown(KeyCode.Z) && inc.GetComponent<ItemNumController>().GetMode() == 2)
        {

            count = 0;
            // 弾丸の複製
            GameObject concrete2s = Instantiate(concrete2) as GameObject;

            Vector3 force;

            force = this.gameObject.transform.forward * concrete_speed;

            // Rigidbodyに力を加えて発射
            //concrete2s.GetComponent<Rigidbody>().AddForce(force);

            // 弾丸の位置を調整
            concrete2s.transform.position = muzzle2.position;

        }

        //スペースを押したら
        //if (Input.GetKeyDown(KeyCode.Z) && (inc.GetComponent<ItemNumController>().GetMode() == 1 || inc.GetComponent<ItemNumController>().GetMode() == 2))
        //{

        //    count = 0;
        //    // 弾丸の複製
        //    GameObject waters = Instantiate(water) as GameObject;

        //    Vector3 force;

        //    force = this.gameObject.transform.right * concrete_speed;

        //    // Rigidbodyに力を加えて発射
        //    //waters.GetComponent<Rigidbody>().AddForce(force);

        //    // 弾丸の位置を調整
        //    waters.transform.position = muzzle.position;


        //}
        //if (Input.GetKeyDown(KeyCode.Z) && (inc.GetComponent<ItemNumController>().GetMode() == 1 || inc.GetComponent<ItemNumController>().GetMode() == 2))
        //{

        //    count = 0;
        //    // 弾丸の複製
        //    GameObject water2s = Instantiate(water2) as GameObject;

        //    Vector3 force;

        //    force = this.gameObject.transform.right * concrete_speed;

        //    // Rigidbodyに力を加えて発射
        //    water2s.GetComponent<Rigidbody>().AddForce(force);

        //    // 弾丸の位置を調整
        //    water2s.transform.position = muzzle.position;


        //}
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (speed.y <= 1.0f)
        {
            jumpflag = false;
        }
    }
}