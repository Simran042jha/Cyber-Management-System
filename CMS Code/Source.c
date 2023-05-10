
#include<conio.h>
#include "hash_table.h"
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#define TABLESZ 20
void heading();
void main_heading();
void menu();
void user_menu();
void insert();
int display();
void search();
void _delete();
void arrival_time();
void user_signup();
void login_user();
void loadTable();
void dumpTable();
void mainlogin(int);
int main()
{
    loadTable();
    mainlogin(0);
}
void mainlogin(int mode)
{
    char username[11]; // variable to hold the username
    char password[11]; // variable to hold the password
    int ch;
    system("CLS");
    system("color 8F");
    heading();
    if (mode == 0)
    {
        printf("\n\n\t\t\t\t\t1) Login as Admin");
        printf("\n\t\t\t\t\t2) Login as user");
        printf("\n\n\t\t\t\t\tEnter your choice (1/2) : ");
        scanf("%d", &ch);
    }
    else
    {
        ch = mode;
    }
    system("CLS");
    switch (ch)
    {
    case 1:
        system("CLS");
        heading();
        printf("\n\n\t\t\t\t\t\t||    ADMIN LOGIN    ||\t\t\t\t");
        printf("\n\n\n\t\t\t\t\tEnter your Username :");
        scanf("%s", &username);
        printf("\t\t\t\t\tEnter your Password :");
        scanf("%s", &password);

        if (strcmp(username, "admin") == 0)
        {
            if (strcmp(password, "cyber123") == 0)
            {
                printf("\n\n\t\t\t\t\tWELCOME ADMIN!!! LOGIN SUCCESSFULL");
                printf("\n\n\t\t\t\t\tPress any key to continue ");
                _getch();
                system("CLS");
                main_heading();
                menu();
            }
            else
            {
                printf("\t\t\t\t\tIncorrect Password !!! Failed to Login");
            }
        }
        else
        {
            printf("\t\t\t\t\tUsername is invalid !!! Failed to Login");
        }
        break;
    case 2:
        system("CLS");
        heading();
        int cho;
        printf("\n\n\t\t\t\t\t1.Login ");
        printf("\n\t\t\t\t\t2.New user ? sign up ");
        printf("\n\t\t\t\t\tEnter your Choice : ");
        scanf("%d", &cho);

        switch (cho)
        {
        case 1:
            system("CLS");
            printf("\n\n\t\t\t\t\t\t||   USER LOGIN    ||\t\t\t\t");
            main_heading();
            login_user();
            break;
        case 2:
            system("CLS");
            heading();
            user_signup();
            break;
        default:
            printf("\n\t\t\t\t\tInvalid Choice!!!");
            break;

        }
    }
}
void loadTable()
{
    Hashtable* tble = create_hashtable(TABLESZ);
    FILE* fp = fopen("cyber.txt", "ab+");

    char line[420];
    const char* delim = ",/:";
    char* ptr;
    size_t uid;
    char usrname[11];
    ArrTime tm;
    if (fp != NULL)
    {
        while (fgets(line, sizeof(line), fp))
        {
            line[strcspn(line, "\n")] = 0;
            line[strcspn(line, "\r")] = 0;
            ptr = strtok(line, delim);
            int count = 1;
            while (ptr != NULL)
            {
                switch (count)
                {
                case 1:
                    uid = atoi(ptr);
                    ptr = strtok(NULL, delim);
                    count +=1;
                    break;
                case 2:
                    strncpy(usrname, ptr, 11);
                    ptr = strtok(NULL, delim);
                    count += 1;
                    break;
                case 3:
                    tm.day = atoi(ptr);
                    ptr = strtok(NULL, delim);
                    tm.mnth = atoi(ptr);
                    ptr = strtok(NULL, delim);
                    tm.yr = atoi(ptr);
                    ptr = strtok(NULL, delim);
                    count += 1;
                    break;
                case 4:
                    tm.hr = atoi(ptr);
                    ptr = strtok(NULL, delim);
                    tm.min = atoi(ptr);
                    ptr = strtok(NULL, delim);
                    count = 1;
                    tble->insert_user(tble, uid, usrname, tm);
                    break;
                }
                
            }
        }
        fclose(fp);
    }
    else
    {
        printf("\n\t\t\t\t\tERROR OPENING FILE !!!");
        return;
    }
}
void dumpTable()
{
    Hashtable* tble = create_hashtable(TABLESZ);
    FILE* fp = fopen("cyber.txt", "w");
    if (fp == NULL)
    {
        printf("\n\t\t\t\t\tERROR DUMPING TO FILE!!!");
        return;
    }
    else
    {
        for (size_t i = 0;i < tble->size; i++)
        {
            data* dat = tble->table_ptr[i];
            while (dat != NULL)
            {
                fprintf(fp, "%d,%s,%02d/%02d/%02d,%02d:%02d\n", dat->id, dat->usrname, dat->arrivalTime.day, dat->arrivalTime.mnth, dat->arrivalTime.yr, dat->arrivalTime.hr, dat->arrivalTime.min);
                dat = dat->next;
            }
        }
        fclose(fp);
    }
    delete_hashtable(tble);
    
}

