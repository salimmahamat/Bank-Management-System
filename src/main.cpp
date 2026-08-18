#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

enum enMenuOptions { ShowClients = 1, AddClient = 2, Delete = 3, Update = 4, Find = 5, Transaction = 6, ManageUsers = 7, Logout = 8 };
enum enTransactionOptions { Deposit = 1, Withdraw = 2, TotalBalance = 3, MainMenu = 4 };
enum enUserManagementOptions {
    eShowUsers = 1, eAddUser = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenu
    = 6
};

enum enPermission {
    pAllPermissions = -1, pShowClients = 1, pAddClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64
};

const string FileName = "AllClients.txt";
const string UsersFile = "Users.txt";
void ShowMainMenu();
void ShowTransactionMenuScreen();
void ShowUserManagementMenuScreen();
void GoBackToMainMenu();
struct stUser
{
    string Username;
    string Password;
    int Permission;
    bool MarkForDelete = false;

};
struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string PhoneNumber;
    double AccountBalance;
    bool MarkForDelete = false;

};

stUser CurrentUser;



bool FindClientByAccountNumber(string AccountNumber, stClient& Client);
bool FindUserByUsername(string Username, stUser& user);

stClient ReadNewClientInfo()
{
    stClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);


    while (FindClientByAccountNumber(Client.AccountNumber, Client) == true)
    {
        cout << "Client with (" << Client.AccountNumber << ") Already Exists, try another Account Number?";

        cout << "\nEnter Account Number? ";
        getline(cin, Client.AccountNumber);

    }

    cout << "Enter Pin Code? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone Number? ";
    getline(cin, Client.PhoneNumber);
    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;

}


int ReadPermissionsToSet()
{
    int Permission = 0;
    char Answer = 'n';

    cout << "\nDo you Want to give full access? Y/N?\n";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        return -1;
    }

    cout << "\nDo you Want to give  access to : \n";

    cout << "\nShow Client list? Y/N?\n";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermission::pShowClients;
    }

    cout << "\nAdd Client Y/N?\n";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermission::pAddClient;
    }

    cout << "\nDelete Client Y/N?\n";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermission::pDeleteClient;
    }

    cout << "\nUpdate Client Y/N?\n";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermission::pUpdateClient;
    }

    cout << "\nFind Client Y/N?\n";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermission::pFindClient;
    }

    cout << "\n Transaction Y/N?\n";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermission::pTransactions;
    }

    cout << "\nManage Users Y/N?\n";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permission += enPermission::pManageUsers;
    }

    return Permission;
}


stUser ReadNewUserInfo()
{
    stUser User;
    cout << "Enter Username? ";
    getline(cin >> ws, User.Username);

    while (FindUserByUsername(User.Username, User))
    {
        cout << "\nUser with Username [" << User.Username << "], already exists. Try another User\n";
        getline(cin >> ws, User.Username);
    }
    cout << "Enter Password? ";
    getline(cin, User.Password);

    User.Permission = ReadPermissionsToSet();

    return User;

}


vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // Store the current word.
    // Find each delimiter and extract the word.
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // Store the word.
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1); // Add the last word.
    }
    return vString;
}



string ConvertClientRecordToLine(stClient Client, string Separator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Separator;
    stClientRecord += Client.PinCode + Separator;
    stClientRecord += Client.Name + Separator;
    stClientRecord += Client.PhoneNumber + Separator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;
}

string ConvertUserRecordToLine(stUser User, string Separator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += User.Username + Separator;
    stClientRecord += User.Password + Separator;
    stClientRecord += to_string(User.Permission);


    return stClientRecord;
}

stClient ConvertLineToClientRecord(string Line, string Separator = "#//#")
{
    stClient Client;

    vector<string>vClientData;

    vClientData = SplitString(Line, Separator);


    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.PhoneNumber = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;

}

stUser ConvertUserLineToRecord(string Line, string Separator = "#//#")
{
    stUser User;

    vector<string>vUsersData;

    vUsersData = SplitString(Line, Separator);


    User.Username = vUsersData[0];
    User.Password = vUsersData[1];
    User.Permission = stoi(vUsersData[2]);

    return User;

}



void AppendDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << stDataLine;
        MyFile << endl;
        MyFile.close();
    }

}

void AddNewClient()
{


    stClient client = ReadNewClientInfo();
    AppendDataLineToFile(FileName, ConvertClientRecordToLine(client));

}

void AddNewUser()
{


    stUser User = ReadNewUserInfo();
    AppendDataLineToFile(UsersFile, ConvertUserRecordToLine(User));

}



vector <stClient> LoadClientsDataFromFile(string FileName)
{
    vector <stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line;
        stClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToClientRecord(Line);
            vClients.push_back(Client);

        }

        MyFile.close();
    }
    return vClients;
}

vector <stUser> LoadUsersDataFromFile(string FileName)
{
    vector <stUser> vUsersDatas;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line;
        stUser User;

        while (getline(MyFile, Line))
        {
            User = ConvertUserLineToRecord(Line);
            vUsersDatas.push_back(User);

        }

        MyFile.close();
    }
    return vUsersDatas;
}




string GetTabs(short Space)
{
    string tab = "\t";
    string sum = "";

    for (int i = 0; i < Space; i++)
    {
        sum += tab;
    }

    return sum;
}

void PrintClientRecord(stClient Client)
{


    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.PhoneNumber;
    cout << "| " << left << setw(12) << Client.AccountBalance;


}

void PrintUserRecord(stUser User)
{


    cout << "| " << left << setw(15) << User.Username;
    cout << "| " << left << setw(10) << User.Password;
    cout << "| " << left << setw(40) << User.Permission;

}


void PrintClientBalances(stClient Client)
{


    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.AccountBalance;


}

void PrintAllClientsData(vector <stClient> vClients)
{


    cout << GetTabs(5) << "Client List (" << vClients.size() << ") Client(s).";
    cout << "\n__________________________________________________________________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone Number";
    cout << "| " << left << setw(12) << "Account Balance";
    cout << "\n__________________________________________________________________________________________________________________\n";


    for (stClient Client : vClients)
    {

        PrintClientRecord(Client);
        cout << endl;

    }

}
void PrintAllUsersData(vector <stUser> vUsersDatas)
{


    cout << GetTabs(5) << "Users List (" << vUsersDatas.size() << ") User(s).";
    cout << "\n__________________________________________________________________________________________________________________\n";
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permission";
    cout << "\n__________________________________________________________________________________________________________________\n";


    for (stUser User : vUsersDatas)
    {

        PrintUserRecord(User);
        cout << endl;

    }

}


void PrintTotalBalances()
{
    vector <stClient> vClients;
    vClients = LoadClientsDataFromFile(FileName);


    cout << GetTabs(5) << "Balances List (" << vClients.size() << ") Client(s).";
    cout << "\n__________________________________________________________________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n__________________________________________________________________________________________________________________\n";
    double TotalBalances = 0;

    if (vClients.size() == 0)
    {
        cout << GetTabs(3) << "No Clients Available in The System.";
    }
    else
    {
        for (stClient Client : vClients)
        {

            PrintClientBalances(Client);
            TotalBalances += Client.AccountBalance;
            cout << endl;

        }

        cout << "\n\n__________________________________________________________________________________________________________________\n";
        cout << GetTabs(5) << "Total Balances = " << TotalBalances << endl;

    }




}


string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Please Enter Account Number?\n";
    cin >> AccountNumber;
    return AccountNumber;
}
string ReadUsername()
{
    string Username;
    cout << "Please Enter Username?\n";
    cin >> Username;
    return Username;
}



string PrintSeparator(short Space)
{
    string tab = "=";
    string sum = "";

    for (int i = 0; i < Space; i++)
    {
        sum += tab;
    }

    return sum;
}

