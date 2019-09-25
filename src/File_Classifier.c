#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
//To store the path of the directory
char path[100];
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
d=opendir(path);
if(d)
{
while((dir=readdir(d))!=NULL)
{
printf("%s\n",dir->d_name);
}
closedir(d);
}
}