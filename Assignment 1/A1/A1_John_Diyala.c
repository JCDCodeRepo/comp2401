#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_BUF  400

unsigned char getBit(unsigned char, int);
unsigned char setBit(unsigned char, int);
unsigned char clearBit(unsigned char, int);
unsigned char encode(unsigned char, unsigned char, int);



int main()
{
  char str[8];
  char enter;
  char input[1000];
  int  choice, key, i;

  //fun and creative additional features
  short int sickMode = 0;
  short int cowboyMode = 0;

  //variables needed for the additional features
  int atoi ( const char * str );
  int rand (void);
  int srand ();
  srand (time(NULL));

  printf("\nYou may:\n");
  printf("  (1) Encrypt a message \n");
  printf("  (2) Decrypt a message \n");
  printf("\n  What is your selection: ");
  fgets(str, sizeof(str), stdin);
  sscanf(str, "%d", &choice);

  //basic input checking
  if (choice != 1 && choice != 2){
	  printf("\n Invalid input. Please enter 1 or 2.\n");
	  printf("\n  what is your selection: ");
	  fgets(str, sizeof(str), stdin);
	  sscanf(str, "%d", &choice);
  }

  switch (choice) {

    case 1:
	//Encryption

	//Get input in plain text format
	printf("\nEnter a plaintext message:  ");
	fgets(input, sizeof(input), stdin);	

	//Get key in proper format
	printf("\nEnter a numerical key <= 255 and >=0:  ");
	while(scanf("%d%c", &key, &enter) != 2 || enter != '\n' || key > 255 || key <= 0)
		printf("\nEnter a numerical key <= 255 and >=0:  ");
	
	//Encrypt the input using the key and the encryption algorithm
	i = 0;
	while (input[i+1] != 0){
		printf ("%d ", encode(input[i], key, i));
		i++;
	}

      break;

    case 2:
	//Decryption

	//Get input in cipher text format
	printf("\nEnter ciphertext:  ");
	fgets(input, sizeof(input), stdin);	

	//Get key in proper key format
	printf("\nEnter the key:  ");
	while(scanf("%d%c", &key, &enter) != 2 || enter != '\n' || key > 255 || key <= 0)
		printf("\nThe key has to be an integer <= 255 and >=0:  ");

	int temp;
	char * parsedInt;

	parsedInt = strtok (input," ");
	temp = atoi(parsedInt);
	i=0;

	//Parse, convert to int, encode, print as char until -1 (the end) is reached.
	do{
		if (sickMode){
			if (encode(temp,key,i) == ' '){
				if (rand() % 7 == 1)
					printf (" *cough*");
				if (rand() % 20 == 1)
					printf (" *ACHOOOO*");
				if (rand() % 9 == 1)
					printf (" *sniff*");
			}
		}
		if (cowboyMode){
			if (encode(temp,key,i) == ' '){
				if (rand() % 5 == 1)
					printf (" -YEEEHAW-");
			}
		}
		printf ("%c", encode(temp,key,i));
		i++;
		parsedInt = strtok (NULL, " ");
		temp = atoi(parsedInt);
	} while (temp != -1);

      break;

    default:

      break;
  }

  return 0;
}


unsigned char encode(unsigned char pt, unsigned char key, int count)
{

int bit_i;
unsigned char result = pt;
//If the source bit xor the key bit is zero, set the same bit in the resulting byte to zero 
//If the source bit xor the key bit is one, set the same bit in the resulting byte to one

	//Counter % 3 = 0 - Examine every other bit of both the source and key bytes, starting at bit 0
	if (count % 3 == 0){
		for (bit_i = 0; bit_i <= 7; bit_i +=2){
			//If source xor key = 0 at bit i, result = 0 at bit i 
			if ((getBit(pt,bit_i ) ^ getBit(key,bit_i)) == 0)
				result = clearBit(result,bit_i); 
			//If source xor key = 1 at bit i, result = 1 at bit i 
			else 
				result = setBit(result,bit_i);
		}
	}
	//Counter % 3 = 1 - Examine every other bit of both the source and key bytes, starting at bit 1
	else if (count % 3 == 1){
		for (bit_i = 1; bit_i <= 7; bit_i +=2){
			//If source xor key = 0 at bit i, result = 0 at bit i 
			if ((getBit(pt,bit_i ) ^ getBit(key,bit_i)) == 0)
				result = clearBit(result,bit_i); 
			//If source xor key = 1 at bit i, result = 1 at bit i 
			else 
				result = setBit(result,bit_i);
		}
	}
	//Counter % 3 = 2 - Examine every bit of both the source and key bytes, starting at bit 0
	else{
		for (bit_i = 0; bit_i <= 7; bit_i ++){
			//If source xor key = 0 at bit i, result = 0 at bit i 
			if ((getBit(pt,bit_i ) ^ getBit(key,bit_i)) == 0)
				result = clearBit(result,bit_i); 
			//If source xor key = 1 at bit i, result = 1 at bit i 
			else 
				result = setBit(result,bit_i);
		}
	}

	return result;

}

/*
  Function:  getBit
  Purpose:   return the value of specified bit
       in:   character from which a bit will be returned
       in:   position of bit to be returned
   return:   value of bit n in character c (0 or 1)
*/ 	
unsigned char getBit(unsigned char c, int n)   
{ 
	return (c & (1 << n)) >> n;
}

/*
  Function:  setBit
  Purpose:   set specified bit to 1
       in:   character in which a bit will be set to 1
       in:   position of bit to be set to 1
   return:   new value of character c with bit n set to 1
*/
unsigned char setBit(unsigned char c, int n)   
{ 
	return c = c | (1 << n);
}

/*
  Function:  clearBit
  Purpose:   set specified bit to 0
       in:   character in which a bit will be set to 0
       in:   position of bit to be set to 0
   return:   new value of character c with bit n set to 0
*/
unsigned char clearBit(unsigned char c, int n) 
{ 
	return c = (c & (~(1 << n)));
}




