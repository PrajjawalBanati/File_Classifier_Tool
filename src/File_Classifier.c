#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
//To store the path of the directory
char path[100];
//To store the extension of all the files
char c[100][100],d[100][100];
//Reference variable to store the extension
char *getext=NULL;
//Following function will be opening the files present in the directory
void direct(char path[]);
int main(void)
{
printf("File Manager\n");
printf("Enter the path of the directory:");
scanf("%s", path);
direct(path);
}
void direct(char path[])
{
//DIR is a typedef defined as a directory stream
DIR *d;
struct dirent *dir;
//Open the directory 
d=opendir(path);
if(d)
{
while((dir=readdir(d))!=NULL)
{
printf("%s\n",dir->d_name);
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