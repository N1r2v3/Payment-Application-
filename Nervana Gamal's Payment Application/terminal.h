
#ifndef TERMINAL_H
#define TERMINAL_H
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "card.h"
// struct contains transaction amount and date
typedef struct ST_terminalData_t
{ 
	float transAmount;
	float maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
	OKK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;
// get transaction date from user
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
// compare transaction date with card's expire date
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
// get transaction amount 
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
// compare trans amount with max amount
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);
// get max transaction amount 
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData);

#endif
