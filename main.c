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
    char title[51], author[51], year[5], ISBN[14], material[16], category[31];
    int shelfNo, totalStock, borrower, currentStock;
    struct book *nxt;
}BOOK;

BOOK *head, info;   //declaring head node and info struct variable where to store the initial info before storing in linked list.

HWND WINAPI GetConsoleWindowNT(void);
void getInfo();
int add();
void update();
void del();
void search();
void display(struct book *p, int start, int end);
struct book *locate(char ISBN[]);
void save();
void retrieve();
char* encrypt(char text[]);
char* decrypt(char text[]);
int menu(int choice);
void gotoxy(int x,int y);

int main(){
HWND hWnd=GetConsoleWindowNT();
MoveWindow(hWnd,900,900,1200,900,TRUE);
int choice;
BOOK *p;

    head=NULL;                   //initializing linked list.
    retrieve();                  //retrieve all previous records.
    while(1){
        system("cls");
        switch(menu(choice)){
            case 1: system("cls");
                printf("\nADD A RECORD\n");
                getInfo();
                add();
                break;
            case 2: system("cls");
                printf("\nUPDATE RECORD\n");
                update();
                break;
            case 3: system("cls");
                printf("\nDELETE RECORD\n");
                del();
                break;
            case 4: system("cls");
                printf("\nSEARCH RECORD\n");
                search();
                break;
            case 5: system("cls");
                printf("\n\t\t\t\t\t\tDISPLAYING ALL RECORDS...\n");
                display(p=head, 0, NULL);
                break;
            case 6: exit(0);

        }
        save();
    }
}

//The getInfo() function prompts the user to enter information about a book, including its title, author, year published, ISBN, category, total number of stock, and number of borrowers. It stores this information in the info struct variable.
void getInfo(){
    fflush stdin;
    printf("ENTER BOOK TITLE: ");
    scanf("%[^\n]", info.title);
    fflush stdin;
    printf("ENTER AUTHOR: ");
    scanf("%[^\n]", info.author);
    fflush stdin;
    printf("ENTER YEAR PUBLISHED: ");
    scanf("%s", info.year);
    fflush stdin;
    printf("ENTER ISBN: ");
    scanf("%s", info.ISBN);
    fflush stdin;
    printf("ENTER MATERIAL: ");
    scanf("%s", info.material);
    fflush stdin;
    printf("ENTER BOOK CATEGORY: ");
    scanf("%[^\n]", info.category);
    fflush stdin;
    printf("ENTER SHELF NO.: ");
    scanf("%d", &info.shelfNo);
    fflush stdin;
    printf("ENTER TOTAL NO. STOCK: ");
    scanf("%d", &info.totalStock);
    fflush stdin;
    printf("ENTER TOTAL NO. OF BORROWER: ");
    scanf("%d", &info.borrower);
}

//The add() function adds a new node to the linked list in alphabetical order, with the info struct as its data.
int add(){
BOOK *q, *p, *n;

    n= (BOOK*) malloc(sizeof(BOOK));    //allocates memory to n.
    *n= info;                           //copy info of the book to n.

    p=q=head;                           //point all pointers to head.
    while(p!=NULL && strcmp(info.title, p->title)>=0){
        q=p;
        p=p->nxt;
    }

    if(p==head){    //if to insert at the head.
        head=n;
    }
    else{           //if to insert in between or at the end.
        q->nxt=n;
    }

    n->nxt=p;  //insert p at the end which contains next node or NULL.
}

