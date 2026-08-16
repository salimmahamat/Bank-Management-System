#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

enum enMenuOptions { ShowClientts = 1, AddClientt = 2, Delete = 3, Update = 4, Find = 5, Transaction = 6, ManageUsers = 7, Exit = 8 };
enum enTransactionOptions { Deposit = 1, Withdraw = 2, TotalBalance = 3, MainMenu = 4 };
enum enUserManageOptions {
    ShowList = 1, AddUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, MainMenu
    = 6
};



const string FileName = "AllClientts.txt";
const string UsersFile = "Users.txt";
void ShowMainMenu();
void ShowTransactionMenuScreen();
void ShowUsersManageMenuScreen();

struct stUser
{
    string Username;
    string Password;
    short Permission;
    bool MarkForDelete = false;

};
struct sClientt
{
    string AccountNumber;
    string PinCode;
    string Name;
    string PhoneNumber;
    double AccountBalance;
    bool MarkForDelete = false;

};

bool FindClienttByAccountNumber(string AccountNumber, sClientt& Clientt);
bool FindUserByUsername(string Username, stUser& user);

sClientt ReadNewClienttInfo()
{
    sClientt Clientt;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Clientt.AccountNumber);


    while (FindClienttByAccountNumber(Clientt.AccountNumber, Clientt) == true)
    {
        cout << "Clientt with (" << Clientt.AccountNumber << ") Already Exists, try another Account Number?";

        cout << "\nEnter Account Number? ";
        getline(cin, Clientt.AccountNumber);

    }

    cout << "Enter Pin Code? ";
    getline(cin, Clientt.PinCode);
    cout << "Enter Name? ";
    getline(cin, Clientt.Name);
    cout << "Enter Phone Number? ";
    getline(cin, Clientt.PhoneNumber);
    cout << "Enter Account Balance? ";
    cin >> Clientt.AccountBalance;

    return Clientt;

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

    return User;

}


vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable
    // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}



string ConvertClienttRecordToLine(sClientt Client, string Separator = "#//#")
{
    string stClienttRecord = "";
    stClienttRecord += Client.AccountNumber + Separator;
    stClienttRecord += Client.PinCode + Separator;
    stClienttRecord += Client.Name + Separator;
    stClienttRecord += Client.PhoneNumber + Separator;
    stClienttRecord += to_string(Client.AccountBalance);

    return stClienttRecord;
}

string ConvertUserRecordToLine(stUser User, string Separator = "#//#")
{
    string stClienttRecord = "";
    stClienttRecord += User.Username + Separator;
    stClienttRecord += User.Password;


    return stClienttRecord;
}

sClientt ConvertLineToClienttRecord(string Line, string Separator = "#//#")
{
    sClientt Clientt;

    vector<string>vClienttData;

    vClienttData = SplitString(Line, Separator);


    Clientt.AccountNumber = vClienttData[0];
    Clientt.PinCode = vClienttData[1];
    Clientt.Name = vClienttData[2];
    Clientt.PhoneNumber = vClienttData[3];
    Clientt.AccountBalance = stod(vClienttData[4]);

    return Clientt;

}

stUser ConvertLineToClienttRecord2(string Line, string Separator = "#//#")
{
    stUser User;

    vector<string>vUsersData;

    vUsersData = SplitString(Line, Separator);


    User.Username = vUsersData[0];
    User.Password = vUsersData[1];

    return User;

}



void AddDataLineToFile(string FileName, string stDataLine)
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

void AddNewClientt()
{


    sClientt client = ReadNewClienttInfo();
    AddDataLineToFile(FileName, ConvertClienttRecordToLine(client));

}

void AddNewUser()
{


    stUser User = ReadNewUserInfo();
    AddDataLineToFile(UsersFile, ConvertUserRecordToLine(User));

}



vector <sClientt> LoadClienttsDataFromFileToVector(string FileName)
{
    vector <sClientt> vClientts;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line;
        sClientt Clientt;

        while (getline(MyFile, Line))
        {
            Clientt = ConvertLineToClienttRecord(Line);
            vClientts.push_back(Clientt);

        }

        MyFile.close();
    }
    return vClientts;
}

