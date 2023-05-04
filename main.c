#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

//ACTIVITY 1: C PROGRAM WITH FILE HANDLING.
//ALCANTARA, JOHN PAULO C. BSCS-NS-2AB

/*A LIBRARY CATALOG WITH THE FF FUNCTIONS:
        [1] ADD RECORD"
        [2] UPDATE RECORD"
        [3] DELETE RECORD"
        [4] SEARCH RECORD"
        [5] DISPLAY ALL RECORDS"
        [6] EXIT"
*/

//Struct BOOK containing attributes of the book:
typedef struct book{
    char title[51], author[51], year[5], refNum[14], material[16], category[31];
    int shelfNo, totalStock, borrower, currentStock;
    struct book *nxt;
}BOOK;

//Struct BORROWER containing attributes of the borrower
typedef struct borrower{
    char name[31], TUP_ID[7], password[14], yearSection[15], contactNum[12], email [51];
    struct borrower *nxt;
}BORROWER;

//Struct TRANSACTION containing attributes of the transaction
typedef struct transaction{
    char title[51], author[31], refNum[14], borrower[31], TUP_ID[7];
    char dateBorrowed[11], dateToReturn[11], librarian[31], status[12];
    struct transaction *nxt;
}TRANSACTION;

BOOK *headBook, infoBook;   //declaring head node and info struct variable where to store the initial info before storing in linked list.
BORROWER *headBorrower, infoBorrower;
TRANSACTION *headTransaction, infoTransaction;

HWND WINAPI GetConsoleWindowNT(void);

//BOOK FUNCTIONS
//The getInfo() function prompts the user to enter information about a book, including its title, author, year published, ISBN, category, total number of stock, and number of borrowers. It stores this information in the info struct variable.
void getInfoBook(){
    fflush stdin;
    printf("ENTER BOOK TITLE: ");
    scanf("%[^\n]", infoBook.title);
    fflush stdin;
    printf("ENTER AUTHOR: ");
    scanf("%[^\n]", infoBook.author);
    fflush stdin;
    printf("ENTER YEAR PUBLISHED: ");
    scanf("%s", infoBook.year);
    printf("ENTER REFERENCE NUMBER: ");
    scanf("%s", infoBook.refNum);
    printf("ENTER MATERIAL: ");
    scanf("%s", infoBook.material);
    fflush stdin;
    printf("ENTER BOOK CATEGORY: ");
    scanf("%[^\n]", infoBook.category);
    printf("ENTER SHELF NO.: ");
    scanf("%d", &infoBook.shelfNo);
    printf("ENTER TOTAL NO. STOCK: ");
    scanf("%d", &infoBook.totalStock);
    printf("ENTER TOTAL NO. OF BORROWER: ");
    scanf("%d", &infoBook.borrower);
}

//The add() function adds a new node to the linked list in alphabetical order, with the info struct as its data.
int addBook(){
BOOK *q, *p, *n;

    n= (BOOK*) malloc(sizeof(BOOK));    //allocates memory to n.
    *n= infoBook;                           //copy info of the book to n.

    p=q=headBook;                           //point all pointers to head.
    while(p!=NULL && strcmp(infoBook.title, p->title)>=0){
        q=p;
        p=p->nxt;
    }

    if(p==headBook){    //if to insert at the head.
        headBook=n;
    }
    else{           //if to insert in between or at the end.
        q->nxt=n;
    }

    n->nxt=p;  //insert p at the end which contains next node or NULL.
}

//The locate() function searches for the book node with a given ISBN, and returns a pointer to that node if it is found.
struct book *locateBook(char refNum[]){
BOOK *p;

    p=headBook;
    while(p!=NULL && strcmp(refNum, p->refNum)!=0){
        p=p->nxt;
    }

    return p;
}

