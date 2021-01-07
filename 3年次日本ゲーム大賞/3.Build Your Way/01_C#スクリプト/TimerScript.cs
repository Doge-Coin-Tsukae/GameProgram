using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class TimerScript : MonoBehaviour {

    //　トータル制限時間
    private float totalTime;
    //　制限時間（分）
    [SerializeField]
    private int minute;
    //　制限時間（秒）
    [SerializeField]
    private float seconds;
    //　開始待ち
    [SerializeField]
    private int startwait;
    [SerializeField]
    private Text UnkoText;      //ゲームクリアとゲームオーバーのやつ

    [SerializeField]
    private GameObject UnkoObject;      //コンテニュー
    private int time;

    //　前回Update時の秒数
    private float oldSeconds;
    private Text timerText;

    int wait = 0;

    //BGM
    public AudioClip MainBGM;


    private AudioSource audioSource;

    bool flag;

    void Start()
    {
        totalTime = minute * 60 + seconds;
        oldSeconds = 0f;
        timerText = GetComponentInChildren<Text>();
        time = 0;

        //音楽
        audioSource = gameObject.GetComponent<AudioSource>();

        flag = false;
    }

    void Update()
    {
        //BGM再生
        if (wait >= startwait && flag == false)
        {
            flag = true;
            audioSource.PlayOneShot(MainBGM);
        }

        //時間切れ
        if (totalTime <= 0f)
        {
            float alfa = 1.0f;
            float red = UnkoText.gameObject.GetComponent<Text>().color.r;
            float green = UnkoText.gameObject.GetComponent<Text>().color.g;
            float blue = UnkoText.gameObject.GetComponent<Text>().color.b;

            UnkoText.gameObject.GetComponent<Text>().color = new Color(red, green, blue, alfa);

            Text score_text = UnkoText.GetComponent<Text>();
            score_text.text = "TIME OVER!!!";
            time++;
        }
        if (time >= 300)
        {

            UnkoObject.gameObject.SetActive(true);
        }

        if (wait < startwait)
        {
            wait++;
        }
        else if (wait >= startwait)
        {
            //　制限時間が0秒以下なら何もしない
            if (totalTime <= 0f)
            {
                return;
            }
            //　一旦トータルの制限時間を計測；
            totalTime = minute * 60 + seconds;
            totalTime -= Time.deltaTime;

            //　再設定
            minute = (int)totalTime / 60;
            seconds = totalTime - minute * 60;

            //　タイマー表示用UIテキストに時間を表示する
            if ((int)seconds != (int)oldSeconds)
            {
                timerText.text = minute.ToString("00") + ":" + ((int)seconds).ToString("00");
            }
            oldSeconds = seconds;
            //  時間が0になったらシーン移行
        }
    }
}
