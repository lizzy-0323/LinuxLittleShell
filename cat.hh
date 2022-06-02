#ifndef CAT_HH
#define CAT_HH
#include<iostream>
using namespace std;
//cat命令的实现
void cat(char* path){
    //判断有无参数
    if(path==NULL){
        cout<<"cat: can't open  "<<path<<endl;
    }else{
        //打开文件
        FILE*fp=fopen(path,"r");
        if(fp==NULL){
            cout<<"cat: can't open  "<<path<<endl;
        }else{
            //读取文件
            char ch;
            while(!feof(fp)){
                ch=fgetc(fp);
                cout<<ch;
            }
            fclose(fp);
        }
        cout<<endl;
    }
}
#endif