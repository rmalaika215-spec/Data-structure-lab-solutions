 #include <iostream>
using namespace std;

struct patient{
	int ID;
	patient* next;
	patient* prev;
	patient(int id)
	{
		ID=id;
		next=nullptr;
		prev=nullptr;
	}
};
class ER
{
	public:
		patient* head;
		patient* tail;
		
		
		ER()
		{
			head=nullptr;
			tail=nullptr;
		
		}
		void insertatbeginning(int id)
		{
			patient* node=new patient(id);
			if (head == nullptr)
			{
				head=node;
				tail=node;
			}
			if (head != nullptr)
			{
				node->next=head;
				head->prev=node;
				head=node;
			}
			cout<<"Patient is admitted"<<endl;
		}
		void insertatend(int id)
		{
			patient* node=new patient(id);
			if (head == nullptr)
			{
				head=node;
				tail=node;
			}
			if (head != nullptr)
			{
				node->prev=tail;
				tail->next=node;
				tail=node;
			}
			cout<<"Patient is admitted!"<<endl;
		}
		void insertatpos(int id,int pos)
		{
			if (pos < 1)
			{
				cout<<"Patient can't be added at this Position";
				return;
			}
			if (pos == 1)
			{
				insertatbeginning(id);
			    return;
		    }
		    patient* node=new patient(id);
		    patient* curr=head;
		    for (int i;i<pos-1;i++)
		    {
		    	curr=curr->next;
			}
			node->prev = curr;
		    node->next = curr->next;
		    if (curr->next != nullptr)
		    {
			    curr->next->prev =node;
		    }
		    curr->next = node;
		    cout<<"Patient is admitted"<<endl;
		}
		void deletefrombeginning()
		{
			 if (head == nullptr)
			 {
			 	cout<<"No Patients to treat";
			 	return;
			 }
			 if (head->next == nullptr)
			 {
			 	delete head;
			 	delete tail;
			 	cout<<"Patient is treated";
			 	return;
			 }
			 patient* temp=head;
			 if (head->next != nullptr)
			 {
			 	head=head->next;
			 	head->prev=nullptr;
			 	delete temp;
			 	cout<<"Patient is treated";
			 }
			 
		}
};
int main()
{
	int id,pos;
	ER queue;
	int choice;

    do {
        cout << "\n===== Hospital Emergency Queue System =====\n";
        cout << "1. Add walk in patient\n";
        cout << "2. Treat the patient\n";
        cout << "3. Add critical patient\n";
        cout << "4. Add patient in between queue\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout<<"Enter patient ID"<<endl;
                cin>>id;
            	queue.insertatend(id);
            	break;
            	
            case 2:
            	queue.deletefrombeginning();
				break;
			
			case 3:
            	cout<<"Enter patient ID"<<endl;
            	cin>>id;
            	queue.insertatbeginning(id);
				break;
				
			case 4:
            	cout<<"Enter patient ID"<<endl;
            	cin>>id;
            	cout<<"Enter position"<<endl;
            	cin>>pos;
            	queue.insertatpos(id,pos);
				break;
			
            case 5:
                cout << "Exiting program." << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 6);

    return 0;
}