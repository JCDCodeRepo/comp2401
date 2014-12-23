-----------------------------------------------
COMP 2401 - Christine Laurendau - Assignment 1
-----------------------------------------------

Author
------
John Diyala (Student #: 100939721)

PURPOSE
--------
To provide the end user with the ability to encrypt and decrypt messages with a key, using the encryption/decryption algorithm provided.
The user can either encrypt a plain text message by providing the message and a key, or the user can decrypt a cipher text message provided they have the correct key.
(otherwise the message will make no sense)

COMPILATION COMMAND
-------------------
gcc -Wall -o A1_John_Diyala -std=c99 A1_John_Diyala.c -lm

LAUNCHING AND OPERATING INSTRUCTIONS
------------------------------------
1- launch command:  ./A1_John_Diyala 
2- Press 1 or 2 then Return depending on whether you want to encrypt or decrypt.
3- Enter plain/cipher text. (If you are decrypting, make sure to add a ' -1' to the end of the cipher text)
4- Enter proper key.

FUN AND CREATIVE ADDITIONAL FEATURES
------------------------------------
on lines 22 and 23 of the code, there exist two variables :   

  short int sickMode = 0;
  short int cowboyMode = 0;

they are both set to 0 by default, but setting either of them to 1 will result in an output that should have been decrypted to look like this:

"How many programmers does it take to change a light bulb? None – It’s a hardware problem"

to look like this:

"How *cough* many *sniff* programmers *cough* does *cough* *ACHOOOO* it take to *cough* change *cough* a light *sniff* bulb?
None *sniff* – *sniff* It’s *ACHOOOO* a *ACHOOOO* hardware *ACHOOOO* problem"

or this:

"How many programmers does it take to change a light -YEEEHAW- bulb? -YEEEHAW- None – -YEEEHAW- It’s a hardware problem"

*set BOTH of them equal to 1 if you're feeling really adventuruous.

