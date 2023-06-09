#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "bookFunctions.c"
#include "borrowerFunctions.c"
#include "transactionFunctions.c"

HWND WINAPI GetConsoleWindowNT(void);
//PARA SA LAHAT

//The gotoxy() function is used to position the console cursor to a specified location, with the x-coordinate and y-coordinate specified as arguments.
void gotoxy(int x,int y){   //A function that Sets the fixed place of displays
    COORD coord = {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//Sets a fixed window size
HWND WINAPI GetConsoleWindowNT(void)
{
    //declare function pointer type
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    //declare one such function pointer
    GetConsoleWindowT GetConsoleWindow;
    //get a handle on kernel32.dll
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    //assign procedure address to function pointer
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
    ,TEXT("GetConsoleWindow"));
    //check if the function pointer is valid
    //since the function is undocumented
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    //call the undocumented function
    return GetConsoleWindow();
}

void studentPortal(int optionStudent){
BOOK *p;
int logInOrRegister, borrowOrBack;
char ID[7];

    switch(optionStudent){

    case 1:
        system("cls");  displayBook(p=headBook, 0, NULL); break;
    case 2:
        system("cls"); searchBook(); break;
    case 3:
        system("cls");
        printf("BORROW BOOK");
        printf("\n[1] LOGIN\n[2] REGISTER\n[3] GO BACK");
        printf("\nSELECT OPTION (1-2): ");
        scanf("%d",&logInOrRegister);
        if (logInOrRegister ==1){
            strcpy(ID, loginBorrower());
            borrowBook(ID);
        }

        else if(logInOrRegister==2){
            getInfoBorrower();
            addBorrower();
            saveInfoBorrower();
            printf("\n[1] BORROW [2] GO BACK");
            printf("\nSELECT OPTION(1-2): ");
            scanf("%d", &borrowOrBack);
            if(borrowOrBack==1){
                strcpy(ID, loginBorrower());
                borrowBook(ID);
            }
        }
        else if(logInOrRegister==3){
            return;
        }
        else{printf("\nSELECT 1-3 ONLY!\n"); system("pause");}
        break;

    case 4:
        system("cls");
        changePassBorrower();
        break; //CHANGE PASS

    case 5:
        return;

    case 6: exit(0);

    default:
        printf("\nSELECT 1-5 ONLY!\n"); system("pause"); break;
    }
}

void adminPortal(int optionAdmin){
BOOK *p;
TRANSACTION *q;
BORROWER *r;
int bookFunctionChoice;
int transactionChoice;
int borrowerChoice;


    switch(optionAdmin){
    case 1: //MANAGE BOOK
        while(1){
            system("cls");
            switch(menuBook(bookFunctionChoice)){
                case 1: system("cls");
                    printf("\nADD A RECORD\n");
                    getInfoBook();
                    addBook(); saveBook();
                    break;
                case 2: system("cls");
                    printf("\nUPDATE RECORD\n");
                    updateBook(); saveBook();
                    break;
                case 3: system("cls");
                    printf("\nDELETE RECORD\n");
                    delBook(); saveBook();
                    break;
                case 4: system("cls");
                    printf("\nSEARCH RECORD\n");
                    searchBook();
                    break;
                case 5: system("cls");
                    printf("\n\t\t\t\t\t\tDISPLAYING ALL RECORDS...\n");
                    displayBook(p=headBook, 0, NULL);
                    break;
                case 6: return;

                default: printf("SELCT 1-6 ONLY!"); system("pause");
                    break;
            }
        }
        break;
    case 2:
        //MANAGE TRANSACTIONS
        while(1){
            system("cls");
            switch(menuTransaction(transactionChoice)){
                case 1: system("cls");
                    printf("\nEDIT STATUS\n");
                    editStatus();
                    saveBook();
                    saveTransaction();
                    break;
                case 2: system("cls");
                    printf("\nSEARCH BORROWING RECORD\n");
                    searchTransaction();
                    break;
                case 3: system("cls");
                    displayAllTransaction(q=headTransaction, 0, NULL);
                    break;
                case 4:
                    return;
            }
         }
        break;

    case 3: //MANAGE BORROWER RECORDS
    while(1){
        system("cls");
        switch(menuBorrower(borrowerChoice)){
            case 1: system("cls");
                printf("\nDISPLAY ALL BORROWER RECORDS\n");
                displayAllBorrower(r=headBorrower, 0, NULL);
                break;
            case 2: system("cls");
                printf("\nSEARCH BORROWING RECORD\n");
                searchBorrower();
                break;
            case 3: system("cls");
                printf("\nUPDATE BORROWING RECORD\n");
                updateBorrower(); saveInfoBorrower();
                break;
            case 4:
                return;
            case 5:
                exit(0); break;
        }
     }
    break;

    case 4:
        return;

    case 5:
        exit(0); break;

    default:
        printf("\nSELECT 1-3 ONLY!\n"); system("pause"); break;

    }
}

int main(){
HWND hWnd=GetConsoleWindowNT();
MoveWindow(hWnd,900, 900, 2000, 2000,TRUE);
int optionPortal, optionAdmin, optionStudent;

    headBook=NULL;                   //initializing linked list.
    headBorrower=NULL;
    headTransaction=NULL;

    retrieveBook();                  //retrieve all previous records.
    retrieveBorrower();
    retrieveTransaction();

        while(optionPortal!=3){
            system("cls");
            printf("\tTUP LIBRARY\n\n");
            printf("\n[1] STUDENT PORTAL");
            printf("\n[2] ADMIN PORTAL");
            printf("\n[3] EXIT PROGRAM");
            printf("\nSELECT OPTION [1-3]: ");
            scanf("%d", &optionPortal);
            switch(optionPortal){
                case 1:
                    optionStudent=0;         //para kapag babalik sa portal choices, 0 na ang optionStudent
                    while(optionStudent!=5){
                        system("cls");
                        printf("\t\tSTUDENT PORTAL\n\n");
                        printf("\n[1] DISPLAY ALL BOOKS");
                        printf("\n[2] SEARCH");
                        printf("\n[3] BORROW");
                        printf("\n[4] CHANGE PASSWORD");
                        printf("\n[5] GO BACK");
                        printf("\n[6] EXIT");
                        printf("\nSELECT OPTION [1-5]: ");
                        scanf("%d", &optionStudent);
                        studentPortal(optionStudent);
                    }
                    break;

                case 2:
                    loginAdmin();
                    optionAdmin=0;         //para kapag babalik sa portal choices, 0 na ang optionStudent
                    while(optionAdmin!=4){
                        system("cls");
                        printf("\t\tADMIN PORTAL\n\n");
                        printf("\n[1] MANAGE BOOK RECORD");
                        printf("\n[2] MANAGE BORROWING RECORD");
                        printf("\n[3] MANAGE BORROWER RECORD");
                        printf("\n[4] GO BACK");
                        printf("\n[5] EXIT");
                        printf("\nSELECT OPTION [1-4]: ");
                        scanf("%d", &optionAdmin);
                        adminPortal(optionAdmin);

                    }
                    break;

                case 3: exit(0); break;

                default: printf("\nCHOOSE 1-3 ONLY!\n"); system("pause"); break;
            }
        }
}
