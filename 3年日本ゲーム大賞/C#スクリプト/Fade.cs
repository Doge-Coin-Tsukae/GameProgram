using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Fade : MonoBehaviour
{
    public float speed = 0.01f;  //透明化の速さ
    float alfa;    //A値を操作するための変数
    float red, green, blue;    //RGBを操作するための変数
    bool FadeStart;
    int Mode;

    void Start()
    {
        //Panelの色を取得
        red = GetComponent<Image>().color.r;
        green = GetComponent<Image>().color.g;
        blue = GetComponent<Image>().color.b;
        alfa = GetComponent<Image>().color.a;
        //FadeStart = false;
        //Mode = 0;
    }
    // Update is called once per frame
    void Update()
    {
        if (FadeStart == true)
        {
            GetComponent<Image>().color = new Color(red, green, blue, alfa);

            if (Mode == 1)
            {
                alfa += speed;
            }
            if(Mode ==2)
            {
                alfa -= speed;
            }

            if (alfa >= 1.0f || alfa <= -1.0f)
            {
                FadeStart = false;
            }
        }
    }

    public void SetMode(int SetMode)
    {
        Mode = SetMode;
        FadeStart = true;
        transform.SetAsLastSibling();
    }

    public bool GetFadeStart()
    {
        return FadeStart;
    }

    public int GetFade()
    {
        return Mode;
    }
}
