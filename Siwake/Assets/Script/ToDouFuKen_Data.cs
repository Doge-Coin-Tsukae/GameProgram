using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ToDouFuKen_Data : MonoBehaviour
{
    string[] Data = new string[47];
    // Start is called before the first frame update
    void Start()
    {
        Data[0] = "北海道";
        Data[1] = "青森県";
        Data[2] = "岩手県";
        Data[3] = "宮城県";
        Data[4] = "秋田県";
        Data[5] = "山形県";
        Data[6] = "福島県";
        Data[7] = "茨城県";
        Data[8] = "栃木県";
        Data[9] = "群馬県";
        Data[10] = "埼玉県";
        Data[11] = "千葉県";
        Data[12] = "東京都";
        Data[13] = "神奈川県";
        Data[14] = "新潟県";
        Data[15] = "富山県";
        Data[16] = "石川県";
        Data[17] = "福井県";
        Data[18] = "山梨県";
        Data[19] = "長野県";
        Data[20] = "岐阜県";
        Data[21] = "静岡県";
        Data[22] = "愛知県";
        Data[23] = "三重県";
        Data[24] = "滋賀県";
        Data[25] = "京都府";
        Data[26] = "大阪府";
        Data[27] = "兵庫県";
        Data[28] = "奈良県";
        Data[29] = "和歌山県";
        Data[30] = "鳥取県";
        Data[31] = "島根県";
        Data[32] = "岡山県";
        Data[33] = "広島県";
        Data[34] = "山口県";
        Data[35] = "徳島県";
        Data[36] = "香川県";
        Data[37] = "愛媛県";
        Data[38] = "高知県";
        Data[39] = "福岡県";
        Data[40] = "佐賀県";
        Data[41] = "長崎県";
        Data[42] = "熊本県";
        Data[43] = "大分県";
        Data[44] = "宮崎県";
        Data[45] = "鹿児島県";
        Data[46] = "沖縄県";
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public string GetData(int Number)
    {
        return Data[Number -1];
    }
}
