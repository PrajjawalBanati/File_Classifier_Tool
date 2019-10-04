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
//Function which return the extension of the file
char* getextension(struct dirent *dir);
//Following function will be opening the files present in the directory
int direct(char path[]);
//Following function will fetch the unique extensions from the array
int getuniqueextension(int m)
int main(void)
{
int m,k;
printf("File Manager\n");
printf("Enter the path of the directory:");
scanf("%s", path);
m=direct(path);
k=getuniqueextension(m);
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
