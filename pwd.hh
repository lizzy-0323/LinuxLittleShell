#ifndef PWD_HH
#define PWD_HH
#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;
//pwd命令的实现
void pwd(){
    char buf[1024];
    char *current_directory=getcwd(buf,256);
    cout<<"absolute path is"<<" "<<"\033[0;32m"<<current_directory<<"\033[0;37m"<<endl;
}
#endif