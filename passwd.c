#include <func.h>

int main()
{
    char* passwd;
    passwd=getpass("请输入密码：");
    printf("passwd = %s\n",passwd);

    return 0;
}

