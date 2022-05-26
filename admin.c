#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
#include <math.h>
#include <stdbool.h>
#include <conio.h>

long long int incrementor = 1000000000;
node head;

void CreateNewUser(void)
{
    client new_client;
    printf("Please Enter Client Full Name: ");
    gets(new_client.FullName);

    printf("\nPlease Enter Client Full Address: ");
    gets(new_client.FullAddress);

    printf("\nPlease Enter Client National ID: ");
    scanf("%lld", &new_client.NationalID);

    int count = (new_client.NationalID == 0) ? 1 : log10(new_client.NationalID) + 1;
    while (count != 14)
    {
        printf("\nPlease enter your National ID contains 14 digit: ");
        scanf("%lld", &new_client.NationalID);
        count = (new_client.NationalID == 0) ? 1 : log10(new_client.NationalID) + 1;
    }
    printf("\nPlease Enter Client Age: ");
    scanf("%d", &new_client.Age);
    new_client.BankAccountID = incrementor + 1;
    incrementor++;

    new_client.Status = "Active";
    if (new_client.Age < 21)
    {
        printf("\nPlease Enter Client Gardian National ID: ");
        scanf("%lld", &new_client.GardianNationalID);
        int count = (new_client.GardianNationalID == 0) ? 1 : log10(new_client.GardianNationalID) + 1;
        while (count != 14)
        {
            printf("\nPlease enter Gardian National ID contains 14 digit: ");
            scanf("%lld", &new_client.GardianNationalID);
            count = (new_client.GardianNationalID == 0) ? 1 : log10(new_client.GardianNationalID) + 1;
        }
    }
    else
    {
        new_client.GardianNationalID = -1;
    }
    int num = (rand() % (9999 - 1000 + 1)) + 1000;
    new_client.Password = num;

    printf("\nPlease Enter Client Balance: ");
    scanf("%lf", &new_client.Balance);
    fflush(stdin);

    printf("\nUser's Bank Account ID is %lld ", new_client.BankAccountID);
    printf("\nUser's Password is %d ", new_client.Password);
    AddNewUser(new_client);
    printf("\nUser Account created successfully!\n");
    fflush(stdin);
}

void MakeTransaction(long long int currentID)
{
    node *CurrentUser = GetUser(currentID);
    long long int AccountID;
    printf("Enter Client Bank Account ID to transfer money to: ");
    scanf("%lld", &AccountID);
    fflush(stdin);
    node *User = GetUser(AccountID);

    if (User)
    {

        printf("Before");
        printf("\nCurrent User Balance: %lf", CurrentUser->value.Balance);
        printf("\nUser Balance: %lf", User->value.Balance);

        double amount;
        printf("\nPlease enter amount to transfer: ");
        scanf("%lf", &amount);
        fflush(stdin);
        if (CurrentUser->value.Balance >= amount)
        {
            User->value.Balance += amount;
            CurrentUser->value.Balance -= amount;
        }
        else
        {
            printf("The amount you enter exceeds your balance\n");
        }
        printf("\nAfter");
        printf("\nCurrent User Balance: %lf", CurrentUser->value.Balance);
        printf("\nUser Balance: %lf", User->value.Balance);
    }
}

void ChangeAccountStatus(long long int currentID)
{
    node *CurrentUser = GetUser(currentID);
    int input;
    printf("\nChoice Status\n");
    printf("1: Set Account to Active State\n");
    printf("2: Set Account to Restricted State\n");
    printf("3: Set Account to Closed\n");
    printf("Your Choice: ");
    scanf("%d", &input);
    fflush(stdin);
    printf("Current Account Status: %s", CurrentUser->value.Status);
    switch (input)
    {
    case 1:
        CurrentUser->value.Status = "Active";
        break;
    case 2:
        CurrentUser->value.Status = "Restricted";
        break;
    case 3:
        CurrentUser->value.Status = "Closed";
        break;
    default:
        printf("Invalid Choice\n");
        break;
    }
    printf("Current Account Status: %s", CurrentUser->value.Status);
    printf("\nStatus changed successfully");
}

void GetCash(long long int currentID)
{
    node *CurrentUser = GetUser(currentID);
    double amount;
    printf("\nPlease enter amount to get: ");
    scanf("%lf", &amount);
    fflush(stdin);

    printf("Before");
    printf("\nCurrent User Balance: %lf", CurrentUser->value.Balance);
    if (CurrentUser->value.Balance >= amount)
    {
        CurrentUser->value.Balance -= amount;
    }
    else
    {
        printf("\nThe amount you enter exceeds your balance\n");
    }
    printf("\nAfter");
    printf("\nCurrent User Balance: %lf", CurrentUser->value.Balance);
}

void DepositInAccount(long long int currentID)
{
    node *CurrentUser = GetUser(currentID);
    double amount;
    printf("\nPlease enter amount to get: ");
    scanf("%lf", &amount);
    fflush(stdin);

    printf("Before");
    printf("\nCurrent User Balance: %lf", CurrentUser->value.Balance);

    CurrentUser->value.Balance += amount;

    printf("\nAfter");
    printf("\nCurrent User Balance: %lf", CurrentUser->value.Balance);
}

