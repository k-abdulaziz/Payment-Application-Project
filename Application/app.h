/* app.h */
#ifndef APP_H
#define APP_H

#include "../Server/server.h"
#define MAX_A_DB 255
#define MAX_T_DB 255
extern ST_accountsDB_t Accounts_DB[MAX_A_DB];
extern ST_transaction_t Transactions_DB[MAX_T_DB];

void appStart(void);

#endif
/* end of app.h */