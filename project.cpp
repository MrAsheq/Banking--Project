#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<cstring>
#include<stdlib.h>
using namespace std;

//                   CLASS USED IN PROJECT


class account
{
    int acno;
    char name[50];
    int deposit;
    char type;
public:
    void create_account();  //get data from user
    void show_account() const;  //show data on screen
    void modify();  //add new data
    void dep(int);  //function to accept amount and add to balance amount
    void draw(int); //function to accept amount and subtract from balance amount
    void report() const;    //function to show data in tabular format
    int retacno() const;    //function to return account number
    int retdeposit() const; //function to return balance amount
    char rettype() const;   //function to return type of account
};         //class ends here

void account::create_account() //BANK SYSTEM- NUMBER 1
{
    cout<<"For Your New Account Follow These Steps  ->\n\nChoose Any Number Which Will Be Your Account Number"<<endl;
    cout<<"Enter Your Account Number                                                : ";
    cin>>acno;
    cout<<"{Dear User, Please Don't Forget Your Account Number}"<<endl<<endl;
    cout<<"Enter Your Name                                                          : ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"Enter Type of The Account (Current = C/ Saving = S)                      : ";
    cin>>type;
    type=toupper(type);
    cout<<"Enter Amount For Deposit(0>=500 For Saving And 0>=1000 For Current)      : ";
    cin>>deposit;
    cout<<endl<<endl;
    cout<<"        ****CONGRATULATIONS****\nYOU ARE NOW A MEMBER OF OUR FAMILY "<<endl;
    cout<<endl<<endl;
    cout<<"Please Tap 'Enter' To Continue";
}

void account::show_account() const
{
    cout<<"\tAccount No. : "<<acno<<endl;
    cout<<"\tAccount Holder Name : ";
    cout<<name<<endl;
    cout<<"\tType of Account : "<<type<<endl;
    cout<<"\tBalance amount : "<<deposit<<endl;
}


void account::modify()
{
    cout<<"\tAccount No. : \n"<<acno;
    cout<<"\tModify Account Holder Name : \n";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\tModify Type of Account : \n";
    cin>>type;
    type=toupper(type);
    cout<<"\tModify Balance amount : \n";
    cin>>deposit;
}


void account::dep(int x)
{
    deposit+=x;
}

void account::draw(int x)
{
    deposit-=x;
}

void account::report() const
{
    cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}


int account::retacno() const
{
    return acno;
}

int account::retdeposit() const
{
    return deposit;
}

char account::rettype() const
{
    return type;
}


//***************************************************************
//      function declaration
//****************************************************************
void write_account();   //function to write record in binary file
void display_sp(int);   //function to display account details given by user
void modify_account(int);   //function to modify record of file
void delete_account(int);   //function to delete record of file
void display_all();     //function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();   //introductory screen function

//***************************************************************
//      THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
    char ch;
    int num;
    intro();
    do
    {
        system("cls");
        cout<<"                           Welcome To The Bank Management System"<<endl;
        cout<<"                                 01. CREAT AN ACCOUNT"<<endl;
        cout<<"                                 02. DEPOSIT"<<endl;
        cout<<"                                 03. WITHDRAW"<<endl;
        cout<<"                                 04. BALANCE ENQUIRY"<<endl;
        cout<<"                                 05. ACCOUT LIST"<<endl;
        cout<<"                                 06. CLOSE AN ACCOUNT"<<endl;
        cout<<"                                 07. MODIFY AN ACCOUNT"<<endl;
        cout<<"                                 08. EXIT"<<endl<<endl<<endl<<endl;
        cout<<"                           Select Your Option Between (1 to 8) \n";
        cin>>ch;
        system("cls");
        switch(ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout<<"Enter The account No. : "; cin>>num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            cout<<"Enter The account No. : "; cin>>num;
            deposit_withdraw(num, 2);
            break;
        case '4':
            cout<<"Enter The account No. : "; cin>>num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout<<"Enter The account No. : "; cin>>num;
            delete_account(num);
            break;
         case '7':
            cout<<"Enter The account No. : "; cin>>num;
            modify_account(num);
            break;
         case '8':
            cout<<"Thanks for using bank management system"<<cout;
            break;
         default :cout<<"a";
        }
        cin.ignore();
        cin.get();
    }while(ch!='8');
    return 0;
}


//***************************************************************
//      function to write in file
//****************************************************************

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.txt",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
    outFile.close();
}

//***************************************************************
//      function to read specific record from file
//****************************************************************

void display_sp(int n)
{
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.txt",ios::binary);
    if(!inFile)
    {
        cout<<"\tFile could not be open !! Press any Key...\n";
        return;
    }
    cout<<"\tBALANCE DETAILS\n";

        while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
    {
        cout<<"\tAccount number does not exist\n";
    }
        cout<<endl;
        cout<<"Please Tap 'Enter' To Continue";
}


//***************************************************************
//      function to modify record of file
//****************************************************************

void modify_account(int n)
{
    bool found=false;
    account ac;
    fstream File;
    File.open("account.txt",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            cout<<"\tEnter The New Details of account\n"<<endl;
            ac.modify();
            int pos=(-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"\t Record Updated\n";
            found=true;
          }
    }
    File.close();
    if(found==false)
        cout<<"\t Record Not Found \n";
}

//***************************************************************
//      function to delete record of file
//****************************************************************


void delete_account(int n)
{
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.txt",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    outFile.open("Temp.txt",ios::binary);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        if(ac.retacno()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.txt");
    rename("Temp.txt","account.txt");
    cout<<"\tRecord Deleted ..\n";
}

//***************************************************************
//      function to display all accounts deposit list
//****************************************************************

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.txt",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any Key...";
        return;
    }
    cout<<"\tACCOUNT HOLDER LIST\n";
    cout<<"====================================================\n";
    cout<<"A/c no.      NAME           Type         Balance\n";
    cout<<"====================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

//***************************************************************
//      function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found=false;
    account ac;
    fstream File;
    File.open("account.txt", ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File could not be open !! Press any Key...\n";
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if(ac.retacno()==n)
        {
            ac.show_account();
            if(option==1)
            {
                cout<<"TO DEPOSITE AMOUNT\n";
                cout<<"Enter The Amount For Deposit : ";
                cin>>amt;
                cout<<endl;
                ac.dep(amt);
            }
            if(option==2)
            {
                cout<<"TO WITHDRAW AMOUNT  \n";
                cout<<"Enter The Amount For Withdraw : ";
                cin>>amt;
                cout<<endl;
                int bal=ac.retdeposit()-amt;
                if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
                    cout<<"***OPSS****\nInsufficient Balance___ (-_-)\n\n\n";
                else
                    ac.draw(amt);
            }
            int pos=(-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout<<"****Record Updated****"<<endl;
            found=true;
            cout<<"Please Tap 'Enter' To Continue";
           }
         }
    File.close();
    if(found==false)
        cout<<"\t Record Not Found \n";
}



void intro()
{
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"                                 ASH BANK LIMITED                            "<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"------------------------------------------------------------------------"<<endl;
    cout<<"                         Welcome To This Journey With Us                "<<endl<<endl;
    cout<<"PROJECT MADE BY : ASHEQ (MING XU)"<<endl;
    cout<<"UNIVERSITY NAME : JIANGSU NORMAL UNIVERSITY"<<endl;
    cout<<"DEPARTMENT NAME : SOFTWARE ENGINEERING"<<endl<<endl<<endl<<endl<<endl<<endl;
    cout<<"-_-_-_-_-_-Please Tap- ' Enter ' To Open Your Banking System-_-_-_-_-_-";
    cin.get();
}

                                                 //end.
