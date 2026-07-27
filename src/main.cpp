
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

enum enMenuOptions{ShowClients=1,AddClient=2, Delete =3, Update =4, Find =5,Exit=6};

const string FileName = "AllClients.txt";
void ShowMainMenu();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string PhoneNumber;
    int AccountBalance;
    bool MarkForDelete = false;

};

bool FindClientByAccNum(string AccountNumber, sClient& Client);

sClient ReadNewClientInfo()
{
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);


    while (FindClientByAccNum(Client.AccountNumber, Client) == true)
    {
        cout << "Client with (" << Client.AccountNumber << ") is Already Exists, try another Account Number?";

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

string ConvertRecordToLine(sClient Clien, string Seperator = "#//#")
{
    string stCleintRecord = "";
    stCleintRecord += Clien.AccountNumber + Seperator;
    stCleintRecord += Clien.PinCode + Seperator;
    stCleintRecord += Clien.Name + Seperator;
    stCleintRecord += Clien.PhoneNumber + Seperator;
    stCleintRecord += to_string(Clien.AccountBalance);

    return stCleintRecord;
}

sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    sClient Client;

    vector<string>vClientData;

    vClientData = SplitString(Line, Seperator);


    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.PhoneNumber = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);

    return Client;

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

void AddNewClient()
{


    sClient client = ReadNewClientInfo();
    AddDataLineToFile(FileName, ConvertRecordToLine(client));

}

vector <sClient> LoadDataFromFileToVector(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);

        }

        MyFile.close();
    }
    return vClients;
}

string Taps(short Space)
{
    string tab = "\t";
    string sum = "";

    for (int i = 0; i < Space; i++)
    {
        sum += tab;
    }

    return sum;
}

void PrintClinetRecord(sClient Client)
{


    cout << "| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(40) << Client.Name;
    cout << "| " << left << setw(12) << Client.PhoneNumber;
    cout << "| " << left << setw(12) << Client.AccountBalance;


}

void PrintAllClientsData(vector <sClient> vClients)
{


    cout << Taps(5) << "Client List (" << vClients.size() << ") Client(s).";
    cout << "\n__________________________________________________________________________________________________________________\n";
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone Number";
    cout << "| " << left << setw(12) << "Account Balance";
    cout << "\n__________________________________________________________________________________________________________________\n";


    for (sClient Client : vClients)
    {

        PrintClinetRecord(Client);
        cout << endl;

    }

}

string ReadAccountNumber()
{
    string AccNum;
    cout << "Please Enter Account Number?\n";
    cin >> AccNum;
    return AccNum;
}

string EqualSympol(short Space)
{
    string tab = "=";
    string sum = "";

    for (int i = 0; i < Space; i++)
    {
        sum += tab;
    }

    return sum;
}

void PrintClinetCard(sClient Client)
{


    cout << "\n\nThe Following Are the Client Details:\n\n";

    cout << "\nAccount Number  : " << Client.AccountNumber;
    cout << "\nPinCode         : " << Client.PinCode;
    cout << "\nClient Name     : " << Client.Name;
    cout << "\nPhone Number    : " << Client.PhoneNumber;
    cout << "\nAccount Balance : " << Client.AccountBalance;



}

bool FindClientByAccNum(string AccountNumber, vector<sClient> vClients, sClient& Client)
{


    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;


}

bool MarkForDeleteByAccNum(string AccountNumber, vector<sClient>& vClients)
{


    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }
    return false;



}

vector<sClient> SaveClientDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient c : vClients)
        {
            if (c.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(c);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

bool DeleteClientInFille(string AccountNumber, vector<sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccNum(AccountNumber, vClients, Client))
    {
        PrintClinetCard(Client);

        cout << "\n\n Are You Sure You Want to Delete This Client? (Y/N):  ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            MarkForDeleteByAccNum(AccountNumber, vClients);
            SaveClientDataToFile(FileName, vClients);

            // Refresh
            vClients = LoadDataFromFileToVector(FileName);

            cout << "\n\n Client Deleted Successfully.";
            return true;
        }
        else
        {

            cout << "\n\n Client with Account Number (" << AccountNumber << ") still there.";
            return false;
        }




    }
    else
    {

        cout << "\n\n Client with Account Number (" << AccountNumber << ") Is Not Found";
        return false;
    }
}

