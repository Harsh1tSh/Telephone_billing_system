#include<iostream>
#include<fstream>
#include<math.h>
#include<cmath>
#include<stdio.h>
#include<conio.h>
#include<string>
#include<process.h>
#include<ctype.h>
#include<dos.h>
#include<Windows.h>
#include<ctime>
#include<iomanip>
using namespace std;

class account
{
    char name[30];
    char address[60];
    long acc_no;
    long phone_no;

    public:
        void add();
        void modify();
        void del();
        void display();
        void generate();
        void help();
};

account obj;

int bil_ctr = 1;

int numdigits(long n)
{
    return (log10(n)+1);
}

const char *mon(int m)
{
    switch (m)
    {
        case (1):
            return "Jan";

        case (2):
            return "Feb";
        
        case (3):
            return "Mar";

        case (4):
            return "Apr";

        case (5):
            return "May";

        case (6):
            return "Jun";

        case (7):
            return "Jul";

        case (8):
            return "Aug";

        case (9):
            return "Sep";

        case (10):
            return "Oct";

        case (11):
            return "Nov";

        case (12):
            return "Dec";

        default:
            return "Invalid Month";
    }
}
void clrscr()
{
    system("cls");
}
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void clreol() {
    std::cout << "\x1B[2K"; // ANSI escape sequence to clear the line
}

int main()
{
    char ch1,ch2;
    while(1)
    {
        clrscr();
        gotoxy(30,5);
        cout << "Supreme Telecom Pvt. Ltd.";
        gotoxy(30,6);
        cout << "_____________________";
        gotoxy(30,8);
        cout << "'M'anage customer Records";
        gotoxy(30,10);
        cout << "'D'isplay list of customers";
        gotoxy(30,12);
        cout << "'G'enerate Bill";
        gotoxy(30,14);
        cout << "'H'elp";
        gotoxy(30,16);
        cout << "'E'xit";
        gotoxy(30,30);

        cout << "Enter your choice";
        ch1 = getch();
        ch1 = toupper(ch1);
        switch(ch1)
        {
            case('D'):
                obj.display();
                break;
            case('G'):
                obj.generate();
                break;
            case('H'):
                obj.help();
                break;
            case('E'):
                clrscr;
                exit(1);
            case('M'):
                ch2='A';
        do
        {
            clrscr();
            gotoxy(30,5);
            cout << "Supreme Telecom Pvt. Ltd.";
            gotoxy(30,6);
            cout << "_________________________";
            gotoxy(30,8);
            cout << "'A'dd new record";
            gotoxy(30,10);
            cout << "'M'odifying existing records";
            gotoxy(30,12);
            cout << "'D'elete existing record";
            gotoxy(30,14);
            cout << "'E'xit";
            gotoxy(30,30);
            cout << "Enter your choice";
            ch2 = getch();
            ch2 = toupper(ch2);
            switch(ch2)
            {
                case('A'):
                    obj.add();
                    break;
                case('M'):
                    obj.modify();
                    break;
                case('D'):
                    obj.del();
                    break;
                case('E'):
                    break;
            }
        }while(ch2!='E');
        }
    }
}

void account :: add()
{
    char ch1;
    fstream fptr1;

    fptr1.open("db.dat",ios::app);
    if(fptr1.fail())
    {
        cout << "Cannot open the db.dat file!";
        getch();
        return;
    }
    clrscr();
    gotoxy(30,5);
    cout << "Enter the new customer's details";

    while(1)
    {
        gotoxy(30,8);
        cout << "Name : ";
        cin >> name;
        if(strlen(name)==0)
        {
            gotoxy(30,30);
            clreol();
            cout << "Name cannot be left blank";
        }
        else
        {
            gotoxy(30,30);
            clreol();
            break;
        }
    }
    while(1)
    {
        gotoxy(30,10);
        cout << "Address : ";
        cin >> address;
        if(strlen(address)==0)
        {
            gotoxy(30,30);
            clreol();
            cout << "Address cannot be left blank"; 
        }
        else
        {
            gotoxy(30,30);
            clreol();
            break;
        }
    }
    while(1)
    {
        gotoxy(30,12);
        cout << "Ph. No  : ";
        cin >> phone_no;
        if(numdigits(phone_no)!=7)
        {
            gotoxy(54,12);
            clreol();
            gotoxy(30,30);
            clreol();
            cout << "Phone no must be of seven digits";
        }
        else
        {
            gotoxy(30,30);
            clreol();
            break;
        }
    }
    while(1)
    {
        gotoxy(30,14);
        cout << "Acc no : ";
        cin >> acc_no;
        if(numdigits(acc_no)!=5)
        {
            gotoxy(54,14);
            clreol();
            gotoxy(30,30);
            clreol();
            cout << "Account number must be of five digits";
        }
        else
        {
            gotoxy(30,30);
            clreol();
            break;
        }
    }
    gotoxy(30,30);
    cout << "'S'ave and exit";
    gotoxy(30,32);
    cout << "'E'xit without saving";
    ch1 = getch();
    ch1 = toupper(ch1);

    switch(ch1)
    {
        case('S'):
            fptr1.write((char*)this,sizeof(obj));
            fptr1.close();
            return;
        case('E'):
            fptr1.close();
            return;
    }
}

