#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
//To store the path of the directory
char path[100];
//To store the extension of all the files
char c[100][100],d[100][100];
//Reference variable to store the extension
char *getext=NULL;
//Function which return the extension of the file
char* getextension(struct dirent *dir);
//Following function will be opening the files present in the directory
int direct(char path[]);
//Following function will fetch the unique extensions from the array
int getuniqueextension(int m);
//Copy function
void copy(char parentpath[],char newpath[],char extension[]);
int main(void)
{
int m,k,i;
char passedpath[100];
printf("File Manager\n");
printf("Enter the path of the directory:");
scanf("%s", path);
strcpy(passedpath,path);
m=direct(path);
k=getuniqueextension(m);
for(i=0;i<k;i++)
    {
        //Current Dircetory in which all the separataed files can be stored
        char p[100]="C:/Users/Prajjawal Banati/Documents/";
        //Making a directory
        mkdir(strcat(p,d[i]));
        //Calling the Copy function to copy the file from one path to another
        copy(strcat(path,"/"),strcat(p,"/"),d[i]);
        //Copying the pre-input path given by the user to conserver the value of it.
        strcpy(path,passedpath);

    }
}
int direct(char path[])
{
//DIR is a typedef defined as a directory stream
DIR *d;
int i=0;
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
//copy the extension in 2-D array c[100][100]
strcpy(c[i],getext);
//Iterate to next address
i++;
}
}
//After the loop is ended directory is closed
closedir(d);
}
return i;
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
//Will get the number of unique extensions present in the directory
int getuniqueextension(int m)
{
int i,j,k=0;
for(i=0;i<m;i++)
{
for(j=0;j<i;j++)
{
if(strcmpi(c[i],c[j])==0)
{
break;
}
}
if(i==j)
{
strcpy(d[k],c[i]);
k++;
}
}
return k;
}
void copy(char parentpath[],char newpath[],char extension[])
{
    DIR *d;
    char buffer[4096],parentfile[50],newffile[50];
    struct dirent *dir;
    int inhnandle,outhandle,bytes;
    d=opendir(path);
    strcpy(parentfile,parentpath);
    strcpy(newffile,newpath);

    if(d)
    {
        while((dir=readdir(d))!=NULL)
        {
            if(!strcmpi(extension,getextension(dir)))
            {
                inhnandle=open(strcat(parentpath,dir->d_name),O_RDONLY | O_BINARY);
                if(inhnandle==-1)
                {
                    puts("Cannot open file\n");
                    exit(1);
                }
                outhandle=open(strcat(newpath,dir->d_name),O_CREAT | O_BINARY | O_WRONLY,S_IWRITE);
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
                remove(parentpath);
                strcpy(parentpath,parentfile);
                strcpy(newpath,newffile);

            }
        }
    }
    closedir(d);
}
