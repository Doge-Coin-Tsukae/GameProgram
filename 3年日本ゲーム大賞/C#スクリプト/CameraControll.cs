using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraControll : MonoBehaviour
{
    public subCamera sc;

    private bool viewCameraIsOn;

    private GameObject mainCamera;
    private GameObject subCamera;
    private GameObject viewCamera;
    private GameObject Timer;
    private GameObject Player;

    // Start is called before the first frame update
    void Start()
    {
        //カメラを取得
        mainCamera = GameObject.Find("Camera");
        subCamera = GameObject.Find("subCamera");
        viewCamera = GameObject.Find("viewCamera");

        Timer = GameObject.Find("TimeCount");
        Player = GameObject.Find("ThirdPersonController");

        //初めにサブカメラでステージ全体を見渡すので、メインカメラを止める。
        mainCamera.SetActive(false);
        //プレイヤーと制限時間を一時停止
        Timer.SetActive(false);
        Player.GetComponent<PlayerControll>().enabled = false;


        viewCameraIsOn = false;
        viewCamera.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        //フラグが切り替わったらカメラも変更して、ゲームスタート
        bool subCameraSet;
        subCameraSet = sc.GetsubCameraIsOn();

        //ボタンが押されたらviewCameraを切り替える
        if(Input.GetKeyDown(KeyCode.Y)|| Input.GetKeyDown("joystick button 3"))
        {
            viewCameraIsOn = !viewCameraIsOn;
        }

        //subCameraの処理が終わった後
        if(subCameraSet==false)
        {
            subCamera.SetActive(false);
            mainCamera.SetActive(true);
            //プレイヤーと制限時間を起動
            Timer.SetActive(true);
            Player.GetComponent<PlayerControll>().enabled = true;


            //ボタンが押されたら、ステージを見渡せるカメラに切り替える
            //viewCameraの処理
            if (viewCameraIsOn==true)
            {
                mainCamera.SetActive(false);
                //Timer.SetActive(false);
                Player.GetComponent<PlayerControll>().enabled = false;
                viewCamera.SetActive(true);
            }

            if (viewCameraIsOn==false)
            {
                mainCamera.SetActive(true);
                //Timer.SetActive(true);
                Player.GetComponent<PlayerControll>().enabled = true;
                viewCamera.SetActive(false);
            }



        }




    }
}