void account :: modify()
{
    char ch;
    long input_no;
    int flag = 0;
    fstream fptr1,fptr2;
    fptr1.open("db.dat",ios::in);
    if(fptr1.fail())
    {
        cout << "Cannot open the db.dat file!";
        getch();
        return;
    }
    fptr2.open("dbtemp.dat",ios::out);
    if(fptr2.fail())
    {
        cout << "Cannot open the dbtemp.dat file!";
        getch();
        return;
    }
    clrscr();
    gotoxy(20,3);
    cout << "Enter the phone no whose record is to be modiified";
    cin >> input_no;

    while(fptr1.read((char*)this, sizeof(obj)))
    {
        if(input_no==phone_no)
        {
            flag = 1;
            gotoxy(20,5);
            cout << "Name";
            gotoxy(20,6);
            cout << "Address";
            gotoxy(20,7);
            cout << "Acc No";
            gotoxy(20,10);
            cout << "Modify this customer record (Y/N)";
            ch = getch();
            ch = toupper(ch);
            if(ch=='Y')
            {
                gotoxy(20,14);
                cout << "Enter the customer's modified details..";
                while(1)
                {
                    gotoxy(20,16);
                    cout << "Name : ";
                    cin >> name;
                    if(strlen(name)==0)
                    {
                        gotoxy(30,30);
                        clreol();
                        cout << "Name cannot be left blank";
                    }
                    else
                    {
                        gotoxy(30,30);
                        clreol();
                        break;
                    }
                }
                while(1)
                {
                    gotoxy(20,18);
                    cout << "Address : ";
                    cin >> address;
                    if(strlen(address)==0)
                    {
                        gotoxy(30,30);
                        clreol();
                        cout << "Address cannot be left blank";
                    }
                    else
                    {
                        gotoxy(30,30);
                        clreol();
                        break;
                    }
                }
                while(1)
                {
                    gotoxy(20,20);
                    cout << "Ph. No : ";
                    cin >> phone_no;
                    if(numdigits(phone_no)!=7)
                    {
                        gotoxy(44,20);
                        clreol();
                        gotoxy(30,30);
                        clreol();
                        cout << "Phone No. must be of 7 digits";
                    }
                    else
                    {
                        gotoxy(30,30);
                        clreol();
                        break;
                    }
                }
                while(1)
                {
                    gotoxy(20,22);
                    cout << "Account no : ";
                    cin >> acc_no;
                    if(numdigits(acc_no)!=5)
                    {
                        gotoxy(44,22);
                        clreol();
                        gotoxy(30,30);
                        clreol();
                        cout << "Account No. must be of five digits";
                    }
                    else
                    {
                        gotoxy(30,30);
                        clreol();
                        break;
                    }
                }
            }
        }
        fptr2.write((char *)this, sizeof(obj));
    }
    fptr1.close();
    fptr2.close();
    if(ch=='N')
    return;
    if(flag==0)
    {
        gotoxy(20,5);
        clreol();
        cout << "Recode for telephone number" << input_no << " does not exist!";
        getch();
        return;
    }
    else
    {
        gotoxy(20,30);
        cout <<"Customer record modified and updated successfully";
        getch();
    }
    fptr1.open("db.dat",ios::out);
    fptr2.open("dbtemp.dat",ios::in);
    while(fptr2.read((char *)this,sizeof(obj)));
    fptr1.write((char *)this,sizeof(obj));

    fptr1.close();
    fptr2.close();

}

