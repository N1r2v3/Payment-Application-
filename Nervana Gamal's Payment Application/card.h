#ifndef __CARD_H
#define __CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char uint8_t;
// struct to carry all card data
typedef struct ST_cardData_t
{
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[100];
	uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{
	OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

// function to get user name and check its length 
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
// function to get card's expiry date and check its format 
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
// function to get card's PAN and check its format and length 
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif
