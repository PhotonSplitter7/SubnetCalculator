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
int gateway[4];//all host bits are 0
int broadcast[4]; //all host bits are 1
int cidrNum = 0;
int hostBits = 0;
int sizeOfNetwork = 0;

int BinAddr [4][8];
int BinMask [4][8];

int IP[4];//perminent variables to store IP and Mask
int SUBNETMASK[4];




printf("Enter IP address:\n\n");
scanf("%s", addrString);//get user address
printf("Enter subnet mask:\n\n");
scanf("%s", maskString);// get subnet mask

//convert string to int
sscanf(addrString, "%d.%d.%d.%d", &ipAddress[0], &ipAddress[1],&ipAddress[2],&ipAddress[3]);
sscanf(maskString, "%d.%d.%d.%d", &subMask[0], &subMask[1],&subMask[2],&subMask[3]);

//copy IP and Mask for perminent storage
for(int i = 0; i<4; i++){
   IP[i] = ipAddress[i];
   SUBNETMASK[i] = subMask[i];
}





//compute binary IP address and binary subnet mask
for(int i = 0; i<4; i++){
for(int j = 0; j < 8; j++){
BinAddr[i][j]= ipAddress[i]%2;
ipAddress[i] = ipAddress[i]/2;
BinMask[i][j]= subMask[i]%2;
subMask[i] = subMask[i]/2;
}
}

//calculate hostBits
for(int r = 0; r<4; r++){
    for(int c = 0; c<8 ; c++){
        if(BinMask[r][c] == 0){hostBits++;}//count number of host bits
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

printf(" CIDR prefix: %d\n", cidrNum);

//calculate size of network
sizeOfNetwork = (pow(2, (32 - cidrNum))-2);
printf("\nsize of network is %d\n", sizeOfNetwork);

//calculate network address (gateway)
int gateWayBin[4][8];

for(int r = 0; r<4; r++){
    for(int c = 0; c<8; c++){
        if(((r*8)+c) >= cidrNum){//if dividing line reached only copy 0's into host bits
            gateWayBin[r][c] = 0;
        }
        //if dividing line not met fill with network bits
        else{
            gateWayBin[r][c] = BinAddr[r][c];
        }
    }
}

//print gateway address binary
printf("\ngateway Binary:");
for(int r = 0; r<4; r++){
    for(int c = 0; c<8; c++){
        printf("%d", gateWayBin[r][c]);
    }
}

printf("\n");









//print binary string for address
for(int j = 0; j< 4;j++){
for(int i = 0; i< 8; i++){
    printf("%d", BinAddr[j][i]);
}
}

printf("\n");

    //print binary string for mask
for(int j = 0; j< 4;j++){
for(int i = 0; i< 8; i++){
    printf("%d", BinMask[j][i]);
}
}

return 0;
}





