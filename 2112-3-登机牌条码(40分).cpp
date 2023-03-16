#include<iostream>
#include<cstring>
#include<vector>
#include<math.h>
using namespace std;
int w, s;  //行宽度，校验级别
string S;  //需要编码的数据

int recognize(char c)
{
    //识别某个字符是大写、小写还是数字
    if (c >= 'A' && c <= 'Z')
    {
        return 0;  //表示大写
    }
    else if (c >= 'a' && c <= 'z')
    {
        return 1;  //表示小写
    }
    else if (c >= '0' && c <= '9')
    {
        return 2;  //表示数字
    }
    else
    {
        return -1;  //表示不符合规定
    }
}

int tran_B(char c)  //翻译大写字母
{
    return (c - 'A');
}

int tran_S(char c)  //翻译小写字母
{
    return (c - 'a');
}

int tran_D(char c)  //翻译数字
{
    return (c - '0');
}

int main()
{
    cin >> w >> s;
    cin >> S;
    //系统一开始是处于大写模式的
    int state = 0;  //0大 1小 2数字
    int i = 0;
    int sta;  //表示每一位的模式
    vector<int> sequence;
    int res;  //每个字符的翻译结果
    char c;  //每个字符
    while (S[i] != '\0')  //逐位编码
    {
        c = S[i];
        sta = recognize(c);
        if (state == sta)  //模式匹配，直接翻译
        {
            switch (state)
            {
            case 0:
                res = tran_B(c);
                break;
            case 1:
                res = tran_S(c);
                break;
            case 2:
                res = tran_D(c);
                break;
            default:
                break;
            }
        }
        else  //模式不匹配，需要先进行模式转换
        {
            if (state == 0)  //当前翻译大写
            {
                if (sta == 1)  //需要小写
                {
                    //大->小
                    sequence.push_back(27);
                    state = 1;
                }
                else if (sta == 2)  //需要数字
                {
                    //大->数字
                    sequence.push_back(28);
                    state = 2;
                }
            }
            else if (state == 1)  //当前小写
            {
                if (sta == 0)  //需要大写
                {
                    //小->大
                    sequence.push_back(28);
                    sequence.push_back(28);
                    state = 0;
                }
                else if (sta == 2)  //需要数字
                {
                    //小->数
                    sequence.push_back(28);
                    state = 2;
                }
            }
            else if (state == 2)  //当前数字
            {
                if (sta == 0)  //需要大写
                {
                    //数字->大
                    sequence.push_back(28);
                    state = 0;
                }
                else if (sta == 1)  //需要小写
                {
                    //数字->小
                    sequence.push_back(27);
                    state = 1;
                }
            }
            //状态转换之后，进行翻译
            switch (state)
            {
            case 0:
                res = tran_B(c);
                break;
            case 1:
                res = tran_S(c);
                break;
            case 2:
                res = tran_D(c);
                break;
            default:
                break;
            }
        }
        //总之是翻译完了，有个res
        sequence.push_back(res);
        i++;
    }
    //全部翻译完
    if (sequence.size() % 2 == 1)  //奇数个
    {
        sequence.push_back(29);
    }
    /*
    //check一下结果，没问题
    for (int i = 0; i < sequence.size(); i++)
    {
        cout << sequence[i] << " ";
    }*/

    //计算码字
    vector<int> codewords;
    for (int i = 0; i < sequence.size(); i+=2)
    {
        int r = 30 * sequence[i] + sequence[i+1];
        codewords.push_back(r);
    }
    /*
    //check一下结果，没问题
    for (int i = 0; i < codewords.size(); i++)
    {
        cout << codewords[i] << " ";
    }*/

    //计算校验码
    int check_code_num;  //校验码字的数目
    if (s == -1)  //不需要校验码字
    {
        check_code_num = 0;
    }
    else  //需要校验
    {
        check_code_num = pow(2, (s+1));
    }

    //长度码字+数据码字+填充码字+校验码字 是w的倍数
    int codeword_num = 1 + codewords.size() + check_code_num;
    int fill_code_num;  //填充码字
    if (codeword_num % w == 0)  //刚好够
    {
        fill_code_num =0;
    }
    else
    {
        fill_code_num = w - (codeword_num % w);
    }
    
    int len_code = 1 + codewords.size() + fill_code_num;  //长度码字

    vector<int> cal_codeword;  //用于计算校验码的码字
    cal_codeword.push_back(len_code);
    for (int i = 0; i < codewords.size(); i++)
    {
        cal_codeword.push_back(codewords[i]);
    }
    for (int i = 0; i < fill_code_num; i++)
    {
        cal_codeword.push_back(900);
    }
    /*
    //验证一下，没问题
    for (int i = 0; i < cal_codeword.size(); i++)
    {
        cout << cal_codeword[i] << " ";
    }*/

    //计算校验码字，
    int n = len_code, k = check_code_num;
    if (k == 0)  //没有校验码字，直接输出就行
    {
        for (int i = 0; i < cal_codeword.size(); i++)
        {
            cout << cal_codeword[i] << endl;
        }
    }
    else  //有校验码字
    {

    }
    
    
    return 0;
}