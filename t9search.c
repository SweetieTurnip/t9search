#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
/*
*  Error code:
*  1 - arguments fault
*  2 - string is too big fault
*  3 - 'number' is not a number fault
*/

#define MAX_LENGTH 100

//function to find the length of string
int length(char *str)
{
    int length = 0;
    while (str[length] != '\0') length++;
    return length;
}

//make string to lower case
void toLowerCase(char *str)
{
    for(int i = 0;str[i] != '\0'; i++)
    {
        str[i] = tolower(str[i]);
    }
}

//if found 'substring' 
bool isFound(char *str1, char *str2)
{
    int lenR = length(str1) - length(str2);
	for(int i=0;i<=lenR;i++)
	{
		for(int j=0;;j++)
		{
			if (str2[j]=='\0') return true;
			if (str1[i+j]!=str2[j]) break; 
		}
	}
	return false; 
}

//if found 'substring' for -s
bool isFounds(char *str1, char *str2) 
{
    int k = 0;
    int len = length(str1);
    for(int i = 0; i<=len; i++) 
    {
        for(int j = 0;;j++)
        {
            if(str1[i+j] == '\0') return false;
            if(str1[i+j] == str2[k]) k++;    //save last position of str2
            else break;
            if(str2[k] == '\0') return true;
        }
    }
    return false;
}

//if found 'substring' for -l 
bool isFoundX(char *str1, char *str2)
{
	for(int i=0;i<=length(str1)-length(str2);i++)
	{
		for(int j=0;;j++)
		{
			if (str2[j]=='\0') return true;
			if (str1[i+j]!=str2[j] && str2[j]!='X') break; //X - is a char of replaced letter
		}
	}
	return false; 
}

//check if string consists numbers
bool consistsNums(char *str)
{
    for (int i = 0; i < length(str); i++)
    {
        if (str[i] < '0' || str[i] > '9') return false; 
    }
    return true;
}
//check if is phone number
bool isPhoneNumber(char *str) 
{
    for(int i = 0;; i++) 
    {
        if(str[i] == '\0') return true;
        if(i == 0)
        {
            if(str[i] == '+') continue; //if number consider first char '+' it is number too
        }
        if(str[i] < '0' || str[i] > '9') return false;
    }
}
//function for getting name/number from stdin
int inputString(char *str) 
{
    int i = 0, c;
    while(true) 
    {
        c = getchar();
        if(c == '\n' || c == EOF) 
        {
		    str[i] = '\0';
		    return c;
        }
        if(i > MAX_LENGTH) return 2;  // if string is too big
        str[i++] = c;
    }
}

//change characters to numbers
void toNums(char *str) 
{
    for(int i = 0; i < length(str); i++) 
    {
        if(str[i] == 'a' || str[i] == 'b' || str[i] == 'c') str[i] = '2';   
        else if(str[i] == 'd' || str[i] == 'e' || str[i] == 'f') str[i] = '3';
        else if(str[i] == 'g' || str[i] == 'h' || str[i] == 'i') str[i] = '4';
        else if(str[i] == 'j' || str[i] == 'k' || str[i] == 'l') str[i] = '5';
        else if(str[i] == 'm' || str[i] == 'n' || str[i] == 'o')  str[i] = '6';
        else if(str[i] == 'p' || str[i] == 'q' || str[i] == 'r' || str[i] == 's') str[i] = '7';
        else if(str[i] == 't' || str[i] == 'u' || str[i] == 'v') str[i] = '8';    
        else if(str[i] == 'w' || str[i] == 'x' || str[i] == 'y' || str[i] == 'z') str[i] = '9'; 
        else if(str[i] == '+') str[i] = '0';    
    }
}
//copy string without char in position n
void copyStrWithoutChar(char *str1, char *str2, int n)
{
	int i,j;
	i = 0, j = 0;
	while(true)
	{
		if (str2[j]=='\0') break;
		if (j==n) j++; //do not copy
		else str1[i++] = str2[j++];
	}	
	str1[i]='\0';
}
//if user missed letters 
bool isMissed(char *str1, char *str2, int l)
{
    char newStr[MAX_LENGTH + 1];
    int len1 = length(str1);
    //condition for breaking recursion
    if(l <= 0)
    {
        if(isFoundX(str1, str2)) return true; //find substring with replaced char
        else return false;    
    }
    for(int i = 0; i < len1; i++)
    {
        copyStrWithoutChar(newStr, str1, i); // delete char in position i
        if(isMissed(newStr, str2, l-1)) return true; //found.  l - max quantity of missed char
    }
    return false;
}
//if user add extra letters 
bool isAddExtra(char *str1, char *str2, int l)
{
    char newStr[MAX_LENGTH + 1];
    int len2 = length(str2);
    //condition of breaking recursion
    if(l <= 0)
    {
        if(isFoundX(str1, str2)) return true;  //find substring with replaced char
        else return false;   
    }
    for(int i = 0; i < len2; i++)
    {
        copyStrWithoutChar(newStr, str2, i); //delete char in position i
        if(isAddExtra(str1, newStr, l-1)) return true; //found. l - max quantity of extra char
    }
    return false;
}
//if user write wrong letters
bool isReplaced(char *str1, char *str2, int l)
{
    char newStr[MAX_LENGTH + 1];
    int len2 = length(str2);
    //condition of breaking recursion 
    if(l <= 0)
    {
        if(isFoundX(str1, str2)) return true;   //find substring with replaced char
        else return false;   
    }
    for(int i = 0; i < len2; i++)
    {
        strcpy(newStr, str2);
        newStr[i] = 'X'; //change char to 'X' in position i
        if(isReplaced(str1, newStr, l-1)) return true; // found. l - max quantity of changed char
    }
    return false;
}

