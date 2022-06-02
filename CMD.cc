#include"CMD.hh"
#include<dirent.h>
using namespace std;
//无参数构造函数
CMD::CMD(){
    argc=0;
    argv=NULL;
}
//标准的构造函数
CMD::CMD(istream& in,char** buffer){
    if(buffer!=NULL){
        argv=buffer;
        argc++;
    }
    else{
        //获取命令
        string command;
        isparam=false;
        getline(in,command);
        //转换成字符串数组
        stringstream ss(command);
        string item;
        argc=0;
        while(getline(ss,item,' ')){
            argc++;
        }
        argv=new char*[argc];
        //转换成字符串数组
        stringstream ss2(command);
        int i=0;
        while(getline(ss2,item,' ')){
            int len=item.size();
            //find params
            if(item[len-1]=='>'){
                isparam=true;
            }
            //save params
            if(isparam){
                params[">"]=item;
            }
            if(item[len-1]=='|'){
                params["|"]=i;
            }
            // if(item[len-1]=='&'){
            //     ishang=true;
            //     item.erase(len-1);
            // }
            argv[i]=new char[item.size()+1];
            strcpy(argv[i],item.c_str());
            i++;
        }
        // for(i=0;argv&&argv[i];i++){
        //     int len=strlen(argv[i]);
        //     if (argv[i][len-1]=='>')
        //     {
        //         params[">"]=item;
        //     }
        //     if( argv[i]=="echo"){
        //         params["echo"]=argv[i+1];
        //     }
            
        // }
    }

}
//析构函数
CMD::~CMD(){
    for(int i=0;i<argc;i++){
        delete[]argv[i];
    }
    params.clear();
    delete[]argv;
}
//获取命令
char* CMD::getCommand(){
    if(argc==0)
        return NULL;
    //cout<<argv[0];
    return argv[0];
}
//获取参数
char* CMD::getParam(int i){
    if(i>=argc)
        return NULL;
    return argv[i];
}
//get command pos
int CMD::getPos(char* command){
    return pos[command];
}
// //后台挂起运行
// void CMD::hang(char* command){
//     pid_t pid=fork();
//     if(pid==0){
//         //child
//         //cout<<"child"<<endl;
//         //cout<<argv[0]<<endl;
//         cout<<"[1]"<<" "<<command<<endl;
//         execvp(command,argv);
//         exit(1);
//     }else{
//         int status;
//         waitpid(pid,&status,0);
//         int err = WEXITSTATUS(status);  // 读取子进程的返回码
//         if (err) { 
//             printf("Error: %s\n", strerror(err));
//         } 
//     }
// }
// //输入输出重定向
// void CMD::redirect(char*command){
//     const char* path=params[">"].c_str();
//     cout<<path<<endl;
//     pid_t pid=fork();
//     if(pid==0){
//         freopen(path,"w",stdout);
//         cout<<"wtf"<<endl;
//         exit(1);
//     }else{
//         int status;
//         waitpid(pid,&status,0);
//         int err = WEXITSTATUS(status); 
//         if (err) { 
//             printf("Error: %s\n", strerror(err));
//         } 
//     }
// }

