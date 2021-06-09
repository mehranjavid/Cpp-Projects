#include<iostream>
#include<stack>
#include<fstream>
#include<string>
#include<stdio.h>

using namespace std;


void readsymboltable();// done //
void readtokens();//done //
void readparsetable(); //done //
void readterminalmapper();//done  //
void readvariablemapper();//done //
int getnumberofvariable(string s);//done //
int getnumberofterminal(string s);//done //
string getcharfromsymboltable(int id);//done //
string getclass(int id);//done //
int strlen(string a);//done //
char terminalorvariable(string s);//done //
bool matchterminals(string s);//done //
void showstack();//done //
string getgrammar(int id);//done//
void readgrammar(); //done//
void pushgrammar(string grammar);//done//


int sizest=0,toksiz=0;
int tokens[150];
string st[150];
int parsetable[26][28];
string grammar[53];
string variables[26];
string terminals[28];
stack <string> stk;



int main()
{
		
	readsymboltable();
	readtokens();
	readparsetable();
	readgrammar();
	readvariablemapper();
	readterminalmapper();
	
	stk.push("$");
	stk.push(variables[0]);
	showstack();
	

   char vort;
   string grm2p,ch1,ch2;	
   int toknum=0,row=0,col;
  
   
 
 while(toknum!=toksiz)
  {
  	if(tokens[toknum]!=-1)
  	{


		    vort=terminalorvariable(stk.top());
		    if(tokens[toknum]<89)
		    {
		    ch1=getcharfromsymboltable(tokens[toknum]);
		     }
		     else
		     {
		     	ch1=getclass(tokens[toknum]);
		     }
		    cout<<"Token number="<<toknum<<endl;
		    cout<< "  Token character :::::>   "<< ch1<<endl;

		    if(vort=='v')
		    {
		       
		       ch2=stk.top();
		       row=getnumberofvariable(ch2);
		       col=getnumberofterminal(ch1);
			        if(parsetable[row][col]!=-1   && parsetable[row][col]!=-2 )
				       {
				       	
						       grm2p=getgrammar(parsetable[row][col]);
						       if(grm2p=="NULL")
						       {
						       	stk.pop();
						         }
						        else
						        {
						        	stk.pop();
						        	pushgrammar(grm2p);
						        }

						        showstack();
				       }
				       else
				       {
				       	cout<<"Syntax Error :::> Using PANIC MODE"<<endl;
				       	  if(parsetable[row][col]==-1)
				       	  {
				       	  	
				       	  	stk.pop();
				       	  	toknum++;
				       	  	showstack();
				       	  }
				       	  else 
				       	  {
				       	  	toknum++;
				       	  	showstack();
				       	  }

				       }
			      
		        
		    }
		    else
		    {
		        if (matchterminals(ch1))
		        {
			       	stk.pop();
		            toknum++;
		            cout<<"There is match ;=@"<<endl;
		            showstack();
		        }
		        else
		        {
		        		stk.pop();
		            toknum++;
		            cout<<"There is an error terminals doesnot match so pop in stack and increment in buffer"<<endl;
		            showstack();
		        }
			       

			       
			       	
			      } 
	  }
	  else
	  {
	  	cout<<"Its a lexical error so pop the stack and scan the input buffer"<<endl;
	  	stk.pop();
	  	toknum++;
	  }
       
    
    cout<<endl;
  }
  showstack();
   cout<<"So string has been parsed ;-@"<<endl;
    

		return 0;
}
void readsymboltable()
{
	string b;
	 fstream finod("symboltableupd.txt", fstream::in);
	char ch2;
	int l=0,lock=0;

			while (finod  >> ch2) 
			{
				if(ch2==',')
					{
						l++;
						
					}
					
				else
					{
					b=ch2;	
				  st[l]+=b;
				    }
				}
				sizest=l;

		/*for(int i=0;i<l;i++) //display symbol table
				{
					cout<<st[i]<<endl;

					}*/
}

