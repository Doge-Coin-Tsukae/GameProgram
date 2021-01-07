using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TenVinChild : MonoBehaviour
{
    [SerializeField]
    private bool Lefty;
    [SerializeField]
    private GameObject TenVinVin;

    [SerializeField]
    private TenVin OyaVinVin;

    float Baranse;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(Lefty == true)
        {
            Baranse = OyaVinVin.GetLeft();
        }
        else
        {
            Baranse = OyaVinVin.GetRight();
        }
    }
    void OnCollisionEnter(Collision collision)
    {
        if (Baranse >= 0 && Baranse < 100)
        {
            Vector3 Pos = transform.position;
            Pos.y -= 0.1f;
            transform.position = Pos;

            Vector3 PosPos = TenVinVin.transform.position;
            PosPos.y += 0.1f;
            TenVinVin.transform.position = PosPos;

            if(Lefty ==true)
            if(Lefty == true)
            {
                OyaVinVin.Left();
            }
            else
            {
                OyaVinVin.Right();
            }
        }
    }
}
