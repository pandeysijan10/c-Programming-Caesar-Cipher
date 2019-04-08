/*Prepared for C-programming mini project
Authors:Sijan Pandey,Sinam Adhikari,Smaran Aryal, Sneha Neopane*/
//Implementation of Caesar cipher
#include<stdio.h>
#include<conio.h>

//opening page
int menu()
{
	int choice;
	printf("What do you want to do?\n");
	printf("1. Encrypt new information and save.\n");
	printf("2. Get already encrypted information in decrypted format.\n");
	printf("3. Exit.\n");
	printf("Enter your choice:");
	scanf("%d",&choice);
	return choice;
}

//function to convert key to shftkey
/*Prepare the shift number from user's pin using a formula.
Formula here adds each digit of entered PIN to create a single digit integer.*/
int getshiftkey(int key)
{
	int shiftkey=0;
	while(key!=0)
	{
		shiftkey=shiftkey+(key%10);
		key=key/10;
	}
	return shiftkey;
}

//encryption function
void encrypt(char string[10000],int shiftkey)
{
	FILE *fptr;
	int i;
	fptr=fopen("Encrypt.safe","w");
	/*Encryption:each letter in the entered string is shifted by
	shift key calculated before.
	A=65(ASCII code of A)
	eg:shift key=2
	then the letter A will be replaced by C i.e. A+2=C 65+2=67
	(67 is ASCII value of C.
	This process is done for every character in the string and the
	encrypted string is saved on a file.
	*/
	for(i=0;string[i]!='\0';i++)
	{
		string[i]=(string[i]+shiftkey);
		/*Special case:if the letter from string[i]+shiftkey exceeds limit 255
		i.e. final ASCII value then after 255 again starts from 0 and
		adds the shift key. Code for that is below.
		Eg if our limit is from A-Z Z+1 means again A.Z+2 means B.*/
		if(string[i]>255)// can be used for letter of 0 to 255 ASCII value.
			string[i]=string[i]-255-1;

	}
	fputs(string,fptr);
	clrscr();
	fclose(fptr);
}

//decryption function
void decrypt(char string[10000],int shiftkey)
{
	int i;
	/*Decryption: Shift key used to retrieve original data.
	Just reverse of encryption logic. Original data is (encrypted letter-shiftkey)
	Remember:encrypted data=original data+shift key*/
	for(i=0;string[i]!='\0';i++)
	{
		string[i]=string[i]-shiftkey;
		if(string[i]<0)
		string[i]=string[i]+255+1;
	}
	clrscr();
	printf("Your decrypted information is:\n\n%s",string);
	printf("\n\nPress any key to exit.");
	getch();
}

//main function
void main()
{
FILE *fptr,*fkey;
char string[10000],string2[10000]="A";
int key,key2,i;
int shiftkey,choice;
label:
clrscr();
//go to main menu function
choice= menu();
if(choice==1)
{
	fptr=fopen("Encrypt.safe","r");
	if(fptr==NULL)//work only if previously file has not been created else say user cannot encrypt new data
	{
		clrscr();
		printf("Enter the information to be encrypted below:\n");
		fflush(stdin);
		/*Get secret string info from user(can include character from all the
		ASCII codes.*/
		gets(string);
		fflush(stdin);
		//Get the secret PIN(numeric password) from user-can be of any length
		printf("Enter PIN[Only numeric value accepted]:");
		scanf("%d",&key);
		fkey=fopen("Key.safe","w");
		fwrite(&key,sizeof(key),1,fkey);//Save key to file Key.safe
		fclose(fkey);
		shiftkey=getshiftkey(key);
		encrypt(string,shiftkey);
		fclose(fptr);
		goto label;
	}
	else
	{
		fclose(fptr);
		printf("You have already saved your info. Select decryption option in the menu.");
		sleep(2);
		goto label;
	}
}

if(choice==2)
{
	fptr=fopen("Encrypt.safe","r");
	fkey=fopen("Key.safe","r");
	if(fptr!=NULL && fkey!=NULL){
		printf("Enter PIN:");
		scanf("%d",&key);
		fread(&key2,sizeof(key2),1,fkey);//get saved key from file key.safe
		fclose(fkey);
	if(key==key2){
		shiftkey=getshiftkey(key);
		fgets(string,sizeof(string),fptr);
		fclose(fptr);
		decrypt(string,shiftkey);
		}
	else{
		fclose(fptr);
		printf("\nPIN mismatch.");
		sleep(1);
		goto label;
		}
	}
	else
	{
	fclose(fptr);
	fclose(fkey);
	printf("File not found. First add some information to encrypt.");
	sleep(2);
	goto label;
	}
}

if(choice==3)
	printf("Press any key to exit.");
getch();
}