//The update() function prompts the user to enter an ISBN, and then searches for the corresponding book node in the linked list. If found, it displays information about the book and prompts the user to choose which information to update. It then updates the chosen information if the user confirms the update.
void updateBook() {
BOOK *p;
int choice,info;
char refNum[14];
char update[51];
int updateInt;

    printf("ENTER REFERENCE NUMBER OF THE BOOK: ");
    scanf("%s", refNum);
    p = locateBook(refNum);

    if(p==NULL){
        printf("\nRECORD NOT FOUND!\n"); system("pause");
    }

    else{
        displayBook(p, 0, p->nxt);  //display(exact position, start sa 1, end if != p->nxt)
        printf("\n[1] BOOK TITLE");
        printf("\n[2] AUTHOR");
        printf("\n[3] YEAR PUBLISHED");
        printf("\n[4] BOOK REFERENCE NUMBER");
        printf("\n[5] MATERIAL");
        printf("\n[6] CATEGORY");
        printf("\n[7] SHELF NO.");
        printf("\n[8] TOTAL STOCK");
        printf("\n[9] NO. OF BORROWER");
        printf("\nCHOOSE THE INFORMATION YOU WISH TO UPDATE (1-7): ");
        scanf("%d", &info);
        fflush stdin;
        printf("\nENTER THE UPDATED INFORMATION: ");

        if(info==7 || info==8 || info==9)
            scanf("%d", &updateInt);
        else{scanf("%[^\n]", update);}
        printf("\nARE YOU SURE TO UPDATE THE RECORD OF %s?\n[1]YES [2]NO : ", p->title);
        scanf("%d", &choice);
        if(choice==1){
            switch(info){
                case 1: strcpy(p->title, update); break;
                case 2: strcpy(p->author, update); break;
                case 3: strcpy(p->year, update); break;
                case 4: strcpy(p->refNum, update); break;
                case 5: strcpy(p->material, update); break;
                case 6: strcpy(p->category, update); break;
                case 7: p->shelfNo= updateInt; break;
                case 8: p->totalStock= updateInt; break;
                case 9: p->borrower= updateInt; break;
            }
        }
    }
}

//The del() function prompts the user to enter an ISBN, and then searches for the corresponding book node in the linked list. If found, it removes the node from the linked list.
void delBook(){
BOOK *p, *q;
int choice;
char refNum[14];

    printf("ENTER THE REFERENCE NUMBER OF THE BOOK: ");
    scanf("%s", refNum);
    p=headBook;
    while(p!=NULL && strcmp(refNum, p->refNum)!=0){
        q=p;
        p=p->nxt;
    }

    if(p==NULL){
        printf("\nRECORD NOT FOUND!\n"); system("pause");
    }

    else{
        displayBook(p, 0, p->nxt);  //display(exact position, start sa 1, end if != p->nxt)
        printf("\nARE YOU SURE TO DELETE THE RECORD OF %s?\n[1]YES [2]NO : ", p->title);
        fflush stdin;
        scanf("%d", &choice);
        if(choice==1){
            if(p==headBook){
                headBook=p->nxt;
            }

            else{
                q->nxt=p->nxt;
            }
            printf("\n_______________________________________________________");
            printf("\nTHE RECORD OF %s DELETED SUCCESSFULLY.\n", p->title); system("pause");
            free(p);
        }
    }
}

