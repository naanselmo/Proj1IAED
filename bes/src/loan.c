#include "loan.h"

void load_init(Loan *loan, int reference, int amount){
	loan->reference = reference;
	loan->amount = amount;
}

int loan_reference(Loan *loan){
	return loan->reference;
}

int loan_amount(Loan *loan){
	return loan->amount;
}

void loan_setAmount(Loan *loan, int amount){
	loan->amount = amount;
}

void loan_updateAmount(Loan *loan, int delta){
	loan_setAmount(loan, loan_amount(loan)+delta);
}