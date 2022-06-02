#ifndef CMD_HH
#define CMD_HH
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
class CMD
{
private:
    /* data */

public:
    int argc;
    char**argv;
    bool isparam;
    unordered_map<string,string>params;
    unordered_map<string,int>pos;
    CMD(istream& in,char **buffer);
    CMD();
    ~CMD();
    void hang(char* command);//挂起
    void redirect(char* command);//重定向
    int getPos(char* command);//get command pos
    char* getCommand();//获取命令
    char* getParam(int i);//获取参数
};
#endif