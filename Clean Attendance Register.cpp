#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	int tp,pp,id;
	cout<<"Enter the total number of participant ";
	cin>>tp;

	int *attendance;
	attendance=(int*)calloc(tp,sizeof(int));

	cout<<"Enter the number of present participant ";
	cin>>pp;

	for (int i=0; i<pp; i++)
	{
		cout<<"Enter the id of prsent participant ";
		cin>>id;

		if (id>=1 && id<=tp)
		{
			attendance[id-1]=1;
		}
		else
		{
			cout<<"Invalid id: This id does not exist"<<endl;
		}
	}
	for(int i=0; i<tp; i++)
	{
		if (attendance[i] == 1)
		{
			cout<<"Participant id no "<<i+1<<" : Present"<<endl;
		}
		else
		{
			cout<<"Participant id no: "<<i+1<<" : Absent"<<endl;
		}
	}
	attendance=nullptr;
	return 0;

}