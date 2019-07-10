#include"jieba.h"
using namespace std;

int main()
{
   // char ch0[]={"金古江湖战旗春秋"};

   // //1.分词
   // //最大概率法(MPSegment: Max Probability)分词所使用的词典路径
   // const char * const DICT_PATH = "cppjieba/dict/jieba.dict.utf8";
   // //隐式马尔科夫模型(HMMSegment: Hidden Markov Model)分词所使用的词典路径
   // const char * const HMM_PATH = "cppjieba/dict/hmm_model.utf8";
   // //用户自定义词典路径
   // const char * const USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";
   // 
   // //2.关键词提取，基于IT-IDF算法
   // //IDF路径，提供关键词及逆文档频率
   // const char* const IDF_PATH = "cppjieba/dict/idf.utf8";//IDF路径
   // 
   // //3.消除停用词
   // //停用词路径
   // const char* const STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";

   // cppjieba::Jieba jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH
   //                       ,STOP_WORD_PATH);
   // vector<string> words;
   // vector<cppjieba::Word> jiebawords;
   // string s = ch0;
   // string result;

   // jieba.Cut(s,words,true);
   // cout<<limonp::Join(words.begin(),words.end(),"/")<<endl;
   
    string str = "结巴分词库的下载和应用";
    WordSegmentation ws;
    vector<string> result = ws.cutsmall(str);
    vector<string> result1 = ws.cuthmm(str);
    vector<string> result2 = ws.cut(str);
    vector<string> result3 = ws.cutall(str);
    vector<string> result4 = ws.cutforSearch(str);
    
    for(auto& i : result)
        cout<<i<<"/";
    cout<<endl;
    for(auto& i : result1)
        cout<<i<<"/";
    cout<<endl;
    for(auto& i : result2)
        cout<<i<<"/";
    cout<<endl;
    for(auto& i : result3)
        cout<<i<<"/";
    cout<<endl;
    for(auto& i : result4)
        cout<<i<<"/";
    cout<<endl;

    return 0;
}

