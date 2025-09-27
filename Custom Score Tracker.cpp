#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    int x;
    cout<<"Enter the no of players ";
    cin>>x;
    
    int *score;
    score=(int*)malloc(x* sizeof(int));
    for (int i=0; i<x; i++)
    {
        cout<<"Enter the score of player "<<i+1<<" : ";
        cin>>score[i];
    }
    for (int i=0; i<x; i++)
    {
        cout<<"Player "<<i+1<<" : "<<score[i]<<endl;
    }
    score=nullptr;

    return 0;
}