//The search() function prompts the user to enter a search term, and then searches the linked list for any books whose title, author, or category matches the search term. It displays information about any matching books.
void searchBook(){
BOOK *p;
char toSearch[51];
char text[51];
int i, searchCategory;
char* categoryPointer;

    printf("\nSEARCH BY CATEGORY");
    printf("\n[1] Book Title");
    printf("\n[2] Author");
    printf("\n[3] Year Published");
    printf("\n[4] Material");
    printf("\n[5] Topic Category");
    printf("\nENTER SEARCH CATEGORY [1-5]: ");
    scanf("%d", &searchCategory);

    fflush stdin;
    printf("ENTER THE TEXT TO SEARCH: ");
    scanf("%[^\n]", toSearch);

    system("cls");
    gotoxy(10,3); printf("TITLE"); gotoxy(30,3); printf("AUTHOR"); gotoxy(50,3); printf("YEAR");
    gotoxy(60,3); printf("REFERENCE NUMBER");  gotoxy(80,3); printf("MATERIAL"); gotoxy(95,3); printf("CATEGORY");
    gotoxy(110,3); printf("SHELF NO."); gotoxy(120,3); printf("TOTAL STOCK"); gotoxy(135,3); printf("BORROWER");
    gotoxy(145,3); printf("CURRENT STOCK");
    gotoxy(5,5); printf("_______________________________________________________________________________________________________________________________________________\n");

    p=headBook;
    for(i=-1; p!=NULL;){
        switch(searchCategory){ //ipo-point si pointer kung saang search category.
        case 1: categoryPointer= p->title; break;
        case 2: categoryPointer= p->author; break;
        case 3: categoryPointer= p->year; break;
        case 4: categoryPointer= p->material; break;
        case 5: categoryPointer= p->category; break;
        }

        if(strstr(categoryPointer, toSearch)!=NULL){  //if ang pino-point ni categoryPointer ay may ganitong "substring", print, else next.
            i++;
            gotoxy(5, 6+i); printf("%d.) ", i+1);
            gotoxy(10,6+i); printf("%s", p->title);
            gotoxy(30,6+i); printf("%s", p->author);
            gotoxy(50,6+i); printf("%s", p->year);
            gotoxy(60,6+i); printf("%s", p->refNum);
            gotoxy(80,6+i); printf("%s", p->material);
            gotoxy(95,6+i); printf("%s", p->category);
            gotoxy(110,6+i); printf("%d", p->shelfNo);
            gotoxy(125,6+i); printf("%d", p->totalStock);
            gotoxy(135,6+i); printf("%d", p->borrower);
            gotoxy(145,6+i); printf("%d", p->totalStock-p->borrower);
        }
        p=p->nxt;
    }
    gotoxy(5,10+i+1); printf("_______________________________________________________________________________________________________________________________________\n");
    gotoxy(5,10+i+3); system("pause");
}

//The display() function displays information about all the books in the linked list.
void displayBook(struct book *p, int start, int end){
int i;

    gotoxy(10,3); printf("TITLE"); gotoxy(30,3); printf("AUTHOR"); gotoxy(50,3); printf("YEAR");
    gotoxy(60,3); printf("REFERENCE NUMBER");  gotoxy(80,3); printf("MATERIAL"); gotoxy(95,3); printf("CATEGORY");
    gotoxy(110,3); printf("SHELF NO."); gotoxy(120,3); printf("TOTAL STOCK"); gotoxy(135,3); printf("BORROWER");
    gotoxy(145,3); printf("CURRENT STOCK");
    gotoxy(5,5); printf("_______________________________________________________________________________________________________________________________________________\n");

    for(i=start; p!=end; i++){
        gotoxy(5, 6+i); printf("%d.) ", i+1);
        gotoxy(10,6+i); printf("%s", p->title);
        gotoxy(30,6+i); printf("%s", p->author);
        gotoxy(50,6+i); printf("%s", p->year);
        gotoxy(60,6+i); printf("%s", p->refNum);
        gotoxy(80,6+i); printf("%s", p->material);
        gotoxy(95,6+i); printf("%s", p->category);
        gotoxy(110,6+i); printf("%d", p->shelfNo);
        gotoxy(120,6+i); printf("%d", p->totalStock);
        gotoxy(135,6+i); printf("%d", p->borrower);
        gotoxy(145,6+i); printf("%d", p->totalStock-p->borrower);
        p=p->nxt;
    }

    gotoxy(5,6+i+1); printf("_______________________________________________________________________________________________________________________________________________\n");
    gotoxy(5,6+i+3); system("pause");
}

