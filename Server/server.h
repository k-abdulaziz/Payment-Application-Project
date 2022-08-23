/* server.h */
#ifndef SERVER_H
#define SERVER_H
#include <stdint.h>  /* for uint8_t */
#include "../Terminal/terminal.h"  /* include terminal.h file */
/* declaration of enum */
typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFICIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
/* declaration of struct */
typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;
/* declaration of enum */
typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;
/* declaration of struct */
typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;
/* declaration of enum */
typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t ;
/* functions prototypes */
EN_transState_t receiveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);
#endif
/* end of server.h */