void heading()
{
    printf("\n\t\t\t\t--------------------------------------------------\t\t\t\t");
    printf("\n\t\t\t\t|       WELCOME TO CYBER MANAGEMENT SYSTEM       |\t\t");
    printf("\n\t\t\t\t--------------------------------------------------\t\t\t\t\n");
}

void main_heading()
{
    printf("\n\t\t\t\t--------------------------------------------------\t\t\t\t");
    printf("\n\t\t\t\t|              CYBER MANAGEMENT SYSTEM            |\t\t");
    printf("\n\t\t\t\t--------------------------------------------------\t\t\t\t");
}

void menu()
{
    int choice;
    printf("\n\n\n\t\t\t\t\t\t  |<--MENU-->|");
    printf("\n\n\t\t\t\t\t\t1.Insert Record");
    printf("\n\t\t\t\t\t\t2.Display Record");
    printf("\n\t\t\t\t\t\t3.Search Record");
    printf("\n\t\t\t\t\t\t4.Delete Record");
    printf("\n\t\t\t\t\t\t5.Exit");
    printf("\n\n\t\t\t\t\t\tEnter your choice :");
    scanf("%d", &choice);
    Hashtable* tble = create_hashtable(TABLESZ);
    switch (choice)
    {
    case 1: system("CLS");
        insert(tble);
        break;

    case 2: 
        system("CLS");
        main_heading();
        display(tble);
        printf("\n\n\t\t\t\t\tPress any key to continue ");
        _getch();
        system("CLS");
        main_heading();
        menu();

    case 3: system("CLS");
        search(tble);
        printf("\n\n\t\t\t\t\tPress any key to continue ");
        _getch();
        system("CLS");
        main_heading();
        menu();
        break;

    case 4: system("CLS");
        _delete(tble);
        break;

    case 5: system("CLS");
        dumpTable();
        exit(0);
    default: printf("INVALID CHOICE !!!");
    }
}

void insert(Hashtable* tble)
{
    time_t mytime;
    struct tm* current_time;
    char name[11], buffer[50], choice = 'y';
    int id;
    ArrTime u_tm;

    system("CLS");
    fflush(stdin);
    while (choice == 'y')
    {
        main_heading();
        printf("\n\n\t\t\t\t\t\tENTER NEW USER DATA :");
        printf("\n\n\t\t\t\t\tEnter User_ID : ");
        scanf("%d", &id);
        printf("\n\n\t\t\t\t\tEnter name of the user : ");
        scanf("%s", &buffer);
        if (strlen(buffer) <= 10)
        {
            strncpy(name, buffer, 11);
        }
        else {
            printf("\n\t\t\t\t\tERROR:Username can be atmost 10 character!! Try again");
            printf("\n\n\t\t\t\t\tPress any key to continue ");
            _getch();
            break;
        }
        mytime = time(NULL);
        current_time = localtime(&mytime);
        u_tm = (ArrTime){ current_time->tm_mday, current_time->tm_mon + 1, current_time->tm_year + 1900, current_time->tm_hour, current_time->tm_min };
        arrival_time();
        tble->insert_user(tble, id, name, u_tm);
        printf("\n\n\t\t\t\t     USER RECORD INSERTED SUCCESSFULLY !!!");
        printf("\n\n\t\t\t\t     Want to add another record ? (y/n) : ");
        scanf(" %c", &choice);
        system("CLS");
    }
    system("CLS");
    main_heading();
    menu();
}

void search(Hashtable* tble)
{
    system("CLS");
    main_heading();
    int my_id;
    int duration, tothr, totmin;
    time_t mytime;
    struct tm* current_time;
    mytime = time(NULL);
    current_time = localtime(&mytime);
    printf("\n\n\t\t\t\t\tEnter user_ID to fetch information :");
    scanf("%d", &my_id);
    data usr_dat = tble->search_user(tble, my_id);
    if (strcmp(usr_dat.usrname, "") != 0)
    {
        printf("\n\t\t\t\t\tRECORD FOUND SUCCESSFULLY !!!");
        printf("\n\n\t\t\t\t\tUser_ID : %d", usr_dat.id);
        printf("\n\t\t\t\t\tName of User : %s", usr_dat.usrname);
        printf("\n\t\t\t\t\tLogin Date And Time : %02d/%02d/%d   %02d:%02d", usr_dat.arrivalTime.day, usr_dat.arrivalTime.mnth, usr_dat.arrivalTime.yr, usr_dat.arrivalTime.hr, usr_dat.arrivalTime.min);
        tothr = (((current_time->tm_hour * 60) + (current_time->tm_min)) - ((usr_dat.arrivalTime.hr * 60) + usr_dat.arrivalTime.min));
        duration = tothr / 60;
        totmin = tothr - (duration * 60);
        printf("\n\t\t\t\t\tDuration : %dHr:%dMin", duration, totmin);
        if (tothr > 300)
        {
            printf("\n\t\t\t\t\tALERT!!! MALICIOUS ACTIVITY");
        }
    }
    else
    {
        printf("\n\t\t\t\t\tRecord not found !!!");
    }

}