void PrintClientCard(stClient Client)
{


    cout << "\n\nThe Following Are the Client Details:\n\n";

    cout << "\nAccount Number  : " << Client.AccountNumber;
    cout << "\nPinCode         : " << Client.PinCode;
    cout << "\nClient Name     : " << Client.Name;
    cout << "\nPhone Number    : " << Client.PhoneNumber;
    cout << "\nAccount Balance : " << Client.AccountBalance;
    cout << endl;
    cout << endl;


}
void PrintUserCard(stUser User)
{


    cout << "\n\nThe Following Are the User Details:\n\n";

    cout << "\nUsername  : " << User.Username;
    cout << "\nPassword  : " << User.Password;
    cout << "\nPermission  : " << User.Permission;
    cout << endl;
    cout << endl;


}



bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient& Client)
{


    for (stClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;


}
bool FindClientByAccountNumber(string AccountNumber, stClient& Client)
{
    vector<stClient> vClients = LoadClientsDataFromFile(FileName);

    for (stClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;


}
bool FindUserByUsername(string Username, stUser& user)
{
    vector<stUser> vUsersDatas = LoadUsersDataFromFile(UsersFile);

    for (stUser C : vUsersDatas)
    {
        if (C.Username == Username)
        {
            user = C;
            return true;
        }

    }
    return false;


}
bool FindUserByUsername(string Username, vector<stUser> vUsersDatas, stUser& user)
{


    for (stUser C : vUsersDatas)
    {
        if (C.Username == Username)
        {
            user = C;
            return true;
        }

    }
    return false;


}



bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{


    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }
    return false;



}

bool MarkUserForDeleteByUsername(string Username, vector<stUser>& vUsersDatas)
{


    for (stUser& C : vUsersDatas)
    {
        if (C.Username == Username)
        {
            C.MarkForDelete = true;
            return true;
        }

    }
    return false;



}



// Rewrite the file while skipping records marked for deletion.
vector<stClient> SaveClientDataToFile(string FileName, vector<stClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;

    if (MyFile.is_open())
    {
        for (stClient c : vClients)
        {
            if (c.MarkForDelete == false)
            {
                DataLine = ConvertClientRecordToLine(c);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

vector<stUser> SaveUserDataToFile(string FileName, vector<stUser> vUsersDatas)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;

    if (MyFile.is_open())
    {
        for (stUser c : vUsersDatas)
        {
            if (c.MarkForDelete == false)
            {
                DataLine = ConvertUserRecordToLine(c);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsersDatas;
}


bool DeleteClientFromFile(string AccountNumber, vector<stClient>& vClients)
{

    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\n Are You Sure You Want to Delete This Client? (Y/N): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientDataToFile(FileName, vClients);

            // Refresh
            vClients = LoadClientsDataFromFile(FileName);

            cout << "\n\n Client Deleted Successfully.";
            return true;
        }
        else
        {

            cout << "\n\n Client With Account Number (" << AccountNumber << ") is still there.";
            return false;
        }




    }
    else
    {

        cout << "\n\n Client With Account Number (" << AccountNumber << ") Is Not Found";
        return false;
    }
}

bool DeleteUserFromFile(string Username, vector<stUser>& vUsersDatas)
{

    stUser User;
    char Answer = 'n';

    if (FindUserByUsername(Username, vUsersDatas, User))
    {
        PrintUserCard(User);

        cout << "\n\n Are You Sure You Want to Delete This User? (Y/N): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            MarkUserForDeleteByUsername(Username, vUsersDatas);
            SaveUserDataToFile(UsersFile, vUsersDatas);

            // Refresh
            vUsersDatas = LoadUsersDataFromFile(UsersFile);

            cout << "\n\n User Deleted Successfully.";
            return true;
        }
        else
        {

            cout << "\n\n User With Username  (" << Username << ") is still there.";
            return false;
        }




    }
    else
    {

        cout << "\n\n User With Username  (" << Username << ") Is Not Found";
        return false;
    }
}



stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "Enter Pin Code? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone Number? ";
    getline(cin, Client.PhoneNumber);
    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;


    return Client;


}

stUser ChangeUserRecord()
{
    stUser User;

    cout << "Enter Username? ";
    getline(cin >> ws, User.Username);
    cout << "Enter Password? ";
    getline(cin, User.Password);

    User.Permission = ReadPermissionsToSet();




    return User;


}



bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)
{

    stClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\n Are You Sure You Want to Update This Client? (Y/N): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }


            }

            SaveClientDataToFile(FileName, vClients);

            cout << "\n\n Client Updated Successfully.";
            return true;
        }
        else
        {

            cout << "\n\n Client With Account Number (" << AccountNumber << ") Still Has the Same Information.";
            return false;
        }


    }
    else
    {
        cout << "\n\n Client With Account Number (" << AccountNumber << ") Is Not Found";
        return false;
    }

}

