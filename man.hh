#ifndef MAN_HH
#define MAN_HH
#include<iostream>
#include<fstream>
#include"cat.hh"
using namespace std;
void man(char*command_name){
    char *filename;
    if(strcmp(command_name,"man")==0){
        //use absolute path
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/man.txt";
        cat(filename);
    }
    else if(strcmp(command_name,"cd")==0){
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/cd.txt";
        cat(filename);
    }
    else if(strcmp(command_name,"pwd")==0){
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/pwd.txt";
        cat(filename);
    }
    else if(strcmp(command_name,"ls")==0){
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/ls.txt";
        cat(filename);
    }
    else if(strcmp(command_name,"history")==0){
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/history.txt";
        cat(filename);
    }  
    else if(strcmp(command_name,"cp")==0){
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/cp.txt";
        cat(filename);
    }
    else if(strcmp(command_name,"cat")==0){
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/cat.txt";
        cat(filename);
    }
    else if(strcmp(command_name,"mkdir")==0){
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/mkdir.txt";
        cat(filename);
    }      
    else if(strcmp(command_name,"mv")==0){
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/mv.txt";
        cat(filename);
    }
    else if(strcmp(command_name,"rm")==0){
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/rm.txt";
        cat(filename);
    }
    else if(strcmp(command_name,"wc")==0){
        filename=(char*)"/home/lazy/linux_homework/lab1/commandmenu/wc.txt";
        cat(filename);
    }      
    else{
        cout<<"command not found"<<endl;
    }
}
#endif