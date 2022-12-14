#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Helper functions*************************

int
pwr (int power)
{
  int num = 2;
  for (int i = 1; i < power; i++)
    {
      num = num * 2;
    }
  if (power == 0)
    return 1;
  return num;

}

void
printAddressDec (int address[4])
{
  for (int i = 0; i < 4; i++)
    {
      printf ("%d", address[i]);
      if (i < 3)
	printf (".");
    }
  return;
}

void
printAddressBin (int address[4][8])
{
  for (int j = 0; j < 4; j++)
    {
      for (int i = 0; i < 8; i++)
	{
	  printf ("%d", address[j][i]);
	}
      printf (".");
    }
  return;
}

//converts decimal IP to Binary
void
convertToBinary (int decimalAddr[4], int BinAddr[4][8])
{

  for (int i = 0; i < 4; i++)
    {
      for (int j = 7; j >= 0; j--)
	{
	  BinAddr[i][j] = decimalAddr[i] % 2;
	  decimalAddr[i] = decimalAddr[i] / 2;
	}
    }

  return;
}

int
getCIDRnum (int BinMask[4][8])
{
  int cidrNum = 0;

  for (int r = 0; r < 4; r++)
    {
      for (int c = 0; c < 8; c++)
	{
	  if (BinMask[r][c] == 1)
	    {
	      cidrNum++;
	    }
	}
    }
  return cidrNum;
}

//calculate decimal address from binary address
void
BinToDec (int decAddr[4], int binAddr[4][8])
{

  int sum = 0;			//adds up power of 2 to get decimal representation of binary octet
  int power = 7;		//power counts down for every column moved over

  for (int r = 0; r < 4; r++)
    {
      for (int c = 0; c < 8; c++)
	{
	  if (binAddr[r][c] == 1)
	    {
	      sum += pwr (power);

	    }			//add 2^power to sum
	  power--;		//power goes down 1 until end where its 2^0 for 1
	}

//once octet calculated above assign it to decimal gateway address
      decAddr[r] = sum;
      sum = 0;			//reset sum for next octet
      power = 7;		//reset power for next octet

    }

  return;
}

//function to calculate gateway from binary IP
void
IPtoGateway (int cidrNum, int IP[4][8], int Gateway[4][8])
{

  for (int r = 0; r < 4; r++)
    {
      for (int c = 0; c < 8; c++)
	{
	  if (((r * 8) + c) >= cidrNum)
	    {			//if dividing line reached only copy 0's into host bits
	      Gateway[r][c] = 0;
	    }
	  //if dividing line not met fill with network bits
	  else
	    {
	      Gateway[r][c] = IP[r][c];
	    }
	}
    }

  return;
}

//function to calculate broadcast from binary IP
void
IPtoBroadcast (int cidrNum, int IP[4][8], int Broadcast[4][8])
{

  for (int r = 0; r < 4; r++)
    {
      for (int c = 0; c < 8; c++)
	{
	  if (((r * 8) + c) >= cidrNum)
	    {			//if dividing line reached only copy 1's into host bits
	      Broadcast[r][c] = 1;
	    }
	  //if dividing line not met fill with network bits
	  else
	    {
	      Broadcast[r][c] = IP[r][c];
	    }
	}
    }

  return;
}

//gets ip for start address
void
getStartAddr (int gateway[4], int firstAddr[4])
{
  for (int i = 0; i < 4; i++)
    {
      firstAddr[i] = gateway[i];
    }
  firstAddr[3] += 1;		//next address to
  return;
}

//gets ip for last address
void
getEndAddr (int broadcast[4], int lastAddr[4])
{
  //copy broadcast address to last address
  for (int i = 0; i < 4; i++)
    {
      lastAddr[i] = broadcast[i];
    }
  //subtract 1 from broadcast address
  lastAddr[3] -= 1;
  return;
}

//main function*********************************

int
main ()
{
  int flag = 1;
  char val;

  while (flag == 1)
    {
//4 octets to hold binary IP address thats converted
      char addrString[16];
      char maskString[16];

      int ipAddress[4];
      int subMask[4];
      int firstAddr[4];
      int lastAddr[4];
      int gateway[4];		//all host bits are 0
      int broadcast[4];		//all host bits are 1
      int cidrNum = 0;
      int sizeOfNetwork = 0;

      int BinAddr[4][8];
      int BinMask[4][8];






      printf ("Enter your IP address:\n\n");
      scanf ("%s", addrString);	//get user address
      printf ("Enter your subnet mask:\n\n");
      scanf ("%s", maskString);	// get subnet mask

//convert string to int
      sscanf (addrString, "%d.%d.%d.%d", &ipAddress[0], &ipAddress[1],
	      &ipAddress[2], &ipAddress[3]);
      sscanf (maskString, "%d.%d.%d.%d", &subMask[0], &subMask[1],
	      &subMask[2], &subMask[3]);






//************************compute network addresses*****************

//compute binary IP address and binary subnet mask
      convertToBinary (ipAddress, BinAddr);
      convertToBinary (subMask, BinMask);

//calculate cidr num
      cidrNum = getCIDRnum (BinMask);

//calculate size of network
      sizeOfNetwork = pwr ( (32 - cidrNum));

//binary addresses for gateway and broadcast
      int gateWayBin[4][8];
      int broadcastBin[4][8];

//calculate binary gateway address from binary IP
      IPtoGateway (cidrNum, BinAddr, gateWayBin);
      IPtoBroadcast (cidrNum, BinAddr, broadcastBin);

//convert decimal gateway address from binary
      BinToDec (broadcast, broadcastBin);
      BinToDec (gateway, gateWayBin);

//calculate start and end IP address
      getStartAddr (gateway, firstAddr);
      getEndAddr (broadcast, lastAddr);

      printf ("\n");
      printf ("Network address:");
      printAddressDec (gateway);
      printf ("\n");
      printf ("Broadcast address:");
      printAddressDec (broadcast);
      printf ("\n");
      printf ("size of network:%d", sizeOfNetwork);
      printf ("\n");
      printf ("First usable IP address:");
      printAddressDec (firstAddr);
      printf ("\nLast usable IP address:");
      printAddressDec (lastAddr);
      printf ("\n");
      printf ("CIDR prefix: /%d\n", cidrNum);

//prompt user to go again
      printf ("\nDo you wish to continue? (y/n)\n");
      scanf (" %c", &val);
//if y selected loop continues
      if (val == 'y' || val == 'Y')
	{
	  flag = 1;
	}

      else
	{
	  flag = 0;
	}


}

return 0;
}