bool UpdateUserByUsername(string Username, vector<stUser>& vUsersDatas)
{

    stUser User;
    char Answer = 'n';

    if (FindUserByUsername(Username, vUsersDatas, User))
    {
        PrintUserCard(User);

        cout << "\n\n Are You Sure You Want to Update This User? (Y/N): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            for (stUser& C : vUsersDatas)
            {
                if (C.Username == Username)
                {
                    C = ChangeUserRecord();
                    break;
                }


            }

            SaveUserDataToFile(UsersFile, vUsersDatas);

            cout << "\n\n Username Updated Successfully.";
            return true;
        }
        else
        {

            cout << "\n\n User With Username (" << Username << ") Still Has the Same Information.";
            return false;
        }


    }
    else
    {
        cout << "\n\n User With Username (" << Username << ") Is Not Found";
        return false;
    }

}



int ReadDepositAmount()
{
    int DepositAmount;
    cout << "Please Enter the Deposit Amount:\n";
    cin >> DepositAmount;
    return DepositAmount;
}

int ReadWithdrawAmount()
{
    int WithdrawAmount;
    cout << "Please Enter the Withdrawal Amount:\n";
    cin >> WithdrawAmount;
    return WithdrawAmount;
}


bool WithdrawMoney(string AccountNumber, vector<stClient>& vClients)
{
    stClient Client;

    int Balance = 0, NewAccountBalance = 0;
    char Answer = 'n';


    while (FindClientByAccountNumber(AccountNumber, vClients, Client) == false)
    {

        cout << "\n\n Client With Account Number (" << AccountNumber << ") Is Not Found";
        AccountNumber = ReadAccountNumber();


    }







    PrintClientCard(Client);

    Balance = ReadWithdrawAmount();

    cout << "\n\n Are You Sure You Want to Perform This Transaction? (Y/N):";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {

        for (stClient& C : vClients)
        {

            if (C.AccountNumber == AccountNumber)
            {

                while (C.AccountBalance <= Balance)
                {
                    cout << "\n\nAmount Exceeds the balance, you can withdraw up to : " << C.AccountBalance << endl;
                    Balance = ReadWithdrawAmount();
                }


                if (C.AccountBalance >= Balance)
                {

                    C.AccountBalance -= Balance;
                }

                NewAccountBalance += C.AccountBalance;
                break;
            }

        }
        SaveClientDataToFile(FileName, vClients);
        cout << "\n\nDone, successfully your account Balance now is : " << NewAccountBalance;
        return true;
    }
    else
    {
        cout << "\n\nThe Transaction Was Canceled.";
        return false;
    }


}

bool DepositMoney(string AccountNumber, vector<stClient>& vClients)
{
    stClient Client;

    int Balance = 0, NewAccountBalance = 0;
    char Answer = 'n';


    while (FindClientByAccountNumber(AccountNumber, vClients, Client) == false)
    {

        cout << "\n\n Client With Account Number (" << AccountNumber << ") Is Not Found";
        AccountNumber = ReadAccountNumber();
    }







    PrintClientCard(Client);

    Balance = ReadDepositAmount();

    cout << "\n\n Are You Sure You Want to Perform This Transaction? (Y/N):";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {

        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Balance;
                NewAccountBalance += C.AccountBalance;
                break;
            }

        }
        SaveClientDataToFile(FileName, vClients);
        cout << "\n\nDone, successfully your account Balance now is : " << NewAccountBalance;
        return true;
    }
    else
    {
        cout << "\n\n The Transaction Was Canceled.";
        return false;
    }


}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<stClient>& vClients)
{

    char Answer = 'n';

    cout << "\n\n Are You Sure You Want to Perform This Transaction? (Y/N):";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {

        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;

                SaveClientDataToFile(FileName, vClients);
                cout << "\n\nDone, successfully your account Balance now is : " << C.AccountBalance;
                return true;
            }

        }
        return false;
    }

    return false;
}




