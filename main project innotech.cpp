#include<iostream>//for cout,cin etc
#include<fstream>//for opening & closing file
#include<conio.h>//for getch
#include<stdio.h>// for gets puts 
#include<string.h>// for stdio function
#include<process.h>// for exit function
#include<stdlib.h>// for 
#include<windows.h>// for sleep function 
#include<limits>// for integer checking
using namespace std;
int checklicence(double);
int checkstock(double);
struct biodata// for biodata storage
{
   double dc;        //dc=licence number of owner
   char nc[20];	     // Medical name of owner
};
void addbio()     //for add biodata into the file"biodata.txt"
{system("color 0C");
	ofstream s;   //tempary variable to store file=s
	s.open("biodata.txt",ios::out);
	biodata b;  //to declare the object of biodata
	cout<<"\nENTER YOUR LICENCE NUMBER : ";
		while(!(cin>>b.dc)) //for checking integers
   {
   	cin.clear();
   	cin.ignore(numeric_limits<streamsize>::max(),'\n');
   	cout<<"\n\tONLY INTEGER VALUE\n";
   	cout<<"\n\t ENTER AGAIN : ";
	}
	cout<<"\nENTER YOUR MEDICAL NAME : ";
	cin.ignore();
	gets(b.nc);
	s.write((char*)&b,sizeof(biodata));  // to write in the file
	s.close();  //to close file
}
struct history //structure for history 
{
	int sr;  						// sr=variable for serial no. of bill
	double licence,batchstock[10];  //batchstock=batch no. of stock to be bill
	//string cname[10];   			//cname=  stockname
	float rate[10],amount;			//rate = cost of total item
	int noofitem; 					// noofitem= no of bitem for bill
	char mode;    					//mode=mode of payment
};
 struct stock   //structure for stock storage
{
	double batch;					//batch= batch no. of stock
	char iname[20];					//product name
	float rate;                    // rate of each product
	int qua;                       // quantity of each product
};
class customer                 // for customer
{
	char name[30],mname[40];  // name = customer name mname= medical name
	double l;                     // l=Licence number
	char addr[40];        //address of customer
	public:
	customer()  //constructor 
		{
			strcpy(name,"empty");
			strcpy(mname,"empty");
			l=0;
			strcpy(addr,"empty");
		}
	void input()// function to input customer
	{
		cout<<"\nENTER CUSTOMER NAME : ";
		cin.ignore();
		cin.getline(name,30);
		cout<<"\nENTER MEDICAL NAME : ";
		cin.getline(mname,40);
		cout<<"\nENTER MEDICAL LICENCE : ";
			while(!(cin>>l))  // for checking integer
  			 {
   			cin.clear();
   			cin.ignore(numeric_limits<streamsize>::max(),'\n');
   			cout<<"\n\tONLY INTEGER VALUE\n";
   			cout<<"\n\t ENTER AGAIN : ";
				}
		cout<<"\nENTER ADDRESS : ";
		cin.getline(addr,40);
		cin.getline(addr,40);
	}
	double lic()// function to return licence
	{
		return l;
	}
	void display() // function to display customer
	{
		cout<<"\nCUSTOMER NAME : ";
	    cout<<name;
		cout<<"\n\nMEDICAL NAME : ";
		puts(mname);
		cout<<"\nMEDICAL LICENCE : ";
		cout<<l;
		cout<<"\n\nADDRESS : ";
		cout<<addr;
	}
};
void update()// function for update customer
{  system("color 0C");
	customer c;  // object of class customer
	ifstream f("customer.txt");// file where customer store
	ofstream f1("temp.txt");// temperary file to transfer customer
	cout<<"\nENTER LICENCE NUMBER : ";
	double l;   // licence no. enter by user
		while(!(cin>>l))
   {
   	cin.clear();
   	cin.ignore(numeric_limits<streamsize>::max(),'\n');
   	cout<<"\n\tONLY INTEGER VALUE\n";
   	cout<<"\n\t ENTER AGAIN : ";
	}
	
	while(f.read((char*)&c,sizeof(customer)))
	{
		if(l==c.lic())
		{
			c.input();
		}
		f1.write((char*)&c,sizeof(customer));	
	}
	f.close();
	f1.close();
	remove("customer.txt");//delete customer file
	rename("temp.txt","customer.txt");// rename temperary file
}
void addcus() // add customer in file customer
{system("color 8F");
	ofstream k;
	k.open("customer.txt",ios::out|ios::app);
	customer c;
	char ch='y';
	while(ch=='y'||ch=='Y')
	{
			c.input();
							int temp23=0;
				if(temp23==0)//CHANGE
				{
					temp23=checklicence(c.lic());
					if(temp23==0)
					cout<<"\n\n\tLICENCE ALREADY REGISTERED \n";
				}
	if(temp23==1)
	k.write((char*)&c,sizeof(customer));
		cout<<"\n\tDO YOU WANT TO ENTER MORE CUSTOMER ('Y' FOR YES) : ";
		cin>>ch;
	}	
	k.close();
}
void rcus()            // To remove customer
{system("color AC");
	customer c;
	cout<<"\nENTER LICENCE NUMBER ";
	double g;// licence no. enter by user
		while(!(cin>>g))
   {
   	cin.clear();
   	cin.ignore(numeric_limits<streamsize>::max(),'\n');
   	cout<<"\n\tONLY INTEGER VALUE\n";
   	cout<<"\n\t ENTER AGAIN : ";
	}
	ifstream cus("customer.txt");
	ofstream f("temp.txt");
	while(cus.read((char*)&c,sizeof(customer)))
	{
		if(g==c.lic())
		{
			cout<<"\n\t**  A CUSTOMER IS DELETED  **";
		}
		else
		f.write((char*)&c,sizeof(customer));
	}
	cus.close();
	f.close();
	remove("customer.txt");// delete that file
	rename("temp.txt","customer.txt");// rename temp file
}
void cusshow()// function to show customer
{	system("color 1E");
	customer y;
	ifstream f1;
	f1.open("customer.txt",ios::in);
	f1.seekg(0);
   while(f1.read((char*)&y,sizeof(customer)))
	{
		y.display();
		cout<<"\n\n";//change
	}
	f1.close();
}
void addstock()// function to add stock
{system("color 8F");
	ofstream f;
	f.open("stock.txt",ios::out|ios::app);
	stock s;
	char ch='y';
	while(ch=='y'||ch=='Y')
	{
		cout<<"\n\nENTER BATCH NUMBER :  ";
			while(!(cin>>s.batch))
  		 {
   			cin.clear();
   		cin.ignore(numeric_limits<streamsize>::max(),'\n');
   		cout<<"\n\tONLY INTEGER VALUE\n";
   		cout<<"\n\t ENTER AGAIN : ";
		}
		cout<<"\nENTER PRODUCT NAME : ";
		cin.getline(s.iname,20);
		cin.getline(s.iname,20);
		cout<<"\nENTER RATE : ";
		cin>>s.rate;
		cout<<"\nENTER QUANTITY : ";
			while(!(cin>>s.qua))
   {
   	cin.clear();
   	cin.ignore(numeric_limits<streamsize>::max(),'\n');
   	cout<<"\n\t ONLY INTEGER VALUE\n";
   	cout<<"\n\t ENTER AGAIN : ";
	}
	int check;
	check=checkstock(s.batch);
	if(check==1)
	f.write((char*)&s,sizeof(stock));
	else
	cout<<"\n\n**** BATCH NUMBER ALREADY REGISTERED ****";
		cout<<"\n\n\t DO YOU WANT TO ENTER MORE STOCK ('Y' FOR YES) : ";
		cin>>ch;
	}
	f.close();
}
void sshow()     // StOCK show
{system("color AC");
	ifstream f3("stock.txt");
	if(!f3)
	{
		cout<<"\n\n\t NO STOCK AVALAIBLE";
		return;
	}
	f3.seekg(0);
	cout<<"\n\n";
	cout<<"BATCH"<<"\t\t"<<"PRODUCT"<<"\t\t"<<"QUANTITY"<<"\t"<<"RATE\n\n";//CHANGE
	stock e;
	while(f3.read((char*)&e,sizeof(stock)))
	{
		cout<<"\n";
		cout<<e.batch<<"\t\t";
		cout<<e.iname<<"\t\t";
		cout<<e.qua<<"\t\t";
		cout<<e.rate<<"\t\t";
		cout<<"\n";
	}
	f3.close();
}
void supdate()
{system("color 0C");
	cout<<"\n ENTER BATCH NUMBER ";
	double b;// entered batch no.
		while(!(cin>>b))
   {
   	cin.clear();
   	cin.ignore(numeric_limits<streamsize>::max(),'\n');
   	cout<<"\n\t ONLY INTEGER VALUE\n";
   	cout<<"\n\t ENTER AGAIN : ";
	}
	cout<<"\nENTER QUANTITY ADDED ";
	int q;
		while(!(cin>>q))
   {
   	cin.clear();
   	cin.ignore(numeric_limits<streamsize>::max(),'\n');
   	cout<<"\n\tONLY INTEGER VALUE\n";
   	cout<<"\n\t ENTER AGAIN : ";
	}
	ifstream f("stock.txt");
	ofstream f1("temp.txt");
	stock s;
	while(f.read((char*)&s,sizeof(stock)))
	{   
		if(b==s.batch)
		{
			s.qua+=q;// quanitiy added
		}
			f1.write((char*)&s,sizeof(stock));
	}
	f.close();
	f1.close();
	remove("stock.txt");
	rename("temp.txt","stock.txt");
}
void showhistory()
{system("color 0C");
	int test=0;
	ifstream f2("history.txt");
	if(!f2)
	{
		test=1;
		cout<<"\n\n\n\tNO HISTORY";
	}
	if(test==0)
	{
		history h3;
		customer c4;
		stock s3;
		while(f2.read((char*)&h3,sizeof(history)))
		{	ifstream f3("customer.txt");
			while(f3.read((char*)&c4,sizeof(c4)))
			{
				if(c4.lic()==h3.licence)
				{
					cout<<"\n\n\n";
					c4.display();
				}
			}
			f3.close();
			cout<<"\n\n";
			cout<<"BILL NUMBER : "<<h3.sr<<"\n\n\n";//CHANGE
			cout<<"BATCH "<<"\t"<<"NAME"<<"\t\t"<<"RATE\n\n";
			for(int i=0;i<h3.noofitem;i++)
			{   
				cout<<h3.batchstock[i]<<"\t";
				ifstream f4("stock.txt");
				while(f4.read((char*)&s3,sizeof(stock)))
				{  
					if(s3.batch==h3.batchstock[i])
					cout<<s3.iname;
				}
				f4.close();
				cout<<"\t\t"<<h3.rate[i];
				cout<<"\n\n";
			}
			cout<<"\n\n\t TOTAL AMOUNT ="<<h3.amount;
			cout<<"\n\n\t MODE OF PAYMENT ="<<h3.mode;
			cout<<"\n\n";
		}
	}
	f2.close();
return;
}
void deletehistory()
{  system("color 8F");
	ifstream f5("history.txt");
	ofstream f6;
	f6.open("temp24.txt",ios::out);
	int bat;
	history h;
	cout<<"\n \nENTER BILL NUMBER TO BE DELETED :";
	cin>>bat;
	while(f5.read((char*)&h,sizeof(history)))
	{
		if(h.sr==bat)
		cout<<"\n\n*** BILL NUMBER "<<bat<<" IS DELETED ***";
		else
		f6.write((char*)&h,sizeof(history));
	}
	f5.close();
	f6.close();
	remove("history.txt");
	rename("temp24.txt","history.txt");
	return;
}
int bill()
{
	ifstream f("customer.txt");
	history h;
	double k;//for licence no. to add
	cout<<"\nENTER LICENCE NUMBER : ";
		while(!(cin>>k))
   {
   	cin.clear();
   	cin.ignore(numeric_limits<streamsize>::max(),'\n');
   	cout<<"\n\tONLY INTEGER VALUE\n";
   	cout<<"\n\t ENTER AGAIN : ";
	}
	h.licence=k;
	double b[10];
	int q[10],z;
	cout<<"\nENTER TOTAL PRODUCT FOR BILL : ";
		while(!(cin>>z))
   {
   	cin.clear();
   	cin.ignore(numeric_limits<streamsize>::max(),'\n');
   	cout<<"\n\tONLY INTEGER VALUE\n";
   	cout<<"\n\t ENTER AGAIN : ";
	}
	h.noofitem=z;
	for(int i=0;i<z;i++)
	{
	cout<<"\nENTER BATCH NUMBER OF "<<i+1<<" "<<"ITEM : ";
		while(!(cin>>b[i]))
   {
   	cin.clear();
   	cin.ignore(numeric_limits<streamsize>::max(),'\n');
   	cout<<"\n\t ONLY INTEGER VALUE\n";
   	cout<<"\n\t ENTER AGAIN : ";
	}
	h.batchstock[i]=b[i];
	cout<<"\nENTER ITS QUANTITY : ";
			while(!(cin>>q[i]))
   {
   	cin.clear();
   	cin.ignore(numeric_limits<streamsize>::max(),'\n');
   	cout<<"\n\tONLY INTEGER VALUE\n";
   	cout<<"\n\t ENTER AGAIN : ";
	}
	}
	system("cls");
	for(int i=0;i<=100;i++)
	{	cout<<"\n\n\n\n\t\t\t\tLOADING PLEASE WAIT";    //big change
		 if(i%4==0)
		 	cout<<".";
		 else if(i%4==1)
		 cout<<"..";
		 else if(i%4==2)
		 cout<<"...";
		 else
		 cout<<"....";
		 cout<<i<<"%";	
		if(i<5&&i>0) 
			Sleep(1000);
		else if(i>47&&i<52)
		Sleep(500);
		else if(i<96&&i>89||i==99)
		Sleep(800);
		else 
		Sleep(50);
		system("cls");
	}
    ifstream w("biodata.txt");
    if(!w)
    {
    	cout<<"\n\n\t**  YOU MUST ENTER BIODATA FIRST   **";
    	w.close();
    	return 0;
	}
	biodata h1;
	w.read((char*)&h1,sizeof(biodata));
	cout<<"\n\t"<<h1.nc;
	w.close();
	customer c;
	int v=0;
	while(f.read((char*)&c,sizeof(customer)))
	{
		if(k==c.lic())
		{
		v=1;
		cout<<"\n";
		c.display();
		}
	}
	if(v==0)
	{
		cout<<"\n\n\n\t\t**  YOUR LICENCE NUMBER IS WRONG YOU MUST EXIT  **";
		exit(0);
	}
	f.close();
	cout<<"\n\nBATCH"<<"\tPARTICULAR"<<"\t";
	cout<<"QUANTITY"<<"\tAMOUNT";
	fstream f2("stock.txt");
	ofstream f3("temp.txt");
	stock d;
	double l;
	float tot=0.0;
		while(f2.read((char*)&d,sizeof(stock)))
	{
		for(int i=0;i<z;i++)
        {
        	if(b[i]==d.batch)
        	{	
		    	cout<<"\n";
        		cout<<"\n";
        		cout<<d.batch<<"\t";
        		cout<<d.iname<<"\t";
        		if(q[i]>d.qua)
        		q[i]=d.qua;
        		cout<<"\t"<<q[i]<<"\t\t";
        		cout<<d.rate*q[i];
        		d.qua-=q[i];
        		tot+=d.rate*q[i];
        		h.rate[i]=d.rate*q[i];
        	}
        }
        		f3.write((char*)&d,sizeof(stock));
	}
	f2.close();
	f3.close();
	remove("stock.txt");
	rename("temp.txt","stock.txt");
	cout<<"\n\n\n\t AMOUNT="<<tot;
	cout<<"\n\n\t GST="<<tot*.12;
	cout<<"\n\n\t TOTAL AMOUNT="<<tot*.12+tot;
	int discount=tot*.12+tot;
	cout<<"\n\n\tDISCOUNT ="<<discount*.05;
	cout<<"\n\n\tNET AMOUNT ="<<discount-discount*.05; 
	cout<<"\n\n\n\t** NO CALM FOR EXPIRE AND BREAKAGE  **";
	Sleep(6000);
	h.amount=discount-discount*.05;
	char mode;
	cout<<"\n\n\n\t ENTER MODE OF PAYMENT 'C' FOR CARD, 'P' FOR PAYTM, 'R' FOR CASH : ";
	cin>>mode;
	h.mode=mode;
	ifstream sr1;
	int srno;
	sr1.open("serialbill.txt",ios::in);
	if(!sr1)
    srno=0;
    else
    srno=sr1.get();
    sr1.close();
    h.sr=srno+1;
    ofstream f4("serialbill.txt");
    srno++;
    f4.put(srno);
    f4.close();
    ofstream g;
	g.open("history.txt",ios::out|ios::app);
	g.write((char*)&h,sizeof(history));
	g.close(); 
	return 0;
}
void changep()
{   char pass[5],temp;//change
	cout<<"\n\t PASSWORD MUST OF GIVEN LIST\n";
	cout<<"\n\t128 125 136 139 458 469 789 456 123\n";
	cout<<"\n\t ENTER NEW PASSWORD : ";
			cin.ignore();
   			gets(pass);
   			cout<<"\n\n\n\t YOUR PASSWORD IS CHANGED\n\n";
	ofstream s;
	s.open("password.txt",ios::out);
	for(int y=0;pass[y]!='\0';y++)
	s.put(pass[y]);
	s.close();
}
int checklicence(double a)
{
	customer c;
	ifstream f5("customer.txt");
	f5.seekg(0);
	while(f5.read((char*)&c,sizeof(customer)))
	{
	if(a==c.lic())
	{
	f5.close();
	return 0;
	}
	}
f5.close();
	return 1;
}
int checkstock(double b)
{
	stock s;
	ifstream f6("stock.txt");
	while(f6.read((char*)&s,sizeof(stock)))
	{
		if(b==s.batch)
		{
			f6.close();
			return 0;
		}
	}
	f6.close();
	return 1;
}
int pcheck(int a)
{	
    ifstream g("password.txt");
    if(!g)
    {
	return 0;
	g.close();
    }
    int i,r;
    i=g.get();
    r=i-48;
    i=g.get();
    r=r*10+(i-48);
    i=g.get();
    r=r*10+(i-48);
    g.close();
	if(a==r)
	return 0;
	else
	return 1;
}
void pattern(int n)
{ 
  cout<<"\n\n";
	int i,j,h,f;
	h=n%10;
	n=n/10;
	j=n%10;
	n/=10;
	i=n%10;
	for(int l=1;l<=7;l++)
	{  f=0;
	cout<<"\t\t";
	    if(l==1||l==4||l==7)
		{   
				cout<<"#";
				for(int r=1;r<=5;r++)
				{
					if((i==1)&&(j==2||j==3)&&(l==1)||(i==4)&&(j==5||j==6)&&(l==4)||(i==7)&&(j==8||j==9)&&(l==7))
					{
					 cout<<"-";
					 f=1;
					}
					else
					cout<<" ";
				}
				cout<<"#";
				for(int r=1;r<=5;r++)
				{
					if((f==1)&&(h==l+2||j==3||h==6||j==6))
					cout<<"-";
					else
					cout<<" ";
				}
				cout<<"#";		
		}
		else
		{
		    for(int p=1;p<=13;p++)
				{
					if(p==7&&h==5&&l<4||p==7&&h==8&&((l>4&&j==5)||j==2)||p==13&&h==6&&l<4||p==13&&h==9&&(l>4&&j==6||j==3))
					cout<<"!";
					else
					cout<<" ";
				}
		}
		
		cout<<"\n";
	}
}
int main()
{ system("color 0C");
		    cout<<"\n\n\n\n\n\n\n\t\t\t\t\t***************  WELCOME  ************";
    		cout<<"\n\n\n";
			cout<<"\t\t\t\t\t##   KIET GROUP OF INSTITUTIONS ##";
			cout<<"\n\n\n\t\t\t\t\t$$  DEPARTMENT OF APPLIED SCIENCE $$";
			cout<<"\n\n\n\t\t\t\t\t          PROJECT OF INNOTECH";
			cout<<"\n\n\n\t\t\t\t\t TOPIC :- MEDICAL BILLING SOFTWARE";
			cout<<"\n\n\n\t\t\t\t GROUP MEMBERS ARE:";
			cout<<"\n\n\t\t\t\t1.PRAFULL VARSHNEY\t SECTION I\n";
			cout<<"\n\t\t\t\t2.RISHABH VARSHNEY\t SECTION W\n \n\t\t\t\t3.SOMIT SHIVHARE\t SECTION W";
			cout<<" \n\n\n\n\t\t\t\t\t***  PRESS ANY KEY TO CONTINUE   ***\n";
			getch();
			system("cls");
			 system("color 9F");
    		int k=0,e=1;
    		int q;
			pattern(0);
			while(e!=0&&k<4)
			{
				k++;
				cout<<"\nENTER YOUR PATTERN ";
 			q=getch();cout<<"*";
			e=getch();cout<<"*";
				q=(q-48)*10+(e-48);
    			e=getch();cout<<"*";
				q=q*10+(e-48);
				e=pcheck(q);
				if(e==0)
				{
					pattern(q);
					cout<<"\n\n\tPASSWORD ACCEPTED\n\n\t PLEASE WAIT...";
					Sleep(1000);
					system("cls");
					
    			}
				else
				cout<<"\n\n\n\tYOUR PASSWORD IS WRONG\n";
			}
			if(k==4&&e!=0)
			{
				cout<<"\n\tYOU TRY 4 WRONG ATTEMPT SO YOU MUST EXIT";
				return 0;
			}
			cout<<"\n\t** MENU 1 **\n";
			char ch5='y';
			while(ch5=='y'||ch5=='Y')
			{   system("color EC");
				cout<<"\n\t 1.CUSTOMER\n";
				cout<<"\n\t 2.STOCK\n";
				cout<<"\n\t 3.BILL\n";
				cout<<"\n\t 4.PASSWORD CHANGE\n";
    			cout<<"\n\t 5.BIODATA\n";
    			cout<<"\n\t 6.HISTORY\n";
				cout<<"\n\n\tANY OTHER KEY FOR EXIT\n";
				char x,t;
				cout<<"\n\n\tENTER YOUR CHOICE : ";
				cin>>x;
				Sleep(1000);
				system("cls");
				char ch1='y';
    			while(ch1=='y'||ch1=='Y')
    			{
					switch(x)
					{
						case '1':{   system("color 2F");
									cout<<"\n\t**  MENU 2 **\n";
		        					cout<<"\n\t 1.FOR UPDATE\n";
									cout<<"\n\t 2.FOR ADD CUSTOMER\n";
									cout<<"\n\t 3.FOR REMOVE CUSTOMER\n";
									cout<<"\n\t 4.FOR DISPLAY\n";
									cout<<"\n\n\tENTER YOUR CHOICE : ";
									cin>>t;
									switch(t)
									{
										case '1':update();
											break;
										case '2':addcus();
											break;
										case '3':rcus();
											break;
										case '4':cusshow();
											break;
										default:cout<<"\n\tYOU ENTER WRONG VALUE\n";	
									}
									break;
								}
						case '2':{ system("color 2F");
									cout<<"\n\t**  MENU 2 **\n";
							        cout<<"\n\t 1.FOR UPDATE QUANTITY\n";
									cout<<"\n\t 2.FOR ADD STOCK\n";
									cout<<"\n\t 3.FOR DISPLAY\n";
									cout<<"\n\n\tENTER YOUR CHOICE : ";
									cin>>t;
									switch(t)
									{
									case '1':supdate();
									break;
									case '2':addstock();
									break;
									case '3':sshow();
									break;
									default:cout<<"\n\tYOU ENTER WRONG VALUE\n";	
									}
									break;
								}
						case '3':{ system("color 2F");
						           bill();
									break;
							   }
						case '4':{ system("color 2F");
								changep();
									break;
								}
						case '5':{ system("color 2F");
									cout<<"\n\t**  MENU 2 **\n";
		       						 cout<<"\n\t1.ADD BIODATA\n";
									cout<<"\n\t2.DISPLAY BIODATA\n";
									cout<<"\n\tENTER YOUR CHOICE : ";
									cin>>t;
									switch(t)
										{
											case '1':addbio();
											break;
											case '2':{system("color 8F");
														ifstream j("biodata.txt");
														int r=0;
														if(!j)
														{  r=1;
															cout<<"\n\tNO BIODATA AVALAIBLE";
														}
														if(r==0)
														{
														biodata g;
														j.read((char*)&g,sizeof(biodata));
														cout<<"\n\n\n\t"<<"LICENCE NUMBER : "<<g.dc;
														cout<<"\n\n\t"<<"MEDICAL NAME : "<<g.nc;
														j.close();
														}
														break;
													}	
										}
									break;
								}		
						case '6':{ system("color 2F");
									cout<<"\n\t**  MENU 2 **\n";
		       						 cout<<"\n\t1.SHOW HISTORY\n";
									cout<<"\n\t2.DELETE HISTORY\n";
									cout<<"\n\tENTER YOUR CHOICE : ";
									cin>>t;
									switch(t)
									{
										case '1':showhistory();
										break;
										case '2':deletehistory();
										break;
									}
								break;
								}		
						default:{system("color 04");
										cout<<"\n\tYOU ENTER OTHER KEY";
										cout<<"\n\tBYE BYE";
										return 0;
									}
					}
					cout<<"\n\n\tDO YOU WANT TO DO MORE IN  MENU 2 ('Y' FOR YES) : ";
					cin>>ch1;
					Sleep(1000);
					system("cls");
   				 }
   				  system("color E1");
					cout<<"\n\t** MENU 1 **\n";
    				cout<<"\n\t 1.CUSTOMER\n";
					cout<<"\n\t 2.STOCK\n";
					cout<<"\n\t 3.BILL\n";
					cout<<"\n\t 4.PASSWORD CHANGE\n";
    				cout<<"\n\t 5.BIODATA\n";
    				cout<<"\n\t 6.HISTORY\n";
					cout<<"\n\n\tANY OTHER KEY FOR EXIT\n";
    				cout<<"\n\n\tDO YOU TO DO ANYTHING IN MENU 1 ('Y' FOR YES) : ";
    				cin>>ch5;
 				   system("cls");
			}
			system("color 04");
	cout<<"\n\n\n\tTHANK YOU";
	cout<<"\n\n\tBYE BYE";
    return 0;
}