//The save() function prints the information of all the book node in a text file.
void saveBook(){
FILE *fp= fopen("bookDetails.txt", "w+");
BOOK *p;

    if(fp==NULL){
        printf("\nTHE FILE ""LibraryCatalog.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        p=headBook;
        while(p!=NULL){
            fprintf(fp, "%s\n%s\n%s\n%s %s %s %d %d %d\n\n", p->title, p->author, p->category, p->material, p->year, p->refNum, p->shelfNo, p->totalStock, p->borrower);
            p=p->nxt;
        }
        fclose(fp);
    }
}

//retrieve() function retrieves all info from the text file and save each book in the linked list.
void retrieveBook(){
FILE *fp= fopen("bookDetails.txt", "r+");
BOOK *p;

    if(fp==NULL){
        printf("THE FILE ""LibraryCatalog.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        while(1){
            fflush stdin;
            fscanf(fp, "\n%[^\n]\n", &infoBook.title);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoBook.author);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoBook.category);
            fflush stdin;
                  //\n%[^\n]\n%[^\n]\n", &info.title, &info.author, &info.category);;
            fscanf(fp, "%s %s %s %d %d %d", &infoBook.material, &infoBook.year, &infoBook.refNum, &infoBook.shelfNo, &infoBook.totalStock, &infoBook.borrower);

            //decrypting the retrieved info.
            //strcpy(info.title, decrypt(info.title)); strcpy(info.author, decrypt(info.author)); strcpy(info.category, decrypt(info.category));
            //strcpy(info.year, decrypt(info.year)); strcpy(info.ISBN, decrypt(info.ISBN));

            if(!feof(fp)){
                addBook();
                fflush stdin;
            }
            else{break;}
        }
    }
    fclose(fp);
}

//encrypt() creates a copy of the original string, encrypts the copy, and returns the encrypted copy.
char* encryptBook(char text[]){                     //char* - return type for string
int i=0;

    char* encrypted= malloc(strlen(text)+1);    //creates a new char pointer variable that is a copy of the text string, which can be modified without changing the original input string.
    strcpy(encrypted, text);                    //copy value of text to new string

    for(i=0; encrypted[i]!='\0'; i++){          //loop through each character of encrypted
        encrypted[i]+=29;                        //add key to each character
    }

    return encrypted;
}

//decrypt() decodes the encrypted text by subtracting the key which is 29 then it returns the text.
char* decryptBook(char text[]){                //char* - return type for string
int i=0;

    for(i=0; text[i]!='\0'; i++){          //loop through each character of encrypted
        text[i]-=29;                       //subtract key to each character
    }

    return text;
}

//The menu() function displays the main menu of the library catalog program and prompts the user to enter a choice. It returns the user's choice.
int menuBook(int choice){
    while(choice<1 || choice>6){
        system("cls");
        printf("LIBRARY CATALOG");
        printf("\nMENU");
        printf("\n[1] ADD RECORD");
        printf("\n[2] UPDATE RECORD");
        printf("\n[3] DELETE RECORD");
        printf("\n[4] SEARCH RECORD");
        printf("\n[5] DISPLAY ALL RECORDS");
        printf("\n[6] GO BACK");
        printf("\nENTER OPTION: ");
        scanf("%d", &choice);
        if(choice<1 || choice>6){
            printf("\nSELECT 1-6 ONLY!\n");
            system("pause");
        }
    }
    return choice;
}

//FOR BORROWER FUNCTIONS

BORROWER *locateTUP_ID(char TUP_ID[]){
BORROWER *p;

    p=headBorrower;
        while(p!=NULL && strcmp(p->TUP_ID, TUP_ID)!=0){
        p=p->nxt;
    }
    return p;
}

void getInfoBorrower(){
    system("cls");
    printf("COMPLETE THE INFORMATION BELOW\n\n");
    printf("TUP ID (Ex. 123456): TUP-M ");
    scanf("%s", &infoBorrower.TUP_ID);
    if(locateTUP_ID(infoBorrower.TUP_ID)!=NULL){
        printf("\nYOUR TUP ID IS ALREADY REGISTERED!\n"); system("pause");
    }
    else{
        printf("PASSWORD: ");
        scanf("%s", &infoBorrower.password);
        printf("NAME (EX. JUAN A. DELA CRUZ): ");
        fflush stdin;
        scanf("%[^\n]", &infoBorrower.name);
        printf("COURSE AND SECTION (EX: BSCS-NS2A: ");
        scanf("%s", &infoBorrower.yearSection);
        printf("CONTACT NUMBER (Ex. 09123456789): ");
        scanf("%s", &infoBorrower.contactNum);
        printf("EMAIL ADDRESS (Ex. juandelacruz@tup.edu.ph): ");
        scanf("%s", &infoBorrower.email);
        printf("\nYOUR ACCOUNT IS SUCCESSFULLY REGISTERED!\n");
    }
}

