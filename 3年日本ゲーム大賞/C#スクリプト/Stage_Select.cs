using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;


public class Stage_Select : MonoBehaviour
{
    [SerializeField]
    private GameObject cleartext;   //クリアのテキスト
    [SerializeField]
    GameObject canvas;             //ステージ選択画面のキャンバス
    [SerializeField]
    GameObject Delete;

    private int []Cleard;        //ステージをクリアしているかどうか識別する(1=true,0=false)
    private int MaxStage = 5;     //ステージ数
    private int DeleteKey;
    // Start is called before the first frame update
    void Start()
    {
        DeleteKey = 0;
        Delete.SetActive(false);
        Cleard = new int[MaxStage];   //配列を用意する(ステージが5つあるので5つ)

        for (int i = 0; i < MaxStage; i++)
        {
            //データ確認
            if (PlayerPrefs.HasKey("Cleard" + i) == false)
            {//なければ新しく作る
                PlayerPrefs.SetInt("Cleard" + i, 0);
            }
            //セーブデータのロード
            Cleard[i] = PlayerPrefs.GetInt("Cleard" + i, 0);

        }

        for (int i = 0; i < MaxStage; i++)
        {
            if (Cleard[i] == 1)
            {
                GameObject Clear = (GameObject)Instantiate(cleartext);
                Clear.transform.SetParent(canvas.transform, false);
                Clear.GetComponent<RectTransform>().anchoredPosition = new Vector2(-780 + (i * 390), -100);
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {

            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit = new RaycastHit();

            if (Physics.Raycast(ray, out hit))
            {
                SceneManager.LoadScene(hit.collider.gameObject.name);
            }
        }
        if (Input.GetKeyDown("joystick button 3"))
        {
            DeleteKey++;
        }

        if(DeleteKey>=3)
        {
            PlayerPrefs.DeleteAll();
            DeleteKey = 0;
            Debug.Log("データ全削除された");
            Delete.SetActive(true);
        }
    }
}
