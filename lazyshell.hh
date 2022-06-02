#ifndef LAZYSHELL_HH
#define LAZYSHELL_HH
#include <iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<vector>
#include"CMD.hh"
using namespace std;

//定义Shell类
class LazyShell{
    public:
    vector<string>history_list;
    //构造函数
    LazyShell();
    //析构函数
    ~LazyShell();
    //执行命令
    void run();
    //挂起命令
    void hang(char**command);
    //redirect command
    void redirect(char** command,char*path);
    //pipe command
    void commandWithPipe(char** argv,int argc);
    //run exe
    void runexe(char* command);
    //history command
    void AddHistory(char*command);
    void ShowHistory(int n);
    private:
    //解析命令
    CMD cmd;
    //定义变量
};
#endif