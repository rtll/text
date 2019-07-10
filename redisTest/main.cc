#include "Redis.h"

Redis* Redis::_pRedis = nullptr;

int main()
{
    if(!(Redis::getInstance()->connect())){
        return 0;
    }
    Redis::getInstance()->sett("ccc","cbla");
    Redis::getInstance()->sett("ddd","bbla");
    Redis::getInstance()->sett("eee","ebla");
    cout<<Redis::getInstance()->get("ccc")<<endl;;
    cout<<Redis::getInstance()->get("ddd")<<endl;
    string str = Redis::getInstance()->get("ppp");
    if(!str.empty())
        cout<<str<<endl;
    Redis::getInstance()->sett("ppp","pbla");
    str = Redis::getInstance()->get("ppp");
    if(!str.empty())
        cout<<str<<endl;

    return 0;
}

