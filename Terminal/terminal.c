#include <stdio.h> /* for puts() and stdin and fgets() */
#include <string.h> /* for strcpn() and strlen() and strcpy() */
#include <ctype.h> /* for isdigit() function*/
#include "terminal.h" /* header file */

/*int main()
{
    ST_cardData_t cardData;
    ST_terminalData_t termData;
*//*    int x = getCardHolderName(&cardData);
    printf("%d", x);*//*
    int y = getCardExpiryDate(&cardData);
    printf("%d", y);
*//*    int z = getCardPAN(&cardData);
    printf("%d", z);*//*
    int x1 = getTransactionDate(&termData);
    printf("\n%d", x1);
    int y1 = isCardExpired(&cardData, &termData);
    printf("\n%d", y1);
*//*    int z1 = isValidCardPAN(&cardData);
    printf("\n%d", z1);
    int x2 = getTransactionAmount(&termData);
    printf("\n%d", x2);
    int z2 = setMaxAmount(&termData);
    printf("\n%d", z2);
    int y2 = isBelowMaxAmount(&termData);
    printf("\n%d", y2);*//*
}*/

/* function to get the transaction date from user */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    uint8_t transDate[20]; /* declaration of an array of unsigned char */
    puts("\nEnter Transaction Date:");
    /* get input from user until new line or exceed max */
    fgets((char*)transDate, 20, stdin);
    transDate[strcspn((char*)transDate, "\n")] = 0; /* stop counting \n in the string */
    /* check if the string is not 10 characters */
    if (strlen((char*)transDate) != 10)
    {
        return WRONG_DATE;
    }
    /* check if the third and sixth characters are not / */
    if (transDate[2] != '/' || transDate[5] != '/')
    {
        return WRONG_DATE;
    }
    /* check if right and left characters are not digits */
    if ( !isdigit(transDate[0]) || !isdigit(transDate[1]) || !isdigit(transDate[3]) ||
         !isdigit(transDate[4]) || !isdigit(transDate[6]) || !isdigit(transDate[7]) ||
         !isdigit(transDate[8]) || !isdigit(transDate[9]))
    {
        return WRONG_DATE;
    }
    else /* if passed all previous checks then correct */
    {
        /* copy cardDate into the according struct member */
        strcpy((char*)termData->transactionDate, (char*)transDate);
        return TERMINAL_OK;
    }
}

/* function to check if card expired or not */
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    /* convert first two chars to int then multiply left by 10 and right by 1
     * then add to each other and assign the result to month variable */
    uint8_t monthExpiration = (((*cardData).cardExpirationDate[0] - '0') * 10)
                            + (((*cardData).cardExpirationDate[1] - '0') * 1);

    /* convert first two chars to int then multiply left by 10 and right by 1
     * then add to each other and assign the result to year variable */
    uint8_t yearExpiration = (((*cardData).cardExpirationDate[3] - '0') * 10)
                           + (((*cardData).cardExpirationDate[4] - '0') * 1);

    /* convert first two chars to int then multiply left by 10 and right by 1
     * then add to each other and assign the result to month variable */
    uint8_t monthTransaction = (((*termData).transactionDate[3] - '0') * 10)
                             + (((*termData).transactionDate[4] - '0') * 1);

    /* convert first two chars to int then multiply left by 10 and right by 1
     * then add to each other and assign the result to year variable */
    uint8_t yearTransaction = (((*termData).transactionDate[8] - '0') * 10)
                            + (((*termData).transactionDate[9] - '0') * 1);

    /* check if transaction date is before expiration */
    if (monthTransaction <= monthExpiration && yearTransaction <= yearExpiration)
    {
        return TERMINAL_OK;
    }
    if (monthTransaction > monthExpiration &&  yearTransaction < yearExpiration)
    {
        return TERMINAL_OK;
    }
    else
    {
        return EXPIRED_CARD;
    }

}

/* function to check PAN */
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    /* check if PAN length between 16 and 19 */
    if (strlen((char*)cardData->primaryAccountNumber) >= 16
    && strlen((char*)cardData->primaryAccountNumber) <= 19)
    {
        return TERMINAL_OK;
    }
    return INVALID_CARD;
}

/* function to get transaction amount */
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    float getTransAmount; /* variable declaration of type float */
    puts("\nEnter Transaction Amount:"); /* ask user for input */
    scanf_s("%f", &getTransAmount); /* scan the input */

    /* check if user input is zero or negative */
    if(getTransAmount <= 0)
    {
        return INVALID_AMOUNT;
    }
    else
    {
        /* assign the value to terminal data */
        termData->transAmount = getTransAmount;
        return TERMINAL_OK;
    }
}

/* function to check if below maximum */
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    /* check if transaction amount is less than or equal maximum */
    if (termData->transAmount <= termData->maxTransAmount)
    {
        return TERMINAL_OK;
    }
    else
    {
        return EXCEED_MAX_AMOUNT;
    }
}

/* function to set maximum amount */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    float setMaxTransAmount = 5000; /* definition of local variable of type float */
    /* check if zero or negative */
    if(setMaxTransAmount <= 0)
    {
        return INVALID_MAX_AMOUNT;
    }
    else
    {
        /* assign to terminal data maximum transaction amount */
        termData->maxTransAmount = setMaxTransAmount;
        return TERMINAL_OK;
    }
}