vector <stUser> LoadClienttsDataFromFileToVector2(string FileName)
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
            User = ConvertLineToClienttRecord2(Line);
            vUsersDatas.push_back(User);

        }

        MyFile.close();
    }
    return vUsersDatas;
}




string Tabs(short Space)
{
    string tab = "\t";
    string sum = "";

    for (int i = 0; i < Space; i++)
    {
        sum += tab;
    }

    return sum;
}

void PrintClienttRecord(sClientt Clientt)
{


    cout << "| " << left << setw(15) << Clientt.AccountNumber;
    cout << "| " << left << setw(10) << Clientt.PinCode;
    cout << "| " << left << setw(40) << Clientt.Name;
    cout << "| " << left << setw(12) << Clientt.PhoneNumber;
    cout << "| " << left << setw(12) << Clientt.AccountBalance;


}

void PrintUserRecord(stUser User)
{


    cout << "| " << left << setw(15) << User.Username;
    cout << "| " << left << setw(10) << User.Password;
    cout << "| " << left << setw(40) << User.Permission;

}


void PrintClienttBalances(sClientt Clientt)
{


    cout << "| " << left << setw(15) << Clientt.AccountNumber;
    cout << "| " << left << setw(40) << Clientt.Name;
    cout << "| " << left << setw(12) << Clientt.AccountBalance;


}

void PrintAllClienttsData(vector <sClientt> vClientts)
{


    cout << Tabs(5) << "Clientt List (" << vClientts.size() << ") Clientt(s).";
    cout << "\n__________________________________________________________________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Clientt Name";
    cout << "| " << left << setw(12) << "Phone Number";
    cout << "| " << left << setw(12) << "Account Balance";
    cout << "\n__________________________________________________________________________________________________________________\n";


    for (sClientt Clientt : vClientts)
    {

        PrintClienttRecord(Clientt);
        cout << endl;

    }

}
void PrintAllUsersData(vector <stUser> vUsersDatas)
{


    cout << Tabs(5) << "Users List (" << vUsersDatas.size() << ") User(s).";
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
    vector <sClientt> vClientts;
    vClientts = LoadClienttsDataFromFileToVector(FileName);


    cout << Tabs(5) << "Balances List (" << vClientts.size() << ") Clientt(s).";
    cout << "\n__________________________________________________________________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Clientt Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n__________________________________________________________________________________________________________________\n";
    double TotalBalances = 0;

    if (vClientts.size() == 0)
    {
        cout << Tabs(3) << "No Clientts Available in The System.";
    }
    else
    {
        for (sClientt Clientt : vClientts)
        {

            PrintClienttBalances(Clientt);
            TotalBalances += Clientt.AccountBalance;
            cout << endl;

        }

        cout << "\n\n__________________________________________________________________________________________________________________\n";
        cout << Tabs(5) << "Total Balances = " << TotalBalances << endl;

    }




}


string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Please Enter Account Number?\n";
    cin >> AccountNumber;
    return AccountNumber;
}
string ReadUserName()
{
    string Username;
    cout << "Please Enter Username?\n";
    cin >> Username;
    return Username;
}



string EqualSymbol(short Space)
{
    string tab = "=";
    string sum = "";

    for (int i = 0; i < Space; i++)
    {
        sum += tab;
    }

    return sum;
}

void PrintClienttCard(sClientt Clientt)
{


    cout << "\n\nThe Following Are the Clientt Details:\n\n";

    cout << "\nAccount Number  : " << Clientt.AccountNumber;
    cout << "\nPinCode         : " << Clientt.PinCode;
    cout << "\nClientt Name     : " << Clientt.Name;
    cout << "\nPhone Number    : " << Clientt.PhoneNumber;
    cout << "\nAccount Balance : " << Clientt.AccountBalance;
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



bool FindClienttByAccountNumber(string AccountNumber, vector<sClientt> vClientts, sClientt& Clientt)
{


    for (sClientt C : vClientts)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Clientt = C;
            return true;
        }

    }
    return false;


}
bool FindClienttByAccountNumber(string AccountNumber, sClientt& Clientt)
{
    vector<sClientt> vClientts = LoadClienttsDataFromFileToVector(FileName);

    for (sClientt C : vClientts)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Clientt = C;
            return true;
        }

    }
    return false;


}
bool FindUserByUsername(string Username, stUser& user)
{
    vector<stUser> vUsersDatas = LoadClienttsDataFromFileToVector2(UsersFile);

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



bool MarkForDeleteByAccountNumber(string AccountNumber, vector<sClientt>& vClientts)
{


    for (sClientt& C : vClientts)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }
    return false;



}

