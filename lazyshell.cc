#include"lazyshell.hh"
#include<iostream>
#include"ls.hh"
#include"cat.hh"
#include"cd.hh"
#include"pwd.hh"
#include"wc.hh"
#include"semaphore.hh"
#include"mkdir.hh"
#include"rm.hh"
#include"cp.hh"
#include"man.hh"
#include"echo.hh"
#include"mv.hh"
using namespace std;
/*
    process:
    *1.output workpath
    *2.Input command
    *3.Analyse command
    *4.run command
*/
/*
    share varible
*/
//sheild Ctrl_C
extern void Ctrl_C(int x){
    fprintf(stderr,"\n Interrupt!\n");
    fflush(stdout);
    return;
}
char **buffer;
static int pcount=1;
bool isMuliple=false;
//run LazyShell
void LazyShell::run(){
    while(true)
    {
        //1.output workpath
        char buf[1024];
        signal(SIGINT,Ctrl_C);
        char *current_directory=getcwd(buf,256);
        if(buffer==NULL){
            strcat(current_directory,"$ ");
            cout<<current_directory;
        }
        else{
            strcat(current_directory,"/child$: ");//multple shell
            cout<<current_directory<<endl;
        }
        CMD cmd=CMD(cin,buffer);
        if(cmd.argc==0)
        {
            continue;
        }
        //3.Analyse command and run command
        char* command=cmd.getCommand();
        int size=strlen(command);
        if(cmd.params.count("|")){//deal with pipe
            commandWithPipe(cmd.argv,cmd.argc);
            continue;
        }
        //hangout command
        if(command[size-1]=='&'){
            command[size-1]='\0';
            hang(cmd.argv);
        }
        //redirect command
        else if(command[size-1]=='>'){
            command[size-1]='\0';
            char *path=new char[cmd.params[">"].size()+1];
            strcpy(path,cmd.params[">"].c_str());
            redirect(cmd.argv,path);
        }
        //exe program
        else if(command[0]=='.'&&command[1]=='/'){
            runexe(command);
        }
        //history command
        else if(strcmp(command,"history")==0){
            if(cmd.getParam(1)!=NULL){
                int param=atoi(cmd.getParam(1))-1;
                ShowHistory(param);
            }else{
                ShowHistory(history_list.size());
            }

        }
        //ls command
        else if(strcmp(command,"ls")==0){
            //judge params
            if(cmd.argc<3){
                char*lsparam=cmd.getParam(1);
                if(lsparam!=NULL&&(strcmp(lsparam,"-l")==0)){
                    ls_withparam(NULL,lsparam);
                }
                else{
                    ls(lsparam);
                }
            }
            else{
                char*param=cmd.getParam(1);
                char*path=cmd.getParam(2);
                ls_withparam(path,param);
            }
        }
        //echo command
        else if(strcmp(command,"echo")==0){
            char*echoParam=cmd.getParam(1);
            echo(echoParam);
        }
        //cat command
        else if(strcmp(command,"cat")==0){
            char*catParam=cmd.getParam(1);
            if(catParam==NULL)
            {
                cout<<"cat: params not enough"<<endl;
            }
            else
            {
                cat(catParam);
            }
        }
        //cd command
        else if(strcmp(command,"cd")==0){
            char*cdParam=cmd.getParam(1);
            if(cdParam==NULL)
            {
                cout<<"cd: params not enough"<<endl;
            }
            else
            {
                cd(cdParam);
            }
        }
        //rm command
        else if(strcmp(command,"rm")==0){
            char*rmParam=cmd.getParam(1);
            if(rmParam==NULL)
            {
                cout<<"rm: params not enough"<<endl;
            }
            else
            {
                rm(rmParam);
            }
        }
        //mkdir command
        else if(strcmp(command,"mkdir")==0){
            char*mkdirParam=cmd.getParam(1);
            if(mkdirParam==NULL)
            {
                cout<<"mkdir: params not enough"<<endl;
            }
            else
            {
                makedir(mkdirParam);
            }
        }
        //wc command
        else if(strcmp(command,"wc")==0){
            char*filename;
            char*choice;
            if(cmd.argc==3){
                filename=cmd.getParam(2);
                choice=cmd.getParam(1);
            }else{
                choice=NULL;
                filename=cmd.getParam(1);
            }
            // cout<<filename<<endl;
            WC wc=WC(filename,choice);
            if(filename==NULL)
            {
                cout<<"wc: params not enough"<<endl;
            }
            else
            {
                wc.count();
            }
        }
        //mv command
        else if(strcmp(command,"mv")==0){
            if(cmd.argc<3){
                cout<<"mv； params not enough"<<endl;
            }
            else{
                string oldname=cmd.getParam(1);
                string newname=cmd.getParam(2);
                mv(oldname,newname);
            }
        }
        //cp command
       else if(strcmp(command,"cp")==0)
        {
            if(cmd.argc<3){
                cout<<"cp； params not enough"<<endl;
            }
            else{
                char* src=cmd.getParam(1);
                char* dst=cmd.getParam(2);
                cp(src,dst);
            }
        }
        //pwd command
        else if(strcmp(command,"pwd")==0){
            pwd();
        }
        //demo command
        else if(strcmp(command,"hello")==0){
            cout<<"help menu:"<<endl;
            cout<<"this is a demo shell"<<endl;
            cout<<"made by lazy1 in DMU"<<endl;
            cout<<"I made a few commands like pwd,cd,etc"<<endl;
        }
        //clear command
        else if(strcmp(command,"clear")==0){
            fputs("\x1b[2J\x1b[H",stdout);
        }
        //man command
        else if(strcmp(command,"man")==0){
            char* command_name=cmd.getParam(1);
            man(command_name);
        }
        //exit command
        else if(strcmp(command,"exit")==0||strcmp(command,"q")==0)
        {
            break;
        }
        //release buffer
        else if(buffer!=NULL){
            buffer=NULL;
            break;
        }
        //store command
        AddHistory(command);
    }
}
//show history
void LazyShell::ShowHistory(int n){
    if(n>history_list.size()-1){
        n--;
    }
    while(n>=0){
        cout<<n+1<<'\t'<<'\t'<<history_list[n]<<endl;
        n--;
    }
}
//add history
void LazyShell::AddHistory(char*commandname){
    history_list.push_back(commandname);
}
//pipe command
void LazyShell::commandWithPipe(char** argv,int argc){
    int i;
    char *infile=(char*)"0.txt";
    for(i=0;i<argc;i++){
        int size=strlen(argv[i]);
        if(argv[i][size-1]=='|'){
            argv[i][size-1]='\0';
            pid_t pid=fork();
            if(pid==0){
                freopen(infile,"w",stdout);
                //ls command
                if(strcmp(argv[i],"ls")==0){
                    re_ls();
                }
                //pwd command
                if(strcmp(argv[i],"pwd")==0){
                    pwd();
                }
                //echo command
                if(i!=0&&(strcmp(argv[i-1],"echo")==0)){
                    echo(argv[i]);
                }
                //run exe file
                if(argv[i][0]=='.'&&argv[i][1]=='/'){
                    runexe(argv[i]);
                }
                else{
                    cout<<"wrong command"<<endl;
                }
                fclose(stdout);
                exit(0);
            }
        }
    }
    sleep(1);
    if(strcmp(argv[i-1],"wc")==0){
        WC wc=WC(infile,NULL);
        wc.count();
    }
    if(strcmp(argv[i-1],"wc&")==0){
        int childid=getpid();
        cout<<"["<<pcount<<"]"<<" "<<childid<<endl;
        pcount++;
        WC wc=WC(infile,NULL);
        wc.count();
    }
    if(strcmp(argv[i-1],"cat")==0){
        cat(infile);
    }
    rm(infile);
}
//runexe in lazyshell
void LazyShell::runexe(char* command){
    string exe=command;
    char buf[1024];
    //remove . and /
    char*path=getcwd(buf,256);
    exe=exe.substr(2);
    const char* exefile=exe.c_str();
    strcat(path,"/");
    strcat(path,(char*)exefile);
    // cout<<path<<endl;
    pid_t pid=fork();
    if(pid==0){
        if(execl(path,"command",(char*)0)==-1){
            cout<<"can't find the exe file"<<endl;
        };
        exit(0);
    }
    else{
        sleep(1);
    }
}

//hang a running process
void LazyShell::hang(char** command){
    Semaphore sem(0);
    pid_t pid=fork();
    if(pid==0){
        int childid=getpid();
        cout<<"["<<pcount<<"]"<<" "<<childid<<endl;
        LazyShell *multpshell;
        buffer=command;
        //activate a new shell
        multpshell->run();
        sem.signal();
        exit(0);
    }else{
        sem.wait();
        int result=waitpid(pid,NULL,0);
        pcount++;
        if(result==-1){
            cout<<"return "<<result<<endl;
        }
    }
}
//redirect
void LazyShell::redirect(char** command,char*path){
    pid_t pid=fork();
    if(pid==0){
        freopen(path,"w",stdout);
        if(strcmp(command[0],"ls")==0){
            re_ls();
        }
        else{
            LazyShell* multpshell;
            buffer=command;
            //activate a new shell
            multpshell->run();
            delete multpshell;
        }
        fclose(stdout);
        exit(0);
    }
    else{
        waitpid(pid,NULL,0);
    }
}

//构造函数
LazyShell::LazyShell(){

}
//析构函数
LazyShell::~LazyShell(){

}