void AddClients()
{

    stClient  Client;



    char AddMore = 'y';
    do
    {
        //system("cls");

        cout << "\nAdding New Client:\n\n";


        AddNewClient();





        cout << "\nClient Added Successfully, Do you want to add more clients? Y / N ? :\n\n";
        cin >> AddMore;

    } while (AddMore == 'y' || AddMore == 'Y');


}
void AddUsers()
{

    stUser  User;



    char AddMore = 'y';
    do
    {
        //system("cls");

        cout << "\nAdding New User:\n\n";


        AddNewUser();





        cout << "\nUser Added Successfully, Do you want to add more Users? Y / N ? :\n\n";
        cin >> AddMore;

    } while (AddMore == 'y' || AddMore == 'Y');




}



void ShowDepositScreen()
{
    cout << PrintSeparator(40) << endl;
    cout << GetTabs(1) << "Deposit Screen\n";
    cout << PrintSeparator(40) << endl;


    stClient Client;
    vector<stClient> vClients = LoadClientsDataFromFile(FileName);

    string AccountNumber = ReadAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        cout << "\n\n Client With Account Number (" << AccountNumber << ") Is Not Found";
        AccountNumber = ReadAccountNumber();
    }

    PrintClientCard(Client);

    double  Amount = ReadDepositAmount();

    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}
void ShowWithdrawScreen()
{
    cout << PrintSeparator(40) << endl;
    cout << GetTabs(1) << "Withdraw Screen\n";
    cout << PrintSeparator(40) << endl;


    stClient Client;
    vector<stClient> vClients = LoadClientsDataFromFile(FileName);

    string AccountNumber = ReadAccountNumber();


    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        cout << "\n\n Client With Account Number (" << AccountNumber << ") Is Not Found";
        AccountNumber = ReadAccountNumber();
    }

    PrintClientCard(Client);

    double  Amount = ReadWithdrawAmount();


    while (Amount > Client.AccountBalance)
    {
        cout << "\n\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        Amount = ReadWithdrawAmount();
    }


    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);

}
void ShowTotalBalancesScreen()
{


    PrintTotalBalances();
}



// Check whether the current user has the required permission.
bool HasPermission(enPermission Permission)
{

    if (CurrentUser.Permission == enPermission::pAllPermissions)
    {
        return true;
    }


    // Check whether the requested permission bit is enabled.
    if ((Permission & CurrentUser.Permission) == Permission)
    {
        return true;
    }
    else
        return  false;
}
void ShowAccessDeniedMessage()
{

    cout << PrintSeparator(40) << endl;
    cout << "\nAccess Denied, You do not have permission to do this\nPlease contact your admin\n" << endl;
    cout << PrintSeparator(40) << endl;

}



void ShowClientsListScreen()
{

    if (!HasPermission(enPermission::pShowClients))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
    }



    vector <stClient> vClient;
    vClient = LoadClientsDataFromFile(FileName);



    PrintAllClientsData(vClient);
}

