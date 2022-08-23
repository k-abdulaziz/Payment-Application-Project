#include <stdio.h> /* for puts() and stdin and fgets() */
#include <string.h> /* for strcpn() and strlen() and strcpy() */
#include <ctype.h> /* for isdigit() function*/
#include "card.h" /* header file */

/* function to get name of cardholder */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    uint8_t userName[50]; /* declaration of an array of unsigned char */
    puts("Enter your Name:"); /* display this string to user to tell what to input */
    /* get input from user and store in the array of userName */
    fgets((char*)userName, 50, stdin);
    /* stop counting \n in the string */
    userName[strcspn((char*)userName, "\n")] = 0; /* stop counting or storing \n in the string */
    /* check if the string is between 20 and 24 */
    if (strlen((char*)userName) >= 20 &&
        strlen((char*)userName) <= 24)
    {
        /* copy userName into the according struct member */
        strcpy((char*)cardData->cardHolderName, (char*)userName);
        return CARD_OK;
    }
    else
    {
        return WRONG_NAME;
    }
}

/* function to get name of card expiry date */
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    uint8_t cardDate[20]; /* declaration of an array of unsigned char */
    puts("\nEnter Expiration Date:");
    fgets((char*)cardDate, 20, stdin);
    cardDate[strcspn((char*)cardDate, "\n")] = 0; /* stop counting \n in the string */
    /* check if the string is not 5 characters */
    if (strlen((char*)cardDate) != 5)
    {
        return WRONG_EXP_DATE;
    }
    /* check if the center character is not / */
    if (cardDate[2] != '/')
    {
        return WRONG_EXP_DATE;
    }
    /* check if right and left characters are not digits */
    if ( !isdigit(cardDate[0]) || !isdigit(cardDate[1])
         || !isdigit(cardDate[3]) || !isdigit(cardDate[4]))
    {
        return WRONG_EXP_DATE;
    }
    else /* if passed all previous checks then correct */
    {
        /* copy cardDate into the according struct member */
        strcpy((char*)cardData->cardExpirationDate, (char*)cardDate);
        return CARD_OK;
    }

}

/* function to get name of card expiry date */
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
    uint8_t cardPAN[30]; /* declaration of an array of unsigned char */
    puts("\nEnter Primary Account Number:"); /* display this string to user to tell what to input */
    /* get input from user and store in the array of cardPAN */
    fgets((char*)cardPAN, 30, stdin);
    cardPAN[strcspn((char*)cardPAN, "\n")] = 0; /* stop counting \n in the string */
    /* if string is greater or equal to 16 and less than or equal 19 */
    if (strlen((char*)cardPAN) >= 16 &&
        strlen((char*)cardPAN) <= 19)
    {
        /* copy cardPAN into the according struct member */
        strcpy((char*)cardData->primaryAccountNumber, (char*)cardPAN);
        return CARD_OK;
    }
    else /* if previous condition not achieved */
    {
        return WRONG_PAN;
    }
}