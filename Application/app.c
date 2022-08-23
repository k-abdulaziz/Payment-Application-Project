#include <stdio.h>
#include "app.h"

int main(void)
{
    appStart();
    return 0;
}

void appStart(void)
{
    ST_transaction_t transData;
    getCardHolderName(&transData.cardHolderData);
    getCardExpiryDate(&transData.cardHolderData);
    getCardPAN(&transData.cardHolderData);
    getTransactionDate(&transData.terminalData);
    if (isCardExpired(&transData.cardHolderData, &transData.terminalData))
    {
        printf("DECLINED_EXPIRED_CARD\n");
        return;
    }
    getTransactionAmount(&transData.terminalData);
    setMaxAmount(&transData.terminalData);
    if (isBelowMaxAmount(&transData.terminalData))
    {
        printf("DECLINED_AMOUNT_EXCEEDING_LIMIT\n");
        return;
    }
    receiveTransactionData(&transData);
}