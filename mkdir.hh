#ifndef MKDIR_HH
#define MKDIR_HH
#include"dirent.h"
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
void makedir(char* filename){
    if(mkdir(filename,0777)!=-1){
        cout<<"mkdir success"<<endl;
    }else{
        cout<<"mkdir failed"<<endl;
    }
}
#endif