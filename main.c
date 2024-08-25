#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#define MaxLine 256
#define ENTER 13
#define TAB 9
#define BCKSPC 8
#define PATH "C:\\Users\\fcbmo\\Desktop\\Project Files\\"
typedef struct
{
    char FirstName[256];
    char LastName[256];
    char ID[256];
    char Email[256];
    char Password[256];
    char UserName[256];
    char Gender[256];
    char Age[256];
    char PhoneNumber[256];
    bool Delete ; //if Delete = True  Delete the record.
    char Buffer[256];
} UserData;
typedef struct
{
    char CustomerUserName[MaxLine];
    char PolicyType[MaxLine];
    int  PolicyDuration; //In Months
    float PolicyFees;
    float LimitCoverageInYear;
    char PolicyClaimsStatus[MaxLine];
    char PhoneNumber[MaxLine];
    char *StartDate[MaxLine];
    char *PolicyNumber[MaxLine];
    bool Delete; //if Delete = True  Delete the record.
    char Buffer[MaxLine];

} PolicyDetails;
char Path [MaxLine] = {"C:\\Users\\Office\\Desktop\\project\\"};
bool ChecK();
void ClearScreen();
void Chat();
bool ValidID(char s[]);
void EditExistingPolicy();
void GeneratePolicyNumber(PolicyDetails *p1);
bool CheckLastName(char s[]);
void CustomerMenu();
bool CheckName(char s[]);
void EditUserData(UserData *customer);
void ShowDate(PolicyDetails *p1);
void AddNewPolicy();
void isDirectoryExists(const char* path);
void AdminChat();
bool CheckAge(char s[]);
void EditAccountInformation();
bool CheckGender(char s[]);
void CreateCustomerEmail(UserData c1);
bool ValidPassword(char s[]);
bool ValidEmail(char s[]);
bool CheckAdmin(char s[]);
void ShowActivePolicies();
bool CheckCustomer(char s[]);
void DeleteAgentAccount();
bool CheckAgent(UserData s);
void UpdateUserDataFile(UserData *updatedCustomer);
void DeleteAccount();
void CreateAgentAccount();
void ShowAgentAccount();
void CustomerMenu();
void AdminMenu();
void AgentMenu();
void StartMenu();
void ShowData();
void DeleteExistingCustomerAccount();
void Login();
void SignUp();
void CreateAdminAccount();
void Exit();
bool CheckPhoneNumber();
void Edit(char s[],UserData Customer ,char ch);
void cin (char ch[]);
void DeleteExistingAgentAccount();
void ModifyInformationOfAgentAccount();
void HidePassword(char pwd[]);
void CreateCustomerAccount();
int main()
{
    system("color 0b");
    char choice[100];
    do {
        StartMenu();
        printf("Enter your choice: ");
        scanf("%s", &choice);
        if (choice[0]=='1'&&strlen(choice)==1)
        {
            ClearScreen();
            Login();
            break;
        }
        else if (choice[0]=='2'&&strlen(choice)==1)
        {
            ClearScreen();
            SignUp();
            break;
        }
        else if (choice[0]=='3'&&strlen(choice)==1)
        {
            ClearScreen();
            Complains();
            break;
        }
        else if (choice[0]=='4'&&strlen(choice)==1)
        {
            ClearScreen();
            Exit();
            break;
        }
        else
        {
            ClearScreen();
            printf("Invalid choice. Please try again.\n");
            Beep(800,300);
        }
    }
    while(true);
    return 0;
}
bool ChecK(char s[])
{
    int n=strlen(s);
    if(n!=1)
        return false;
    if(s[0]=='y' || s[0]=='Y' || s[0]=='n' || s[0]=='N' )
        return true;
    else
        return false;
}
void StartMenu()
{
    printf("\n____ LIFEGUARD Company Management System ____\n");
    printf("1: Login\n");
    printf("2: Sign Up\n");
    printf("3: Reach Us\n");
    printf("4: Exit\n");
}
void GenerateUsername(char email[50],char username[50])
{
    for(int i=0;i<strlen(email);i++)
    {
        if(email[i] == '@') break;
        else username[i] = email[i];
    }

}
void ClearScreen()
{
    printf("\e[1;1H\e[2J");
}
bool ValidID(char s[])
{
    if(strlen(s)!=14)
        return false;
    for (int i = 0; i < strlen(s); ++i) {
        if(!(s[i]>='0'&&s[i]<='9')){
            return false;
        }
    }
    return true;
}
void cin (char ch[])
{
    scanf("%s",ch);
}
void HidePassword(char password[])
{
    int i;
    char ch;
    while(1){
        ch = getch();
        if(ch == ENTER || ch == TAB){
            password[i] = '\0';
            break;
        }else if(ch == BCKSPC){
            if(i>0){
                i--;
                printf("\b \b");
            }
        }else{
            password[i++] = ch;
            printf("* \b");
        }
    }
}
bool ValidEmail(char s[])
{
    int x=0,y=0;
    for (int i = 1; i < strlen(s); ++i) {
        if (s[i]==' '){
            return false;
        }
        if (s[i]=='@'&&s[i+1]!='.'){
            x++;
        }
        if (s[i]=='.'&&s[i-1]!='@'&&x>0){
            y++;
            break;
        }
    }
    if (x>0&&y>0)
        return true;
    else return false;
}
bool ValidPassword(char s[])
{
    int Chr=0,chr=0,num=0,spc=0;
    for (int i = 0; i < strlen(s); ++i) {
        if (s[i]==' '){
            return false;
        }else if (s[i]>='a'&&s[i]<='z'){
            chr++;
        }else if (s[i]>='A'&&s[i]<='Z'){
            Chr++;
        }else if (s[i]>='0'&&s[i]<='9'){
            num++;
        }else {
            spc++;
        }
    }
    if (Chr>0&&chr>0&&num>0&&spc>0&&strlen(s)>=8){
        return true;
    }
    else
        return false;
}
void DeleteAccount()
{
    ClearScreen();
    printf("Enter User Name To Delete: \n");
    char s [MaxLine];
    cin(s);
    FILE *UserFilePointer = fopen("C:\\Users\\Office\\Desktop\\project\\UserData.bin","ab+");
    if (UserFilePointer == NULL) {
        printf("Cannot Open The File.\n");
        return ;
    }
    UserData customer;
    while(fread(&customer,sizeof(UserData),1,UserFilePointer))
    {
        if(strcmp(customer.UserName,s))
        {
            printf("Are You Sure You Want To Delete %s ? (Y/N)\n",s);
            char ch;
            cin(&ch);
            if(ch=='y' || ch =='Y')
            {
                customer.Delete = true ;
                ClearScreen();
                printf("Account Deleted Successfully. \n");
                strcat(Path,s);
                rmdir(Path);
            }
        }
        else
        {
            Beep(800,300);
            ClearScreen();
            printf("User Name Not Found.\n");
            printf("Please Try Again.\n");
            DeleteAccount();
        }
    }
}
void CreateAgentAccount()
{
    ClearScreen();
    UserData Agent ;
    printf("Enter First Name: \n");
    cin(Agent.FirstName);
    while (CheckName(Agent.FirstName)!=true||strlen(Agent.FirstName)<1)
    {
        printf("Invalid Name. Try again\n");
        Beep(800,300);
        printf("Enter First Name: \n");
        cin(Agent.FirstName);
    }
    printf("Enter Last Name: \n");
    char temp[1000];
    fgets(temp,sizeof(temp),stdin);
    fgets(Agent.LastName,sizeof(Agent.LastName),stdin);
    while (CheckLastName(Agent.LastName)!=true||strlen(Agent.LastName)<1)
    {
        printf("Invalid Name. Please Try Again\n");
        Beep(800,300);
        printf("Enter Last Name: \n");
        fgets(temp,sizeof(temp),stdin);
        fgets(Agent.LastName,sizeof(Agent.LastName),stdin);
    }
    printf("Enter The Agent's National ID: \n");
    cin(Agent.ID);
    while(ValidID(Agent.ID)!=true||strlen(Agent.ID)<1)
    {
        printf("Invalid ID. Please Try Again\n");
        Beep(800,300);
        printf("Enter The Agent's National ID: \n");
        cin(Agent.ID);
    }

    printf("Enter The Agent's Email Address: \n");
    cin(Agent.Email);
    while (ValidEmail(Agent.Email)!=true||strlen(Agent.Email)<1)
    {
        printf("Invalid Email.Please Try again\n");
        Beep(800,300);
        printf("Enter The Agent's Email Address: \n");
        cin(Agent.Email);
    }
    printf( "Enter 'M' For Male 'F' For Female.\nEnter The Agent's Gender:\n");
    cin(Agent.Gender);
    if(Agent.Gender=="M"||Agent.Gender=="m")
    {
        strcpy(Agent.Gender,"Male");
    }
    else if(Agent.Gender=="F"||Agent.Gender=="f")
    {
        strcpy(Agent.Gender,"Female");
    }
    while(CheckGender(Agent.Gender)!=true||strlen(Agent.Gender)<1)
    {
        printf("Invalid Gender. Please Try Again\n");
        Beep(800,300);
        printf( "Enter The Agent's Gender:\nEnter 'M' For Male 'F' For Female : \n");
        cin(Agent.Gender);
        if(Agent.Gender=="M"||Agent.Gender=="m")
        {
            strcpy(Agent.Gender,"Male");
        }
        else if(Agent.Gender=="F"||Agent.Gender=="f")
        {
            strcpy(Agent.Gender,"Female");
        }
    }
    printf("Enter The Agent's Age: \n");
    cin(Agent.Age);
    while(CheckAge(Agent.Age)!=true||strlen(Agent.Age)<1)
    {
        printf("Invalid Age. Please Try Again\n");
        Beep(800,300);
        printf("Enter The Agent's Age: \n");
        cin(Agent.Age);
    }

    printf("Enter The Agent's Phone Number: \n");
    cin(Agent.PhoneNumber);
    while(CheckPhoneNumber(Agent.PhoneNumber)!=true)
    {
        printf("Invalid Number. Please Try Again\n");
        Beep(800,300);
        printf("Enter The Agent's Phone Number: \n");
        cin(Agent.PhoneNumber);
    }
    GenerateUsername(Agent.Email,Agent.UserName);
    strcpy(Agent.Password,"Agent123");
    printf("The Agent's User Name is: %s\nThe Agent's Password is: %s\n",Agent.UserName,Agent.Password);
    FILE *AgentData=fopen("C:\\Users\\Office\\Desktop\\project\\AgentData.bin","ab+");
    fwrite(&Agent,sizeof(Agent),1,AgentData);
    fclose(AgentData);
    AdminMenu();
}
void ShowAgentAccount()
{
    ClearScreen();
    FILE *AgentData=fopen("C:\\Users\\Office\\Desktop\\project\\AgentData.bin","rb");
    FILE *View=fopen("C:\\Users\\Office\\Desktop\\project\\AgentsAccount.csv","w");
    if(AgentData==NULL)
    {
        printf("Error Opening File\n");
        return;
    }
    UserData temp;
    bool flag =false;
    while(fread(&temp,sizeof(UserData),1,AgentData))
    {
        if (temp.Delete==false)
        {
            fprintf(View,"%s , %s , %s , %s , %s , %s , %s \n",temp.FirstName,temp.LastName,temp.Email,temp.ID,temp.Gender,temp.Age,temp.PhoneNumber);
            flag=true;
        }
    }
    if(flag)
    {
        printf("Data is in file \"AgentsData\"\n");
    }
    else
    {
        Beep(800,300);
        printf("ERROR\n");
    }
    fclose(AgentData);
    fclose(View);
    AdminMenu();
}
void DeleteAgentAccount()
{
    ClearScreen();
    FILE *AgentData=fopen("C:\\Users\\Office\\Desktop\\project\\AgentData.bin","ab+");
    FILE *NewFile=fopen("C:\\Users\\Office\\Desktop\\project\\New.bin","ab+");
    UserData Agent,temp;
    bool flag=false;
    printf("Enter The Agent's User Name: ");
    scanf("%s",Agent.UserName);
    while (fread(&temp,sizeof(UserData),1,AgentData))
    {
        if (strcmp(Agent.UserName,temp.UserName))
        {
            temp.Delete=true;
            flag = true;
        }
        fwrite(&temp,sizeof(UserData),1,NewFile);
    }
    remove(AgentData);
    rename(NewFile,"C:\\Users\\Office\\Desktop\\project\\AgentData.bin");
    fclose(AgentData);
    fclose(NewFile);
    if (flag){
        printf("Account Deleted Successfully.\n");
    }else {
        printf("ERROR\n");
    }
    AdminMenu();
}
void AdminMenu()
{
    printf("Welcome.\n");
    printf("1:Create New Agent Account\n");
    printf("2:Create New Admin Account\n");
    printf("3:Delete Existing Agent Account\n");
    printf("4:Modify Information of Agent Account\n");
    printf("5:Show All Agent Accounts\n");
    printf("6:View Data\n");
    printf("7:Customer Chat\n");
    printf("8:Main Menu\n");
    printf("9:Exit\n");
    printf("Enter Your Choice: \n");
    char choice[100];
    do{
        scanf("%s",choice);
        if (choice[0]=='1'&&strlen(choice)==1)
        {
            CreateAgentAccount();
            break;
        }
        else if (choice[0]=='3'&&strlen(choice)==1)
        {
            DeleteAgentAccount();
            break;
        }
        else if (choice[0]=='4'&&strlen(choice)==1)
        {
            ModifyInformationOfAgentAccount();
            break;
        }
        else if (choice[0]=='5'&&strlen(choice)==1)
        {
            ShowAgentAccount();
            break;
        }
        else if (choice[0]=='6'&&strlen(choice)==1)
        {
            ShowData();
            break;
        }
        else if (choice[0]=='2'&&strlen(choice)==1)
        {
            CreateAdminAccount();
            break;
        }
        else if (choice[0]=='7'&&strlen(choice)==1)
        {
            ClearScreen();
            AdminChat();
            break;
        }
        else if (choice[0]=='8'&&strlen(choice)==1)
        {
            ClearScreen();
            main();
            break;
        }else if (choice[0]=='9'&&strlen(choice)==1){
            Exit();
            break;
        }
        else
        {
            printf("Invalid Choice. Please try Again\n");
        }
    }while(true);
}
void Login()
{
    FILE *UserFilePointer = fopen("C:\\Users\\Office\\Desktop\\project\\UserData.bin","ab+");
    FILE *AdminDataPTR = fopen("C:\\Users\\Office\\Desktop\\project\\AdminData.bin","ab+");
    FILE *AgentDataPTR = fopen("C:\\Users\\Office\\Desktop\\project\\AgentData.bin","ab+");
    char Email[256];
    char Password[256];
    UserData customer;
    printf("Enter Your Email:\n");
    cin(Email);
    printf("Enter your password:\n");
    HidePassword(Password);
    while(fread(&customer,sizeof(UserData),1,UserFilePointer))
    {
        if(strcmp(customer.Email,Email)==0&&customer.Delete==false)
        {
            if(strcmp(customer.Password,Password)==0)
            {
                ClearScreen();
                CustomerMenu();
                return;
            }
        }
    }
    fclose(UserFilePointer);
    while(fread(&customer,sizeof(UserData),1,AdminDataPTR))
    {
        if(strcmp(customer.Email,Email)==0&&customer.Delete==false)
        {
            if(strcmp(customer.Password,Password)==0)
            {
                ClearScreen();
                AdminMenu();
            }
        }
    }
    fclose(AdminDataPTR);
    while(fread(&customer,sizeof(UserData),1,AgentDataPTR))
    {
        if(strcmp(customer.Email,Email)==0&&customer.Delete==false)
        {
            if(strcmp(customer.Password,Password)==0)
            {
                ClearScreen();
                AgentMenu();
            }
        }
    }
    fclose(AgentDataPTR);
    ClearScreen();
    Beep(800,300);
    printf("Invalid Email Or Password!.\n");
    main();
    return ;

}
void ShowDate(PolicyDetails *p1)
{
    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    char formattedDate[MaxLine];
    sprintf(formattedDate, "%d-%02d-%02d", date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);
    strncpy(p1->StartDate, formattedDate, 20);
    p1->StartDate[19] = '\0';
}
void GeneratePolicyNumber(PolicyDetails *p1)
{
    static long long policy_counter = 1001;
    snprintf(p1->PolicyNumber, sizeof (policy_counter), "%llu", policy_counter);
    policy_counter++;
}
void AddNewPolicy()
{
    ClearScreen();
    if(CheckAgent)
    {
        ClearScreen();
        FILE *Policy;
        Policy = fopen("C:\\Users\\Office\\Desktop\\project\\Policies.bin","ab+");
        if (Policy == NULL)
        {
            printf("File not found.\n");
            return;
        }
        PolicyDetails p1;
        printf("Enter Username: \n");
        scanf("%s",p1.CustomerUserName);
        printf("Enter Customer Phone Number: \n");
        scanf("%s",p1.PhoneNumber);
        printf("1.Health \n2.Vehicle \n3.Property\nEnter Policy Type: ");
        char choice[100];
        scanf("%s",choice);
        while((choice[0]=='1'||choice[0]=='2'||choice[0]=='3')&&strlen(choice)>1)
        {
            printf("Invalid Choice. Please Try Again\n");
            printf("1.Health \n2.Vehicle \n3.Property\nEnter Policy Type: ");
            scanf("%s",choice);
        }
        if(choice[0]=='1')
        {
            strcpy(p1.PolicyType,"Health");
        }
        else if(choice[0]=='2')
        {
            strcpy(p1.PolicyType,"Vehicle");
        }
        else if(choice[0]=='3')
        {
            strcpy(p1.PolicyType,"Property");
        }
        strcpy(p1.PolicyClaimsStatus,"Under Review");
        printf("Enter Policy Duration (in months): \n");
        scanf("%d",&p1.PolicyDuration);
        printf("Enter Policy Fees: \n");
        scanf("%f",&p1.PolicyFees);
        ShowDate(&p1);
        GeneratePolicyNumber(&p1);
        p1.LimitCoverageInYear = (p1.PolicyFees*12)*3;
        fwrite(&p1,sizeof(PolicyDetails),1,Policy);
        fclose(Policy);
        ClearScreen();
        printf("Policy added successfully.\n\n");
        printf("Customer User Name: %s \t\t Start Date: %s \nCustomer Phone Number: %s \nPolicy Type: %s \t\t Policy Duration: %d\nPolicy Fees: %f$ \t\t Policy Number: %s\nClaim Status: %s\nLimit Coverage In A Year: %f$\n\n\n",p1.CustomerUserName,p1.StartDate,p1.PhoneNumber,p1.PolicyType,p1.PolicyDuration,p1.PolicyFees,p1.PolicyNumber,p1.PolicyClaimsStatus,p1.LimitCoverageInYear);
    }
    AgentMenu();
}
void CustomerMenu()
{
    char choice[100];
    printf("1:Edit Account Information\n");
    printf("2:Show Active Policies\n");
    printf("3:Complains\n");
    printf("4:Chat With an Admin\n");
    printf("5:Main Menu\n");
    printf("6:Exit\n");
    do{
        printf("Enter Your Choice: ");
        scanf("%s",choice);
        if (choice[0]=='1'&&strlen(choice)==1)
        {
            EditAccountInformation();
            break;
        }
        else if (choice[0]=='2'&&strlen(choice)==1)
        {
            ShowActivePolicies();
            break;
        }
        else if (choice[0]=='3'&&strlen(choice)==1)
        {
            ClearScreen();
            Complains();
            break;
        }
        else if (choice[0]=='4'&&strlen(choice)==1)
        {
            ClearScreen();
            Chat();
            break;
        }
        else if (choice[0]=='5'&&strlen(choice)==1)
        {
            ClearScreen();
            main();
            break;
        }
        else if (choice[0]=='6'&&strlen(choice)==1)
        {
            ClearScreen();
            Exit();
            break;
        }
        else
        {
            printf("Invalid Choice. Please Try Again\n");
        }
    }while(true);
}
void AgentMenu()
{
UserData *p1;
    printf("1:Add New Policy.\n");
    printf("2:Edit Existing Policy\n");
    printf("3:Edit Existing Customer Account\n");
    printf("4:Create New Customer Account\n");
    printf("5:Main Menu\n");
    printf("6:Exit\n");
    do{
        char choice[100];
        printf("Enter Choice: ");
        scanf("%s",choice);
        if (choice[0]=='1'&&strlen(choice)==1)
        {
            AddNewPolicy();
            break;
        }
        else if (choice[0]=='2'&&strlen(choice)==1)
        {
            EditExistingPolicy();
            break;
        }
        else if (choice[0]=='3'&&strlen(choice)==1)
        {
            EditUserData(p1);
            break;
        }else if (choice[0]=='4'&&strlen(choice)==1)
        {
            CreateCustomerAccount();
            break;
        }else if (choice[0]=='5'&&strlen(choice)==1)
        {
            ClearScreen();
            main();
            break;
        }
        else if (choice[0]=='6'&&strlen(choice)==1)
        {
            ClearScreen();
            Exit();
            break;
        }
        else
        {
            printf("Invalid Choice. Please Try Again\n");
        }
    }while(true);
}
bool CheckLastName(char s[])
{
    bool flag=false;
    for (int i = 0; i < strlen(s); i++)
    {
        if ((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') || (flag)&&s[i]==' '||s[i]=='\n')
        {
            flag=true;
        }
        else
        {
            return false;
        }
    }
    return true;
}
bool CheckName(char s[])
{
    bool flag=false;
    for (int i = 0; i < strlen(s); i++)
    {
        if ((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z'))
        {
            flag=true;
        }
        else
        {
            return false;
        }
    }
    return true;
}
bool CheckAge(char s[])
{
    for (int i = 0; i < strlen(s); i++) {
        if (s[i]<'0'||s[i]>'9'){
            return false;
        }
    }
    if (strlen(s) < 2 || strlen(s) == 2&&s[0]<='1'&&s[1]<'8')
    {
        return false;
    }
    return true;
}
bool CheckGender(char s[])
{
    int n=strlen(s);
    if(n!=1)
        return false;
    if(s[0]=='m' || s[0]=='M' || s[0]=='f' || s[0]=='F' )
        return true;
    else
        return false;
}
bool CheckPhoneNumber(char s[])
{
    if ((s[0]=='0'&& s[1]=='1'&&(s[2]=='1'||s[2]=='2'||s[2]=='5'||s[2]=='0'))&&strlen(s)==11) {
        for (int i = 2; i < strlen(s); ++i) {
            if (s[i] >= '0' && s[i] <= '9') {
                continue;
            } else return false;
        }
    }
    else return false;
    return true ;
}
void EditUserData(UserData *customer)
{
    int choice;
    bool dataChanged = false;
    ClearScreen();
    do {
        printf("\nEdit User Data Menu:\n");
        printf("1. First Name\n");
        printf("2. Last Name\n");
        printf("3. National ID\n");
        printf("4. Email Address\n");
        printf("5. Gender\n");
        printf("6. Age\n");
        printf("7. Phone Number\n");
        printf("8. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter new First Name: \n");
                cin(customer->FirstName);
                dataChanged = true;
                break;
            case 2:
                printf("Enter new Last Name: \n");
                cin(customer->LastName);
                dataChanged = true;
                break;
            case 3:
                printf("Enter new National ID: \n");
                cin(customer->ID);
                dataChanged = true;
                break;
            case 4:
                printf("Enter new Email Address: \n");
                cin(customer->Email);
                dataChanged = true;
                break;
            case 5:
                printf("Enter new Gender ('M' for Male, 'F' for Female): \n");
                cin(customer->Gender);
                dataChanged = true;
                break;
            case 6:
                printf("Enter new Age: \n");
                cin(customer->Age);
                dataChanged = true;
                break;
            case 7:
                printf("Enter new Phone Number: \n");
                cin(customer->PhoneNumber);
                dataChanged = true;
                break;
            case 8:
                if (dataChanged)
                {
                    UpdateUserDataFile(customer);
                }
                printf("Exiting edit menu.\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                Beep(800, 300);
        }
    } while (choice != 8);
}
void UpdateUserDataFile(UserData *updatedCustomer)
{
    ClearScreen();
    UserData *allUsers = NULL;
    UserData tempUser;
    size_t userCount = 0;
    FILE *file = fopen("C:\\Users\\Office\\Desktop\\project\\UserData.bin", "rb+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Read all records into a dynamically allocated array
    while (fread(&tempUser, sizeof(UserData), 1, file))
    {
        allUsers = realloc(allUsers, (userCount + 1) * sizeof(UserData));
        if (allUsers == NULL)
        {
            printf("Memory allocation failed.\n");
            fclose(file);
            return;
        }
        if (strcmp(tempUser.Email, updatedCustomer->Email) == 0)
        {
            allUsers[userCount++] = *updatedCustomer; // Update the existing record
        }
        else
        {
            allUsers[userCount++] = tempUser; // Copy the existing record
        }
    }

    // Rewind the file to the beginning for writing
    rewind(file);

    // Write all records back to the file
    for (size_t i = 0; i < userCount; i++)
    {
        fwrite(&allUsers[i], sizeof(UserData), 1, file);
    }

    // Clean up
    free(allUsers);
    fclose(file);
    printf("Data updated successfully.\n");
    CustomerMenu();
}
void ShowData()
{
    ClearScreen();
    FILE *fptr_Data= fopen("C:\\Users\\Office\\Desktop\\project\\UserData.bin","rb");
    FILE *fptr_show= fopen("C:\\Users\\Office\\Desktop\\project\\ViewData.csv","w");
    UserData temp;
    bool flag = false ;
    while(fread(&temp,sizeof(UserData),1,fptr_Data))
    {
        if (temp.Delete==false)
        {
            fprintf(fptr_show,"%s , %s , %s , %s , %s , %s , %s \n",temp.FirstName,temp.LastName,temp.Email,temp.ID,temp.Gender,temp.Age,temp.PhoneNumber);
            flag = true ;
        }
    }
    if(flag)
    {
        printf("Data is in file \"ViewData\"\n");
        AdminMenu();
    }
    else
    {
        Beep(800,300);
        printf("ERROR\n");
    }
    fclose(fptr_show);
    fclose(fptr_Data);
    AdminMenu();
    return;
}
void CreateAdminAccount()
{
    ClearScreen();
    UserData c1;
    printf("Enter Email: ");
    scanf("%s",c1.Email);
    while(ValidEmail(c1.Email)==false)
    {
        printf("Invalid Email. Please Try Again.\n");
        Beep(800,300);
        printf("Enter Email: ");
        scanf("%s",c1.Email);
    }
    printf("Password Must Include at Least: \n");
    printf("Eight Characters Long.\nOne Special Character.\nOne Upper Case Letter.\nOne Lower Case Letter.\nOne Digit.\n");
    printf("Enter Password: \n");
    scanf("%s",c1.Password);
    while(ValidPassword(c1.Password)==false)
    {
        ClearScreen();
        Beep(800,300);
        printf("Invalid Password. Please Try Again.\n");
        printf("Password Must Include at Least: \n");
        printf("Eight Characters Long.\nOne Special Character.\nOne Upper Case Letter.\nOne Lower Case Letter.\nOne Digit.\n");
        printf("Enter Password: ");
        scanf("%s",c1.Password);
    }
    FILE *LoginPTR = fopen("C:\\Users\\Office\\Desktop\\project\\AdminData","ab+");
    fwrite(&c1.Email,sizeof(c1.Email),1,LoginPTR);
    if(fwrite == 0)
    {
        ClearScreen();
        Beep(800,300);
        printf("Something Went Wrong.\n");
    }
    fwrite(&c1.Password,sizeof(c1.Email),1,LoginPTR);
    if(fwrite == 0)
    {
        ClearScreen();
        Beep(800,300);
        printf("Something Went Wrong.\n");
    }
    fclose(LoginPTR);
    ClearScreen();
    printf("Account Created Successfully.");
    AdminMenu();
}
void SignUp()
{
    UserData Customer ;
    ClearScreen();
    printf("Enter First Name: \n");
    cin(Customer.FirstName);
    while (CheckName(Customer.FirstName)!=true||strlen(Customer.FirstName)<1)
    {
        printf("Invalid Name. Try again\n");
        Beep(800,300);
        printf("Enter First Name: \n");
        cin(Customer.FirstName);
    }
    printf("Enter Last Name: \n");
    getchar();
    fgets(Customer.LastName,sizeof(Customer.LastName),stdin);
    while (CheckLastName(Customer.LastName)!=true||strlen(Customer.LastName)<1)
    {
        printf("Invalid Name. Please Try Again\n");
        Beep(800,300);
        getchar();
        fgets(Customer.LastName,sizeof(Customer.LastName),stdin);
    }
    printf("Enter Your National ID: \n");
    cin(Customer.ID);
    while(ValidID(Customer.ID)!=true||strlen(Customer.ID)<1)
    {
        printf("Invalid ID. Please Try Again\n");
        Beep(800,300);
        printf("Enter Your National ID: \n");
        cin(Customer.ID);
    }

    printf("Enter Your Email Address: \n");
    cin(Customer.Email);
    while (ValidEmail(Customer.Email)!=true||strlen(Customer.Email)<1)
    {
        printf("Invalid Email.Please Try again\n");
        Beep(800,300);
        printf("Enter Your Email Address: \n");
        cin(Customer.Email);
    }
    printf( "Enter 'M' For Male 'F' For Female\nEnter Your Gender:\n");
    cin(Customer.Gender);
    if(strcmp(Customer.Gender,"M")||strcmp(Customer.Gender,"m"))
    {
        strcpy(Customer.Gender,"Male");
    }
    else if(strcmp(Customer.Gender,"F")||strcmp(Customer.Gender,"f"))
    {
        strcpy(Customer.Gender,"Female");
    }
    /*while(CheckGender(Customer.Gender)!=true||strlen(Customer.Gender)<1)
    {
        printf("Invalid Gender. Please Try Again\n");
        Beep(800,300);
        printf( "Enter 'M' For Male 'F' For Female\nEnter Your Gender:");
        cin(Customer.Gender);
        if(strcmp(Customer.Gender,"M")||strcmp(Customer.Gender,"m"))
        {
            strcpy(Customer.Gender,"Male");
        }
        else if(Customer.Gender=="F"||Customer.Gender=="f")
        {
            strcpy(Customer.Gender,"Female");
        }
    }*/
    GenerateUsername(Customer.Email,Customer.UserName);
    printf("Enter Your Age: \n");
    cin(Customer.Age);
    while(CheckAge(Customer.Age)!=true||strlen(Customer.Age)<1)
    {
        printf("Invalid Age. Please Try Again\n");
        Beep(800,300);
        printf("Enter Your Age: \n");
        cin(Customer.Age);
    }

    printf("Enter Your Phone Number: \n");
    cin(Customer.PhoneNumber);
    while(CheckPhoneNumber(Customer.PhoneNumber)!=true)
    {
        printf("Invalid Number. Please Try Again\n");
        Beep(800,300);
        printf("Enter Your Phone Number: \n");
        cin(Customer.PhoneNumber);
    }
    strcpy(Customer.Password,"00000");
    FILE *UserFilePointer= fopen("C:\\Users\\Office\\Desktop\\project\\UserData.bin","ab+");
    fwrite(&Customer,sizeof(UserData),1,UserFilePointer);
    if(fwrite != 0)
    {
        strcat(Path,Customer.UserName);
        mkdir(Path);
        printf("\n\nYour UserName is: %s\n",Customer.UserName);
        printf("Your Password is: %s\n",Customer.Password);
        main();
    }
    else
    {
        printf("Something Went Wrong.\n");
        Beep(800,300);
        Exit();
    }
    fclose(UserFilePointer);
    main();
}
void Exit()
{
    ClearScreen();
    printf("Exiting the program. Thank you.\n");
    exit(0);
}
void CreateCustomerAccount()
{
    ClearScreen();
    UserData customer;
    printf("Enter First Name: ");
    scanf("%s",customer.FirstName);
    customer.FirstName[strcspn(customer.FirstName, "\n")] = 0;
    while (!CheckName(customer.FirstName))
    {
        printf("Invalid Name. Try again: ");
        scanf("%s",customer.FirstName);
        customer.FirstName[strcspn(customer.FirstName, "\n")] = 0;
    }
    printf("Enter Last Name: \n");
    getchar();
    fgets(customer.LastName, sizeof(customer.LastName), stdin);
    customer.LastName[strcspn(customer.LastName, "\n")] = 0;
    while (!CheckName(customer.LastName))
    {
        printf("Invalid Name. Try again: \n");
        getchar();
        fgets(customer.LastName, sizeof(customer.LastName), stdin);
        customer.LastName[strcspn(customer.LastName, "\n")] = 0;
    }

    printf("Enter Email Address: ");
    scanf("%s",customer.Email);
    customer.Email[strcspn(customer.Email, "\n")] = 0;
    while (!ValidEmail(customer.Email))
    {
        printf("Invalid Email. Try again: ");
        scanf("%s",customer.Email);
        customer.Email[strcspn(customer.Email, "\n")] = 0;
    }
    printf("Enter Gender (Male/Female): ");
    scanf("%s",customer.Gender);
    customer.Gender[strcspn(customer.Gender, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%s",customer.Age);
    customer.Age[strcspn(customer.Age, "\n")] = 0;

    printf("Enter Phone Number: ");
    scanf("%s",customer.PhoneNumber);
    customer.PhoneNumber[strcspn(customer.PhoneNumber, "\n")] = 0;
    while (!CheckPhoneNumber(customer.PhoneNumber))
    {
        printf("Invalid Phone Number. Try again: ");
        scanf("%s",customer.PhoneNumber);
        customer.PhoneNumber[strcspn(customer.PhoneNumber, "\n")] = 0;
    }
    FILE* file = fopen("C:\\Users\\Office\\Desktop\\project\\CustomerData.bin", "ab+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    fwrite(&customer, sizeof(UserData), 1, file);
    fclose(file);
    printf("Customer Account Created Successfully.\n");
    AgentMenu();
}
void DeleteExistingAgentAccount()
{
    ClearScreen();
    char username[MaxLine];
    printf("Enter User Name Of The Agent To Delete: ");
    scanf("%s", &username);

    FILE *file = fopen("C:\\Users\\Office\\Desktop\\project\\AgentData.bin", "rb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    UserData *agents = NULL;
    int count = 0;
    UserData temp;

    // Read all agents into memory except the one to delete
    while (fread(&temp, sizeof(UserData), 1, file))
    {
        if (strcmp(temp.ID, username) != 0)
        {
            agents = realloc(agents, (count + 1) * sizeof(UserData));
            if (agents == NULL)
            {
                printf("Memory allocation error.\n");
                fclose(file);
                return;
            }
            agents[count++] = temp;
        }
    }
    fclose(file);
    // Write the updated list back to the file
    file = fopen("C:\\Users\\Office\\Desktop\\project\\AgentData.bin", "wb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        free(agents);
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fwrite(&agents[i], sizeof(UserData), 1, file);
    }
    fclose(file);
    free(agents);

    printf("Agent account deleted successfully.\n");
    AdminMenu();
}
void DeleteExistingCustomerAccount()
{
    ClearScreen();
    char username[MaxLine];
    printf("Enter User Name Of The Customer To Delete: ");
    scanf("%s",&username);

    FILE *file = fopen("C:\\Users\\Office\\Desktop\\project\\CustomerData.bin", "rb");
    if (file == NULL)
    {
        printf("Error Opening File.\n");
        return;
    }

    // Temporary array to hold customers except the one to delete
    UserData *customers = NULL;
    int count = 0;
    UserData temp;

    // Read all customers into memory except the one to delete
    while (fread(&temp, sizeof(UserData), 1, file))
    {
        if (strcmp(temp.ID,username) != 0)
        {
            customers = realloc(customers, (count + 1) * sizeof(UserData));
            if (customers == NULL)
            {
                printf("Memory Allocation Error.\n");
                fclose(file);
                return;
            }
            customers[count++] = temp;
        }
    }
    fclose(file);
    // Write the updated list back to the file
    file = fopen("C:\\Users\\Office\\Desktop\\project\\CustomerData.bin", "wb");
    if (file == NULL)
    {
        printf("Error Opening File.\n");
        free(customers);
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fwrite(&customers[i], sizeof(UserData), 1, file);
    }
    fclose(file);
    free(customers);

    printf("Customer Account Deleted Successfully.\n");
    AdminMenu();
}
void ModifyInformationOfAgentAccount()
{
    ClearScreen();
    char username[MaxLine];
    printf("Enter User Name Of The Agent To Modify: ");
    scanf("%s", username);
    FILE *file = fopen("C:\\Users\\Office\\Desktop\\project\\AgentData.bin", "rb+");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    UserData temp;
    int found = 0;
    long pos;

    while (fread(&temp, sizeof(UserData), 1, file))
    {
        if (strcmp(temp.UserName, username) == 0)
        {
            found = 1;
            printf("Current Information:\n");
            printf("First Name: %s\n", temp.FirstName);
            printf("Last Name: %s\n", temp.LastName);
            printf("Email: %s\n", temp.Email);
            printf("ID: %s\n", temp.ID);

            // Get New Data From User
            printf("Enter new First Name: ");
            scanf("%s", temp.FirstName);
            printf("Enter new Last Name: ");
            scanf(" %[^\n]%*c", temp.LastName);
            printf("Enter new Email: ");
            scanf("%s", temp.Email);

            pos = ftell(file) - sizeof(UserData);
            if (fseek(file, pos, SEEK_SET) != 0)
            {
                perror("Error seeking in file");
                break;
            }

            // Write The Updated Record
            if (fwrite(&temp, sizeof(UserData), 1, file) != 1)
            {
                perror("Error writing to file");
                break;
            }
            printf("Agent information updated successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("No agent found with this username: %s.\n", username);
    }

    fclose(file);
    AdminMenu();
}
//Not Working...TRY!!!!!!!
void EditExistingPolicy()
{
    ClearScreen();
    char policyNumber[MaxLine];
    printf("Enter the Policy Number of the policy to modify: ");
    scanf("%s", policyNumber);
    FILE *file = fopen("C:\\Users\\Office\\Desktop\\project\\Policies.bin", "rb+");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    PolicyDetails temp;
    int found = 0;
    long pos;

    while (fread(&temp, sizeof(PolicyDetails), 1, file))
    {
        if (strcmp(temp.PolicyNumber, policyNumber) )
        {
            found = 1;
            printf("Current Information:\n");
            printf("Policy Number: %s\n", temp.PolicyNumber);
            printf("Policy User Name: %s\n", temp.CustomerUserName);
            printf("Policy Type: %s\n", temp.PolicyType);
            printf("Premium Amount: %.2f\n", temp.PolicyFees);
            printf("Duration (Months): %d\n\n", temp.PolicyDuration);

            printf("Enter new Policy Holder Name: ");
            scanf(" %255[^\n]", temp.CustomerUserName);
            printf("Enter new Policy Type: ");
            scanf(" %99[^\n]", temp.PolicyType);
            printf("Enter new Premium Amount: ");
            scanf("%f", &temp.PolicyFees);
            printf("Enter new Duration (Months): ");
            scanf("%d", &temp.PolicyDuration);

            pos = ftell(file) - sizeof(PolicyDetails);
            if (fseek(file, pos, SEEK_SET) != 0)
            {
                perror("Error seeking in file");
                break;
            }
            if (fwrite(&temp, sizeof(PolicyDetails), 1, file) != 1)
            {
                perror("Error writing to file");
                break;
            }
            printf("\nPolicy information updated successfully.\n");
            break;
        }
    }

    if (!found)
    {
        ClearScreen();
        printf("No policy found with number %s.\n", policyNumber);
    }

    fclose(file);
    AgentMenu();
}
void EditAccountInformation()
{
    ClearScreen();
    char password[MaxLine];
    printf("Enter Password Account To Modify: ");
    HidePassword(password);
    FILE *file = fopen("C:\\Users\\Office\\Desktop\\project\\UserData.bin", "rb+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    UserData temp;
    int found = 0;
    long pos;

    // Read all user data and find the matching one
    while (fread(&temp, sizeof(UserData), 1, file))
    {
        if (strcmp(temp.Password,password) == 0)
        {
            found = 1;
            printf("\nCurrent Information:\n");
            printf("Password: %s\n", temp.Password);
            printf("First Name: %s\n", temp.FirstName);
            printf("Last Name: %s\n", temp.LastName);
            printf("National ID: %s\n", temp.ID);
            printf("Phone Number: %s\n", temp.PhoneNumber);
            printf("Age: %s\n", temp.Age);
            printf("Gender: Female\n\n");
            // Get New data From User
            printf("\n\nEnter New Password: \n");
            HidePassword(&temp.Password);
            printf("\nEnter New First Name: ");
            scanf(" %[^\n]%*c", temp.FirstName);
            printf("Enter New Last Name: ");
            scanf(" %[^\n]%*c", temp.LastName);
            printf("Enter New National ID: ");
            scanf(" %[^\n]%*c", temp.ID);
            printf("Enter New Phone Number: ");
            scanf(" %[^\n]%*c", temp.PhoneNumber);
            printf("Enter New Age: ");
            scanf(" %[^\n]%*c",temp.Age);

            pos = ftell(file) - sizeof(UserData);
            fseek(file, pos, SEEK_SET);

            fwrite(&temp, sizeof(UserData), 1, file);
            printf("\nAccount Information Updated Successfully.\n\n");
            break;
        }
    }

    if (!found)
    {
        ClearScreen();
        Beep(800,300);
        printf("Wrong Password!.\n");
    }

    fclose(file);
    CustomerMenu();
}
//Claims??
void ShowActivePolicies()
{
    ClearScreen();
    char Username[MaxLine];
    printf("Enter User Name To Display Active Policies: ");
    scanf("%s",Username); //نعمل variable  نخزن فيه ال UserName في function CustomerMenu

    FILE *file = fopen("C:\\Users\\Office\\Desktop\\project\\policies.bin", "rb");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    PolicyDetails temp;
    int found = 0;
    printf("Active policies for %s:\n",Username);
    while (fread(&temp, sizeof(PolicyDetails), 1, file))
    {
        if (strcmp(temp.CustomerUserName,Username) == 0 && (temp.Delete == false ))
        {
            found = 1;
            printf("Policy Number: %s\n", temp.PolicyNumber);
            printf("Policy User Name: %s\n", temp.CustomerUserName);
            printf("Policy Type: %s\n", temp.PolicyType);
            printf("Premium Amount: %.2f\n", temp.PolicyFees);
            printf("Policy Start Date: %s\n", temp.StartDate);
            printf("Duration (Months): %d\n", temp.PolicyDuration);
            printf("Claim Status: %s\n\n", temp.PolicyClaimsStatus);
        }
    }

    if (!found)
    {
        ClearScreen();
        printf("No Active Policies Found For User Name %s.\n",Username);
    }

    fclose(file);
    CustomerMenu();
}
void Complains()
{
    ClearScreen();
    printf("HotLine: 19909\t Email:LIFEGUARD@info.com.eg\n");
}
void Chat()
{
    ClearScreen();
    char username[MaxLine];
    printf("____ Welcome to LIFEGUARD chat ____\n\n\n");
    printf("Enter Your User Name: \n");
    cin(username);
    char path[]="C:\\Users\\Office\\Desktop\\project\\";
    strcat(username,"_chat");
    strcat(path,username);
    strcat(path,".txt");
    FILE *fptr=fopen(path,"a+");
    char temp[MaxLine];
    int i=1;
    while(fgets(temp,sizeof (temp),fptr))
    {
        printf("%s",temp);
    }
    printf("Enter Your Massage: \n");
    getchar();
    fgets(temp,sizeof (temp),stdin);
    fprintf(fptr,"Customer: %s",temp);
    fclose(fptr);
    printf("\nThanks An Admin Will Contact You Soon.\n\n");
    CustomerMenu();
}
void AdminChat()
{
    ClearScreen();
    char username[MaxLine];
    printf("____ Welcome to LIFEGUARD chat ____\n\n\n");
    printf("Enter Your User Name: \n");
    cin(username);
    char path[]="C:\\Users\\Office\\Desktop\\project\\";
    strcat(username,"_chat");
    strcat(path,username);
    strcat(path,".txt");
    FILE *fileptr = fopen(path,"a+");
    char text[5000];
    while (fgets(text, sizeof(text),fileptr))
    {
        printf("%s",text);
    }

    char Text[5000];
    printf("\n\nEnter Your Message: \n");
    getchar();
    fgets(Text,sizeof(Text),stdin);
    fprintf(fileptr,"Admin: %s",Text);
    fclose(fileptr);
    AdminMenu();

}
