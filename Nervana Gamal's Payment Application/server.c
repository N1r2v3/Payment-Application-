#include "server.h"
// data base
struct ST_accountsDB_t accounts[255] = { 
	{RUNNING,1000,"12888877162546175"},{RUNNING,2000,"61288887716254617"},{RUNNING,3000,"51288887716254617"}
	,{RUNNING,2000,"12878887716254617"},{RUNNING,4000,"12888887716254617"},
{BLOCKED,5000,"1288887716254617"},{RUNNING,1000,"1288887716254617"},{RUNNING,2000,"12888877162546176"},
	{RUNNING,3000,"12888877162546177"},{RUNNING,4000,"12888877162546173"},{BLOCKED,5000,"abcdefghijklmnop1010"}
,{BLOCKED,5000,"15655435690871342"},{RUNNING,1000,"545721694307219"},{RUNNING,2000,"768473627189172679"}
,{RUNNING,3000,"117665557734565"},{RUNNING,4000,"111111111117665557"},{BLOCKED,5000,"11288887716254617"}
,{BLOCKED,5000,"156554356908713426"},{RUNNING,1000,"54572169430721988"},{RUNNING,2000,"768473627189172675"}
,{RUNNING,3000,"11766555773456576"},{RUNNING,4000,"111111111117665554"},{BLOCKED,5000,"128888771625461723"}
,{BLOCKED,5000,"156554356908713428"},{RUNNING,1000,"54572169430721966"},{RUNNING,2000,"7684736271891726778"}
,{RUNNING,3000,"117665557734565543"},{RUNNING,4000,"111111111117665553"},{BLOCKED,5000,"1258546050114856"}
,{BLOCKED,5000,"1565543569087134265"},{RUNNING,1000,"5457216943072195"},{RUNNING,2000,"7684736271891726765"}
,{RUNNING,3000,"117665557734565654"},{RUNNING,4000,"11111111111766555"},{BLOCKED,5000,"1258546050485612"}
,{BLOCKED,5000,"156554356908713425"},{RUNNING,1000,"54572169430721965"},{RUNNING,2000,"676847362718917267"},
	{RUNNING,3000,"11766555773456554"},{RUNNING,4000,"111111111117665551"},{BLOCKED,5000,"1258546050444856"}
,{BLOCKED,5000,"415655435690871342"},{RUNNING,1000,"5457216943072195"},{RUNNING,2000,"768473627189172676"}
,{RUNNING,3000,"11766555773456589"},{RUNNING,4000,"111111111117665559"},{BLOCKED,5000,"12585460504856485"}
,{BLOCKED,5000,"12585460504856789"}
,{RUNNING,1000,"3315655435690871342"},{RUNNING,2000,"5457216943072194"},{RUNNING,3000,"768473627189172675"},
	{RUNNING,4000,"11766555773456500"},{BLOCKED,5000,"1111111111176655544"},{BLOCKED,5000,"1258546780504856"}
,{RUNNING,1000,"2115655435690871342"},{RUNNING,2000,"5457216943072193"},{RUNNING,3000,"768473627189172677"},
	{RUNNING,4000,"09117665557734565"},{BLOCKED,5000,"1111111111176655533"},{BLOCKED,5000,"12585460504856765"}
,{RUNNING,1000,"9915655435690871342"},{RUNNING,2000,"5457216943072197"},{RUNNING,3000,"76847362718917267"}
,{RUNNING,4000,"06117665557734565"},{BLOCKED,5000,"1111111111176655577"},{BLOCKED,5000,"1258885460504856"}
,{RUNNING,1000,"45615655435690871342"},{RUNNING,2000,"545721694307219"},{RUNNING,3000,"67676667645556666"}
,{RUNNING,4000,"66117665557734565"},{BLOCKED,5000,"1111111111176655522"},{BLOCKED,5000,"1258546050485643"}
,{RUNNING,1000,"11111111111111111111"},{RUNNING,2000,"2222222222222222"},{RUNNING,3000,"55555555555555"},
	{RUNNING,4000,"77777777777777777"},{BLOCKED,5000,"987654321987654321"},{BLOCKED,5000,"123456789123456789"} };

struct ST_transaction_t transactions[255] = { 0 };
uint8_t transSequanse=0;// global variable to count the number of transactions

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	uint8_t i = 0;
	uint8_t flag = 0;
	EN_transState_t status;
	/// getting card data

	flag = getCardHolderName(&transData->cardHolderData);
	fflush(stdin);
	if (flag)
	{
		printf("\nwrong holder name\n");
		return ACCOUNT_NOT_FOUND;
	}
	flag = 0;
	flag = getCardExpiryDate(&transData->cardHolderData);
	fflush(stdin);
	if (flag)
	{
		printf("\nwrong expire date format\n");
		return ACCOUNT_NOT_FOUND;
	}
	flag = 0;
	flag = getCardPAN(&transData->cardHolderData);
	fflush(stdin);
	if (flag)
	{
		printf("\nwrong PAN  format\n");
		return ACCOUNT_NOT_FOUND;
	}
	flag = 0;
	// getting transaction data 
	flag = getTransactionDate(&transData->terminalData);
	fflush(stdin);
	if (flag)
	{
		printf("\nwrong Date  format\n");
		return ACCOUNT_NOT_FOUND;
	}
	flag = 0;
	// checking if card expired
	flag = isCardExpired(transData->cardHolderData ,transData->terminalData);
	if (flag==0)
	{
		printf("\nexpired card\n");
		return ACCOUNT_NOT_FOUND;
	}
	// getting amounts 
	flag = 0;
	flag = getTransactionAmount(&transData->terminalData);
	fflush(stdin);
	if (flag)
	{
		printf("\nmoney cannot be lower than 0\n");
		return ACCOUNT_NOT_FOUND;
	}
	flag = 0;
	flag = setMaxAmount(&transData->terminalData);
	if (flag)
	{
		printf("\nmoney cannot be lower than 0\n");
		return ACCOUNT_NOT_FOUND;
	}
	flag = 0;
	flag = isBelowMaxAmount(&transData->terminalData);// checking max trans
	if (flag)
	{
		printf("\nExeeds maximum amount \n");
		return LOW_BALANCE;
	}
	
	return APPROVED;

	
}

EN_serverError_t isValidAccount(ST_transaction_t* transData)
{
	uint8_t flag = 0,i;// used in for loop
	uint8_t stringflag; // used in string comparing
	
	for (i = 0; i < 78; i++)
	{
		 stringflag= strcmp(transData->cardHolderData.primaryAccountNumber, accounts[i].primaryAccountNumber);

		if (stringflag == 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag==1)
	{
		transData->serverIndex = i;
		return  OK1;
	}
	else
	{
		transData->serverIndex = -1;
		return ACCOUNT_NOT_FOUND;
	}
	return OK1;
}




EN_serverError_t isAmountAvailable(ST_transaction_t* transData)
{// checking user balance
	if (transData->terminalData.transAmount >= accounts[transData->serverIndex].balance)
		return LOW_BALANCE;
	return APPROVED;
}


EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	// checking if the transaction array is maximum
	if (transSequanse == 255)
		return SAVING_FAILED;

	else
	{
		// minus balance and save transaction
		accounts[transData->serverIndex].balance-=transData->terminalData.transAmount;
		transactions[transSequanse] = *transData;
		transSequanse++;
	}
	
}

EN_serverError_t isBlockedAccount(ST_transaction_t* transData)
{
	
	    return accounts[transData->serverIndex].state;

}
