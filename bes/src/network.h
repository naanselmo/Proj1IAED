#pragma once

#include "includes.h"
#include "bank.h"

typedef struct 
{
	int banksNum;
	Bank banks[1000];
} Network;	

void network_init(Network *network);

void network_addBank(Network *network, char *name, char rating, int reference);