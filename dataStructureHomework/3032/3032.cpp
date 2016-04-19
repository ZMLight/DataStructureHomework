#include <iostream>
#include <cstring>
using namespace std;

class LongInt
{
    friend LongInt operator+(const LongInt &, const LongInt &);
    friend ostream &operator<<(ostream &, const LongInt &);
    friend bool operator>(const LongInt &,const LongInt &);
    friend LongInt operator-(const LongInt&,const LongInt &);
    friend bool operator==(const LongInt &n1,const LongInt &n2);
    friend bool operator>=(const LongInt &n1,const LongInt &n2);
//    friend LongInt fun(LongInt &n,LongInt &m);
private:
    char *num;
public:
    LongInt(const char* n="");
    LongInt(const LongInt &);
    LongInt &operator=(const LongInt &);

};

LongInt::LongInt(const char*n)
{
    if(strcmp(n,"0")==0) n="";
    int len=strlen(n);

    num=new char[len+1];
    for(int i=0;i<len;i++)num[len-i-1]=n[i];
    num[len]='\0';
}

LongInt::LongInt(const LongInt &other)
{
    num = new char[strlen(other.num)+1];
    strcpy(num,other.num);
}

LongInt &LongInt::operator=(const LongInt &right)
{
    if (this ==&right) return *this;
    delete num;
    num = new char[strlen(right.num)+1];
    strcpy(num,right.num);
    return *this;
}

ostream &operator<<(ostream &os,const LongInt &obj)
{
    for(int i=strlen(obj.num)-1;i>=0;--i) os<<obj.num[i];
    if(strlen(obj.num)==0) os<<0;
    return os;
}

LongInt operator+(const LongInt &n1,const LongInt &n2)
{
    LongInt n;
    int len1=strlen(n1.num),len2=strlen(n2.num);
    int minLen = (len1>len2?len2:len1);
    int len=(len1>len2?len1:len2)+1;
    int carry=0,result;
    int i=0;

    delete n.num;
    n.num = new char[len+1];
    for(i=0;i<minLen;i++)
    {
        result = n1.num[i]-'0'+n2.num[i]-'0'+carry;
        n.num[i]=result%10 +'0';
        carry = result/10;
    }

    while(i<len1)
    {
        result = n1.num[i]-'0'+carry;
        n.num[i]=result %10 +'0';
        carry = result/10;
        ++i;
    }
    while(i<len2)
    {
        result = n2.num[i]-'0'+carry;
        n.num[i]=result %10 +'0';
        carry = result/10;
        ++i;
    }
    if(carry !=0) n.num[i++]=carry +'0';
    n.num[i]='\0';
    if(i !=len)
    {
        char *tmp=n.num;
        n.num=new char[len];
        strcpy(n.num,tmp);
        delete tmp;
    }

    return n;
}

LongInt operator-(const LongInt &n1,const LongInt &n2)
{
    if (n1==n2) return "";

    LongInt n;
    int len1=strlen(n1.num),len2=strlen(n2.num);
    int minus=0,i=0;
    char *tmp;

    tmp= new char[len1+1];
    for(i=0;i<len2;i++)
    {
        tmp[i] = n1.num[i]-n2.num[i]-minus;
        if(tmp[i]<0){tmp[i]+=10;minus=1;}
        else minus=0;
        tmp[i]+='0';
    }

    while(i<len1)
    {
        tmp[i]=n1.num[i]-'0'-minus;
        if(tmp[i]<0){tmp[i]+=10;minus=1;}
        else minus=0;
        tmp[i]+='0';
        ++i;
    }

    do{
        --i;
    }while(i>=0&&tmp[i]=='0');

    tmp[i+1]='\0';

    delete n.num;
    n.num=new char[i+2];
    strcpy(n.num,tmp);
    delete tmp;

    return n;
}

bool operator==(const LongInt &n1,const LongInt &n2)
{
    return strcmp(n1.num,n2.num)==0;
}

bool operator>(const LongInt &n1,const LongInt &n2)
{
    int len1=strlen(n1.num),len2=strlen(n2.num);
    if (len1>len2) return true;
    else if(len1<len2) return false;

    for (int i=len1-1;i>=0;--i)
    {
        if(n1.num[i]>n2.num[i]) return true;
        else if(n1.num[i]<n2.num[i]) return false;
    }

    return false;
}


bool operator>=(const LongInt &n1,const LongInt &n2)
{
    if(n1>n2) return true;
    if(n1==n2) return true;
    return false;
}

//LongInt fun(LongInt &n, LongInt &m)
//{
//    LongInt r;
//    LongInt k("2"),yuan("1");
//    while(n>=k)
//    {
//        r = r + m;
//        while(r >= k)
//            r = r - k;
//        k = k + yuan;
//    }
//    return r + yuan;
//}


int main()
{
    char *temp;
    temp = new char[1001];
    cin.getline(temp,1001);
    LongInt a(temp),b("1"),c("1"),tmp,res,yuan("1");
    while (a>b)
    {
        c=c+c;
        b=b+c;
    }
    b = b-c;
    tmp= a-b;
    res = tmp + tmp;
    res = res - yuan;
    cout<<res;
//    LongInt i(temp),m("2"),r;
//    LongInt k("2"),yuan("1"),zero;

//    cout<<i<<' '<<m<<' '<<tmp<<' '<<k<<' '<<yuan<<endl;
//    i = i + yuan;
//    cout<<i<<endl;
//    while(i>=k)
//    {
//        r = r + m;
//        while(r > k)
//            r = r - k;
////        cout<<r<<endl;
//    }
//    r = r + yuan;
//    cout<< r;
    delete [] temp;

    return 0;
}
