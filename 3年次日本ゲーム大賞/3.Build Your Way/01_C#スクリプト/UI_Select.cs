using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_Select : MonoBehaviour
{

    public GameObject UI_Concrete;
    public GameObject UI_Concrete2;

    private int flag;

    // Start is called before the first frame update
    void Start()
    {
        flag = 0;
    }

    // Update is called once per frame
    void Update()
    {
        switch (flag)
        {
            case 0:

                UI_Concrete.SetActive(true);
                UI_Concrete2.SetActive(false);

                if (Input.GetKeyDown(KeyCode.LeftShift) || Input.GetKeyDown("joystick button 2"))
                {
                    flag++;
                }

                break;

            case 1:

                UI_Concrete.SetActive(false);
                UI_Concrete2.SetActive(true);

                if (Input.GetKeyDown(KeyCode.LeftShift) || Input.GetKeyDown("joystick button 2"))
                {
                    flag--;
                }

                break;

            default:

                break;
        }
    }
}
