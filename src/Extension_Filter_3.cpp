#include<iostream>
#include<dirent.h>
#include<fcntl.h>
#include <cstring>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#ifndef O_BINARY
#define O_BINARY 0
#endif
using namespace std;
int GetLength(char Path[]);
void FolderSort(char path[]);
char* GetExtension(char FilePath[]);
void ReverseWord(char *extension);
void FileCopy(char oldpath[],char newpath[]);
int main()
{
    int caseno;
    char path[256];
    cout<<"Enter the path of folder:-"<<endl;
    cin>>path;
    int length=GetLength(path);
    path[length-1]!='/'?  (path[length]='/', path[length+1]='\0') : path[length]='\0' ;
    FolderSort(path);
}
int GetLength(char Path[])
{
    int length=0;
    for(int i=0;Path[i]!='\0';i++)
    {
        length++;
    }
    return length;
}
void ReverseWord(char *extension)
{
    int length=GetLength(extension);
    for(int i=0;i<length/2;i++)
    {
        char temp=extension[i];
        extension[i]=extension[length-i-1];
        extension[length-i-1]=temp;
    }
}
char* GetExtension(char FilePath[])
{
    char* extension=new char[5];
    int length=GetLength(FilePath);
    for(int i=length-1;FilePath[i]!='.';i--)
    {
        extension[length-i-1]=FilePath[i];
    }
    ReverseWord(extension);
    return extension;
}
void FolderSort(char path[])
{
    DIR* directory;
    char* dirname;
    char* filename;
    char* extension;
    char* oldfilepath;
    char* newfilepath;
    struct dirent* dir;
    directory=opendir(path);
    if(directory)
    {
        
        while((dir=readdir(directory))!=NULL)
        {   
            if(!strcmp(dir->d_name,".") || !strcmp(dir->d_name,".."))
            {
                continue;
            }
            else 
            {
                dirname=new char[GetLength(dir->d_name)+1];
                filename=new char[GetLength(dir->d_name)];
                extension=new char[5];
                switch (dir->d_type)
                {
                    case DT_REG:
                        strcpy(filename,dir->d_name);
                        strcat(path,filename);
                        oldfilepath=new char[GetLength(path)];
                        strcpy(oldfilepath,path);
                        strcpy(extension,GetExtension(path));
                        path[GetLength(path)-GetLength(filename)]='\0';
                        mkdir(strcat(path,extension),0777);
                        strcat(path,"/");
                        strcat(path,filename);
                        newfilepath=new char[GetLength(path)];
                        strcpy(newfilepath,path);
                        FileCopy(oldfilepath,newfilepath);
                        remove(oldfilepath);
                        path[GetLength(path)-GetLength(extension)-GetLength(filename)-1]='\0';
                        break;
                    case DT_DIR:
                        strcpy(dirname,dir->d_name);
                        strcat(dirname,"/");
                        strcat(path,dirname);
                        FolderSort(path);
                        path[GetLength(path)-GetLength(dirname)]='\0';
                        break;
                    default:
                        break;
                }
                   
            }
            
        }
    }
    // delete [] dirname; 
    // delete [] filename;
    // delete [] extension;
    // delete [] oldfilepath;
    // delete [] newfilepath;

}
void FileCopy(char oldpath[],char newpath[])
{
    char buffer[4096];
    int inhnandle,outhandle,bytes;
    inhnandle=open(oldpath,O_BINARY);
    if(inhnandle==-1)
    {
        puts("Cannot open file\n");
        exit(1);
    }
    outhandle=open(newpath,O_CREAT | O_BINARY | O_WRONLY);
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
