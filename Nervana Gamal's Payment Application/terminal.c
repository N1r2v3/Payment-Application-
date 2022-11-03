 #include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	// setting the default of state by ok
	EN_terminalError_t status = OKK;
	printf("\n Please enter Transaction Date in format DD/MM/YYYY: ");
	// getting date from user
	gets(termData->transactionDate,100,stdin);
	fflush(stdin);
	// checking length
	if (!(strlen(termData->transactionDate) == 10))
	{
		status = WRONG_DATE;
	}
	// checking the format
	if (termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/')
	{
		status = WRONG_DATE;
	}

	// checking the month if greater than 12 
	if ((termData->transactionDate[3] == '1' && termData->transactionDate[4] > '2') || termData->transactionDate[3] > '1')
	{
		status = WRONG_DATE;
	}

	//checking days greater than 21
	if ((termData->transactionDate[0] == '3' && termData->transactionDate[1] > '1') || termData->transactionDate[0] > '3')
	{
		status = WRONG_DATE;
	}

	return status;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	EN_terminalError_t status = OKK;
	int i = 0;
	char transDate[6]; //taking copy of transaction date in the format of MM/YY 
	// setting first 3 input
	for (i = 0; i < 3; i++)
	{
		transDate[i] = termData.transactionDate[i + 3]; // +3 because the date starts with DD/
	}
	//copying year
	transDate[3] = termData.transactionDate[8];
	transDate[4] = termData.transactionDate[9];
	// comparing trans date and expire date
	int flag = strcmp(transDate, cardData.cardExpirationDate);
	if (flag)
		status = EXPIRED_CARD;


	return status;
}



EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t status = OKK;
	printf("\n Please enter the Transaction Amount: ");
	fflush(stdin);
	scanf("%f" ,&termData->transAmount);
	getchar(); // to take \n

	if (termData->transAmount < 0)// to make sure that money is greater than 0
		status = INVALID_AMOUNT;

	return status;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	//comparing amounts 
	EN_terminalError_t status = OKK;
	if (termData->maxTransAmount < termData->transAmount)
		status = EXCEED_MAX_AMOUNT;

	return status;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t status = OKK;
	printf("\n Please enter the max Transaction Amount for the Terminal: ");
	fflush(stdin);
	scanf("%f", &termData->maxTransAmount);
	getchar();// take \n
	if (termData->maxTransAmount < 0)// check for negative numbers
		status = INVALID_MAX_AMOUNT;
	return status;
}
/*void test(void)
{
	EN_terminalError_t status;
	ST_cardData_t cardN;
	ST_terminalData_t termData;
   
	getCardExpiryDate(&cardN);
	getCardHolderName(&cardN);
    getCardPAN(&cardN);
	
	while (1)
	{ 
		printf("===========================================\n\n");
		status = getTransactionDate(&termData);
		printf("\n getTransactionDate %d", status);
		status = isCardExpired(cardN, termData);
		printf("\n isCardExpired %d", status);
		status = getTransactionAmount(&termData);
		printf("\n getTransactionAmount %d", status);
		status = setMaxAmount(&termData);
		printf("\nsetMaxAmount %d", status);
		status = isBelowMaxAmount(&termData);
		printf("\n isBelowMaxAmount %d", status);
	}

}*/