void account :: del()
{
    char ch;
    long input_no;
    int flag=0;
    fstream fptr1,fptr2;
    fptr1.open("db.dat",ios::in);
    if(fptr1.fail())
    {
        cout << "Cannot open the db.dat file!";
        getch();
        return;
    }
    fptr2.open("dbtemp.dat",ios::out);
    if(fptr2.fail())
    {
        cout << "Cannot open the dbtemp.dat file!";
        getch();
        return;
    }
    clrscr();
    gotoxy(20,3);
    cout << "Enter phone no whose record is to be deleted : ";
    cin >> input_no;

    while(fptr1.read((char *)this, sizeof(obj)))
    {
        if(input_no==phone_no)
        {
            flag = 1;
            gotoxy(20,5);
            cout << "Name " << name;
            gotoxy(20,6);
            cout << "Address " << address;
            gotoxy(20,7);
            cout << "Acc No " << acc_no;
            gotoxy(20,10);
            cout << "Delete the customer record (Y/N)";
            ch = getch();
            ch = toupper(ch);
            if(ch=='N')
            fptr2.write((char *)this,sizeof(obj));
        }
        else
        fptr2.write((char *)this,sizeof(obj));
    }
    fptr1.close();
    fptr2.close();

    if(ch=='N')
    return;

    if(flag==0)
    {
        gotoxy(20,5);
        cout << "Record for telephone number " << input_no << " does not exist";
        getch();
        return;
    }
    else
    {
        gotoxy(20,12);
        cout << "Customer record for " << input_no << " deleted successfully";
        getch();
    }

    fptr1.open("db.dat",ios::out);
    fptr2.open("dbtemp.dat",ios::in);

    while(fptr2.read((char *)this,sizeof(obj)))
    fptr1.write((char *)this,sizeof(obj));
    fptr1.close();
    fptr2.close();
}

void account :: display()
{
    fstream fptr1;
    int count;

    fptr1.open("db.dat",ios::in);
    if(fptr1.fail())
    {
        cout << "Cannot open the db.dat file!";
        getch();
        return;
    }
    clrscr();
    gotoxy(2,2);
    cout << "Name";
    gotoxy(2,3);
    cout << "__________";
    gotoxy(30,2);
    cout << "Phone No";

    gotoxy(30,3);
    cout << "__________";
    gotoxy(55,2);
    cout << "Account Number";
    gotoxy(55,3);
    cout << "__________";

    count = 4;
    while(fptr1.read((char *)this,sizeof(obj)))
    {
        if(count>=19)
        {
            gotoxy(30,30);
            cout << "Press any key to continue";
            getch();
            clrscr();
            gotoxy(2,2);
            cout << "Name";
            gotoxy(2,3);
            cout << "______";

            gotoxy(30,2);
            cout << "Phone No";
            gotoxy(30,3);
            cout << "___________";
            gotoxy(55,2);
            cout << "Account No";
            gotoxy(55,3);
            cout << "_______________";
            count =4;
        }
        gotoxy(2,count);
        cout << name;
        gotoxy(30,count);
        cout << phone_no;
        gotoxy(60,count);
        cout << acc_no;
        count++;
    }
    gotoxy(22,30);
    cout << "Press any key to go back to previous menu ";
    getch();
    fptr1.close();

}

