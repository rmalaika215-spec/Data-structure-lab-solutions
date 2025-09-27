#include<iostream>
using namespace std;
int main(){
	int cap=250, lat=200, esp=300;
	int*ptrcap=&cap;
	int*ptrlat=&lat;
	int*ptresp=&esp;
	int quantcap=0,quantlat=0,quantesp=0;
	int*ptrcapq=&quantcap;
	int*ptrlatq=&quantlat;
	int*ptrespq=&quantesp;
	cout<<("enter the quantity for cap");
	cin>>quantcap;
	cout<<("enter the quantity for lat");
	cin>>quantlat;
	cout<<("enter the quantity for esp");
	cin>>quantesp;
	cout<<"-------Cafe Bill-------"<<endl;
cout<<"Esspresso ("<<*ptresp<<" x "<<*ptrespq<<") = "<<*ptresp * *ptrespq<<endl;
cout<<"Latte ("<<*ptrlat<<" x "<<*ptrlatq<<") = "<<*ptrlat * *ptrlatq<<endl;
cout<<"Cappucino ("<<*ptrcap<<" x "<<*ptrcapq<<") = "<<*ptrcap * *ptrcapq<<endl;
cout<<endl;
int total;
int *ptrtotal=&total;
*ptrtotal=(*ptrcap) * (*ptrcapq)+(*ptrlat)*(*ptrlatq)+(*ptresp)*(*ptrespq);
cout<<"Total Bill = "<<*ptrtotal<<endl;


    return 0;
}