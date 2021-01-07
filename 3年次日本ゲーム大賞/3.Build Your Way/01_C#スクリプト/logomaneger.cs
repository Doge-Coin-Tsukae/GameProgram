using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class logomaneger : MonoBehaviour
{
    public GameObject Fade;
    // Start is called before the first frame update
    void Start()
    {
        Fade.GetComponent<Fade>().SetMode(2);
    }

    // Update is called once per frame
    void Update()
    {
        
        if (Fade.GetComponent<Fade>().GetFadeStart() == false)
        {
            if(Fade.GetComponent<Fade>().GetFade()==1)
            {
                SceneManager.LoadScene("Title");
            }
            Fade.GetComponent<Fade>().SetMode(1);
        }
    }
}
