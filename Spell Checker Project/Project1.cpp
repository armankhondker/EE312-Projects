// SpellCheck <Project1.cpp>
// EE 312 Project 1 submission by 2/4/18
// Arman Khondker
// aak2464
// Slip days used: <0>
// Spring 2018


#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I *insist* that you indent
 * reasonably and consistently in your code. I strongly encourage you to avoid big functions
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */

/*     *****Function isLetter*****
 * Input: A single char
 * Outputs: 0 (FALSE) if the char is not a letter
 *          1 (TRUE) if the char is a letter
 */

int inAlphabet(char letter)
{   if(((letter > 0x60 && letter < 0x7B)||(letter<0x5B && letter > 0x40 ))== 0)  //checks to see if is not in Alphabet
    {
        return 0;         //False
    }
    else
    {
        return 1;         //True
    }
}

/*      *****Function printWord*****
 * Input: A char pointer to a word that is null terminated
 * Output: Prints the input to console
 */

void printWord(char* word)
{
    printf("%s\n",word);     //prints the word with a new line escape sequence
}

/*     *****Function inDictionary*****
 * Inputs: The char pointer to the dictionary, the length of a word, the word that we are checking
 * Outputs: Prints the word given ONLY if it is not in the dictionary
 */

void inDictionary(char dictionary[], int length, char* word)
{
    int i =0;        //index of dictionary
    int j= 0;        //index of word
    int flag =0;          //flag to determine whether or not we print out the word beacuse it is mispelled
    int dictionaryWordLength=0;

    while(dictionary[i]!=0)
    {
        j=0;                                //reset j every time
        dictionaryWordLength=0;             //reset the comparison dictionary word length every time
        int actualDictionaryWordLength=0;     /* need to use and increment this variable so that edge case is passed
                                              this is the actual length of the current word in dictionary */

        while (dictionary[i] != '\n')           //continue until the end of a dictionary word
        {

            if (dictionary[i] == word[j] || dictionary[i] == word[j] + 0x20 || dictionary[i] == word[j]-0x20)  //checks to see if same letter regardless of uppercase or lowercase
            {
                i++;
                j++;
                dictionaryWordLength++;
            }
            else
            {
                i++;             //very important to increment here or else will get stuck
            }

            actualDictionaryWordLength++;  //need to use and increment this variable so that edge case is passed


            if(dictionaryWordLength==length && actualDictionaryWordLength==length)     //if same length, then it is in dictionary
            {
                flag = 1;                        //Flag set to indicate it is in the dictionary
            }

        }
         i++;

    }

   if(flag==0)                         //this means word is not in dictionary, therefore print it
    {
        printWord(word);
    }

}

void spellCheck(char article[], char dictionary[])
{
    while (*article!=0)              //keep looping while the article has still not been terminated
    {
        int length = 0;                         //set length to 0 every time
        char *placeInArticle = article;               //This will hold address the current word

        while (inAlphabet(*article))
        {
            length++;                          //keeps incrementing length until it reaches a nonletter
            article++;
        }

        while (*article && !inAlphabet(*article)==1)        //increment to next word
        {
            article++;                //keeps going until reaches next word in article
        }


        if (length != 1)                                          //allows us to pass by 1 letter words
        {
            *(placeInArticle + length) = '\0';                      //add null termination so that we can use %s in the printinDictionary(dictionary, length, placeInArticle);          //checks if current word is in dictionary or not, if not then it prints it out
            inDictionary(dictionary, length, placeInArticle); //checks if current word is in dictionary or not, if not then it prints it out
        }
    }
}













