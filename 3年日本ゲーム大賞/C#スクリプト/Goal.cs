using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Goal : MonoBehaviour
{
    private bool Clear;         //ゴールにたどり着いたか
    private bool koolfade;
    private int time;           //待機時間

    [SerializeField]
    private Text UnkoText;      //Clear文字

    [SerializeField]
    private GameObject ItemControll;

    [SerializeField]
    private GameObject Particle;      //パーティクル

    [SerializeField]
    private GameObject Fade;
    // Start is called before the first frame update
    void Start()
    {
        Clear = false;
        koolfade = false;
        time = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if(Clear==true)
        {
            float alfa = 1.0f;
            float red = UnkoText.gameObject.GetComponent<Text>().color.r;
            float green = UnkoText.gameObject.GetComponent<Text>().color.g;
            float blue = UnkoText.gameObject.GetComponent<Text>().color.b;

            UnkoText.gameObject.GetComponent<Text>().color = new Color(red, green, blue, alfa);

            time++;
        }

        if(time >=300)
        {
            //クリアフラグを建てる(力技)
            if(SceneManager.GetActiveScene().name == "Stage 1")
            {   //ステージ1
                PlayerPrefs.SetInt("Cleard" + 0, 1);
            }
            if (SceneManager.GetActiveScene().name == "Stage 2")
            {   //ステージ2
                PlayerPrefs.SetInt("Cleard" + 1, 1);
            }
            if (SceneManager.GetActiveScene().name == "Stage 3")
            {   //ステージ3
                PlayerPrefs.SetInt("Cleard" + 2, 1);
            }
            if (SceneManager.GetActiveScene().name == "Stage 4")
            {   //ステージ4
                PlayerPrefs.SetInt("Cleard" + 3, 1);
            }
            if (SceneManager.GetActiveScene().name == "Stage 5")
            {   //ステージ5
                PlayerPrefs.SetInt("Cleard" + 4, 1);
            }

            if (koolfade == false)
            {
                Fade.GetComponent<Fade>().SetMode(1);
                koolfade = true;
            }
            if (Fade.GetComponent<Fade>().GetFadeStart() == false)
            {
                SceneManager.LoadScene("StageSelect");
            }
        }
    }
    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name == "ThirdPersonController")
        {
            if(Clear == false)
            {
                Instantiate(Particle,new Vector3(transform.position.x + 5, transform.position.y + 1, transform.position.z + 5), new Quaternion(0, 0, 0, 0)); //パーティクル用ゲームオブジェクト生成
                Instantiate(Particle, new Vector3(transform.position.x + 5, transform.position.y + 1, transform.position.z - 5), new Quaternion(0, 0, 0, 0)); //パーティクル用ゲームオブジェクト生成
                Instantiate(Particle, new Vector3(transform.position.x - 5, transform.position.y + 1, transform.position.z + 5), new Quaternion(0, 0, 0, 0)); //パーティクル用ゲームオブジェクト生成
                Instantiate(Particle, new Vector3(transform.position.x - 5, transform.position.y + 1, transform.position.z - 5), new Quaternion(0, 0, 0, 0)); //パーティクル用ゲームオブジェクト生成
            }
            Clear = true;
        }
    }

    public bool GetClear()
    {
        return Clear;
    }
}