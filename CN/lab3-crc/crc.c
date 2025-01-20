#include<stdio.h>  
#include<string.h>  
#define N strlen(gen_poly)  

char data[28];  
char check_value[28];  
char gen_poly[10];  
int data_length,i,j;  

void XOR() {
    for (j = 1; j < N; j++) {
        if (check_value[j] == gen_poly[j])
            check_value[j] = '0';
        else
            check_value[j] = '1';
    }
}  
void crc(){  
    for(i=0;i<N;i++)  
        check_value[i]=data[i];  
    do{  
        if(check_value[0]=='1')  
            XOR();  
        for(j=0;j<N-1;j++)  
            check_value[j]=check_value[j+1];  
        check_value[j]=data[i++];  
        printf("Partial remainder: %s\n", check_value);
    }while(i<=data_length+N-1);  
}  
void receiver() {  
    printf("\nEnter the received data: ");  
    scanf("%s", data);  
    printf("Data received: %s\n", data);  
    crc();  
   
    printf("\nCRC: %s\n", check_value);  
   
    for(i = 0; (i < N - 1) && (check_value[i] != '1'); i++);
    if(i < N - 1)  
        printf("\nError detected\n");  
    else  
        printf("\nNo error detected\n\n");  
}
 
 
 
int main()  
{  
    printf("\nEnter data to be transmitted: ");  
    scanf("%s",data);  
    printf("Enter the divisor: ");  
    scanf("%s",gen_poly);  
    data_length=strlen(data);  
    for(i=data_length;i<data_length+N-1;i++)  
        data[i]='0';  
    crc();  
    printf("CRC: %s",check_value);  
    for(i=data_length;i<data_length+N-1;i++)  
        data[i]=check_value[i-data_length];  
    printf("\nCodeword: %s\n",data);  
    receiver();  
    return 0;  
}