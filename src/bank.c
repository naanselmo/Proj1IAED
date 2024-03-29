/* =====================
 * Grupo 5, IAED, LEIC-T
 * 81900 - Nuno Anselmo
 * 81943 - Gonçalo Matos
 * 82047 - André Mendes
   ===================== */

#include "includes.h"
#include "bank.h"

Bank* bank_new(char name[], char rating, unsigned int reference){
	/* We should definitely check whether we receive a NULL pointer or not.
	However, we can't really handle this. If it throws OOM, nothing we can do.
	Might as well let it throw a segmentation fault, at least it's meaningful */
	Bank *bank = malloc(sizeof(Bank));
	strcpy(bank->name, name);
	bank->rating = rating;
	bank->reference = reference;
	bank->loansNum = 0;
	bank->loans = NULL;
	return bank;
}

void bank_terminate(Bank *bank){
	/* Although loans might be a NULL pointer, it's ignored by free if that is the case */
	free(bank->loans);
	free(bank);
}

void bank_addLoan(Bank *bank, Bank *loanee, int amount){
	int i;
	for (i = 0; i < bank_loansNum(bank); i++){
		Loan *currentLoan = bank_loan(bank, i);
		if(loan_loanee(currentLoan) == loanee){
			loan_updateAmount(currentLoan, amount);
			return;
		}
	}
	loan_new(bank, loanee, amount);
}

void bank_removeLoan(Bank *bank, Loan *loan){
	Loan *loans;
	int index;
	/* Figure out which index corresponds to our loan */
	for(index = 0; index < bank->loansNum; index++)
	{
		if(loan == &bank->loans[index])
			break;
	}
	
	/* Allocate new memory, and move everything except the loan to be removed */
	loans = malloc(sizeof(Loan)*(bank->loansNum -1));
	memcpy(loans, bank->loans, (index)*sizeof(Loan));
	memcpy(loans+index, bank->loans + index + 1, (bank->loansNum - index - 1)*sizeof(Loan));
    free(bank->loans);
    bank->loans = loans;
	bank->loansNum--;
}

int bank_totalLoaned(Bank *bank, int filter){
	int i, total = 0, totalFiltered = 0;
	for(i = 0; i < bank_loansNum(bank); i++){
		Loan *loan = bank_loan(bank, i);
		int amount = loan_amount(loan);
		if(filter && bank_rating(loan_loanee(loan)) == BAD_RATING){
			totalFiltered += amount;
		}
		total += amount; 	
	}
	/* If we decide to filter, only count loans to banks with a poor rating; otherwise, count all */
	return filter ? totalFiltered : total;
}

Loan* bank_loan(Bank *bank, int id){
	return &bank->loans[id];
}

Loan* bank_loanByLoanee(Bank *bank, Bank *loanee){
	int i;
	for (i = 0; i < bank_loansNum(bank); i++){
		Loan *currentLoan = bank_loan(bank, i);
		if(loan_loanee(currentLoan) == loanee){
			return currentLoan;
		}
	}
	return NULL;
}

char* bank_name(Bank *bank){
	return bank->name;
}

void bank_setRating(Bank *bank, char rating){
	bank->rating = rating;
}

char bank_rating(Bank *bank){
	return bank->rating;
}

unsigned int bank_reference(Bank *bank){
	return bank->reference;
}

int bank_loansNum(Bank *bank){
	return bank->loansNum;
}