sClient ChangeClientRecorde(string AccountNumber)
{
    sClient Client;

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

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccNum(AccountNumber, vClients, Client))
    {
        PrintClinetCard(Client);

        cout << "\n\n Are You Sure You Want to Update This Client? (Y/N):  ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecorde(AccountNumber);
                    break;
                }


            }

            SaveClientDataToFile(FileName, vClients);

            cout << "\n\n Client Updated Successfully.";
            return true;
        }
        else
        {

            cout << "\n\n Client with Account Number (" << AccountNumber << ") Still Has the Same Information.";
            return false;
        }
        

    }
    else
    {
        cout << "\n\n Client with Account Number (" << AccountNumber << ") Is Not Found";
        return false;
    }

}

bool FindClientByAccNum(string AccountNumber, sClient& Client)
{
    vector<sClient> vClients = LoadDataFromFileToVector(FileName);

    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;


}

void AddClients()
{
   
    sClient  Client;
   
   

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


void ShowPrintClientsScreen()
{
    cout << EqualSympol(40) << endl;
    cout << Taps(1) << "Print Clients Screen\n";
    cout << EqualSympol(40) << endl;

    vector <sClient> vClient;
    vClient = LoadDataFromFileToVector(FileName);



    PrintAllClientsData(vClient);
}

void ShowAddNewClientsScreen()
{
    AddClients();
}

void ShowDeleteClientScreen()
{
    cout << EqualSympol(40) << endl;
    cout << Taps(1) << "Delete Client Screen\n";
    cout << EqualSympol(40) << endl;

    vector <sClient> vClient = LoadDataFromFileToVector(FileName);
    string Accnum = ReadAccountNumber();
    DeleteClientInFille(Accnum, vClient);


}

void ShowUpdateClientScreen()
{
    cout << EqualSympol(40) << endl;
    cout << Taps(1) << "Update Client Screen\n";
    cout << EqualSympol(40) << endl;

    string Accnum = ReadAccountNumber();
    vector <sClient> vClient = LoadDataFromFileToVector(FileName);

    UpdateClientByAccountNumber(Accnum, vClient);
}

void ShowFindClientScreen()
{
    cout << EqualSympol(40) << endl;
    cout << Taps(1) << "Find Client Screen\n";
    cout << EqualSympol(40) << endl;

    sClient Client;
    string AccountNumber = ReadAccountNumber();

    if (FindClientByAccNum(AccountNumber, Client))
    {
        PrintClinetCard(Client);
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
}

void ShowEndScreen()
{
   

        cout << EqualSympol(40)<<endl;
        cout << Taps(2) << "Program Ends :-)" << endl;
        cout << EqualSympol(40)<<endl;


}


short ReadMainMenuNumber()
{
    short Number;
    cout << "Choose what you want to do [1 to 6]:\n";
    cin >> Number;
    return Number;
}

void GoBackToMainMenu()
{

    cout << "\n\nPress any key to go back to main menu....";
    system("pause>0");
    
    ShowMainMenu();
}

void PerformMainMenuOption(enMenuOptions Number)
{


    switch (Number) {
        case enMenuOptions::ShowClients:
            system("cls");
            ShowPrintClientsScreen();
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
        case enMenuOptions::Exit:
            system("cls");
            ShowEndScreen();
            break;
    }


}

void ShowMainMenu()
{
    system("cls");
    cout << EqualSympol(40) << endl;
    cout << Taps(2) << "Menu" << endl;
    cout << EqualSympol(40) << endl;

    cout << Taps(1) << "[1] Show Client List.\n";
    cout << Taps(1) << "[2] Add New Client.\n";
    cout << Taps(1) << "[3] Delete Client.\n";
    cout << Taps(1) << "[4] Update Client Info.\n";
    cout << Taps(1) << "[5] Find Client.\n";
    cout << Taps(1) << "[6] Exit.\n\n";
    cout << EqualSympol(40) << endl;

    PerformMainMenuOption((enMenuOptions)ReadMainMenuNumber());


}


int main()
{

    ShowMainMenu();
   

    system("pause>0");
    return 0;

}
