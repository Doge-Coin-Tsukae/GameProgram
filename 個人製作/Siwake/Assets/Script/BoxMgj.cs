using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BoxMgj : MonoBehaviour
{
    private bool flag;      //上か下か選択したかどうか
    private bool Up;        //上が押されたか
    private bool Down;      //下が押されたか
    private int Type;       //0スルー,１上,2下
    private int ToDouFuKen; //都道府県
    private float Speed;    //箱が進むスピード
    private Transform mypos;
    private GameObject GameManeger;     //ゲームマネージャの習得

    public GameObject score_object;     //箱に書く行き先テキスト
    // Start is called before the first frame update
    void Start()
    {
        //変数の初期化
        flag = false;
        Up = false;
        Down = false;
        mypos = this.transform;
        Type = Random.Range(0, 3);
        GameManeger = GameObject.Find("g_mgj");
        Speed = GameManeger.GetComponent<gamemaneger>().GetSpeed();

        //行き先によって箱に書く行き先を決める
        switch (Type)
        {
            case 0:
                //沖縄行き
                ToDouFuKen = 47;
                break;
            case 1:
                //関東ガチャ
                ToDouFuKen = Random.Range(8, 14);
                break;
            case 2:
                //関東以外ガチャ
                while (true)
                {
                    ToDouFuKen = Random.Range(1, 46);
                    //関東以外が出たらループを抜ける
                    if (ToDouFuKen < 8 || ToDouFuKen > 14)
                    {
                        break;
                    }
                }
                break;
            default:
                break;
        }

        //行き先テキスト変更
        TextMesh score_text = score_object.GetComponent<TextMesh>();
        score_text.text = GameManeger.GetComponent<ToDouFuKen_Data>().GetData(ToDouFuKen);
    }

    // Update is called once per frame
    void Update()
    {
        mypos = this.transform;

        Vector3 pos = mypos.position;

        if (flag == false)
        {
            pos.z += Speed;
        }

        if (Up == true)
        {
            pos.x -= 0.05f;
        }

        if (Down == true)
        {
            pos.x += 0.05f;
        }

        mypos.position = pos;

        //消える条件
        //ボタンを押さずにスルーした場合
        if (mypos.position.z >= 6.5f)
        {
            //行き先が当たっているとき
            if (Type == 0)
            {
                GameManeger.GetComponent<gamemaneger>().SetPoint();
            }
            //行き先が間違いの時
            else
            {
                GameManeger.GetComponent<gamemaneger>().DownLife();
            }
            Destroy(this.gameObject);
        }
        //上を押したとき
        if (mypos.position.x <= -3.0f)
        {
            //行き先が当たっているとき
            if (Type == 1)
            {
                GameManeger.GetComponent<gamemaneger>().SetPoint();
            }
            //行き先が間違いの時
            else
            {
                GameManeger.GetComponent<gamemaneger>().DownLife();
            }
            Destroy(this.gameObject);
        }
        //下を押したとき
        if (mypos.position.x >= 3.0f)
        {
            //行き先が当たっているとき
            if (Type == 2)
            {
                GameManeger.GetComponent<gamemaneger>().SetPoint();
            }
            //行き先が間違いの時
            else
            {
                GameManeger.GetComponent<gamemaneger>().DownLife();
            }
            Destroy(this.gameObject);
        }

    }
    void OnCollisionStay(Collision collision)
    {
        //上ボタン
        if (Input.GetKey(KeyCode.UpArrow))
        {
            if (flag == false)
            {
                Up = true;
                flag = true;
                mypos.position = new Vector3(0.0f, 0.68f, -1.0f);
            }
        }
        //下ボタン
        if (Input.GetKey(KeyCode.DownArrow))
        {
            if (flag == false)
            {
                Down = true;
                flag = true;
                mypos.position = new Vector3(0.0f, 0.68f, -1.0f);
            }
        }
    }
}
