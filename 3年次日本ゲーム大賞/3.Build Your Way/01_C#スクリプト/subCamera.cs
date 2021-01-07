using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class subCamera : MonoBehaviour
{
    //メインカメラとサブカメラを切り替えるフラグ
    public bool subCameraIsOn;
    //カメラを往復させるためのフラグ
    private bool CameraTurn;

    //プレイヤー位置座標格納用
    Vector3 pos;
    //ゴール座標格納用
    Vector3 goal_pos;

    public float speed = 25.0f;
    private float startTime;
    private float journeyLength;

    // Start is called before the first frame update
    void Start()
    {
        //trueの時サブカメラを起動、falseの時メインカメラを起動
        subCameraIsOn = true;

        CameraTurn = false;

        //プレイヤーの初期位置をカメラの始点とする
        pos.x = GameObject.Find("ThirdPersonController").transform.position.x;
        pos.y = GameObject.Find("ThirdPersonController").transform.position.y + 2.0f;
        pos.z = GameObject.Find("ThirdPersonController").transform.position.z - 25.0f;
        this.transform.position = pos;

        //ゴールの座標をカメラの終点とする。

        goal_pos.x = GameObject.Find("Goal").transform.position.x;
        goal_pos.y = GameObject.Find("Goal").transform.position.y + 2.0f;
        goal_pos.z = GameObject.Find("Goal").transform.position.z - 25.0f;


        startTime = Time.time;
        //距離を代入
        journeyLength = Vector3.Distance(pos, goal_pos);
    }

    // Update is called once per frame
    void Update()
    {

        //0～1の割合を求める
        float distCoverd = (Time.time - startTime) * speed;
        float fracJourney = distCoverd / journeyLength;



        if (CameraTurn == true)
        {
            //goal_posからposまでの距離を補間し、それをカメラの位置座標とする(Uターン)
            transform.position = Vector3.Lerp(goal_pos, pos, fracJourney);

            if (transform.position == pos)
                subCameraIsOn = false;
        }

        if (CameraTurn == false)
        {
            //posからgoal_posまでの距離を補間し、それをカメラの位置座標とする。
            transform.position = Vector3.Lerp(pos, goal_pos, fracJourney);

            if (transform.position == goal_pos)
            {
                CameraTurn = true;
                //スタートタイムをリセット
                startTime = Time.time;
            }

        }





    }

    public bool GetsubCameraIsOn()
    {
        return subCameraIsOn;
    }


}