void ShowAddNewClientsScreen()
{

    if (!HasPermission(enPermission::pAddClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
    }
    AddClients();
}

void ShowDeleteClientScreen()
{
    if (!HasPermission(enPermission::pDeleteClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
    }

    cout << PrintSeparator(40) << endl;
    cout << GetTabs(1) << "Delete Client Screen\n";
    cout << PrintSeparator(40) << endl;

    vector <stClient> vClient = LoadClientsDataFromFile(FileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClientFromFile(AccountNumber, vClient);


}

void ShowUpdateClientScreen()
{
    if (!HasPermission(enPermission::pUpdateClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
    }

    cout << PrintSeparator(40) << endl;
    cout << GetTabs(1) << "Update Client Screen\n";
    cout << PrintSeparator(40) << endl;

    string AccountNumber = ReadAccountNumber();
    vector <stClient> vClient = LoadClientsDataFromFile(FileName);

    UpdateClientByAccountNumber(AccountNumber, vClient);
}

void ShowFindClientScreen()
{
    if (!HasPermission(enPermission::pFindClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
    }

    cout << PrintSeparator(40) << endl;
    cout << GetTabs(1) << "Find Client Screen\n";
    cout << PrintSeparator(40) << endl;

    stClient Client;
    string AccountNumber = ReadAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
}

void ShowEndScreen()
{


    cout << PrintSeparator(40) << endl;
    cout << GetTabs(2) << "Program Ends :-)" << endl;
    cout << PrintSeparator(40) << endl;


}



//User
void ShowUsersListScreen()
{
    vector <stUser> vUsersDatas;
    vUsersDatas = LoadUsersDataFromFile(UsersFile);

    PrintAllUsersData(vUsersDatas);
}
void ShowAddNewUserScreen()
{
    AddUsers();
}
void ShowDeleteUserScreen()
{
    cout << PrintSeparator(40) << endl;
    cout << GetTabs(1) << "Delete User Screen\n";
    cout << PrintSeparator(40) << endl;

    vector <stUser> vUsersDatas = LoadUsersDataFromFile(UsersFile);
    string Username = ReadUsername();
    DeleteUserFromFile(Username, vUsersDatas);


}
void ShowUpdateUserScreen()
{
    cout << PrintSeparator(40) << endl;
    cout << GetTabs(1) << "Update User Screen\n";
    cout << PrintSeparator(40) << endl;

    vector <stUser> vUsersDatas = LoadUsersDataFromFile(UsersFile);
    string Username = ReadUsername();

    UpdateUserByUsername(Username, vUsersDatas);

}
void ShowFindUserScreen()
{
    cout << PrintSeparator(40) << endl;
    cout << GetTabs(1) << "Find User Screen\n";
    cout << PrintSeparator(40) << endl;

    stUser User;
    string Username = ReadUsername();

    if (FindUserByUsername(Username, User))
    {
        PrintUserCard(User);
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
    }
}




short ReadMenuOptions(string Message)
{
    short Number;
    cout << Message;
    cin >> Number;
    return Number;
}

void GoBackToMainMenu()
{

    cout << "\n\nPress Any Key to Return to the Main Menu...";
    system("pause>0");

    ShowMainMenu();
}

void GoBackToTransactionMenu()
{

    cout << "\n\nPress Any Key to Return to the Transaction Menu...";
    system("pause>0");

    ShowTransactionMenuScreen();
}

void GoBackToUserManagementMenu()
{
    cout << "\n\nPress Any Key to Return to the User Manage Menu...";
    system("pause>0");

    ShowUserManagementMenuScreen();
}




void PerformTransactionMenuOption(enTransactionOptions Number)
{
    switch (Number) {
    case enTransactionOptions::Deposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionMenu();
        break;
    case enTransactionOptions::Withdraw:
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransactionMenu();
        break;
    case enTransactionOptions::TotalBalance:
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionMenu();
        break;
    case enTransactionOptions::MainMenu:
        system("cls");

        ShowMainMenu();
        break;
    }
}

void Login();
void PerformMainMenuOption(enMenuOptions Number)
{


    switch (Number) {
    case enMenuOptions::ShowClients:
        system("cls");
        ShowClientsListScreen();
        GoBackToMainMenu();
        break;
    case enMenuOptions::AddClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenu();
        break;
    case enMenuOptions::Delete:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenu();
        break;
    case enMenuOptions::Update:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenu();
        break;
    case enMenuOptions::Find:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenu();
        break;
    case enMenuOptions::Transaction:
        system("cls");
        ShowTransactionMenuScreen();
        break;
    case enMenuOptions::ManageUsers:
        system("cls");
        ShowUserManagementMenuScreen();
        break;
    case enMenuOptions::Logout:
        system("cls");
        Login();
        break;
    }


}

void PerformUserManagementMenuOption(enUserManagementOptions Number)
{
    switch (Number) {
    case enUserManagementOptions::eShowUsers:
        system("cls");
        ShowUsersListScreen();
        GoBackToUserManagementMenu();
        break;
    case enUserManagementOptions::eAddUser:
        system("cls");
        ShowAddNewUserScreen();
        GoBackToUserManagementMenu();
        break;
    case enUserManagementOptions::eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToUserManagementMenu();
        break;
    case enUserManagementOptions::eUpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        GoBackToUserManagementMenu();
        break;
    case enUserManagementOptions::eFindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToUserManagementMenu();
        break;
    case enUserManagementOptions::eMainMenu:
        system("cls");
        ShowMainMenu();
        break;
    }


}



void ShowMainMenu()
{
    system("cls");
    cout << PrintSeparator(40) << endl;
    cout << GetTabs(2) << "Menu" << endl;
    cout << PrintSeparator(40) << endl;

    cout << GetTabs(1) << "[1] Show Client List.\n";
    cout << GetTabs(1) << "[2] Add New Client.\n";
    cout << GetTabs(1) << "[3] Delete Client.\n";
    cout << GetTabs(1) << "[4] Update Client Info.\n";
    cout << GetTabs(1) << "[5] Find Client.\n";
    cout << GetTabs(1) << "[6] Transaction.\n";
    cout << GetTabs(1) << "[7] Manage Users.\n";
    cout << GetTabs(1) << "[8] Logout.\n\n";
    cout << PrintSeparator(40) << endl;

    PerformMainMenuOption((enMenuOptions)ReadMenuOptions("Choose What You Want to Do [1 to 8]: "));


}
void ShowTransactionMenuScreen()
{
    system("cls");
    cout << PrintSeparator(40) << endl;
    cout << GetTabs(1) << "Transaction Menu Screen" << endl;
    cout << PrintSeparator(40) << endl;

    cout << GetTabs(1) << "[1] Deposit.\n";
    cout << GetTabs(1) << "[2] Withdraw.\n";
    cout << GetTabs(1) << "[3] Total Balances.\n";
    cout << GetTabs(1) << "[4] Main Menu.\n";

    cout << PrintSeparator(40) << endl;

    PerformTransactionMenuOption((enTransactionOptions)ReadMenuOptions("Choose What You Want to Do [1 to 4]: "));

}

void ShowUserManagementMenuScreen()
{

    system("cls");
    cout << PrintSeparator(40) << endl;
    cout << GetTabs(1) << "Users Manage Menu Screen" << endl;
    cout << PrintSeparator(40) << endl;

    cout << GetTabs(1) << "[1] List Users.\n";
    cout << GetTabs(1) << "[2] Add New User.\n";
    cout << GetTabs(1) << "[3] Delete User.\n";
    cout << GetTabs(1) << "[4] Update Users.\n";
    cout << GetTabs(1) << "[5] Find User.\n";
    cout << GetTabs(1) << "[6] Main Menu.\n";

    cout << PrintSeparator(40) << endl;

    PerformUserManagementMenuOption((enUserManagementOptions)ReadMenuOptions("Choose What You Want to Do [1 to 6]: "));

}


bool FindUserByUsernameAndPassword(string Username, string Password, stUser& User)
{
    vector<stUser> vUsersDatas = LoadUsersDataFromFile(UsersFile);

    for (stUser U : vUsersDatas)
    {
        if (U.Username == Username && U.Password == Password)
        {
            User = U;
            return true;
        }

    }
    return false;


}


bool LoadUserInfo(string Username, string Password)
{

    if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
        return true;
    else
        return false;

}

void Login()
{


    bool LoginFailed = false;
    string Username, Password;


    do
    {

        system("cls");
        cout << PrintSeparator(40) << endl;
        cout << GetTabs(1) << "Login Screen" << endl;
        cout << PrintSeparator(40) << endl;

        if (LoginFailed)
        {
            cout << "\nInvalid Username/Password!\n";
        }

        cout << "\nEnter Username\n";
        cin >> Username;
        cout << "\nEnter Password\n";
        cin >> Password;

        LoginFailed = !LoadUserInfo(Username, Password);



    } while (LoginFailed);
    ShowMainMenu();

}

int main()
{

    Login();
    system("pause>0");
    return 0;

}