//The update() function prompts the user to enter an ISBN, and then searches for the corresponding book node in the linked list. If found, it displays information about the book and prompts the user to choose which information to update. It then updates the chosen information if the user confirms the update.
void update() {
BOOK *p;
int choice,info;
char ISBN[11];
char update[51];
int updateInt;

    printf("ENTER ISBN OF THE BOOK: ");
    scanf("%s", ISBN);
    p = locate(ISBN);

    if(p==NULL){
        printf("\nRECORD NOT FOUND!\n"); system("pause");
    }

    else{
        display(p, 0, p->nxt);  //display(exact position, start sa 1, end if != p->nxt)
        printf("\n[1] BOOK TITLE");
        printf("\n[2] AUTHOR");
        printf("\n[3] YEAR PUBLISHED");
        printf("\n[4] ISBN");
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
                case 4: strcpy(p->ISBN, update); break;
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
void del(){
BOOK *p, *q;
int choice;
char ISBN[11];

    printf("ENTER THE ISBN OF THE BOOK: ");
    scanf("%s", ISBN);
    p=head;
    while(p!=NULL && strcmp(ISBN, p->ISBN)!=0){
        q=p;
        p=p->nxt;
    }

    if(p==NULL){
        printf("\nRECORD NOT FOUND!\n"); system("pause");
    }

    else{
        display(p, 0, p->nxt);  //display(exact position, start sa 1, end if != p->nxt)
        printf("\nARE YOU SURE TO DELETE THE RECORD OF %s?\n[1]YES [2]NO : ", p->title);
        fflush stdin;
        scanf("%d", &choice);
        if(choice==1){
            if(p==head){
                head=p->nxt;
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

//The locate() function searches for the book node with a given ISBN, and returns a pointer to that node if it is found.
struct book *locate(char ISBN[]){
BOOK *p;

    p=head;
    while(p!=NULL && strcmp(ISBN, p->ISBN)!=0){
        p=p->nxt;
    }

    return p;
}

//The search() function prompts the user to enter a search term, and then searches the linked list for any books whose title, author, or category matches the search term. It displays information about any matching books.
void search(){
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
    gotoxy(60,3); printf("ISBN");  gotoxy(80,3); printf("MATERIAL"); gotoxy(95,3); printf("CATEGORY");
    gotoxy(110,3); printf("SHELF NO."); gotoxy(120,3); printf("TOTAL STOCK"); gotoxy(135,3); printf("BORROWER");
    gotoxy(145,3); printf("CURRENT STOCK");
    gotoxy(5,5); printf("_______________________________________________________________________________________________________________________________________________\n");

    p=head;
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
            gotoxy(60,6+i); printf("%s", p->ISBN);
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
void display(struct book *p, int start, int end){
int i;

    gotoxy(10,3); printf("TITLE"); gotoxy(30,3); printf("AUTHOR"); gotoxy(50,3); printf("YEAR");
    gotoxy(60,3); printf("ISBN");  gotoxy(80,3); printf("MATERIAL"); gotoxy(95,3); printf("CATEGORY");
    gotoxy(110,3); printf("SHELF NO."); gotoxy(120,3); printf("TOTAL STOCK"); gotoxy(135,3); printf("BORROWER");
    gotoxy(145,3); printf("CURRENT STOCK");
    gotoxy(5,5); printf("_______________________________________________________________________________________________________________________________________________\n");

    for(i=start; p!=end; i++){
        gotoxy(5, 6+i); printf("%d.) ", i+1);
        gotoxy(10,6+i); printf("%s", p->title);
        gotoxy(30,6+i); printf("%s", p->author);
        gotoxy(50,6+i); printf("%s", p->year);
        gotoxy(60,6+i); printf("%s", p->ISBN);
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
void save(){
FILE *fp= fopen("libraryCatalog.txt", "w+");
BOOK *p;

    if(fp==NULL){
        printf("\nTHE FILE ""LibraryCatalog.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        p=head;
        while(p!=NULL){
            fprintf(fp, "%s\n%s\n%s\n%s %s %s %d %d %d\n\n", p->title, p->author, p->category, p->material, p->year, p->ISBN, p->shelfNo, p->totalStock, p->borrower);
            p=p->nxt;
        }
        fclose(fp);
    }
}

//retrieve() function retrieves all info from the text file and save each book in the linked list.
void retrieve(){
FILE *fp= fopen("LibraryCatalog.txt", "r+");
BOOK *p;

    if(fp==NULL){
        printf("THE FILE ""LibraryCatalog.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        while(1){
            fflush stdin;
            fscanf(fp, "\n%[^\n]\n", &info.title);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &info.author);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &info.category);
            fflush stdin;
                  //\n%[^\n]\n%[^\n]\n", &info.title, &info.author, &info.category);;
            fscanf(fp, "%s %s %s %d %d %d", &info.material, &info.year, &info.ISBN, &info.shelfNo, &info.totalStock, &info.borrower);

            //decrypting the retrieved info.
            //strcpy(info.title, decrypt(info.title)); strcpy(info.author, decrypt(info.author)); strcpy(info.category, decrypt(info.category));
            //strcpy(info.year, decrypt(info.year)); strcpy(info.ISBN, decrypt(info.ISBN));

            if(!feof(fp)){
                add();
                fflush stdin;
            }
            else{break;}
        }
    }
    fclose(fp);
}

//encrypt() creates a copy of the original string, encrypts the copy, and returns the encrypted copy.
char* encrypt(char text[]){                     //char* - return type for string
int i=0;

    char* encrypted= malloc(strlen(text)+1);    //creates a new char pointer variable that is a copy of the text string, which can be modified without changing the original input string.
    strcpy(encrypted, text);                    //copy value of text to new string

    for(i=0; encrypted[i]!='\0'; i++){          //loop through each character of encrypted
        encrypted[i]+=29;                        //add key to each character
    }

    return encrypted;
}

//decrypt() decodes the encrypted text by subtracting the key which is 29 then it returns the text.
char* decrypt(char text[]){                //char* - return type for string
int i=0;

    for(i=0; text[i]!='\0'; i++){          //loop through each character of encrypted
        text[i]-=29;                       //subtract key to each character
    }

    return text;
}

//The menu() function displays the main menu of the library catalog program and prompts the user to enter a choice. It returns the user's choice.
int menu(int choice){
    while(choice<1 || choice>6){
        printf("LIBRARY CATALOG");
        printf("\nMENU");
        printf("\n[1] ADD RECORD");
        printf("\n[2] UPDATE RECORD");
        printf("\n[3] DELETE RECORD");
        printf("\n[4] SEARCH RECORD");
        printf("\n[5] DISPLAY ALL RECORDS");
        printf("\n[6] EXIT");
        printf("\nENTER OPTION: ");
        scanf("%d", &choice);
        if(choice<1 || choice>6){
            printf("\nENTER 1-6 ONLY!");
            system("pause");
        }
    }
    return choice;
}

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





