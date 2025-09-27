#include <iostream>
using namespace std;

int generateCode(int x)
{
    int y=1;
    if (x==0)
    {
        cout<<"your secret code is 1"<<endl;
    }
    else{
        for (int i=1; i<=x;i++)
        {
            y*=i;
        }
    }
      return y;
}

int main()
{
    int x;
    cout<<"enter the number to get a secret code ";
    cin>>x;
    int (*codeptr)(int x);
    codeptr=generateCode;
    cout<<"your secret code is "<<codeptr(x)<<endl;


    return 0;
}