void OpenAccount(void)
{
    long long int AccountID;
    printf("Enter Client Bank Account ID: ");
    scanf("%lld", &AccountID);
    fflush(stdin);
    if (SearchForUser(AccountID))
    {
        int input;
        printf("1: Make Transaction\n");
        printf("2: Change Account Status\n");
        printf("3: Get Cash\n");
        printf("4: Deposit in Account\n");
        printf("5: Return to main Menu\n");
        printf("Your Choice: ");
        scanf("%d", &input);
        fflush(stdin);
        switch (input)
        {
        case 1:
            MakeTransaction(AccountID);
            break;
        case 2:
            ChangeAccountStatus(AccountID);
            break;
        case 3:
            GetCash(AccountID);
            break;
        case 4:
            DepositInAccount(AccountID);
            break;
        case 5:
            return;
            break;
        default:
            printf("Invalid Choice\n");
            break;
        }
    }
    else
    {
        printf("Invalid Bank Account ID\n");
        return;
    }
}

void MainMenu(void)
{
    int input;
    int ExitFlag = 0;
    while (ExitFlag == 0)
    {
        printf("\n1: Create New Account\n");
        printf("2: Open Existing Account\n");
        printf("3: Log out\n");
        printf("Your Choice: ");
        scanf("%d", &input);
        fflush(stdin);
        switch (input)
        {
        case 1:
            CreateNewUser();
            break;
        case 2:
            OpenAccount();
            break;
        case 3:
            printf("Thank You\nGood Bye\n\n");
            ExitFlag = 1;
            break;
        default:
            printf("Invalid Choice please try again\n");
            break;
        }
    }
    return;
}

int HidePassword(void)
{
    int i;
    char ch;
    char *password;
    for (i = 0; i < 10; i++)
    {
        ch = getch();
        password[i] = ch;

        if (ch != 13) // 13 is ASCII of Enter key
            printf("*");
        if (ch == 13)
            break;
    }
    password[i] = '\0';
    int pass = atoi(password);
    return pass;
}

void ChangePassword(long long int currentID)
{
    node *CurrentUser = GetUser(currentID);

    printf("Enter your old password: ");
    int old_password = HidePassword();
    if (CurrentUser->value.Password == old_password)
    {
        printf("\nEnter your new password: ");
        int new_password = HidePassword();
        printf("\nConfirm your new password: ");
        int confirm_password = HidePassword();
        if (confirm_password == new_password)
        {
            CurrentUser->value.Password = new_password;
            printf("\nPassword changed successfully!\n");
            return;
        }
        else
        {
            printf("\nYou entered wrong password");
            return;
        }
    }
    else
    {
        printf("You entered wrong password");
        return;
    }
}

void UserMenu(long long int AccountID)
{

    int input;
    int ExitFlag = 0;
    while (ExitFlag == 0)
    {
        printf("\n1: Make Transaction\n");
        printf("2: Change Account Password\n");
        printf("3: Get Cash\n");
        printf("4: Deposit in Account\n");
        printf("5: Return to main Menu\n");
        printf("Your Choice: ");
        scanf("%d", &input);
        fflush(stdin);
        switch (input)
        {
        case 1:
            MakeTransaction(AccountID);
            break;
        case 2:
            ChangePassword(AccountID);
            break;
        case 3:
            GetCash(AccountID);
            break;
        case 4:
            DepositInAccount(AccountID);
            break;
        case 5:
            ExitFlag = 1;
            return;
        default:
            printf("Invalid Choice\n");
            break;
        }
    }
}


void Login(void)
{
    int input;
    int ID, Password, UserPassword;
    long long int UserID;
    int ExitFlag = 0;
    while (ExitFlag == 0)
    {
        printf("1: Admin\n");
        printf("2: User\n");
        printf("3: Exit System");
        printf("\nYour Choice: ");
        scanf("%d", &input);
        fflush(stdin);
        switch (input)
        {
        case 1:
            printf("Enter Admin ID: ");
            scanf("%d", &ID);
            printf("Enter Admin Password: ");
            Password = HidePassword();
            if (ID == 123 && Password == 123)
            {
                MainMenu();
            }
            else
            {
                printf("Invalid ID or Password\n");
                Login();
            }
            break;
        case 2:
            printf("Enter User Bank Account ID: ");
            scanf("%lld", &UserID);
            printf("Enter your Password: ");
            UserPassword = HidePassword();
            node *User = GetUser(UserID);
            if (User != NULL && User->value.Password == UserPassword)
            {
                UserMenu(UserID);
            }
            else
            {
                printf("Invalid ID or Password\n");
                Login();
            }
            break;
        case 3:
            printf("Thank You\nGood Bye\n");
            ExitFlag = 1;
            break;
        default:
            printf("Invalid Choice\n");
            break;
        }
    }
}


void main(void)
{
    Login();
    system("Pause");
    return;
}