using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class gamemaneger : MonoBehaviour
{

    [SerializeField]
    GameObject Box;
    private float time;
    private float totaltime;
    private int Point;
    private int Life;
    private float Speed;
    public GameObject score_object;
    public GameObject Life_object;
    // Start is called before the first frame update
    void Start()
    {
        Speed = 0.03f;
        time = 0.0f;
        totaltime = 0.0f;
        Point = 0;
        Life = 3;
    }

    // Update is called once per frame
    void Update()
    {
        Text score_text = score_object.GetComponent<Text>();
        score_text.text = "仕分けた数: "+ Point.ToString();
        Text Life_text = Life_object.GetComponent<Text>();
        Life_text.text = "許される誤配数: " + (Life - 1);
        time += 0.1f;
        totaltime += 0.1f;

        if (time >= 50.0f)
        {
            RespornBox();
            time = 0.0f;
        }

        if(totaltime >= 600)
        {
            Speed += 0.03f;
            totaltime = 0;
        }
    }

    void RespornBox()
    {
        GameObject.Instantiate(Box,new Vector3(0.0f,0.7f,-5.0f),Quaternion.identity);
    }
    
    public void SetPoint()
    {
        Point++;
    }

    public void DownLife()
    {
        Life--;

        if(Life <=0)
        {
            SceneManager.LoadScene("Result");
        }
    }

    public float GetSpeed()
    {
        return Speed;
    }
}
