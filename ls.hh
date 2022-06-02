#ifndef LS_HH
#define LS_HH
#include<iostream>
#include<string.h>
#include<unordered_set>
#include<dirent.h>
#include<time.h>
#include <langinfo.h>
#include <grp.h>
#include <sys/types.h>
#include <pwd.h>
#include<sys/stat.h>
using namespace std;
//sort files
bool cmp(string s1,string s2){
    return s1<s2;
}
//output pre
char * getperm(char * perm , struct stat fileStat) {
	if ( S_ISLNK(fileStat.st_mode) ) {
		perm[0] = 'l';
	}
	else if ( S_ISDIR(fileStat.st_mode) ) {
		perm[0] = 'd';
	}
	else if ( S_ISCHR(fileStat.st_mode) ) {
		perm[0] = 'c';
	}
	else if ( S_ISSOCK(fileStat.st_mode) ) {
		perm[0] = 's';
	}
	else if ( S_ISFIFO(fileStat.st_mode) ) {
		perm[0] = 'p';
	}
	else if ( S_ISBLK(fileStat.st_mode) ) {
		perm[0] = 'b';
	}
	else {
		perm[0] = '-';
	}
	perm[1] = ((fileStat.st_mode & S_IRUSR) ? 'r' : '-');
	perm[2] = ((fileStat.st_mode & S_IWUSR) ? 'w' : '-');
	perm[3] = ((fileStat.st_mode & S_IXUSR) ? 'x' : '-');
	perm[4] = ((fileStat.st_mode & S_IRGRP) ? 'r' : '-');
	perm[5] = ((fileStat.st_mode & S_IWGRP) ? 'w' : '-');
	perm[6] = ((fileStat.st_mode & S_IXGRP) ? 'x' : '-');
	perm[7] = ((fileStat.st_mode & S_IROTH) ? 'r' : '-');
	perm[8] = ((fileStat.st_mode & S_IWOTH) ? 'w' : '-');
	perm[9] = ((fileStat.st_mode & S_IXOTH) ? 'x' : '-');

	if ( fileStat.st_mode & S_ISUID ) {
		perm[3] = 's';
	}
	else if ( fileStat.st_mode & S_IXUSR ) {
		perm[3] = 'x';
	}
	else {
		perm[3] = '-';
	}

	if ( fileStat.st_mode & S_ISGID ) {
		perm[6] = 's';
	}
	else if ( fileStat.st_mode & S_IXGRP ) {
		perm[6] = 'x';
	}
	else {
		perm[6] = '-';
	}

	if ( fileStat.st_mode & S_ISVTX ) {
		perm[9] = 't';
	}
	else if ( fileStat.st_mode & S_IXOTH ) {
		perm[9] = 'x';
	}
	else {
		perm[9] = '-';
	}

	perm[10] = 0;

	return perm;
}
//ls command
void ls(char* path){
    DIR*dir_ptr;
    char s[1000];
    string res[1000];
    unordered_set<string>hash;
    struct dirent*direntp;
    int count=0;
    int cnt=0;
    if(path==NULL){
        dir_ptr=opendir(".");
    }else{
        dir_ptr=opendir(path);
    }
    if(dir_ptr!=NULL){
        while(direntp=readdir(dir_ptr)){
            if (strcmp(direntp->d_name,"..")==0||strcmp(direntp->d_name,".")==0)
            {
                continue;
            }
            else
            {
                strcpy(s,direntp->d_name);
                // judge if is a dir
                if(direntp->d_type==DT_DIR){
                    hash.insert(direntp->d_name);
                }
                res[cnt++]=s;
            }
        }
        closedir(dir_ptr);
        sort(res,res+cnt,cmp);
        for(int i=0;i<cnt;i++){
            int size=res[i].size();
            //choose color by file type
            if(res[i][size-1]=='c'||res[i][size-1]=='C'){
                cout<<"\033[0;31m";
            }
            if(res[i][size-1]=='o'||res[i][size-1]=='O'){
                cout<<"\033[0;32m";
            }
            if(res[i][size-1]=='h'||res[i][size-1]=='H'){
                cout<<"\033[0;33m";
            }
            if((hash.count(res[i])!=0)){
                cout<<"\033[0;34m";
            }
            cout<<res[i]<<"\t";
            cout<<"\033[0;37m";
            if(count%5==0&&count!=0){
                cout<<endl;
            }
            count++;
        }
        cout<<endl;
    }
    else{
        cout<<"ls: can't open "<<path<<endl;
    }
}
//ls command with param
void ls_withparam(char*path,char *param){
    DIR*dir_ptr;
    struct stat statbuf;
    char datestring[256];
    char modestr[11];
    struct passwd *pwd;
    struct group *grp;
    struct tm*tm;
    struct dirent*direntp;
    int count=0;
    int cnt=0;
    if(path==NULL){
        dir_ptr=opendir(".");
    }else{
        dir_ptr=opendir(path);
    }
    if(dir_ptr!=NULL){
        while(direntp=readdir(dir_ptr)){
            
            if (strcmp(direntp->d_name,"..")==0||strcmp(direntp->d_name,".")==0)
            {
                continue;
            }
            if(stat(direntp->d_name,&statbuf)==-1){
                continue;
            }
            else
            {
                printf("%10.10s", getperm(modestr,statbuf));
                printf("%4ld", statbuf.st_nlink);

                /* 如果使用 getpwuid() 找到所有者的名称，则打印出所有者的名称。  */
                if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
                printf(" %-8.8s", pwd->pw_name);
                else
                printf(" %-8d", statbuf.st_uid);

                /* 如果使用 getgrgid() 找到组名，则打印出组名。 */
                if ((grp = getgrgid(statbuf.st_gid)) != NULL)
                printf(" %-8.8s", grp->gr_name);
                else
                printf(" %-8d", statbuf.st_gid);

                /* 打印文件的大小。  */
                printf(" %9jd", (intmax_t)statbuf.st_size);

                tm = localtime(&statbuf.st_mtime);

                /* 获取本地化的日期字符串。 */
                strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);

                printf(" %s %s\n", datestring, direntp->d_name);
            }
        }
        closedir(dir_ptr);
    }
    else{
        cout<<"ls: can't open "<<path<<endl;
    }
}  

//a ls used in redirection
void re_ls(){
    DIR*dir_ptr;
    struct dirent*direntp;
    int count=0;
    dir_ptr=opendir(".");
    if(dir_ptr!=NULL){
        while(direntp=readdir(dir_ptr)){
            if (strcmp(direntp->d_name,"..")==0||strcmp(direntp->d_name,".")==0)
            {
                continue;
            }
            cout<<direntp->d_name<<"\t";
            if(count%5==0&&count!=0){
                cout<<endl;
            }
            count++;
        }
        closedir(dir_ptr);
    }
    cout<<endl;
}
#endif

