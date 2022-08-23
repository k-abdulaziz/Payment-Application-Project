#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#include <stdio.h> /* for printf() */
#include <string.h> /* for strcmp() */
#include "server.h" /* header file */

#define MAX_A_DB 255
#define MAX_T_DB 255

ST_accountsDB_t Accounts_DB[MAX_A_DB] = {{5500.0,  RUNNING, "1966589945389114"},
                                         {25423.5, RUNNING, "307966026107481877"},
                                         {7453.90, BLOCKED, "49532281179719430"},
                                         {15967.0, RUNNING, "801536000345187706"},
                                         {87684.0, BLOCKED, "7958197400023330"},
                                         {124652.4,BLOCKED, "0442191854275788092"},
                                         {96746.25,RUNNING, "083925770699635120"},
                                         {1208.6,  RUNNING, "2507274567333751260"},
                                         {45369.24,BLOCKED, "220622371229152670"},
                                         {36974.14,RUNNING, "30048664293536532"}};

ST_transaction_t Transactions_DB[MAX_T_DB] = {0};
int i, sequence_number = 0;

EN_transState_t receiveTransactionData(ST_transaction_t* transData)
{
    if (isValidAccount(&transData->cardHolderData, Accounts_DB))
    {
        transData->transState = FRAUD_CARD;
        printf("FRAUD_CARD\n");
        return FRAUD_CARD;
    }
    else if (isBlockedAccount(Accounts_DB))
    {
        transData->transState = DECLINED_STOLEN_CARD;
        printf("DECLINED_STOLEN_CARD\n");
        return DECLINED_STOLEN_CARD;
    }
    else if (isAmountAvailable(&transData->terminalData))
    {
        transData->transState = DECLINED_INSUFFICIENT_FUND;
        printf("DECLINED_INSUFFICIENT_FUND\n");
        return DECLINED_INSUFFICIENT_FUND;
    }
    else if (saveTransaction(transData))
    {
        transData->transState = INTERNAL_SERVER_ERROR;
        printf("INTERNAL_SERVER_ERROR\n");
        return INTERNAL_SERVER_ERROR;
    }
    else
    {
        /* subtract the transaction amount from account balance */
        Accounts_DB[i].balance -= transData->terminalData.transAmount;
        printf("New Balance: %f\n", Accounts_DB[i].balance);
        transData->transState = APPROVED;
        printf("APPROVED");
        return APPROVED;
    }
}

/* function to check the validity of account by searching for PAN Account database */
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference)
{
    for (i = 0; i < MAX_A_DB; i++)
    {
        if(!strcmp((char*)cardData->primaryAccountNumber,(char *)(accountReference+i)->primaryAccountNumber))
        {
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}

/* function to check if account is blocked or running */
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference)
{
    if(accountReference[i].state == RUNNING)
    {
        return SERVER_OK;
    }
    return BLOCKED_ACCOUNT;
}

/* function to check if account balance covers the transaction amount */
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    if (termData->transAmount > Accounts_DB[i].balance)
    {
        return LOW_BALANCE;
    }
    else
    {
        return SERVER_OK;
    }
}

/* function to save transaction data */
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    transData->transactionSequenceNumber = sequence_number;
    Transactions_DB[sequence_number] = *transData;
    sequence_number++;
    if (getTransaction(sequence_number - 1,transData) == 0)
    {
        return SERVER_OK;
    }
    return SAVING_FAILED;

}

/* function to returns transaction data */
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    int counter;
    for (counter = 0; counter < 255; counter++)
    {
        if(Transactions_DB[counter].transactionSequenceNumber == transactionSequenceNumber)
        {
            *transData = Transactions_DB[counter];
            printf("\nName: %s\n", Transactions_DB[counter].cardHolderData.cardHolderName);
            printf("PAN: %s\n", Transactions_DB[counter].cardHolderData.primaryAccountNumber);
            printf("Expiry_Date: %s\n", Transactions_DB[counter].cardHolderData.cardExpirationDate);
            printf("Trans_Amount: %f\n", Transactions_DB[counter].terminalData.transAmount);
            printf("Max_trans_Amount: %f\n", Transactions_DB[counter].terminalData.maxTransAmount);
            printf("Trans_Date: %s\n", Transactions_DB[counter].terminalData.transactionDate);
            printf("Trans_State: %u\n", Transactions_DB[counter].transState);
            printf("Trans_seq_num : %u\n", Transactions_DB[counter].transactionSequenceNumber);
            return SERVER_OK;
        }
    }
    return TRANSACTION_NOT_FOUND;
}