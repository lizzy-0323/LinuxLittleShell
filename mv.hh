#ifndef MV_HH
#define MV_HH
#include<stdio.h>
#include<iostream>
using namespace std;
//mv command
void mv(string oldname,string newname){
    int flag;
    if((flag=rename(oldname.c_str(),newname.c_str()))==-1){
        cout<<"mv: failed"<<endl;
    }
}
#endif