void account :: generate()
{
    long input_no;
    char choice;
    int flag = 0;
    int lcalls,tcalls,icalls;
    float bill,tbill;
    float rental=145.82;
    int dd,mm,yy;

    time_t now = time(nullptr);
    tm *timeinfo = localtime(&now);
    dd = timeinfo->tm_mday;
    mm = timeinfo->tm_mon + 1; // Month is 0-based, so add 1
    yy = timeinfo->tm_year + 1900;

    std :: fstream fptr1;
    fptr1.open("db.dat",ios::in);
    if(fptr1.fail())
    {
        cout << "Cannot open the db.dat file!";
        getch();
        return;
    }
    clrscr();
    gotoxy(2,2);
    cout << "Enter the telephone number : ";
    cin >> input_no;

    flag = 0;
    while(fptr1.read((char *)this,sizeof(obj)))
    {
        if(flag==1)
        break;
        if(phone_no==input_no)
        {
            clrscr();
            gotoxy(30,2);

            cout << "Supreme Telecom Pvt. Ltd.";

            gotoxy(2,5);
            cout << "Name : " << name;
            gotoxy(40,5);
            cout << "Address : " << address;
            gotoxy(2,7);
            cout << "Account No : " << acc_no;
            gotoxy(40,7);
            cout << "Telphone No : " << phone_no;

            gotoxy(2,9);
            cout << " Bill No : " << mm << "_" << bil_ctr;
            bil_ctr++;
            gotoxy(40,9);
            cout << "Billing cycle : " << mon(mm);

            gotoxy(2,16);
            cout << "Number of local calls: ";
            gotoxy(65,16);
            cin >> lcalls;

            gotoxy(2,18);
            cout << "Number of trunk calls: ";
            gotoxy(65,18);
            cin >> tcalls;

            gotoxy(2,20);
            cout << "Number of ISD calls: ";
            gotoxy(65,20);
            cin >> icalls;
            bill = lcalls*0.25+tcalls*1.00+icalls*5.00;

            gotoxy(2,32);
            cout << "Total call charges: ";
            gotoxy(65,32);

            cout << setprecision(2);
            cout << bill;

            gotoxy(2,33);
            cout << "Monthly Charges : ";
            gotoxy(65,33);
            cout << rental;

            gotoxy(2,34);
            cout << "Service Tax (12.36%) : ";
            gotoxy(65,34);
            cout << (bill+rental)*0.1236;

            tbill = bill + rental + (bill+rental)*0.1236;

            gotoxy(2,36);
            cout << "Total charges before " << dd << " " << mon(mm) << " " << yy;

            gotoxy(65,36);
            cout << tbill;

            gotoxy(2,37);
            cout << "Total charges after " << dd << " " << mon(mm) << " " << yy;

            gotoxy(65,37);
            cout << tbill+100.00;

            gotoxy(55,45);
            cout << "Press any key to continue";
            getch();
            flag = 1;    

        }
    }
    if(flag=0)
    {
        gotoxy(2,4);
        cout << "Record for telephone number " << input_no << "Does not exist";
        getch();
    }
    fptr1.close();

}

void account :: help()
{
    clrscr();
    gotoxy(1,2);
    cout << "Telephone Billing system is a command driven application that helps manage";
    gotoxy(1,4);
    cout << "records of the customers as well as generate their telephone bills";

    gotoxy(1,8);
    cout << "Press any key to continue...";
    getch();
    gotoxy(1,8);
    clreol();
    gotoxy(15,8);
    cout << "Option";
    gotoxy(15,9);
    cout << "___________";
    gotoxy(55,8);
    cout << "Description";
    gotoxy(55,9);
    cout << "____________";
    gotoxy(1,10);
    cout << "'M'anage customer records               -";

    gotoxy(40,10);
    cout << "Helps to mannipulate customer records";

    gotoxy(1,12);
    cout << "'A'dd new record                 -";
    gotoxy(40,12);
    cout << "Adds a new customer record";

    gotoxy(1,14);
    cout << "'M'odify existing record           -";
    gotoxy(40,14);
    cout << "Modifies an existing customer record";

    gotoxy(1,16);
    cout << "'D'elete existing record     -";
    gotoxy(40,16);
    cout << "Deletes an existing customer records ";

    gotoxy(1,18);
    cout << "'D'isplay list of customers       -";
    gotoxy(40,18);
    cout << "Displays the list of existing customers";

    gotoxy(1,20);
    cout << "'G'enerate Bill               -";
    gotoxy(40,20);
    cout << "Helps to generate telephone bill";

    gotoxy(1,22);
    cout << "'H'elp          -";
    gotoxy(40,22);
    cout << "Provides help documentation";

    gotoxy(1,24);
    cout << "'E'xit";
    gotoxy(40,24);
    cout << "Exits the current screeb/application";

    gotoxy(45,45);
    cout << "Press any key to go back..";
    getch();

}

// so many hours and still not working 
// i don't know               >>>>>>>>>>            :<
