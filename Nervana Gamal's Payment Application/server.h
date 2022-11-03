#ifndef SERVER_H
#define SERVER_H
#include "terminal.h"

typedef int uint32_t ;
typedef enum EN_transState_t
{
	APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;
typedef enum EN_accountState_t
{
	RUNNING,
	BLOCKED
}EN_accountState_t;
typedef struct ST_transaction_t
{
	ST_cardData_t cardHolderData;
	ST_terminalData_t terminalData;
	EN_transState_t transState;
	uint32_t transactionSequenceNumber;
	// added to save the index in the server array
	uint8_t serverIndex;
}ST_transaction_t;



typedef enum EN_serverError_t
{
	OK1, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

typedef struct ST_accountsDB_t
{   EN_accountState_t state;
	float balance;
	uint8_t primaryAccountNumber[20];
	

}ST_accountsDB_t;

// recieve all input such as card and terminal data
EN_transState_t recieveTransactionData(ST_transaction_t* transData);
// changed the argument type to save the index to avoid multiple search for the PAN
// search for PAN and save it's index
EN_serverError_t isValidAccount(ST_transaction_t* transData);
// check the balance of the card if it contains the amount needed to be withdrawn
EN_serverError_t isAmountAvailable(ST_transaction_t* transData);
// subtract the money from balance and takes copy of transaction to array
EN_serverError_t saveTransaction(ST_transaction_t* transData);
EN_serverError_t isBlockedAccount(ST_transaction_t* transData);



#endif
