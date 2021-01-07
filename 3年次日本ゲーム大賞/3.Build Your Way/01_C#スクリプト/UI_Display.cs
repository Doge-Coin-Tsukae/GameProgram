using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UI_Display : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        // ワールドのy軸に沿って1秒間に90度回転
        transform.Rotate(new Vector3(0, 90, 0) * Time.deltaTime, Space.World);
    }
}
