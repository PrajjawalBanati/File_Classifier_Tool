#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
char path[100],passed[100];
char *getext=NULL;
char* getextension(struct dirent *dir);
void copyfile1(char oldpath[],char newpath[]);
void extensionfilter();
int direct(char path[]);
int main(void)
{
printf("File Manager\n");
printf("Enter the path of the directory:(End the path with /)");
scanf("%s", path);
strcpy(passed,path);
extensionfilter();
}
void extensionfilter()
{
    DIR *d;
    struct dirent *dir;
    //Open the directory
    d=opendir(path);
    if(d)
    {
        while((dir=readdir(d))!= NULL)
        {
            getext=getextension(dir);
            //if there is only a "." in the file name like in case of folders
            if(!strcmp(getext,"."))
            {
                continue;
            }
            else
            {
                char p[100];
                strcpy(p,path);
                mkdir(strcat(p,getext));
                strcat(p,"/");
                copyfile1(strcat(path,dir->d_name),strcat(p,dir->d_name));
                remove(path);
                strcpy(path,passed);
            }
        }
    }
    closedir(d);
}
char* getextension(struct dirent *dir)
{
int k;
char *ext;
//strchr function returns the string after the . character
ext=strrchr(dir->d_name,46);
if(!ext)
{
printf("No extension.\n");
}
else
{
//returns the string
return ext;
}
}
void copyfile1(char oldpath[],char newpath[])
{
    char buffer[4096];
    int inhnandle,outhandle,bytes;
    inhnandle=open(oldpath,O_RDONLY | O_BINARY);
    if(inhnandle==-1)
    {
        puts("Cannot open file\n");
        exit(1);
    }
    outhandle=open(newpath,O_CREAT | O_BINARY | O_WRONLY,S_IWRITE);
    if(outhandle==-1)
    {
        printf("Cannot open file");
        close(inhnandle);
        exit(2);
    }
    while(1)
    {
        bytes=read(inhnandle,buffer,4096);
        if(bytes>0)
        {
            write(outhandle,buffer,bytes);
        }
        else
        {
             break;
        }
    }
    close(inhnandle);
    close(outhandle);
}
