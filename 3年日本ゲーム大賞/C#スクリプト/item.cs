using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class item : MonoBehaviour
{
    public GameObject inc; // エディターから取得できるようにpublicにしておく
    public int Num;
    public int type;
    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        //回転させる
        transform.Rotate(new Vector3(0, 1, 0));
    }
    void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            Debug.Log("ぶつかった");
            inc.GetComponent<ItemNumController>().AddItemNum(1);
            //アイテムのタイプで個数識別
            if(type == 1)
                other.gameObject.GetComponent<Player>().AddItem(Num);
            if(type ==2)
                other.gameObject.GetComponent<Player>().AddItemFlat(Num);

            gameObject.SetActive(false);
        }
    }
}
