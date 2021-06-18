#include<iostream>
#include<fstream>
#include<iomanip>
#include<ctype.h>
#include<math.h>
#include<conio.h>
#include<ctime>


 
using namespace std;
 
 
 
class telephone
{
	char name[20];
	char address[20];
	long int ph_no;
public:
	void get(void);
	void show(void);
	long int getph_no();
};
 
 
 
void telephone::get(void)
{
	cout << "\nEnter Name: ";
	cin.ignore();
	cin.getline(name, 20);
	cout << "Enter Address: ";
	cin.ignore();
	cin.getline(address, 20);
	cout << "\nEnter Phone Number: ";
	cin >> ph_no;
}
 
 
void telephone::show()
{
	cout << "\nName: " << name;
	cout << "\nAddress: " << address;
	cout << "\nPhone Number: " << ph_no;
}
 
long int  telephone::getph_no()
{
	return ph_no;
}
 
 
void write_telephone()
{
	telephone tel;
	ofstream outFile;
	outFile.open("telephone.dat", ios::binary | ios::app);
	tel.get();
	outFile.write(reinterpret_cast<char *> (&tel), sizeof(telephone));
	outFile.close();
	cout << "\n\nTelephone Directory Has Been Created...";
	cin.ignore();
	cin.get();
}
 
 
 
