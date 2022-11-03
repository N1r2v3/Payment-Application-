#ifndef app_H
#define app_H
#include <stdio.h>
#include <stdlib.h>
#include "server.h"
typedef enum States {
	GETDATA,WRONG_INPUT,CHECK_VALIDITY,CHECK_BALANCE,SUCESS_TRANS, CHECK_STOLED,END
}States;
void appStart(void);



#endif
