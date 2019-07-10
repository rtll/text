#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
size_t nBytesCode(const char ch)
{
    if(ch & (1 << 7))//如果ch是多字节的，下面循环判断utf-8编码的长度
    {
        int nBytes = 1;
        for(int idx = 0; idx != 6; ++idx)
        {
            if(ch & (1 << (6 - idx)))
            {
                ++nBytes;
            } else
                break;
        }
        return nBytes;
    }
    return 1;
}

size_t length(const string & str)
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

int triple_min(const int & a, const int & b, const int & c)
{
    return a < b ?(a < c ? a : c) : (b < c ? b : c);
}

int editDistance(const string & lhs, const string & rhs)
{
    size_t lhs_len = length(lhs);
    size_t rhs_len = length(rhs);
    size_t blhs_len = lhs.size();
    size_t brhs_len = rhs.size();

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
    for(size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len && lhs_idx <= blhs_len; ++dist_i, ++lhs_idx)
    {
        //cout << "lhs_idx = " << lhs_idx << endl;
        size_t nBytes = nBytesCode(lhs[lhs_idx]);
        sublhs = lhs.substr(lhs_idx, nBytes);
        lhs_idx += (nBytes - 1);

        for(size_t dist_j = 1, rhs_idx = 0; dist_j <= rhs_len && rhs_idx <= brhs_len; ++dist_j, ++rhs_idx)
        {
            //cout << "rhs_idx = " << lhs_idx << endl;
            nBytes = nBytesCode(rhs[rhs_idx]);
            subrhs = rhs.substr(rhs_idx, nBytes);
            rhs_idx += (nBytes - 1);
            if(sublhs == subrhs)
            {
                editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j - 1];
            } else {
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
    cout << "中过" << endl;
    const string s1 = "中国asd";
    const string s2 = "中国红";
    const string s3 = "é";
    const string s4 = "克";
    int i = s3[0];
    int j = s3[1];
    int k = s3[2];
    cout << "s1 sizeof " << s1.size() << " s1 length " << length(s1) << endl;
    cout << "s1[0] : " << s1.substr(0,3) << " s2[1] : "<<s1.substr(3,3) << endl;
    cout << "s2 sizeof " << s2.size() << " s2 length " << length(s2) << endl;
    cout << "é sizeof " << s3.size() << " é length " << length(s3) << endl;
    cout<<i<<" "<<j<<" "<<k<<endl;
    if((s4.size())==3)
        cout << "s4 " <<s4<<" 是一个汉字"<< endl;
    cout << "s1 s2 editDistance " << editDistance(s1, s2) << endl;
    const string s5 = "bat";
    const string s6 = "skinblisterscallositiescornschilblains";
    cout << "s5 s6 editDistance " << editDistance(s5, s6) << endl;
    
    return 0;
}
