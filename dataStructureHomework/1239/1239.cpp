#include <iostream>
using namespace std;

int main()
{
    int Tax[8] = {0,3,10,20,25,30,35,40}, taxs = 0;
    int Salary = 0;

    cin >> Salary;

    Salary -= 3500;
    if(Salary>=0&&Salary<=1500)
        taxs += Salary*Tax[1]/100;
    else if(Salary>=1500&&Salary<=4500)
        taxs += 45 + (Salary-1500)*Tax[2]/100;
    else if(Salary>=4500&&Salary<=9000)
        taxs += 345 + (Salary-4500)*Tax[3]/100;
    else if(Salary>=9000&&Salary<=35000)
        taxs += 1245 + (Salary-9000)*Tax[4]/100;
    else if(Salary>=35000&&Salary<=55000)
        taxs += 7745 + (Salary-35000)*Tax[5]/100;
    else if(Salary>=55000&&Salary<=80000)
        taxs += 13745 + (Salary-55000)*Tax[6]/100;
    else if(Salary>=80000)
        taxs += 22495 + (Salary-80000)*Tax[7]/100;

    cout << taxs;

    return 0;
}
