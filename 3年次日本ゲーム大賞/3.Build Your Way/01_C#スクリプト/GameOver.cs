using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class GameOver : MonoBehaviour
{
    private bool Over;          //死んだかどうか
    private int time;           //待機時間

    [SerializeField]
    private Text UnkoText;      //ゲームクリアとゲームオーバーのやつ

    [SerializeField]
    private GameObject UnkoObject;      //コンテニュー

    [SerializeField]
    private GameObject Particle;      //コンテニュー

    // Start is called before the first frame update
    void Start()
    {
        time = 0;
        Over = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (Over == true)
        {
            float alfa = 1.0f;
            float red = UnkoText.gameObject.GetComponent<Text>().color.r;
            float green = UnkoText.gameObject.GetComponent<Text>().color.g;
            float blue = UnkoText.gameObject.GetComponent<Text>().color.b;

            UnkoText.gameObject.GetComponent<Text>().color = new Color(red, green, blue, alfa);

            Text score_text = UnkoText.GetComponent<Text>();
            score_text.text = "YOU DIED!!!";

            time++;
        }
        if (time >= 300)
        {

            UnkoObject.gameObject.SetActive(true);
        }
    }
    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name == "ThirdPersonController")
        {
            Over = true;
        }
        Instantiate(Particle, collision.transform.position, new Quaternion(0,0,0,0)); //パーティクル用ゲームオブジェクト生成
        Destroy(collision.gameObject);
    }
}
