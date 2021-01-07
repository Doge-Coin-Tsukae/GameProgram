using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class cursor : MonoBehaviour
{
    bool Use;       //使用
    bool Out;       //シーン抜け出すときに使う
    int Stage;
    int Time;
    string Name;
    [SerializeField]
    GameObject Fade;

    // Start is called before the first frame update
    void Start()
    {
        Stage = 1;
        Time = 0;
        Out = false;
        Use = false;
        Fade.GetComponent<Fade>().SetMode(2);
    }

    // Update is called once per frame
    void Update()
    {
        if (Use==true)
        {
            float dph = Input.GetAxis("Horizontal");
            Vector3 Pos = transform.position;

            Pos.x =  200 + 380 * Stage;

            if (dph >= 1.0f && Time >= 30)
            {
                Stage++;
                Time = 0;
            }
            if (dph <= -1.0f && Time >= 30)
            {
                Stage--;
                Time = 0;
            }

            if(Stage>=4)
            {
                Stage = 4;
            }
            if(Stage<=0)
            {
                Stage = 0;
            }

            transform.position = Pos;
            Time++;

            if (Input.GetKeyDown("joystick button 0"))
            {
                Ray ray = Camera.main.ScreenPointToRay(Pos);
                RaycastHit hit = new RaycastHit();

                if (Physics.Raycast(ray, out hit))
                {
                    Name = hit.collider.gameObject.name;
                    Use = false;
                    Out = true;
                    Fade.GetComponent<Fade>().SetMode(1);
                }
            }
        }
        else
        {
            if(Fade.GetComponent<Fade>().GetFadeStart() == false)
            {
                if (Out == true)
                {
                    SceneManager.LoadScene(Name);
                }
                Use = true;
            }
        }

    }
}
