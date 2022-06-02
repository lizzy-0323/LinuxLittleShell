#ifndef CP_HH
#define CP_HH
#include<iostream>
#include<unistd.h>
#include<fstream>
using namespace std;
//cp command
void cp(const char *s1,const char*s2){
    ifstream src(s1,ios::binary);
    ofstream dest(s2,ios::binary);
    dest<<src.rdbuf();
    src.close();
    dest.close();
    //if src or dest is null
    if(!src||!dest){
        cout<<"copy failed"<<endl;
    }
}
#endif