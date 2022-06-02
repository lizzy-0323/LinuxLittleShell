#ifndef ECHO_HH
#define ECHO_HH
#include<iostream>
using namespace std;
void echo(char* sentense){
    if(sentense==NULL)
        cout<<"echo: params not enough"<<endl;
    else
        cout<<sentense<<endl;
}
#endif