void _delete(Hashtable *tble)
{
    system("CLS");
    main_heading();
    time_t mytime;
    struct tm* current_time;
    mytime = time(NULL);
    current_time = localtime(&mytime);
    int my_id;
    printf("\n\t\t\t\t\t|-------- PREVIOUS ENTERED DATA --------|");
    int status = display(tble);
    if (status == 0)
    {
        printf("\n\n\n\t\t\t\tEnter ID of the user which you want to _delete : ");
        scanf("%d", &my_id);
        if (tble->delete_user(tble, my_id, 0) == 0)
        {
            printf("\n\n\t\t\t\t\t|----- Updated Records -----| ");
            display(tble);
        }
    }
    else
    {
        printf("\n\t\t\t\t\tPlease enter data first!!");
    }
    printf("\n\n\t\t\t\t\tPress any key to Continue");
    _getch();
    system("CLS");
    main_heading();
    menu();
}

int display(Hashtable *tble)
{
    printf("\n\n\t\t\t\t\tUSER DETAILS ARE AS FOLLOWS :");
    //printf("\n\t\t\t   ____________________________________________________________________");
    printf("\n\n\t\t\t   User_ID\t\tName of User\t\tDate\t\tTime\t Duration");
    //printf("\n\t\t\t   ____________________________________________________________________");
    int status = tble->show(tble);
    return status;
}

void arrival_time()
{
    time_t rawtime;
    struct tm* timeinfo;
    struct tm* dateinfo;
    char buf[80];
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    dateinfo = localtime(&rawtime);

    strftime(buffer, 80, "%I:%M:%S", timeinfo);
    strftime(buf, 80, "%b %d, %Y", dateinfo);
    printf("\n\n\t\t\t\tArrival Time : %s", buffer);
    printf("\t\tDate : %s", buf);
}

void user_menu()
{
    int choice;
    printf("\n\n\n\t\t\t\t\t\t  |<--MENU-->|");
    printf("\n\n\t\t\t\t\t\t1.View Your Record");
    printf("\n\t\t\t\t\t\t2.Exit");
    printf("\n\n\t\t\t\t\t\tEnter your choice :");
    scanf("%d", &choice);
    Hashtable* tble = create_hashtable(TABLESZ);
    switch (choice)
    {
    case 1: system("CLS");
        search(tble);
        printf("\n\n\t\t\t\t\tPress any key to continue ");
        _getch();
        system("CLS");
        main_heading();
        user_menu();
        break;

    case 2: system("CLS");
        exit(0);
        break;
    }
}

void user_signup()
{
    FILE* fp;
    char usern[11], pass[11];
    char buffer[50];
    printf("\n\t\t\t\t\tEnter Username : ");
    scanf("%s", buffer);
    if (strlen(buffer)<=10)
    {
        strncpy(usern, buffer, 11);
        printf("\n\t\t\t\t\tPassword : ");
        scanf("%s", buffer);
        if (strlen(buffer) <= 10)
        {
            strncpy(pass, buffer, 11);
            fp = fopen("login.txt", "a");
            if (fp == NULL)
            {
                printf("\n\t\t\t\t\tERROR:Cannot signup user");
            }
            else
            {
                fprintf(fp, "%s %s\n", usern, pass);
                fclose(fp);
                printf("\n\t\t\t\t\tNew user created successfully!!");
                printf("\n\n\t\t\t\t\tPress any key to continue ");
                _getch();
                mainlogin(0);
            }
        }
        else
        {
            printf("\n\t\t\t\t\tERROR:Password length can be atmost 10 character!! Try again");
            printf("\n\n\t\t\t\t\tPress any key to continue ");
            _getch();
            mainlogin(0);
        }
    }
    else
    {
        printf("\n\t\t\t\t\tERROR:Username can be atmost 10 character!! Try again");
        printf("\n\n\t\t\t\t\tPress any key to continue ");
        _getch();
        mainlogin(0);
    }

    
}

void login_user()
{
    char u_id[11], p[11];
    char usern[11], pass[11];
    FILE* fp;
    fp = fopen("login.txt", "ab+");
    printf("\n\t\t\t\t\tUsername : ");
    scanf("%s", u_id);
    while (fscanf(fp, "%s %s", &usern, &pass) != EOF)
    {
        if (strcmp(u_id, usern) == 0)
        {
            printf("\n\t\t\t\t\tPassword : ");
            scanf("%s", &p);
            if (strcmp(p, pass) == 0)
            {
                fclose(fp);
                printf("\n\n\t\t\t\t\tWELCOME USER!!! LOGIN SUCCESSFULL");
                printf("\n\n\t\t\t\t\tPress any key to continue ");
                _getch();
                system("CLS");
                main_heading();
                user_menu();
            }
        }
        
    }
    fclose(fp);
    printf("\n\t\t\t\t\tIncorrect username or password");
    printf("\n\t\t\t\t\tTRY AGAIN");
    printf("\n\n\t\t\t\t\tPress any key to continue ");
    _getch();
    mainlogin(0);
}