void display_all()
{
	telephone tel;
	ifstream inFile;
	inFile.open("telephone.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while (inFile.read(reinterpret_cast<char *> (&tel), sizeof(telephone)))
	{
		tel.show();
		cout << "\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}
 
 
 
void display_sp(long int n)
{
	telephone tel;
	ifstream inFile;
	inFile.open("telephone.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag = false;
	while (inFile.read(reinterpret_cast<char *> (&tel), sizeof(telephone)))
	{
		if (tel.getph_no() == n)
		{
			tel.show();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\nrecord not exist";
	cin.ignore();
	cin.get();
}
 
 
void modify_telephone(long int n)
{
	bool found = false;
	telephone tel;
	fstream File;
	File.open("telephone.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	while (!File.eof() && found == false)
	{
 
		File.read(reinterpret_cast<char *> (&tel), sizeof(telephone));
		if (tel.getph_no() == n)
		{
			tel.show();
			cout << "\n\nPlease Enter The New Details" << endl;
			tel.get();
			int pos = (-1)*static_cast<int>(sizeof(tel));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char *> (&tel), sizeof(telephone));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}
 
 
 
void delete_telephone(long int n)
{
	telephone tel;
	ifstream inFile;
	inFile.open("telephone.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat", ios::out);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char *> (&tel), sizeof(telephone)))
	{
		if (tel.getph_no() != n)
		{
			outFile.write(reinterpret_cast<char *> (&tel), sizeof(telephone));
		}
	}
	outFile.close();
	inFile.close();
	remove("telephone.dat");
	rename("Temp.dat", "telephone.dat");
	cout << "\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}
 
 
 
void directory()
{
	char ch;
	int num;
	cout.setf(ios::fixed | ios::showpoint);
	cout << setprecision(2);
	do
	{
		system("cls");
		cout << "\t\t\t\t**\t**";
		cout << "\t\t\t\t***\t***";
		cout << "\t\t\t\t****\t****";
		cout << "\t\t\t\t*****\t*****";
		cout << "\t\t\t\t******\t******";
		cout << "\t\t\t\t*******\t*******";
		cout << "\t\t\t\t*******\t*******";
		cout << "\t\t\t\t******\t******";
		cout << "\t\t\t\t*****\t*****";
		cout << "\t\t\t\t****\t****";
		cout << "\t\t\t\t***\t***";
		cout << "\t\t\t\t**\t**";
		cout << "\t\t\t\t*\t*";
 
		cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
		cout << "\n\t\t1. Add Telephone Record";
		cout << "\n\t\t2. Show Records";
		cout << "\n\t\t3. Search Telephone Records";
		cout << "\n\t\t4. Modify Record";
		cout << "\n\t\t5. Delete Record";
		cout << "\n\t\t6. EXIT";
		cout << "\n\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
		cout << "\n\t\tPlease Enter Your Choice (1-6): ";
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':	write_telephone(); break;
		case '2':	display_all(); break;
		case '3':	cout << "\n\tPlease Enter Phone Number: "; cin >> num;
			display_sp(num); break;
		case '4':	cout << "\n\tPlease Enter Phone Number: "; cin >> num;
			modify_telephone(num); break;
		case '5':	cout << "\n\tPlease Enter Phone Number: "; cin >> num;
			delete_telephone(num); break;
		case '6':	return;
		default:	cout << "\a";
 
		}
	} while (ch != '7');
 
	
}

// **********directory ends**************


class calculator
{
 char letter;
 char letter1;
 char letter2;
 char letter3;
 char letter4;
 int a,b;
 double a1,b1;
 int result;
 double result1;
 public:void compute()
{
 
do
 {
 	system("cls");
 	cout<<"*****************CALCULATOR ******************\n";
 	cout<<"\t 1 : Arithmetic Operations \n";
 	cout<<"\t 2 : Trigonometric operations \n";
 	cout<<"\t 3 : Logarithmic operations \n";
 	cout<<"\t 4 : Power operations \n";
 	cout<<"\t 5 : Exit... \n";
 
	letter = getche();
 	switch(letter)

 {
case '1':

  {      system("cls");
          cout<<"\n\n\t---ARITHMATIC OPERATION MENU---\n\n";
          
          cout<<"\t1 : Addition \n";
          cout<<"\t2 : Subtraction \n";
          cout<<"\t3 : Multipilication \n";
          cout<<"\t4 : Division \n\n";
          letter1 = getche();
             switch(letter1)
              {
                case '1':
                         {system("cls");
                        cout<<"\n\nEnter first number...";
                        cin>>a;
                        cout<<"Enter another number...";
                        cin>>b;
                        result=a+b;
                        cout<<"\n\nResult = "<<result<<endl;
                        system("pause");
            
                        break;
                          }                
                case '2':
                     	 {
                     	 	system("cls");
                   		cout<<"\n\nEnter first number...";
                        cin>>a;
                        cout<<"Enter another number...";
                        cin>>b;
                   		result=a-b;
                   		cout<<"\n\nResult = "<<result<<endl;
                   		system("pause");
                   		
                   		 break;
                    	}

                case '3':
                         {
                         	system("cls");
                   		cout<<"\n\nEnter first number...";
                        cin>>a;
                        cout<<"Enter another number...";
                        cin>>b;
                   		result=a*b;
                   		cout<<"\n\nResult = "<<result<<endl;
                   		system("pause");
                   	
                    	break;
                   		}
               
                case '4':        
                          {
                          	system("cls");
                      		cout<<"\n\nEnter first number...";
                            cin>>a;
                            cout<<"Enter another number...";
                        	cin>>b;
                      		if(a!=0)
                       		{
                        	result=a/b;
                          	cout<<"\n\nResult = "<<result<<endl;
                          	system("pause");
                    
                       		}
                             break;
                          }
                   
              }// end of inner switch
              break;
        }// end of case 1 arithmatic operation

 case '2':
         {
		  system("cls");
          cout<<"\n\n";
   		  cout<<"\t1 : Sin function \n";
          cout<<"\t2 : Cos function \n";
          cout<<"\t3 : Tan function \n";
    	  letter2=getche();
   		 switch(letter2)
    	{
   		 case '1':
     	{
            system("cls");   	
    	 	cout<<"\n\n Enter a number...";
    	 	cin>>a1;
 
     		result1=(sin(a1));
    		 cout<<"\n\nResult = "<<result1<<endl;
    		 system("pause");
    		 
    		 break;
     	}
    	case '2':
       {
       	system("cls");
      		cout<<"\n\n Enter a number...";
      		cin>>a1;
      		result1=(cos(a1));
     		 cout<<"\n\nResult = "<<result1<<endl;
      		system("pause");
      		break;
        }
    	case '3':
       {
     	 	system("cls");
     		cout<<"\n\n Enter a number...";
     		cin>>a1;
     		result1=(tan(a1));
     		cout<<"\n\nResult = "<<result1<<endl;
     		system("pause");
     		break;
	   }

   	  }// inner switch
    break;
     }//inner case 2 trignometric
    	case '3':
		{
			system("cls");
   			cout<<"\n\n";
    		cout<<"\t1 : Natural log\n";
    		cout<<"\t2 : log with base 10 \n";
    		letter3=getche();
    	switch(letter3)
    	{
    	case '1':
   		{
   			system("cls");
     		cout<<"\n\n Enter a number...";
     		cin>>a1;
	 		result1=log(a1);
     		cout<<"\n\n Result = "<<result1<<endl;
     		system("pause");
     		break;
   		}
    	case '2':
     	{
     		system("cls");
     		cout<<"\n\n Enter a number...";
     		cin>>a1;
    		 result1= log10(a1);
    		 cout<<"\n\n Result = "<<result1<<endl;
    		 system("pause");
    		 break;
     	}
     	}// end of switch
     		break;
     	}// end of case 3 logrithmic
    	case '4':
    	{		system("cls");
    			cout<<"\n1) Press 1 for Power \n";
    			cout<<"2) Press 2 for Square root \n";
    			cout<<"Enter your choice....";
    			letter4=getche();
   				 switch(letter4)
    	{
    	case '1':
    	 {
     		system("cls");
      		cout<<"\n\nEnter a number...";
     		cin>>a1;
      		cout<<"Enter power...";
      		cin>>b1;
      		result1=pow(a1,b1);
      		cout<<"\n\nResult = "<<result1<<endl;
      		system("pause");
      		break;
     	}
    case '2':
     {	
     		system("cls");
     		 cout<<"\n\nEnter a number...";
      		cin>>a;
      		result1=sqrt(a);
      		cout<<"\n\nResult = "<<result1<<endl;
      		system("pause");
      		break;

     	}

    }// end of switch
           break;
         }// end of case power function

  }// outer switch
}while(letter != '5');
}

}obj;
void cal()
{
	obj.compute();
	
}
	// ***********calculator ends***********
	

class watch
{
	public:
		int i,h=0,m=0,s=0;
		public:void clearscreen()
		{
			int n;
			for(n=0;n<50;n++)
			cout<<"\n";
		}
		void time()
		{    int k,l;
			int count = 0;
			cout<<"setup time and day\n";
			cout<<"please enter the time format in hh:mm:ss"<<endl;
			cin>>h>>m>>s;
			cout<<"enter 1 for sunday "<<"\n"<<"enter 2 for monday "<<"\n"<<"enter 3 for tuesday "<<"\n"<<"enter 4 for wednesday "<<
			"enter 5 for thrusday "<<"\n"<<"enter 6 for friday "<<"\n"<<"enter 7 for saturday"<<endl;
			cin>>i;
			start:
				
				for(h;h<24;h++)
				{
					for(m;m<60;m++)
					{
						for(s;s<60;s++)
						{
							count ++;
							if(count == 10)
					         return;
							
							cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<h<<":"<<m<<":"<<s;
							if(h<12)
							{
								cout<<" AM"<<'\n';
							}
							else
							{
								cout<<" PM"<<'\n';
							}
							
							switch(i)
							{
								case 1:cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"SUNDAY";
								break;
								case 2:cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"MONDAY";
								break;
								case 3:cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"TUESDAY";
								break;
								case 4:cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"WEDNESDAY";
								break;
								case 5:cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"THRUSDAY";
								break;
								case 6:cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"FRIDAY";
								break;
								case 7:cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"SATURDAY";
								break;
								default:cout<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<'\t'<<"enter valid input";
								break;	
							}
							
						//	cout << string(33, '\n');
							for(double j=0;j<15505000;j++)
						{
							for(double k=0;k<36;k++)
							{
									k++;
								
								}
								
							}
							system("cls");
				
							}	s=0;
						}m=0;
						
					}h=0;
				i++;
					
				goto start;
			}
		
};
void timer()
{
	watch w;
	w.time();
	
}


int main()
{
	int ch;
	while(1)
	{
		cout<<"\n\t----HOME SCREEN MENU----";
		cout<<"\n\t1-Contacts \n\t2-Calculator \n\t3-Clock \n\t4-Power Off\n\t:";
		cin>>ch;
		switch(ch)
		{
			case 1:
				directory();
				break;
			case 2:
				cal();
				break;
			case 3:
				system("cls");
				timer();
				break;
			case 4:
				system("cls");
				cout<<"\n\tShutting Down....\n\n";
				return 0;
			default :
				cout<<"\n\t*No such option!\n\n ";
					
		}
		system("cls");
	}
}