bool MarkForDeleteByUsername(string Username, vector<stUser>& vUsersDatas)
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



vector<sClientt> SaveClienttDataToFile(string FileName, vector<sClientt> vClientts)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;

    if (MyFile.is_open())
    {
        for (sClientt c : vClientts)
        {
            if (c.MarkForDelete == false)
            {
                DataLine = ConvertClienttRecordToLine(c);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClientts;
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


bool DeleteClienttInFile(string AccountNumber, vector<sClientt>& vClientts)
{

    sClientt Clientt;
    char Answer = 'n';

    if (FindClienttByAccountNumber(AccountNumber, vClientts, Clientt))
    {
        PrintClienttCard(Clientt);

        cout << "\n\n Are You Sure You Want to Delete This Clientt? (Y/N): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            MarkForDeleteByAccountNumber(AccountNumber, vClientts);
            SaveClienttDataToFile(FileName, vClientts);

            // Refresh
            vClientts = LoadClienttsDataFromFileToVector(FileName);

            cout << "\n\n Clientt Deleted Successfully.";
            return true;
        }
        else
        {

            cout << "\n\n Clientt With Account Number (" << AccountNumber << ") is still there.";
            return false;
        }




    }
    else
    {

        cout << "\n\n Clientt With Account Number (" << AccountNumber << ") Is Not Found";
        return false;
    }
}

bool DeleteUserInFile(string Username, vector<stUser>& vUsersDatas)
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

            MarkForDeleteByUsername(Username, vUsersDatas);
            SaveUserDataToFile(UsersFile, vUsersDatas);

            // Refresh
            vUsersDatas = LoadClienttsDataFromFileToVector2(UsersFile);

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



sClientt ChangeClienttRecord(string AccountNumber)
{
    sClientt Clientt;

    Clientt.AccountNumber = AccountNumber;

    cout << "Enter Pin Code? ";
    getline(cin >> ws, Clientt.PinCode);
    cout << "Enter Name? ";
    getline(cin, Clientt.Name);
    cout << "Enter Phone Number? ";
    getline(cin, Clientt.PhoneNumber);
    cout << "Enter Account Balance? ";
    cin >> Clientt.AccountBalance;


    return Clientt;


}

stUser ChangeUserRecord(string Username)
{
    stUser User;

    cout << "Enter Username? ";
    getline(cin >> ws, User.Username);
    cout << "Enter Password? ";
    getline(cin, User.Password);
    /*
     cout << "Enter Permission? ";
    cin, User.Permission;
    */



    return User;


}



bool UpdateClienttByAccountNumber(string AccountNumber, vector<sClientt>& vClientts)
{

    sClientt Clientt;
    char Answer = 'n';

    if (FindClienttByAccountNumber(AccountNumber, vClientts, Clientt))
    {
        PrintClienttCard(Clientt);

        cout << "\n\n Are You Sure You Want to Update This Clientt? (Y/N): ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClientt& C : vClientts)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClienttRecord(AccountNumber);
                    break;
                }


            }

            SaveClienttDataToFile(FileName, vClientts);

            cout << "\n\n Clientt Updated Successfully.";
            return true;
        }
        else
        {

            cout << "\n\n Clientt With Account Number (" << AccountNumber << ") Still Has the Same Information.";
            return false;
        }


    }
    else
    {
        cout << "\n\n Clientt With Account Number (" << AccountNumber << ") Is Not Found";
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
                    C = ChangeUserRecord(Username);
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


bool WithdrawMoney(string AccountNumber, vector<sClientt>& vClientts)
{
    sClientt Clientt;

    int Balance = 0, NewAccountBalance = 0;
    char Answer = 'n';


    while (FindClienttByAccountNumber(AccountNumber, vClientts, Clientt) == false)
    {

        cout << "\n\n Clientt With Account Number (" << AccountNumber << ") Is Not Found";
        AccountNumber = ReadAccountNumber();


    }







    PrintClienttCard(Clientt);

    Balance = ReadWithdrawAmount();

    cout << "\n\n Are You Sure You Want to Perform This Transaction? (Y/N):";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClientt& C : vClientts)
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
        SaveClienttDataToFile(FileName, vClientts);
        cout << "\n\nDone, successfully your account Balance now is : " << NewAccountBalance;
        return true;
    }
    else
    {
        cout << "\n\nThe Transaction Was Canceled.";
        return false;
    }


}

