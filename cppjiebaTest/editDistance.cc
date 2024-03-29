#include <string>
#include <iostream>
using namespace std;
   
//判断字符的字节长，以便区分编码规则，实现utf-8编码
/// 获取一个字节高位开头为1的个数
size_t nBytesCode(const char ch)
{
    if(ch & (1 << 7))//如果ch是多字节的，下面循环，判断utf-8编码的字节长
    {
        int nBytes = 1;
        for(int idx = 0; idx != 6; ++idx)
        {
            if(ch & (1 << (6 - idx)))
            {
                ++nBytes;  
            }
            else
                break;
        }
        return nBytes;//返回字节长
    }
    return 1;
} 
 
size_t length(const string &str)
{
    size_t ilen = 0;
    for(size_t idx = 0; idx != str.size(); ++idx)
    {
        int nBytes = nBytesCode(str[idx]);
        idx += (nBytes - 1);
        ++ilen;
    }
    return ilen;
}
 
int triple_min(const int &a, const int &b, const int &c)
{
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}
 
int editDistance(const string & lhs, const string &rhs)
{//计算最小编辑距离-包括处理中英文
    size_t lhs_len = length(lhs);//字符长
    size_t rhs_len = length(rhs);
    size_t blhs_len = sizeof(lhs);//字节长
    size_t brhs_len = sizeof(rhs);
 
    int editDist[lhs_len + 1][rhs_len + 1];
    for(size_t idx = 0; idx <= lhs_len; ++idx)
    {
        editDist[idx][0] = idx;
    }
 
    for(size_t idx = 0; idx <= rhs_len; ++idx)
    {
        editDist[0][idx] = idx;
    }
     
    string sublhs, subrhs;
    for(size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len && lhs_idx <= blhs_len; ++dist_i, ++lhs_idx)//lhs_idx<=blhs_len一定要加上，防止substr处理越界，自己调试几下就清楚了
    {
        size_t nBytes = nBytesCode(lhs[lhs_idx]);
        sublhs = lhs.substr(lhs_idx, nBytes);
        lhs_idx += (nBytes - 1);
 
        for(size_t dist_j = 1, rhs_idx = 0; dist_j <= rhs_len && rhs_idx <= brhs_len; ++dist_j, ++rhs_idx)
        {
            nBytes = nBytesCode(rhs[rhs_idx]);
            subrhs = rhs.substr(rhs_idx, nBytes);
            rhs_idx += (nBytes - 1);
            if(sublhs == subrhs)
            {
                editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j - 1];
            }
            else
            {
                editDist[dist_i][dist_j] = triple_min(
                    editDist[dist_i][dist_j - 1] + 1,
                    editDist[dist_i - 1][dist_j] + 1,
                    editDist[dist_i - 1][dist_j - 1] + 1);
            }
        }
    }
    return editDist[lhs_len][rhs_len];
}

int main()
{
    const string s1 = "中国";
    const string s1 = "中国";
    const string s1 = "中国";

    while(1){
        cout<<"中过";
        cin>>s1>>s2;
        cout<<editDistance(s1,s2)<<endl;
    }
}
