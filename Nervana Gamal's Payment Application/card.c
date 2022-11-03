#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    EN_cardError_t status = OK;
    printf("\nPlease Enter Card Name Holder: ");
    // get data from user
    gets( cardData->cardHolderName, 100, stdin);
    fflush(stdin);
    // check length of name
    if (strlen(cardData->cardHolderName) > 24 || strlen(cardData->cardHolderName) < 20)
    {
        status = WRONG_NAME;
    }
    return status;
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    // status default is ok , if the input is wrong it will be changed in the code
    EN_cardError_t status = OK;
    printf("\nPlease Enter Card Expiry date in format MM/YY: ");
   gets( cardData->cardExpirationDate, 100, stdin);
   fflush(stdin);
    //first check the length
    if (!(strlen(cardData->cardExpirationDate) ==5))
    {
        status = WRONG_EXP_DATE;
    }
    // checking the format
    if(cardData->cardExpirationDate[2]!='/')
        status = WRONG_EXP_DATE;
    // checking the month if greater than 12 
    if ((cardData->cardExpirationDate[0] == '1' && cardData->cardExpirationDate[1] > '2') || cardData->cardExpirationDate[0]>'1')
    
        status = WRONG_EXP_DATE;
    

    return status;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    EN_cardError_t status = OK;
    int i = 0;
    printf("\nPlease Enter Card's Primary Account Number: ");
   // getting data from user
    gets( cardData->primaryAccountNumber, 100, stdin);
    fflush(stdin);
    //first check the length
    if ((strlen(cardData->primaryAccountNumber) > 20) || (strlen(cardData->primaryAccountNumber) < 15))
    {
        return  WRONG_PAN;
    }
    // check that all chars are numbers
    for (i = 0; status == OK && i < strlen(cardData->primaryAccountNumber)-1; i++)
    {
        if (cardData->primaryAccountNumber[i] > '9' || cardData->primaryAccountNumber[i] < '0')
        {
            return WRONG_PAN;
        }
    }
   return OK;
}
