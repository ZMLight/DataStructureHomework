#include <iostream>
using namespace std;
bool isleapYear(int year);
int MonthDays(int month,int year);
int FirstDayOfMonth(int month,int year);
void PrintDate(int month,int year,int seq,int num);

bool IsLeapYear(int year)
{
    if ((year%4==0 && year%100 !=0) || year%400 == 0)
        return true;
    else
        return false;
}

int MonthDays(int month, int year)
{
    int num=0;

    switch (month)
    {
        case 1: num = 31;break;
        case 2: num = 28;if (IsLeapYear(year)) num+=1;break;
        case 3: num = 31;break;
        case 4: num = 30;break;
        case 5: num = 31;break;
        case 6: num = 30;break;
        case 7: num = 31;break;
        case 8: num = 31;break;
        case 9: num = 30;break;
        case 10: num = 31;break;
        case 11: num = 30;break;
        case 12: num = 31;break;
        default: cout<<"Wrong Input!";
    }
    return num;
}

int FirstDayOfMonth(int month, int year)
{
    int i=0,j=0,num=1;
    for (i=1850;i<year;i++)
        for (j=1;j<13;j++)
            num += MonthDays(j,i);
    for (j=1;j<month;j++)
        num += MonthDays(j,year);
    num = num % 7;

    return num+1;
}

void PrintDate(int month,int year,int seq,int num)
{
    int fdnum,days = 0;
    fdnum = FirstDayOfMonth(month,year);
    if(num<fdnum)
        days = 8-fdnum+seq*num+(seq-1)*(7-num);
    if(num>=fdnum)
        days = (seq-1)*7+num-fdnum+1;

    if(days>MonthDays(month,year))
        cout<<"none"<<endl;
    else
    {
        cout<<year<<'/';
        if(month<10)
            cout<<'0'<<month<<'/';
        else
            cout<<month<<'/';
        if(days<10)
            cout<<'0'<<days<<endl;
        else
            cout<<days<<endl;
    }
}

int main()
{
    int month,seq,num,year1,year2,tmpyear;
    int i=0;
    cin>>month>>seq>>num>>year1>>year2;
    if(year1>year2)
    {
        tmpyear = year1;
        year1 = year2;
        year2 = tmpyear;
    }
    for(i = year1;i<=year2;i++)
        PrintDate(month,i,seq,num);
    return 0;
}


