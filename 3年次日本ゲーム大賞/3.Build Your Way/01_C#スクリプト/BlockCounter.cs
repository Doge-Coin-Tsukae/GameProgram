using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BlockCounter : MonoBehaviour
{
    public GameObject Block;    //playerを入れる
    public int Type;            //箱か板か
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //テキスト受け取る
        Text score_text = GetComponent<Text>();
        //ブロック
        if (Type == 1)
        {
            score_text.text = "x" + Block.GetComponent<Player>().GetItemNum().ToString();
        }
        //板
        else
        {
            score_text.text = "x" + Block.GetComponent<Player>().GetItemNumFlat().ToString();
        }
    }
}
