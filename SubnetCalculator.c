#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
//4 octets to hold binary IP address thats converted
char addrString[16];
char maskString[16];
int inputAddress[4];//holds 4 octets need to seperate by decimals
int inputMask[4];
int BinAddr [4][8];
int BinMask [4][8];

int cdrNum = 0;
int numNets = 0;

printf("Enter IP address:\n\n");
scanf("%s", addrString);//get user address
printf("Enter subnet mask:\n\n");
scanf("%s", maskString);// get subnet mask

//convert string to int
sscanf(addrString, "%d.%d.%d.%d", &inputAddress[0], &inputAddress[1],&inputAddress[2],&inputAddress[3]);
sscanf(maskString, "%d.%d.%d.%d", &inputMask[0], &inputMask[1],&inputMask[2],&inputMask[3]);

//fill binary address array with 1's or 0's
for(int i = 0; i<4; i++){
for(int j = 0; j < 8; j++){
BinAddr[i][j]= inputAddress[i]%2;
inputAddress[i] = inputAddress[i]/2;
}
}

for(int j = 0; j< 4;j++){
for(int i = 0; i< 8; i++){
    printf("%d", BinAddr[j][i]);

}
}









return 0;
}


