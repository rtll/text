#include <string.h> 
#include <hiredis/hiredis.h> 
#include <iostream>
using namespace std;

void doTest() 
{ 
    //redisĬ�ϼ����˿�Ϊ6387 �����������ļ����޸� 
    redisContext* c = redisConnect("127.0.0.1", 6379); 
    //err�ֶ�Ϊ0��ʾ������������0��ʾ����
    if ( c->err) 
    { 
        //�ͷ�redis����
        redisFree(c); 
        printf("Connect to redisServer faile\n");
        //errstr�ֶα�ʾ������Ϣ
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
    //set����ذ���type�ֶ�ӦΪ״̬����str�ֶ�ӦΪ"ok"/"OK"
    if( !(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str,"OK")==0)) 
    { 
        printf("Failed to execute command[%s],%s\n",command1,r->str); 
        freeReplyObject(r); 
        redisFree(c); 
        return; 
    }    
    printf("Succeed to execute command[%s]\n", command1);
    //�ͷ�����ذ�,�Խ�����һ������ķ��ذ�
    freeReplyObject(r); 
       
    const char* command2 = "stest1"; 
    r = (redisReply*)redisCommand(c, "strlen %s" ,command2);
    //���ذ�������ӦΪ���Σ���integer�ֶλ�ȡֵ
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
    //���ذ�������ӦΪ�ַ�������str�ֶλ�ȡ�ַ������ҿɴ�len�ֶλ�ȡ����
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
    //��Ϊû��stest2����������Է��ذ�������ӦΪ��(NIL)
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
    ////del����ɹ����ر�ɾ����key����
    //if( !(r->type == REDIS_REPLY_INTEGER)  ){
    //     printf("Failed to execute command[del mylist]");
    //     freeReplyObject(r);redisFree(c);return;
    //}
    //printf("Succeed to execute command[del mylist] and deleted members %lld\n",r->integer);    
    //freeReplyObject(r);
    //����
    for(int j = 0 ; j!= 100000 ; ++j){
        char buf[64];
        snprintf(buf,64,"%d",j);
        r = (redisReply*)redisCommand(c,"lpush mylist element-%s",buf);
        //lpush�����������Ԫ�ظ���
        if( !(r->type == REDIS_REPLY_INTEGER) ){
            printf("Failed to execute command[lpush mylist element-%s]\n",buf);
            freeReplyObject(r);redisFree(c);return;
        }
        printf("Succeed to execute command[push mylist element-%s] and members num is %lld\n",buf,r->integer);    
        freeReplyObject(r);
    }
    //����
    //0��ʾ��һ��Ԫ�أ�1��ʾ�ڶ�����-1��ʾ������һ����-2��ʾ�����ڶ������Դ�����
    r = (redisReply*)redisCommand(c,"lrange mylist 0 -1");
    //���ڻ�ȡlist/set/zset/hash�������ĵ�Ԫ�أ����ذ�������ӦΪARRAY
    //elements�ֶ�Ϊ����Ԫ�صĸ�����elementΪredisReply*���͵�Ԫ���ǵ�����
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