int main(int argc, char* argv[])
{
    char name[MAX_LENGTH + 1], number[MAX_LENGTH + 1]; //variables for name and number
    char newName[MAX_LENGTH + 1], newNumber[MAX_LENGTH + 1]; //variables to copy name and number
    int c1, c2; //variables of input
    bool happened = false; //for writing 'Not found'
    bool sFlag = false, lFlag = false; //flags of arguments -s -l
    int levD; //variable for argument L
    char srchStr[MAX_LENGTH + 1]; //variable for argument search
    srchStr[0] = '\0';
    //read arguments
    for(int i = 1; i < argc; i++) 
    {
        if(strcmp(argv[i], "-s") == 0 && i == 1) sFlag = true;
        else if(strcmp(argv[i], "-l") == 0) 
        {
            lFlag = true;
            if((++i < argc) && (consistsNums(argv[i]))) levD = atoi(argv[i]);
            else
            {
                fprintf(stderr, "Argument L for -l is wrong or do not exists\n");
                return 1;
            }
        }
        else
        {
            if(srchStr[0] != '\0')
            {
                fprintf(stderr, "Argument is already defined\n");
                return 1;
            }
            strcpy(srchStr, argv[i]);
            if(!consistsNums(srchStr)) 
            {
                fprintf(stderr, "Argument is not consists numbers: %s\n", srchStr);
                return 1;
            }
        } 
    }
    //faults of arguments
    if(srchStr[0] == '\0' && sFlag) 
    {
        fprintf(stderr, "-s whithout argument\n");
        return 1;
    }
    if(srchStr[0] == '\0' && lFlag) 
    {
        fprintf(stderr, "Do not exists searching argument for -l\n");
        return 1;
    }
    if(sFlag && lFlag)
    {
        fprintf(stderr, "Can not be -s and -l together\n");
        return 1;
    }

    c1 = 0, c2 = 0; 
    while(true)
	{   
        //check if 'name' is not 'empty'
        while(true) 
        {
            c1 = inputString(name);
            if(c1 == 2) 
            {
                fprintf(stderr, "Name is too big\n");
                return 2; 
            }
			if (c1==EOF || length(name)>0) break; //found not empty string
        }
        //check if 'number' is not 'empty'
        while(true) 
        {
            c2 = inputString(number);
            if(c2 == 2) 
            {
                fprintf(stderr, "Number is too big\n");
                return 2;
            }
			if (c2==EOF || length(number)>0) break; //found not empty string
        }
        if(length(name) > 0 && length(number) > 0)
        {
            //check if 'number' is phone number
	        if(!isPhoneNumber(number))
            {
                fprintf(stderr, "Is not a number %s\n", number);
                return 3;
            } 
	        toLowerCase(name); //make name to lower case
            strcpy(newNumber, number); //copy number to newNumber
            toNums(newNumber); //change if exist in number first char '+' to '0'
            strcpy(newName, name); //copy name to newStr for checking substring
            toNums(newName); //replaces letters in newStr to nums for checking substring

            //if argc < 2 write all contacts
            if(argc < 2) 
            {
                printf("%s, %s\n", name, number);
                happened = true;
            }
            //if in argument -s
            else if(sFlag)
            {
                if(isFounds(newName, srchStr) || isFounds(newNumber, srchStr))
                {
                    printf("%s, %s\n", name, number);
                    happened = true;
                }
            }
            //if in argument -l
            else if(lFlag)
            {    
                if(isReplaced(newName, srchStr, levD) || isReplaced(newNumber, srchStr, levD))
                {
                    printf("%s, %s\n", name, number);
                    happened = true;
                }  
                else if(isMissed(newName, srchStr, levD) || isMissed(newNumber, srchStr, levD))
                {
                    printf("%s, %s\n", name, number);
                    happened = true;
                }
                else if(isAddExtra(newName, srchStr, levD) || isAddExtra(newNumber,srchStr, levD))
                {
                    printf("%s, %s\n", name, number);
                    happened = true;
                }
            }
            //if in file exist argument of search
            else if(isFound(newName, srchStr) || isFound(newNumber, srchStr))
            {
                printf("%s, %s\n", name, number);
                happened = true;
            }

	    }
        //condition of breaking cyclus
        if(c1 == EOF || c2 == EOF) break;
    }
    if(!happened) printf("Not found\n"); //if not find a name and number print 'Not found'
    return 0;
}    