bool DepositMoney(string AccountNumber, vector<sClientt>& vClientts)
{
    sClientt Clientt;

    int Balance = 0, NewAccountBalance = 0;
    char Answer = 'n';


    while (FindClienttByAccountNumber(AccountNumber, vClientts, Clientt) == false)
    {

        cout << "\n\n Clientt With Account Number (" << AccountNumber << ") Is Not Found";
        AccountNumber = ReadAccountNumber();
    }







    PrintClienttCard(Clientt);

    Balance = ReadDepositAmount();

    cout << "\n\n Are You Sure You Want to Perform This Transaction? (Y/N):";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClientt& C : vClientts)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Balance;
                NewAccountBalance += C.AccountBalance;
                break;
            }

        }
        SaveClienttDataToFile(FileName, vClientts);
        cout << "\n\nDone, successfully your account Balance now is : " << NewAccountBalance;
        return true;
    }
    else
    {
        cout << "\n\n The Transaction Was Canceled.";
        return false;
    }


}
bool DepositBalanceToClienttByAccountNumber(string AccountNumber, double Amount, vector<sClientt>& vClientts)
{

    char Answer = 'n';

    cout << "\n\n Are You Sure You Want to Perform This Transaction? (Y/N):";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClientt& C : vClientts)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;

                SaveClienttDataToFile(FileName, vClientts);
                cout << "\n\nDone, successfully your account Balance now is : " << C.AccountBalance;
                return true;
            }

        }
        return false;
    }


}




