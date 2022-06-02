#ifndef CD_HH
#define CD_HH
#include<iostream>
using namespace std;
//cd命令的实现
void cd(char* path){
    //判断有无参数
    if(path==NULL){
        cout<<"cd: can't open "<<path<<endl;
    }else{
        //判断是否为目录
        if(chdir(path)==-1){
            cout<<"cd: can't open "<<path<<endl;
        }
    }
}
#endif