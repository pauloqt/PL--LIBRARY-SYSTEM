#ifndef BORROWERFUNCTIONS_H_INCLUDED
#define BORROWERFUNCTIONS_H_INCLUDED


//Struct BORROWER containing attributes of the borrower
typedef struct borrower{
    char name[31], TUP_ID[7], password[14], yearSection[15], contactNum[12], email [51];
    struct borrower *nxt;
}BORROWER;
BORROWER *headBorrower, infoBorrower;
char encryptedPass[7];

BORROWER *locateTUP_ID(char TUP_ID[]);
void passDisp();
void getInfoBorrower();
int addBorrower();
void saveInfoBorrower();
void retrieveBorrower();
BORROWER* loginBorrower();


#endif // BORROWERFUNCTIONS_H_INCLUDED