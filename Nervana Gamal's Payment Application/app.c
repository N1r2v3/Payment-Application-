#include "app.h"

void appStart(void)
{
	uint8_t flag, endFlag=0;
	States state = GETDATA; // default state to get data
	ST_transaction_t transData;
	printf("\n==================================================================================\n");
	printf("WELCOME TO PAYMENT APPLICATION ");
	printf("\n==================================================================================\n");

	while(1)
	{
		switch (state)
		{
		case (GETDATA):
			flag = recieveTransactionData(&transData);
			if (flag) state = WRONG_INPUT;
			else state = CHECK_VALIDITY;
			break;
		case(CHECK_VALIDITY):
			flag = isValidAccount(&transData);
			if (flag)
			{
				printf("\n STOLEN ACCOUNT \n\t the card has been withdrawn\n");
				state = END;
			}
			else
			{
				state = CHECK_STOLED;
			}
			break;
		case(CHECK_STOLED):
		{
			flag =isBlockedAccount(&transData);
			printf("hi\n");
			if (flag ) {
				state = END;
				printf("\n STOLEN ACCOUNT \n\t the card has been withdrawn\n");
				
			}

			else
			{
				state = CHECK_BALANCE;
				printf("\n RUNNING\n");
			}
		}
		break;
		
		case(CHECK_BALANCE):
			flag = isAmountAvailable(&transData);
		
			if (flag)
			{
				printf("\n Insuffient balance in your account\n");
				state = END;
			}
			else state = SUCESS_TRANS;
			break;
		case (SUCESS_TRANS):
			printf("\n Transaction has been saved successfully\n");
			saveTransaction(&transData);
			state = END;
			break;
		case(WRONG_INPUT):
			printf("\n wrong input please try again\n");
			state = END;
			break;
		case (END):
			state = GETDATA;// to start again
			
			printf("THANK YOU FOR USING OUR APP to exit enter 1 to add another trans enter 0 \n");
			scanf_s("%d", &endFlag);
			getchar();
			printf("\n ******************************************************************************************\n");
			break;
		}
		if (endFlag==1) break;
		fflush(stdin);
	
	}


}
void main()
{
	appStart();
}