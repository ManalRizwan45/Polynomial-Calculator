#include<iostream>
using namespace std;
template<class T>
class polynomial
{
private:
class term
{
public:
	T coeff;
	T exp;
	term* next;
term()
{
	coeff=NULL;
	exp=NULL;
	next=nullptr;
}
};

term* head;
term* tail;
int size;
public:
//default comstructor
polynomial()
{
	head=nullptr;
	tail=nullptr;
	size=NULL;
}
// copy constructor
polynomial(const polynomial & obj)
{
	head=tail=nullptr;
	term* t=obj.head;
	this->size=obj.size;
	while(t!=nullptr)
	{
		insertatail(t->coeff, t->exp);
		t=t->next;
	}
}
// assignment operator
polynomial operator=(const polynomial & obj)
{
	head=tail=nullptr;
	term* t=obj.head;
	this->size=obj.size;
	
	while(t!=nullptr)
	{
		insertatail(t->coeff, t->exp);
		t=t->next;
	}
	return obj;
}

// + operator
 polynomial operator+(const polynomial & obj)
{
	polynomial<T> temp;
	term* t1=head;
	term* t2=obj.head;
	
	while(t1!=nullptr && t2!=nullptr)
	{
	    if(t1->exp==t2->exp)// adding like terms of the polynomials
	{
	   temp.insertatail(t1->coeff+t2->coeff,t1->exp);
	   t1=t1->next;
	   t2=t2->next;
	}
		// inserting terms in the resultant in decreasing order
		else if(t1->exp>t2->exp)
		{
			temp.insertatail(t1->coeff,t1->exp);
			t1=t1->next;
		}
		else if(t1->exp<t2->exp)
		{
			temp.insertatail(t2->coeff,t2->exp);
			t2=t2->next;
		}
	}

	// inserting remaining terms in the resultant incase the polynomials are not empty
		while(t1!=nullptr)
		{
			temp.insertatail(t1->coeff,t1->exp);
			t1=t1->next;
		}
	
		while(t2!=nullptr)
		{
			temp.insertatail(t2->coeff,t2->exp);
			t2=t2->next;
		}
		// updating the size of the resultant
		int count=0;
		t1=temp.head;
		while(t1!=nullptr)
		{
			count++;
			t1=t1->next;
		}

		temp.size=count;
		
	    return temp;
 }
 // add function
void add( polynomial  obj, const polynomial & obj1)
{
	// copying the resultant in the caller object
	*this=obj+obj1;

}
// * operator
polynomial operator*(const polynomial & obj)
{
	polynomial<T> temp;
	term* t1=head;
	term* t2=obj.head;
	//checking if the lists are empty

	if(t1==nullptr || t2==nullptr)
	{
		cout<<"zero polynomial"<<endl;
	}
	else
	//multiplying the terms
	while(t1!=nullptr)
	{
		t2=obj.head;
		while(t2!=nullptr)
		{
	   
	   temp.insertatail(t1->coeff*t2->coeff,t1->exp+t2->exp);
	   t2=t2->next;
	   }
		  t1=t1->next;
	}
		// updating the size of the resultant
		int count=0;
		t1=temp.head;
		while(t1!=nullptr)
		{
			count++;
			t1=t1->next;
		}

		temp.size=count;
	
	return temp;
}
void multiply(polynomial obj, const polynomial & obj1)
{
	// copying the resultant in the caller object
	*this=obj*obj1;	
}
// [] operator
T operator[](const T n)
{
	term* t=head;
	int sum=0;

	while(t!=nullptr)
	{
		sum=sum+(t->coeff*(pow(n,t->exp)));
		t=t->next;
	}
	return sum;
}
// evaluate function
T evaluate(const T n)
{
	polynomial p=*this;
	return p[n];
}
void insertathead(T c, T e)
{
	term* t= new term;
	t->coeff=c;
	t->exp=e;
	if(tail==nullptr)
	{
		head=tail=t;
	}
	else
	{
		t->next=head;
		head=t;
	}
}
void  insertatail(T c, T e)
{ 
	term* t= new term;
	t->coeff=c;
	t->exp=e;
	if(head==nullptr)
	{
		head=tail=t;
	}
	else
	{
		tail->next=t;
		tail=t;
	}
	
}
// this function is used in input function
void insertbefore(T e1, T c1, T e2)
{
	term * pre=head;
	term * nex=head->next;
	if(head->exp==e2)
	{
		insertathead(c1,e1);
	}
	else
	{
		while(nex!=nullptr)
		{
			if(nex->exp==e2)
			{
				term* t=new term;
				t->coeff=c1;
				t->exp=e1;
				t->next=nex;
				pre->next=t;
			
				break;
			}
			pre=nex;
			nex=nex->next;
		}
	}
}
// this function is used in input function
 void insertafter(T e1, T c1, T e2)
{
	term* pre=head;
	term* nex=head->next;

	if(tail->exp==e2)
	{
		insertatail(c1,e1);
	}
	else
	{
		while(pre!=nullptr)
		{
			if(pre->exp==e2)
			{
				term* t=new term;
				t->coeff=c1;
				t->exp=e1;
				pre->next=t;
				t->next=nex;
				
				break;
			}
			pre=nex;
			nex=nex->next;
		}
	}
}
 // this function is used in input function to simplify the polynomial
void ifequal( T c, T e)
{
	term* t=head;

	while(t!=nullptr)
	{
		if(t->exp==e)
		{
			t->coeff=t->coeff+c;
			break;
		}
		t=t->next;
	}
}
// input function
void input()
{
	int s, count;
	cout<<"Please enter the no. of terms of the polynomial:"<<endl;
	cin>>s;
	size=s;
	count=size;
	// taking the first input out of the loop for comparison for the incoming inputs
	 T C,E;
	cout<<"Enter the coefficient and the exponent:"<<endl;
	cin>>C>>E;
	insertathead(C,E);

	int i=0;
	while(i!=size-1)
	{
		cout<<"Enter the coefficient and the exponent:"<<endl;
	    cin>>C>>E;
		//when the exponent is greater than head's exponent
		if(E>head->exp)
		{
			insertbefore(E,C,head->exp);
			i++;
		}
		// when the exponent is less than tail's exponent
		else if(E<tail->exp)
		{
           insertafter(E,C,tail->exp);
		   i++;
		   
		}
		//when the exponent is less than head's exponent but greater than tail's exponent
		else if(E<head->exp && E>tail->exp)
		{
			term*temp1=head;
			while(E<temp1->exp)
			{
				temp1=temp1->next;
			}
			insertbefore(E,C,temp1->exp);
			i++;
		}
		// simplifying the polynomial incase of like terms
		else
		{
			ifequal(C,E);
			count--;
			i++;
		}
			}
	//updating size incase of simplification
	size=count;

}
// print function
void print()
{
	term*t=head;
	int i=0;
	
	while(t!=nullptr)
	{  
		// when the exponent of a term is 0

		if(t->exp==0)
		{
			// signs of terms
			if(t->coeff>0)
			{
			cout<<"+"<<t->coeff;
			t=t->next;
			}
			else
			{
			  cout<<t->coeff;
			   t=t->next;
			}	
		}

		if(t==nullptr)
		{
			break;
		}
		// when the exponent is not zero
		else if(t!=head)
		{
			if(t->coeff>0)
			{
            cout<<"+"<<t->coeff<<"n"<<"^"<<t->exp;
			t=t->next;
			}
			else
			{
			   cout<<t->coeff<<"n"<<"^"<<t->exp;
			   t=t->next;
			}
		}
		else
		{
			cout<<t->coeff<<"n"<<"^"<<t->exp;
			t=t->next;
		}
		
		
	}
	cout<<endl;
}
~polynomial()
{
	term*t=head;
	term*dt=new term;

	while(t!=nullptr)
	{
		dt=t;
		t=t->next;
		delete dt;
	}
}

		
};
int main()
{

	cout<<"Polynomial Calculator:"<<endl;
	cout<<"Enter 1 to input your first polynomial and display it"<<endl;
	cout<<"Enter 2 to input your second polynomial and display it"<<endl;
	cout<<"Enter 3 to add the two polynomials and display the resultant polynomial"<<endl;
	cout<<"Enter 4 to multiply the two polynomials and display the resultant polynomial"<<endl;
	cout<<"Enter 5 to evaluate your polynomials for a number of your choice"<<endl;
	cout<<"Enter 6 to exit the calculator"<<endl;
	
	int choice=0;
	polynomial<int>p1;
	polynomial<int>p2;
	polynomial<int>p3;
	polynomial<int>p4;
	
	while(choice!=6)
	{
	   cout<<"Enter choice:"<<endl;
	   cin>>choice;
	   if(choice==1)
	   {   cout<<"first polynomial:"<<endl;
	       p1.input();
		   cout<<"first polynomial:"<<endl;
	      p1.print();
		   
	   }
	   else if(choice==2)
	   {
		   cout<<"second polynomial:"<<endl;
	       p2.input();
		   cout<<"second polynomial:"<<endl;
          p2.print();
	   }
	   else if(choice==3)
	   {
		   cout<<"Resultant polynomial after addition:"<<endl;
		   p3.add(p1,p2);
	       p3.print();
	   }
	   else if(choice==4)
	   {
		   cout<<"Resultant polynomial after multiplication:"<<endl;
		   p4.multiply(p1,p2);
	       p4.print();
	   }
	   else if(choice==5)
	   {
		   int num;
		   int poly;
		   cout<<"Enter the number for which you want to evaluate the polynomial:"<<endl;
	       cin>>num;
		   cout<<"Enter the polynomial you want to evaluate:"<<endl;
		   cin>>poly;
		   if(poly==1)
		   {
			   cout<<"Evaluation:"<<endl;
	           cout<<p1.evaluate(num)<<endl;
		   }
		   else 
		   { 
			   cout<<"Evaluation:"<<endl;
	         cout<<p2.evaluate(num)<<endl;
		   }
	   }
	}
	system("pause");
	return 0;
} 