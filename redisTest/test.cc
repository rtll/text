#include <string.h> 
#include <hiredis/hiredis.h> 
#include <iostream>
using namespace std;

void doTest() 
{ 
    //redis默认监听端口为6387 可以再配置文件中修改 
    redisContext* c = redisConnect("127.0.0.1", 6379); 
    //err字段为0表示连接正常，非0表示出错
    if ( c->err) 
    { 
        //释放redis连接
        redisFree(c); 
        printf("Connect to redisServer faile\n");
        //errstr字段表示错误信息
        printf("Error : %s\n",c->errstr);
        return ; 
    } 
    printf("Connect to redisServer Success\n"); 
       
    const char* command1 = "set stest1 value1"; 
    redisReply* r = (redisReply*)redisCommand(c, command1); 
    if( NULL == r) 
    { 
        printf("Execut command1 failure\n"); 
        redisFree(c); 
        return; 
    } 
    //set命令返回包的type字段应为状态，且str字段应为"ok"/"OK"
    if( !(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK")==0)) 
    { 
        printf("Failed to execute command[%s],%s\n",command1,r->str); 
        freeReplyObject(r); 
        redisFree(c); 
        return; 
    }    
    printf("Succeed to execute command[%s]\n", command1);
    //释放命令返回包,以接收下一条命令的返回包
    freeReplyObject(r); 
       
    const char* command2 = "stest1"; 
    r = (redisReply*)redisCommand(c, "strlen %s" ,command2);
    //返回包的类型应为整形，从integer字段获取值
    if ( r->type != REDIS_REPLY_INTEGER) 
    { 
        printf("Failed to execute command[%s]\n",command2); 
        freeReplyObject(r); 
        redisFree(c); 
        return; 
    } 
    int length =  r->integer; 
    freeReplyObject(r); 
    printf("The length of 'stest1' is %d.\n", length); 
    printf("Succeed to execute command[%s]\n", command2); 
       
    const char* command3 = "get stest1"; 
    r = (redisReply*)redisCommand(c, command3);
    //返回包的类型应为字符串，从str字段获取字符串，且可从len字段获取长度
    if ( r->type != REDIS_REPLY_STRING) 
    { 
        printf("Failed to execute command[%s]\n",command3); 
        freeReplyObject(r); 
        redisFree(c); 
        return; 
    } 
    cout<<"The value of 'stest1' is "<<r->str
        <<" and it's len is "<<r->len<<endl; 
    freeReplyObject(r); 
    printf("Succeed to execute command[%s]\n", command3); 
       
    const char* command4 = "get stest2"; 
    r = (redisReply*)redisCommand(c, command4); 
    //因为没有stest2这个键，所以返回包的类型应为空(NIL)
    if ( r->type != REDIS_REPLY_NIL) 
    { 
        printf("Failed to execute command[%s]\n",command4); 
        freeReplyObject(r); 
        redisFree(c); 
        return; 
    } 
    printf("The value of 'stest2' is %s\n", r->str); 
    freeReplyObject(r); 
    printf("Succeed to execute command[%s]\n", command4);    
    
    //r = (redisReply*)redisCommand(c,"del mylist");
    ////del命令成功返回被删除的key数量
    //if( !(r->type == REDIS_REPLY_INTEGER)  ){
    //     printf("Failed to execute command[del mylist]");
    //     freeReplyObject(r);redisFree(c);return;
    //}
    //printf("Succeed to execute command[del mylist] and deleted members %lld\n",r->integer);    
    //freeReplyObject(r);
    //建表
    for(int j = 0 ; j!= 100000 ; ++j){
        char buf[64];
        snprintf(buf,64,"%d",j);
        r = (redisReply*)redisCommand(c,"lpush mylist element-%s",buf);
        //lpush命令返回链表中元素个数
        if( !(r->type == REDIS_REPLY_INTEGER) ){
            printf("Failed to execute command[lpush mylist element-%s]\n",buf);
            freeReplyObject(r);redisFree(c);return;
        }
        printf("Succeed to execute command[push mylist element-%s] and members num is %lld\n",buf,r->integer);    
        freeReplyObject(r);
    }
    //读表
    //0表示第一个元素，1表示第二个，-1表示倒数第一个，-2表示倒数第二个，以此类推
    r = (redisReply*)redisCommand(c,"lrange mylist 0 -1");
    //对于获取list/set/zset/hash等容器的的元素，返回包的类型应为ARRAY
    //elements字段为容器元素的个数，element为redisReply*类型的元素们的数组
    if(r->type != REDIS_REPLY_ARRAY){
        printf("Failed to execute command[lrange myslist 0 -1]\n");
        freeReplyObject(r);redisFree(c);return;
    }
    for(size_t i = 0 ; i != r->elements ; ++i){
        cout<<i<<" : "<<r->element[i]->str<<"("<<r->element[i]->len
            <<")"<<endl;
    }
    freeReplyObject(r);

    redisFree(c); 
} 
   
int main() 
{ 
    doTest(); 
    return 0; 
}