void readtokens()
{
	fstream finod("token.txt", fstream::in);
	char buffer[1000];
	char ch=' ';
	int temp=0;

	  while (ch !='$') 
    {
    	
      finod >>noskipws  >> ch;
          buffer[temp]=ch;
          temp++;
        
      
    }
    cout<<endl;
    /*for(int i=0;i<temp;i++)
    {
    	cout<<buffer[i];
    }*/
    ofstream fintemp("temporary.txt");
    int lock=0,numoftokens=0;
    for(int i=0;i<temp;i++)
    {

	    if (buffer[i]==',')
	    {
	    	lock++;
	    }
	    if(lock==1)
	    {
	    	if(buffer[i]!=',' && buffer[i]!='>')
	    	{
          fintemp << buffer[i];
             }
	    }
	    if(buffer[i]=='>')
	    	{
	    		lock--;
	    		fintemp << ' ' ;
	    		numoftokens++;
                  
	    	}
   }
   fintemp.close();
   int num;
   ifstream fint("temporary.txt");
     for(int i=0;i<numoftokens;i++)
    {
    	
      fint >> num;
          tokens[i]=num;
  
    }
    toksiz=numoftokens;
     /*  for(int i=0;i<numoftokens;i++)
    {
    	
      cout<<tokens[i];
    }
    */

}
void readparsetable()
{
 ifstream is("parsetable.txt");

 

    int i = 0, j = 0, x = 0;
    char ab;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 28; j++)
        {
           
           is>>parsetable[i][j];
        }
    

 

    }
    /*for (int i = 0; i < 26; i++)
    {
        for (int k = 0; k < 28; k++)
        {

 

            cout << parsetable[i][k] << "   ";
        }
        cout << endl;

 

    }*/

}
void readgrammar()
{
	 fstream fingr("grammar.txt", fstream::in);
	 grammar[0]="empty";
	 string b;
	 
	 int l=1;
		char ch;
			
		  while (ch !='#') 
		    {
		    	
		      fingr >>noskipws  >> ch;
		      if(ch!='#')
		    	{
		    		if(ch==',')
		    		{
		    			l++;
		    			grammar[l]="";
		    		}
		    		else
		    		{
		          grammar[l]+=ch;
		      }
		          
		        }
		      
		    }
					/*for(int i=1;i<=52;i++)
					{
				     cout<<grammar[i]<<endl; 
				    }*/
}
void readvariablemapper()
{
		string b;
	     fstream finv("variables.txt", fstream::in);
	      char ch2;
	        int l=0;

			while (finv  >> ch2) 
			{
				if(ch2==',')
					{
						l++;
						
					}
					
				else
					{
					b=ch2;	
				  variables[l]+=b;
				    }
				}

				/*for(int i=0;i<26;i++)
				{
					cout<<variables[i]<<"  ";
				}*/
				
}
void readterminalmapper()
{
	string b;
	     fstream fint("terminal.txt", fstream::in);
	      char ch2;
	        int l=0;

			while (fint  >> ch2) 
			{
				if(ch2==',')
					{
						l++;
						
					}
					
				else
					{
					b=ch2;	
				  terminals[l]+=b;
				    }
				}
				/*for(int i=0;i<27;i++)
				{
					cout<<terminals[i]<<"  ";
				}*/
}
string getcharfromsymboltable(int id)
{
  string ret;
  ret=st[id];
  return ret;
}
int getnumberofvariable(string s)
{
	for(int i=0;i<26;i++)
	{
		if(s==variables[i])
		{
			return i;
		}
	}
	return -1;
}
int getnumberofterminal(string s)
{
		for(int i=0;i<28;i++)
			     {
				if(s==terminals[i])
				{
					return i;
				}
			}
			 if(s[0]=='+' || s[0]=='-' || s[0]=='0' || s[0]=='1' || s[0]=='2' ||  s[0]=='3' || s[0]=='4' || s[0]=='5' || s[0]=='6' || s[0]=='7' || s[0]=='8' || s[0]=='9' )
              {
              	return 22;
              }
              int lastindex=strlen(s)-1;
              if(s[lastindex]=='_' || s[lastindex]=='0' || s[lastindex]=='1' || s[lastindex]=='2' ||  s[lastindex]=='3' || s[lastindex]=='4' || s[lastindex]=='5' || s[lastindex]=='6' || s[lastindex]=='7' || s[lastindex]=='8' || s[lastindex]=='9' )
              {
                return 0;
              }
              return -1;
}
string getclass(int id)
{
	string laxeme=getcharfromsymboltable(id);
	string a;
	if(laxeme[0]=='+' || laxeme[0]=='-' || laxeme[0]=='0' || laxeme[0]=='1' || laxeme[0]=='2' ||  laxeme[0]=='3' || laxeme[0]=='4' || laxeme[0]=='5' || laxeme[0]=='6' || laxeme[0]=='7' || laxeme[0]=='8' || laxeme[0]=='9' )
		{
			a="number";
			return  a;
		}
		else
		{
			a="identifier";
			return a;

		}
}
string getgrammar(int id)
{
	string a;
	a=grammar[id];
	return a;
}
int strlen(string a)
{
 char ch='a';
 int size=0;
 while(ch!='\0')
 {
 	ch=a[size];
 	size++;
 }
 return size-1;

}
char terminalorvariable(string s)
{
	for(int i=0;i<26;i++)
	{
		if(variables[i]==s)
		{
			return 'v';
		}
	}
	return 't';
}
bool matchterminals(string s)
{
	if(s == stk.top())
	{
		return true;
	}
	return false;
}
void showstack() 
{ 
	stack <string> s=stk;
    while (!s.empty()) 
    { 
        cout << '\t' << s.top(); 
        s.pop();
        cout<<endl; 
    } 
    
} 
void pushgrammar(string grammar)
{
  string temp="",temp1="";
  int sizeg=strlen(grammar);
    stack<string> stktemp;
  int i=0,numofw=0;
  char ch='a';
  int lock=0;
  cout<<"grammar to push--->";
  while(i!=sizeg)
  {
  	ch=grammar[i];
  	i++;
  	cout<<ch;
  	if(ch==' ')
  	{
  		lock=1;
  	}
  	else
  	{
  		lock=0;
  	}
  	if(lock==0)
  	{
  		temp+=ch;
  	}
  	else
  	{
  		stktemp.push(temp);
  		numofw++;
  		temp="";
  	}
  }

  stktemp.push(temp);
  numofw++;
  i=0;
  cout<<endl;
  while(i!=numofw)
  {
  	stk.push(stktemp.top());
  	stktemp.pop();
  	i++;
  }

}
