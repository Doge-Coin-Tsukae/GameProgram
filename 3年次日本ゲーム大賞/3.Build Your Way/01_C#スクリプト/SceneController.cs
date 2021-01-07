using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class SceneController : MonoBehaviour
{
    bool Botton;           //ボタン押されたか
    bool YesOrNo;       //true=Yes,false=No

    [SerializeField]
    private GameObject Fade;
    // Start is called before the first frame update
    void Start()
    {
        Botton = false;
        YesOrNo = false;
    }

    // Update is called once per frame
    void Update()
    {
        //ボタンが押された時に処理を行う
        if (Botton == true)
        {//フェードが終わったか
            if (Fade.GetComponent<Fade>().GetFadeStart() == false)
            {//押されたボタンで変える
                if (YesOrNo == true)
                {//リトライ(Yes)
                    SceneManager.LoadScene(SceneManager.GetActiveScene().name);
                }
                else
                {//戻る(No)
                    SceneManager.LoadScene("StageSelect");
                }
            }
        }
    }

    //YESボタンが押された
    public void YesButtonClicked()
    {
        Fade.GetComponent<Fade>().SetMode(1);
        YesOrNo = true;
        Botton = true;   
    }

    //NOボタンが押された
    public void NoButtonClicked()
    {
        Fade.GetComponent<Fade>().SetMode(1);
        YesOrNo = false;
        Botton = true;
    }
}
