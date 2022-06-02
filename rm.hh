#ifndef RM_HH
#define RM_HH
#include<iostream>
using namespace std;
void rm(char*path){
    if(path==NULL){
        cout<<"rm: can't open "<<path<<endl;
    }else{
        if(remove(path)==-1){
            cout<<"rm: can't open "<<path<<endl;
        }
    }
}
#endif