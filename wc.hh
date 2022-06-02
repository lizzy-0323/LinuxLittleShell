#ifndef WC_HH
#define WC_HH
#include<iostream>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
using namespace std;
//专门创建一个类，用来统计不同种类的信息
class WC
{
private:
    /* data */
    int chars;//字符数
    int lengths;//当前行的长度
    int words;//字数
    int bytes;
    int lines;//行数
    int max_line_length;//最长的行的长度
    int flag;
    char*filename;
    char*param;
public:
    WC(char*filename,char*param);
    WC(/* args */);
    void count();//计数函数
    ~WC();
};
//
WC::WC(char*filename,char*param)
{
    this->flag=0;
    this->chars=0;
    this->bytes=0;
    this->lengths=0;//当前行的长度
    this->max_line_length=0;
    this->words=0;
    this->lines=0;
    this->filename=filename;
    this->param=param;
}
WC::WC(/* args */)
{

}

WC::~WC()
{

}
void WC::count(){
    FILE *fp;
    struct stat get_message={};
    //if not specific text
    if(filename!="0.txt"){
        cout<<filename<<endl;
    }

    int ret=stat(filename,&get_message);
    if(ret==-1){
        cout<<"wc: "<<"file not exists"<<endl;
        return;
    }
    mode_t mode=get_message.st_mode;
    //如果是目录
    if(S_ISDIR(mode)){
        cout<<filename<<" Is a directory"<<endl;
    }
    else{
        bytes=get_message.st_size;
        fp=fopen(filename,"r");
        if(fp==NULL){
            cout<<"file open failed\n"<<endl;
        }
        else{
            char ch;
            //to the file end
            while((ch=fgetc(fp))!=EOF){
                chars++;
                // bytes+=sizeof(ch);
                if(ch!='\n'){
                    lengths++;
                }
                if(ch=='\n'){
                    lines++;
                    if(lengths>max_line_length)
                        max_line_length=lengths;
                    lengths=0;
                }
                if(ch=='\t'||ch==' '||ch=='\n'){
                    flag=0;
                    continue;
                }
                else{
                    if(flag==0){
                        words++;
                        flag=1;
                    }
                }
            }
            fclose(fp);
            if(param==NULL){
                cout<<lines<<"\t"<<words<<"\t"<<bytes<<"\t"<<filename<<endl;
            }
            else if(strcmp(param,"-l")==0){
                cout<<lines<<"\t"<<filename<<endl;
            }
            else if(strcmp(param,"-w")==0){
                cout<<words<<"\t"<<filename<<endl;
            }
            else if(strcmp(param,"-m")==0){
                cout<<chars<<"\t"<<filename<<endl;
            }
            else if(strcmp(param,"-c")==0){
                cout<<bytes<<"\t"<<filename<<endl;
            }
            else if(strcmp(param,"-L")==0){
                cout<<max_line_length<<"\t"<<filename<<endl;
            }
            else{
                cout<<"Please input correct params"<<endl;
            }
        }

    }

}

#endif