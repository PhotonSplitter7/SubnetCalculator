#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
//4 octets to hold binary IP address thats converted
char addrString[16];
char maskString[16];

int ipAddress[4];
int subMask[4];
int firstAddr[4];
int lastAddr[4];
int gateway[4];
int broadcast[4];
int cidrNum = 0;
int sizeOfNetwork = 0;

int BinAddr [4][8];
int BinMask [4][8];




printf("Enter IP address:\n\n");
scanf("%s", addrString);//get user address
printf("Enter subnet mask:\n\n");
scanf("%s", maskString);// get subnet mask

//convert string to int
sscanf(addrString, "%d.%d.%d.%d", &ipAddress[0], &ipAddress[1],&ipAddress[2],&ipAddress[3]);
sscanf(maskString, "%d.%d.%d.%d", &subMask[0], &subMask[1],&subMask[2],&subMask[3]);



//compute binary IP address
for(int i = 0; i<4; i++){
for(int j = 0; j < 8; j++){
BinAddr[i][j]= ipAddress[i]%2;
ipAddress[i] = ipAddress[i]/2;
}
}

//compute binary subnet mask
for(int i = 0; i<4; i++){
for(int j = 0; j < 8; j++){
BinMask[i][j]= subMask[i]%2;
subMask[i] = subMask[i]/2;
}
}

//************************compute network addresses*****************



//calculate cidr num
 for(int r = 0; r< 4;r++){
for(int c = 0; c< 8; c++){
    if(BinMask[r][c] == 1){
        cidrNum++;
    }
}}

printf("\n\n CDR num is: %d\n\n\n", cidrNum);

//calculate size of network
sizeOfNetwork = (pow(2, (32 - cidrNum))-2);
printf("\nsize of network is %d\n", sizeOfNetwork);

//



//print binary string for mask
for(int j = 0; j< 4;j++){
for(int i = 0; i< 8; i++){
    printf("%d", BinMask[j][i]);
}
}

return 0;
}