void AddClientts()
{

    sClientt  Clientt;



    char AddMore = 'y';
    do
    {
        //system("cls");

        cout << "\nAdding New Clientt:\n\n";


        AddNewClientt();





        cout << "\nClientt Added Successfully, Do you want to add more clients? Y / N ? :\n\n";
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
    cout << EqualSymbol(40) << endl;
    cout << Tabs(1) << "Deposit Screen\n";
    cout << EqualSymbol(40) << endl;


    sClientt Clientt;
    vector<sClientt> vClientts = LoadClienttsDataFromFileToVector(FileName);

    string AccountNumber = ReadAccountNumber();


    while (!FindClienttByAccountNumber(AccountNumber, vClientts, Clientt))
    {

        cout << "\n\n Clientt With Account Number (" << AccountNumber << ") Is Not Found";
        AccountNumber = ReadAccountNumber();
    }

    PrintClienttCard(Clientt);

    double  Amount = ReadDepositAmount();

    DepositBalanceToClienttByAccountNumber(AccountNumber, Amount, vClientts);

}
void ShowWithdrawScreen()
{
    cout << EqualSymbol(40) << endl;
    cout << Tabs(1) << "Withdraw Screen\n";
    cout << EqualSymbol(40) << endl;


    sClientt Clientt;
    vector<sClientt> vClientts = LoadClienttsDataFromFileToVector(FileName);

    string AccountNumber = ReadAccountNumber();


    while (!FindClienttByAccountNumber(AccountNumber, vClientts, Clientt))
    {

        cout << "\n\n Clientt With Account Number (" << AccountNumber << ") Is Not Found";
        AccountNumber = ReadAccountNumber();
    }

    PrintClienttCard(Clientt);

    double  Amount = ReadWithdrawAmount();


    while (Amount > Clientt.AccountBalance)
    {
        cout << "\n\nAmount Exceeds the balance, you can withdraw up to : " << Clientt.AccountBalance << endl;
        Amount = ReadWithdrawAmount();
    }


    DepositBalanceToClienttByAccountNumber(AccountNumber, Amount * -1, vClientts);

}
void ShowTotalBalancesScreen()
{


    PrintTotalBalances();
}



void ShowPrintClienttsScreen()
{

    vector <sClientt> vClientt;
    vClientt = LoadClienttsDataFromFileToVector(FileName);



    PrintAllClienttsData(vClientt);
}

void ShowAddNewClienttsScreen()
{
    AddClientts();
}

void ShowDeleteClienttScreen()
{
    cout << EqualSymbol(40) << endl;
    cout << Tabs(1) << "Delete Clientt Screen\n";
    cout << EqualSymbol(40) << endl;

    vector <sClientt> vClientt = LoadClienttsDataFromFileToVector(FileName);
    string AccountNumber = ReadAccountNumber();
    DeleteClienttInFile(AccountNumber, vClientt);


}

void ShowUpdateClienttScreen()
{
    cout << EqualSymbol(40) << endl;
    cout << Tabs(1) << "Update Clientt Screen\n";
    cout << EqualSymbol(40) << endl;

    string AccountNumber = ReadAccountNumber();
    vector <sClientt> vClientt = LoadClienttsDataFromFileToVector(FileName);

    UpdateClienttByAccountNumber(AccountNumber, vClientt);
}

void ShowFindClienttScreen()
{
    cout << EqualSymbol(40) << endl;
    cout << Tabs(1) << "Find Clientt Screen\n";
    cout << EqualSymbol(40) << endl;

    sClientt Clientt;
    string AccountNumber = ReadAccountNumber();

    if (FindClienttByAccountNumber(AccountNumber, Clientt))
    {
        PrintClienttCard(Clientt);
    }
    else
    {
        cout << "\nClientt with Account Number (" << AccountNumber << ") is Not Found!";
    }
}

void ShowEndScreen()
{


    cout << EqualSymbol(40) << endl;
    cout << Tabs(2) << "Program Ends :-)" << endl;
    cout << EqualSymbol(40) << endl;


}


//User
void ShowUserListScreen()
{
    vector <stUser> vUsersDatas;
    vUsersDatas = LoadClienttsDataFromFileToVector2(UsersFile);

    PrintAllUsersData(vUsersDatas);
}
void ShowAddNewUserScreen()
{
    AddUsers();
}
void ShowDeleteUserScreen()
{
    cout << EqualSymbol(40) << endl;
    cout << Tabs(1) << "Delete User Screen\n";
    cout << EqualSymbol(40) << endl;

    vector <stUser> vUsersDatas = LoadClienttsDataFromFileToVector2(UsersFile);
    string Username = ReadUserName();
    DeleteUserInFile(Username, vUsersDatas);


}
void ShowUpdateUserScreen()
{
    cout << EqualSymbol(40) << endl;
    cout << Tabs(1) << "Update User Screen\n";
    cout << EqualSymbol(40) << endl;

    vector <stUser> vUsersDatas = LoadClienttsDataFromFileToVector2(UsersFile);
    string Username = ReadUserName();

    UpdateUserByUsername(Username, vUsersDatas);

}
void ShowFindUserScreen()
{
    cout << EqualSymbol(40) << endl;
    cout << Tabs(1) << "Find User Screen\n";
    cout << EqualSymbol(40) << endl;

    stUser User;
    string Username = ReadUserName();

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

void GoBackToUserManageMenu()
{
    cout << "\n\nPress Any Key to Return to the User Manage Menu...";
    system("pause>0");

    ShowUsersManageMenuScreen();
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

void PerformMainMenuOption(enMenuOptions Number)
{


    switch (Number) {
    case enMenuOptions::ShowClientts:
        system("cls");
        ShowPrintClienttsScreen();
        GoBackToMainMenu();
        break;
    case enMenuOptions::AddClientt:
        system("cls");
        ShowAddNewClienttsScreen();
        GoBackToMainMenu();
        break;
    case enMenuOptions::Delete:
        system("cls");
        ShowDeleteClienttScreen();
        GoBackToMainMenu();
        break;
    case enMenuOptions::Update:
        system("cls");
        ShowUpdateClienttScreen();
        GoBackToMainMenu();
        break;
    case enMenuOptions::Find:
        system("cls");
        ShowFindClienttScreen();
        GoBackToMainMenu();
        break;
    case enMenuOptions::Transaction:
        system("cls");
        ShowTransactionMenuScreen();
        break;
    case enMenuOptions::ManageUsers:
        system("cls");
        ShowUsersManageMenuScreen();
        break;
    case enMenuOptions::Exit:
        system("cls");
        ShowEndScreen();
        break;
    }


}

void PerformUserManageMenuOption(enUserManageOptions Number)
{
    switch (Number) {
    case enUserManageOptions::ShowList:
        system("cls");
        ShowUserListScreen();
        GoBackToUserManageMenu();
        break;
    case enUserManageOptions::AddUser:
        system("cls");
        ShowAddNewUserScreen();
        GoBackToUserManageMenu();
        break;
    case enUserManageOptions::DeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToUserManageMenu();
        break;
    case enUserManageOptions::UpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        GoBackToUserManageMenu();
        break;
    case enUserManageOptions::FindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToUserManageMenu();
        break;
    case enUserManageOptions::MainMenu:
        system("cls");
        ShowMainMenu();
        break;
    }


}




void ShowMainMenu()
{
    system("cls");
    cout << EqualSymbol(40) << endl;
    cout << Tabs(2) << "Menu" << endl;
    cout << EqualSymbol(40) << endl;

    cout << Tabs(1) << "[1] Show Clientt List.\n";
    cout << Tabs(1) << "[2] Add New Clientt.\n";
    cout << Tabs(1) << "[3] Delete Clientt.\n";
    cout << Tabs(1) << "[4] Update Clientt Info.\n";
    cout << Tabs(1) << "[5] Find Clientt.\n";
    cout << Tabs(1) << "[6] Transaction.\n";
    cout << Tabs(1) << "[7] Manage Users.\n";
    cout << Tabs(1) << "[8] Exit.\n\n";
    cout << EqualSymbol(40) << endl;

    PerformMainMenuOption((enMenuOptions)ReadMenuOptions("Choose What You Want to Do [1 to 8]: "));


}
void ShowTransactionMenuScreen()
{
    system("cls");
    cout << EqualSymbol(40) << endl;
    cout << Tabs(1) << "Transaction Menu Screen" << endl;
    cout << EqualSymbol(40) << endl;

    cout << Tabs(1) << "[1] Deposit.\n";
    cout << Tabs(1) << "[2] Withdraw.\n";
    cout << Tabs(1) << "[3] Total Balances.\n";
    cout << Tabs(1) << "[4] Main Menu.\n";

    cout << EqualSymbol(40) << endl;

    PerformTransactionMenuOption((enTransactionOptions)ReadMenuOptions("Choose What You Want to Do [1 to 4]: "));

}

void ShowUsersManageMenuScreen()
{

    system("cls");
    cout << EqualSymbol(40) << endl;
    cout << Tabs(1) << "Users Manage Menu Screen" << endl;
    cout << EqualSymbol(40) << endl;

    cout << Tabs(1) << "[1] List Users.\n";
    cout << Tabs(1) << "[2] Add New User.\n";
    cout << Tabs(1) << "[3] Delete User.\n";
    cout << Tabs(1) << "[4] Update Users.\n";
    cout << Tabs(1) << "[5] Find User.\n";
    cout << Tabs(1) << "[6] Main Menu.\n";

    cout << EqualSymbol(40) << endl;

    PerformUserManageMenuOption((enUserManageOptions)ReadMenuOptions("Choose What You Want to Do [1 to 6]: "));

}
