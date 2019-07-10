#include "cppjieba/include/cppjieba/Jieba.hpp"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const char * const DICT_PATH = "cppjieba/dict/jieba.dict.utf8";//�����ʷ�(MPSegment: Max Probability)�ִ���ʹ�õĴʵ�·��
const char * const HMM_PATH = "cppjieba/dict/hmm_model.utf8";//��ʽ����Ʒ�ģ��(HMMSegment: Hidden Markov Model)�ִ���ʹ�õĴʵ�·��
const char * const USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";//�û��Զ���ʵ�·��
const char* const IDF_PATH = "cppjieba/dict/idf.utf8";//IDF·��
const char* const STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";//ͣ�ô�·��

class WordSegmentation//ʹ�ý�ͷִʿ���зִ�
{
public:
    WordSegmentation()
    :_jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
    {
        cout << "cppjieba init!" << endl;
    }

    vector<string> cutsmall(const string & str)
    {
        vector<string> words;
        //�ײ�ΪMPsegment:����MP�д��㷨
        _jieba.CutSmall(str, words,0);
        return words;
    }
    
    vector<string> cuthmm(const string & str)
    {
        vector<string> words;
        //�ײ�ΪHMMsegment:����HMM�д��㷨
        _jieba.CutHMM(str, words);
        return words;
    }
    
    vector<string> cut(const string & str)
    {
        vector<string> words;
        //�ײ�ΪMixSegment:�ں�MP��HMM���д��㷨,Ч�����
        _jieba.Cut(str, words);
        return words;
    }
    
    vector<string> cutall(const string & str)
    {
        vector<string> words;
        //�ײ�ΪFullSegment:�г�����մ�ߵ��ֵ���Ĵ���
        _jieba.CutAll(str, words);
        return words;
    }
    
    vector<string> cutforSearch(const string & str)
    {
        vector<string> words;
        //�ײ�ΪQuerySegment:����Mix�����д�,�Խϳ�����ʹ��Full������
        _jieba.CutForSearch(str, words);
        return words;
    }
private:
    cppjieba::Jieba _jieba;
};
