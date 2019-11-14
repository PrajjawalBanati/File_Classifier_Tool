#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
#include<math.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
char path[100];
char passedpath[100];
double data[100][100];
int a=0;
void readfile(char file1[],char file2[]);
void removeunwantedsymbols(char file[]);
int direct(char path[]);
int* calculate(int m,int n);
int compare(double javapercent,double cpercent);
void copyfile(char oldpath[],char newpath[]);
int main(void)
{
    int i=0,j,m=0,n=9;
    char name[30];
    int status;
    printf("Enter the path of the directory:\n(Don't forget to end the path with /)\n");
    scanf("%s",path);
    strcpy(passedpath,path);
    m=direct(path);
    int* number=calculate(m,n);
    FILE *fp;
    fp=fopen("E:/SEM V/Minor-I/src/file_name.txt","r");
    while(fscanf(fp,"%s",name)!=EOF)
    {
        char newpath[100];
         switch(number[i])
         {
             case 1: //printf("This is a Java File.\n");
             //printf("Making Java folder\n");
             strcpy(newpath,path);
             mkdir(strcat(newpath,"Java/"));
             copyfile(strcat(path,name),strcat(newpath,name));
             strcpy(path,passedpath);
             break;
             case 2: //printf("This is a c file\n");
             //printf("Making C folder\n");
             strcpy(newpath,path);
             mkdir(strcat(newpath,"C/"));
             copyfile(strcat(path,name),strcat(newpath,name));
             //remove(path);
             strcpy(path,passedpath);
             break;
             default: //printf("This is some another file\n");
             //printf("Making Others folder\n");
             strcpy(newpath,path);
             mkdir(strcat(newpath,"Others/"));
             copyfile(strcat(path,name),strcat(newpath,name));
             //remove(path);
             strcpy(path,passedpath);
             break;
        }
        i++;

     }


    return 0;
}
int direct(char path[])
{
    FILE *fp;
    DIR *d;
    int b=0;
    struct dirent *dir;
    fp=fopen("E:/SEM V/Minor-I/src/file_name.txt","w");
    d=opendir(path);
    if(d)
    {
        while((dir=readdir(d))!= NULL)
        {
                if(!strcmp(dir->d_name,"."))
                {
                    continue;
                }
                if(!strcmp(dir->d_name,".."))
                {
                    continue;
                }
                else
                {
                    char *name=(char *)malloc(50*sizeof(char));
                    strcpy(name,dir->d_name);
                    fprintf(fp,"%s\n",name);
                    strcat(path,name);
                    //printf("Opening %s\n",path);
                    removeunwantedsymbols(path);
                    strcpy(path,passedpath);
                    free(name);
                    b++;
                }
        }
        closedir(d);
    }
    fclose(fp);
    return b;
}

void removeunwantedsymbols(char file[])
{
    FILE *fp,*fp3;
    char ch;
    fp=fopen(file,"r");
    fp3=fopen("E:/SEM V/Minor-I/src/sample.txt","w");
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='(' || ch==')')
            {
                ch=' ';
            }
        putc(ch,fp3);
    }
    fclose(fp3);
    readfile("E:/SEM V/Minor-I/src/java.txt","E:/SEM V/Minor-I/src/sample.txt");
    remove("E:/SEM V/Minor-I/src/sample.txt");
}

void readfile(char file1[],char file2[])
{
    FILE *fp,*fp1;
    char ch[100],s[100];
    int j=0;
    double count=0;
    fp1=fopen(file1,"r");
    while(fscanf(fp1,"%s",ch)!=EOF)
    {
        count=0;
        fp=fopen(file2,"r");
        while(fscanf(fp,"%s",s)!=EOF)
        {
            if(strcmpi(ch,s)==0)
            {
                count++;
            }
        }
        data[a][j]=count;
        j++;
        fclose(fp);
    }
    fclose(fp1);
    a++;

}

int* calculate(int m,int n)
{
    int i,j,k=0;
    double temp=0;
    double javapercent=0,cpercent=0;
    double* normalized=(double *) malloc(m*sizeof(double));
    int* foldernumber=(int *) malloc(m*sizeof(int));
    int please[50];
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {

            if(data[i][j]!=0)
            {
                data[i][j]=1+log10(data[i][j]);
            }
             temp=temp+data[i][j]*data[i][j];
        }
        normalized[i]=sqrt(temp);
        temp=0;
    }
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            data[i][j]=data[i][j]/normalized[i];
        }
    }
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(j<4)
            {
                javapercent=javapercent+data[i][j];
            }
            if(j>=4)
            {
                cpercent=cpercent+data[i][j];
            }
        }
        foldernumber[k]=compare(javapercent,cpercent);
        javapercent=0;
        cpercent=0;
        k++;
    }
    return foldernumber;

}
int compare(double javapercent,double cpercent)
{
   if((javapercent-cpercent)>0 && (cpercent-javapercent)<0)
   {
      return 1;
   }
   if((javapercent-cpercent)<0 && (cpercent-javapercent)>0)
   {
       return 2;
   }
   if((javapercent-cpercent)==(cpercent-javapercent))
   {
        return 3;
   }

}
void copyfile(char oldpath[],char newpath[])
{
    char buffer[4096];
    int inhnandle,outhandle,bytes,result;
    inhnandle=open(oldpath,O_RDONLY | O_BINARY);
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
    result=remove(oldpath);
    if(result==-1)
    {
        perror("Error:\n");
    }

}