int addBorrower(){
BORROWER *q, *p, *n;

     n= (BORROWER*)malloc(sizeof(BORROWER));    //allocates memory to n.
    *n= infoBorrower;                           //copy info of the book to n.

    p=q=headBorrower;                           //point all pointers to head.
    while(p!=NULL && strcmp(infoBorrower.name, p->name)>=0){
        q=p;
        p=p->nxt;
    }

    if(p==headBorrower){    //if to insert at the head.
        headBorrower=n;
    }
    else{           //if to insert in between or at the end.
        q->nxt=n;
    }
    n->nxt=p;  //insert p at the end which contains next node or NULL.
}

void saveInfoBorrower(){//"borrowerDetails.txt"

FILE *fp= fopen("borrowerDetails.txt", "w+");
BORROWER *p;

    if(fp==NULL){
        printf("\nTHE FILE ""borrowerDetails.txt"" DOES NOT EXIST\n");
        system("pause");
    }
    else{
        p=headBorrower;
        while(p!=NULL){
            fprintf(fp, "%s\n%s %s %s %s %s\n\n", p->name, p->TUP_ID, p->password, p->yearSection, p->contactNum, p->email);
            p=p->nxt;
        }
        fclose(fp);
        system("pause");
    }
}

//retrieve() function retrieves all info from the text file and save each book in the linked list.
void retrieveBorrower(){
FILE *fp= fopen("borrowerDetails.txt", "r+");
BOOK *p;

    if(fp==NULL){
        printf("THE FILE ""borrowerDetails.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        while(1){
            fflush stdin;
            fscanf(fp, "\n%[^\n]\n", &infoBorrower.name);
            fflush stdin;
            fscanf(fp, "%s %s %s %s\n\n", infoBorrower.TUP_ID, infoBorrower.password, infoBorrower.yearSection, infoBorrower.contactNum);
            //decrypting the retrieved info.
            //strcpy(info.title, decrypt(info.title)); strcpy(info.author, decrypt(info.author)); strcpy(info.category, decrypt(info.category));
            //strcpy(info.year, decrypt(info.year)); strcpy(info.ISBN, decrypt(info.ISBN));

            if(!feof(fp)){
                addBorrower();
                fflush stdin;
            }
            else{break;}
        }
    }
    fclose(fp);
}

void loginBorrower(){

BORROWER *p;
char enteredID[7], enteredPass[7];
int tries=3, flag=0;


    while (tries > 0 && flag==0) {
        system("cls");
        printf("Please enter your TUP ID: ");
        scanf("%s", enteredID);
        printf("Please enter your password: ");
        scanf("%s", enteredPass);

        p=locateTUP_ID(enteredID);
        if(p!=NULL && strcmp(enteredPass, p->password)==0){     //para di need i-compare lahat ng pass, ID lang.
            printf("Login successful!\n"); system("pause");
            flag=1;
        }

        else{
            printf("Invalid TUP ID or password. ");
            tries--;
            printf("\nYou have %d tries left.\n", tries);
            system("pause");
            system("cls");
        }
    }
    if (tries == 0) {
        printf("You have exceeded the maximum number of tries.\n");
        system("pause");
    }
}

void borrowBook(){


}

//FOR TRANSACTIONS FUNCTIONS

