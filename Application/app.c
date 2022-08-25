#include <stdio.h>
#include "app.h"

int main(void)
{
    appStart();
    return 0;
}

void appStart(void)
{
    ST_transaction_t transData;                   /* creating a struct of type ST_transaction_t */
    getCardHolderName(&transData.cardHolderData); /* calling of a function to get the name from the user */
    getCardExpiryDate(&transData.cardHolderData); /* calling of a function to get the expiration date from the user */
    getCardPAN(&transData.cardHolderData);        /* calling of a function to get the PAN from the user */
    getTransactionDate(&transData.terminalData);  /* calling of a function to get the transaction date from the user */

    /* check if the card is expired by calling the function to compare both expiration and transaction date */
    if (isCardExpired(&transData.cardHolderData, &transData.terminalData)) 
    {
        printf("DECLINED_EXPIRED_CARD\n");
        return;
    }

    getTransactionAmount(&transData.terminalData); /* calling of a function to get the transaction amount from the user */
    setMaxAmount(&transData.terminalData);         /* calling of a function to set the maximum amount */

    /* check if the amount exceeding the limit by calling the function to compare both amount and maximum */
    if (isBelowMaxAmount(&transData.terminalData))
    {
        printf("DECLINED_AMOUNT_EXCEEDING_LIMIT\n");
        return;
    }
	
    receiveTransactionData(&transData); /* calling function to check validity status, balance and saving of transaction */
}