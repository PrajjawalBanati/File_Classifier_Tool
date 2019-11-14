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
int getnumber(char *extension);
void copyfile1(char oldpath[],char newpath[]);
void extensionfilter();
int direct(char path[]);
int main(void)
{
printf("File Manager\n");
printf("Enter the path of the directory:(End the path with /)");
scanf("%s", path);
//To conserve value of path
strcpy(passed,path);
extensionfilter();
}
void extensionfilter()
{
    DIR *d;
    struct dirent *dir;
    int number;
    d=opendir(path);
    if(d)
    {
        while((dir=readdir(d))!= NULL)
        {
            getext=getextension(dir);
            if(!strcmp(getext,"."))
            {
                continue;
            }
            else
            {
                number=getnumber(getext);
                switch(number)
                {
                    case 1:strcat(path,"Documents/");
                    char newpath[100];
                    strcpy(newpath,path);
                    mkdir(newpath);
                    strcpy(path,passed);
                    copyfile1(strcat(path,dir->d_name),strcat(newpath,dir->d_name));
                    remove(path);
                    strcpy(path,passed);
                    break;
                    case 2: strcat(path,"Programs/");
                    strcpy(newpath,path);
                    mkdir(newpath);
                    strcpy(path,passed);
                    copyfile1(strcat(path,dir->d_name),strcat(newpath,dir->d_name));
                    remove(path);
                    strcpy(path,passed);
                    break;
                    case 3: strcat(path,"Codes/");
                    strcpy(newpath,path);
                    mkdir(newpath);
                    strcpy(path,passed);
                    copyfile1(strcat(path,dir->d_name),strcat(newpath,dir->d_name));
                    remove(path);
                    strcpy(path,passed);
                    break;

                }
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
int getnumber(char *extension)
{
    int number=0;
    char ext[10];
    FILE *fp,*fp1,*fp2;
    fp=fopen("E:/SEM V/Minor-I/src/Documents.txt","r");
    while(fscanf(fp,"%s",ext)!=EOF)
    {
        if(!strcmp(extension,ext))
        {
            number=1;
            rewind(fp);
            break;
        }
    }
    fclose(fp);
    fp1=fopen("E:/SEM V/Minor-I/src/Programs.txt","r");
    while(fscanf(fp1,"%s",ext)!=EOF)
    {
        if(!strcmp(extension,ext))
        {
            number=2;
            rewind(fp1);
            break;
        }
    }
    fclose(fp1);
    fp2=fopen("E:/SEM V/Minor-I/src/Codes.txt","r");
    while(fscanf(fp2,"%s",ext)!=EOF)
    {
        if(!strcmp(extension,ext))
        {
            number=3;
            rewind(fp2);
            break;
        }
    }
    fclose(fp2);
    return number;

}