void saveTransaction(){
FILE *fp= fopen("transactionDetails.txt", "w+");
TRANSACTION *p;

    if(fp==NULL){
        printf("\nTHE FILE ""transactionDetails.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        p=headTransaction;
        while(p!=NULL){
            fprintf(fp, "%s\n%s\n%s\n%s\n%s %s %s %s %s\n\n", p->title, p->author, p->refNum, p->borrower, p->TUP_ID, p->dateBorrowed, p->dateToReturn, p->librarian, p->status);
        }
        fclose(fp);
    }
}

void retrieveTransaction(){
FILE *fp= fopen("transactionDetails.txt", "r+");
TRANSACTION *p;

    if(fp==NULL){
        printf("THE FILE ""transactionDetails.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        while(1){
            fflush stdin;
            fscanf(fp, "\n%[^\n]\n", &infoTransaction.title);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoTransaction.author);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoTransaction.refNum);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoTransaction.borrower);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoTransaction.TUP_ID);
            fflush stdin;
            fscanf(fp, "%s %s %s %s %s", &infoTransaction.dateBorrowed, &infoTransaction.dateToReturn, &infoTransaction.librarian, &infoTransaction.dateBorrowed, &infoTransaction.status);

            //decrypting the retrieved info.
            //strcpy(info.title, decrypt(info.title)); strcpy(info.author, decrypt(info.author)); strcpy(info.category, decrypt(info.category));
            //strcpy(info.year, decrypt(info.year)); strcpy(info.ISBN, decrypt(info.ISBN));

            if(!feof(fp)){
                addBook();
                fflush stdin;
            }
            else{break;}
        }
    }
    fclose(fp);
}

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
int logInOrRegister;
    switch(optionStudent){

    case 1:
        system("cls");  displayBook(p=headBook, 0, NULL); break;
    case 2:
        system("cls"); searchBook(); break;
    case 3:
        system("cls");
        printf("BORROW BOOK");
        printf("\n[1] LOGIN\n[2] REGISTER");
        printf("\nSELECT OPTION (1-2): ");
        scanf("%d",&logInOrRegister);
        if (logInOrRegister ==1){
            loginBorrower();
        }
        else if(logInOrRegister==2){
            getInfoBorrower();
            addBorrower();
            saveInfoBorrower();
            loginBorrower();
        }
        else{printf("\nSELECT 1-2 ONLY!\n"); system("pause");}
        break;
    case 4:
        system("cls"); break; //CHANGE PASS
    case 5:
        return;
    default:
        printf("\nSELECT 1-5 ONLY!\n"); system("pause"); break;
    }
}

void adminPortal(int optionAdmin){
BOOK *p;
int bookFunctionChoice;

    switch(optionAdmin){
    case 1:
        while(1){
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

            }
        }
    case 2:
        //BORROWING RECORD SWITCH CASE
        break;
    case 3:
        return;
    default:
        printf("\nSELECT 1-5 ONLY!\n"); system("pause"); break;

    }
}

int main(){
HWND hWnd=GetConsoleWindowNT();
MoveWindow(hWnd,900,900,1200,900,TRUE);
int optionPortal, optionAdmin, optionStudent;

    headBook=NULL;                   //initializing linked list.
    retrieveBook();                  //retrieve all previous records.
    retrieveBorrower();
        while(optionPortal!=3){
            system("cls");
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
                        printf("\n[1] DISPLAY ALL BOOKS");
                        printf("\n[2] SEARCH");
                        printf("\n[3] BORROW");
                        printf("\n[4] CHANGE PASSWORD");
                        printf("\n[5] GO BACK");
                        printf("\nSELECT OPTION [1-5]: ");
                        scanf("%d", &optionStudent);
                        studentPortal(optionStudent);
                    }
                    break;

                case 2:
                    optionAdmin=0;         //para kapag babalik sa portal choices, 0 na ang optionStudent
                    while(optionAdmin!=3){
                        system("cls");
                        printf("\n[1] MANAGE BOOK RECORD");
                        printf("\n[2] MANAGE BORROWING RECORD");
                        printf("\n[3] GO BACK");
                        printf("\nSELECT OPTION [1-3]: ");
                        scanf("%d", &optionAdmin);
                        adminPortal(optionAdmin);

                    }
                    break;

                case 3: exit(0); break;

                default: printf("\nCHOOSE 1-3 ONLY!\n"); system("pause"); break;
            }
        }
}
