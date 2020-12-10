using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class overlap : MonoBehaviour
{
    private bool isnotoverlap;
    // Start is called before the first frame update
    void Start()
    {
        isnotoverlap = true;
    }
    public bool IsNotOverlap()
    {
        return isnotoverlap;
    }

    // Update is called once per frame
    void Update()
    {
        //isnotoverlap = true;
    }
    void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("concrete"))
            isnotoverlap = false;
    }
    void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("concrete"))
            isnotoverlap = true;
    }

}
