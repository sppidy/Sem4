#include<stdio.h>
void gettrans(char code[],char trans[],char par,int n){
    for(int i=0;i<n;i++){
        trans[i]=code[i];
    }
    trans[n]=par;
}
int main(){
    int n;
    printf("Enter length of bit code : ");
    scanf("%d",&n);
    char code[n];
    printf("Enter bit code : ");
    scanf("%s",code);
    int ch1,ch2;
    printf("Enter choice of parity (even=1,odd=2) and (1 or 0) : ");
    scanf("%d %d",&ch1,&ch2);
    char trans[n+1];
    if(ch2==1){
        if(ch1==1){
            int c=0;
            for(int i=0;i<n;i++){
                if(code[i]=='1')  c++;
            }
            if(c%2==0){
                gettrans(code,trans,'0',n);
            }
            else{
                gettrans(code,trans,'1',n);
            }
        }
        else if(ch1==2){
            int c=0;
            for(int i=0;i<n;i++){
                if(code[i]=='1')  c++;
            }
            if(c%2!=0){
                gettrans(code,trans,'0',n);
            }
            else{
                gettrans(code,trans,'1',n);
            }
        }
        else{
            printf("Invalid Choice");
        }
    }
    else if(ch2==0){
        if(ch1==1){
            int c=0;
            for(int i=0;i<n;i++){
                if(code[i]=='0')  c++;
            }
            if(c%2==0){
                gettrans(code,trans,'1',n);
            }
            else{
                gettrans(code,trans,'0',n);
            }
        }
        else if(ch1==2){
            int c=0;
            for(int i=0;i<n;i++){
                if(code[i]=='0')  c++;
            }
            if(c%2!=0){
                gettrans(code,trans,'1',n);
            }
            else{
                gettrans(code,trans,'0',n);
            }
        }
        else{
            printf("Invalid Choice");
        }
    }
    printf("%s",trans);
   
    char rec[n+1];
    printf("Enter Recieved data : ");
    scanf("%s",rec);
    if(trans[n]!=rec[n]){
        printf("Error");
    }
    else{
        if(ch2==1){
            if(ch1==1){
                int c=0;
                for(int i=0;i<n+1;i++){
                    if(rec[i]=='1')  c++;
                }
                if(c%2==0){
                    printf("No Error");
                }
                else{
                    printf("Error");
                }
            }
            else if(ch1==2){
                int c=0;
                for(int i=0;i<n+1;i++){
                    if(rec[i]=='1')  c++;
                }
                if(c%2!=0){
                    printf("No Error");
                }
                else{
                    printf("Error");
                }
            }
            else{
                printf("Invalid Choice");
            }
        }
        else if(ch2==0){
            if(ch1==1){
                int c=0;
                for(int i=0;i<n+1;i++){
                    if(rec[i]=='0')  c++;
                }
                if(c%2==0){
                    printf("No Error");
                }
                else{
                    printf("Error");
                }
            }
            else if(ch1==2){
                int c=0;
                for(int i=0;i<n+1;i++){
                    if(rec[i]=='0')  c++;
                }
                if(c%2!=0){
                    printf("No Error");
                }
                else{
                    printf("Error");
                }
            }
            else{
                printf("Invalid Choice");
            }
    }
}