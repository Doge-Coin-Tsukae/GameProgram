using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TenVin : MonoBehaviour
{
    Vector2 Baranse;
    // Start is called before the first frame update
    void Start()
    {
        Baranse = new Vector2(50, 50);
    }

    // Update is called once per frame
    void Update()
    {
    }

    public void Left()
    {
        Baranse.x += 1;
        Baranse.y -= 1;
    }
    public void Right()
    {
        Baranse.y += 1;
        Baranse.x -= 1;
    }
    public float GetLeft()
    {
        return Baranse.x;
    }
    public float GetRight()
    {
        return Baranse.y;
    }
}
