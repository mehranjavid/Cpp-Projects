#include<iostream>
#include<stack>
#include<fstream>
#include<string>
#include<stdio.h>

using namespace std;

void readsymboltable();//done
void readtransitiontable();//done
void readmappers();//done
void fillbuffer();//done
int newstate(int currentstate,int chnum);//done
int getnumofchar(char ch);//done
int getid(string laxeme,int state);//done
void maketoken(string laxeme,int id,int state);//done
void makeerror(string lexeme);//done
int makeentryinST(string ch);//done
bool checkfinalstate(int currentstate);//done
string adjust(string laxeme,int state);//done
int strlen(string str);//done
void maketokenb();//done


int tt[20][24];
string st[150];
int sizest,sizeofcode=0;
char characters[23];
string buffer;
ofstream MyFiletok("token.txt");
ofstream MyFileE("error.txt");

int main()
{
 readsymboltable();
 readtransitiontable();
 readmappers();
 fillbuffer();



  //driver
 int i=0,lock=0,currentstate=0,chnum,lock1=0;
 char currentch;
 string laxeme="";
  cout<<endl;

  
  while(i!=sizeofcode)
  {
			  	// getch
					if(lock==0)
					{
			         currentch=buffer[i];
			        // cout<<"character red is"<<currentch<<endl;
			         i++;
					}  
					else
					{
						                     
						lock=0;
					}
                //cout<<currentstate<<"="<<currentch<<endl;
              
			     laxeme+=currentch;
               
			    chnum=getnumofchar(currentch);
			   // cout<<chnum<<",";
			    if(chnum!=-1)
			    {
			    	currentstate=newstate(currentstate,chnum);   
                     
			    	if(checkfinalstate(currentstate))
			    	{
			        
			          
			         // cout<<"laxeme made is="<<laxeme<<".with state"<<currentstate<<endl;
			          
			          maketoken(laxeme,getid(laxeme,currentstate),currentstate);
			          if(currentstate==20)
			          {
			          	lock=1;
			          }
                       currentstate=0;
			          laxeme="";
			    	}
			    	//cout<<"state changed to="<<currentstate<<endl;
			    	if(currentstate==-1)
			    	{
			    		currentstate=0;
			    		maketokenb();
			    		makeerror(laxeme);
			    		//cout<<"error made with laxeme="<<laxeme<<endl;
			    		laxeme="";

			    	}
			    	
			    }
			    else
			    {

			    	makeerror(laxeme);
			    	maketokenb();
			    	//cout<<"making error wiht laxeme="<<laxeme<<endl;
			    	laxeme="";
			    	currentstate=0;
			    }

 }

 


 return 0;
}
void readsymboltable()
{
	string b;
	 fstream finod("symboltable.txt", fstream::in);
	char ch2;
	int l=0;

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
void readtransitiontable()
{
	 ifstream is("Transitiontable.txt");
		   int r=0,c= 0;
		   int i=0,j=0,x=0;
   
			  while ( is >> x)
			   {
			   	tt[i][j]=x;
			   	j++;
				   	if (j==24)
				   	{
				   		j=0;
				   		i++;
				   	}

			    }
		   /* for(int i=0;i<20;i++)
		    {
		    	for(int y=0;y<24;y++)
		    	{
		    		cout<<tt[i][y]<<" ";
		    	}
		    	cout<<endl;
		    }*/
}
void readmappers()
{
	char ch1;
		int sizech=0;
		fstream fino("mapper.txt", fstream::in);
		
		for(int i=0;i<23;i++)
		{
			fino>>ch1;
			characters[i]=ch1;
			sizech++;
		}
		characters[23]=' ';
		sizech++;
		
		/*for(int i=0;i<sizech;i++)
		{
			cout<<characters[i]<<" ";
		}*/
}
void fillbuffer()
{
	char ch;
	fstream fin("code.txt", fstream::in);
  while (ch !='#') 
    {
    	
      fin >>noskipws  >> ch;
      if(ch!='#')
    	{
          buffer+=ch;
          sizeofcode++;
        }
      
    }
   // cout<<buffer<<endl;
    //cout<<sizeofcode;

}
int newstate(int currentstate,int chnum)
{

	return  tt[currentstate][chnum];

}
int getnumofchar(char ch)
{
	if(ch>='A'  && ch<='Z')
	{
		return 3;
	}
	else if(ch>='a'  && ch<='z')
	{
		return 3;
	}
	else if(ch>='0'  && ch<='9')
	{
		return 4;
	}	
	for(int i=0;i<24;i++)
	{
		if(characters[i]==ch)
		{
			return i;
		}
	}
	return -1;
}
int getid(string laxeme,int state)
{
	string lex=adjust(laxeme,state);
	
	for(int i=0;i<sizest+1;i++)
	{
		if(lex==st[i])
		{
			return i;
		}
	}
	
	int id=makeentryinST(lex);
	return id;
}
void maketoken(string laxeme,int id,int state)
{
	if(laxeme!=" ")
	{
    laxeme=adjust(laxeme,state);
    MyFiletok << "<";	
	if(id>=0 && id<61)
		{
			MyFiletok << "keyword";
		}
	else if(id>=61 && id<67)
		{
			MyFiletok<< "punctuation";
		}
	else if(id>=67 && id<89)
		{
			MyFiletok << "operator";
		}
		else if(id==-1)
		{
			makeerror(laxeme);
		}
    	else
	    {
			if(laxeme[0]=='+' || laxeme[0]=='-' || laxeme[0]=='0' || laxeme[0]=='1' || laxeme[0]=='2' ||  laxeme[0]=='3' || laxeme[0]=='4' || laxeme[0]=='5' || laxeme[0]=='6' || laxeme[0]=='7' || laxeme[0]=='8' || laxeme[0]=='9' )
			{

				MyFiletok << "Number";
				
			}

			else
			{ 
	          MyFiletok << "identifier";
			}
		}
	//cout<<laxeme<<",";
	MyFiletok << ",";
	MyFiletok << id;
	MyFiletok << ">";
   }
	
}
int makeentryinST(string ch)
{
	int check=0,lastindex;
	lastindex=strlen(ch)-1;
	if(ch[lastindex]=='_' || ch[lastindex]=='0' || ch[lastindex]=='1' || ch[lastindex]=='2' ||  ch[lastindex]=='3' || ch[lastindex]=='4' || ch[lastindex]=='5' || ch[lastindex]=='6' || ch[lastindex]=='7' || ch[lastindex]=='8' || ch[lastindex]=='9' )
     {
       sizest++;
	st[sizest]=ch;
	return sizest-1;
     }
     else if(ch[0]=='-' || ch[0]=='+' || ch[0]=='0' || ch[0]=='1' || ch[0]=='2' ||  ch[0]=='3' || ch[0]=='4' || ch[0]=='5' || ch[0]=='6' || ch[0]=='7' || ch[0]=='8' || ch[0]=='9' )
	 {
	     sizest++;
	st[sizest]=ch;
	return sizest-1;	
	 }
	 return -1;
	
}
void makeerror(string laxeme)
{
	MyFileE << "<";	
	MyFileE << laxeme;
	
	MyFileE << ">";
}
bool checkfinalstate(int currentstate)
{
    if(currentstate==20  || currentstate==21)
		{
			return true;
		}
		else
		{
			return false;
		}

}
string adjust(string laxeme,int state)
{
	if (state==20)
	{
      string a;
      int size=strlen(laxeme);
      for(int i=0;i<size-1;i++)
      {
      	a+=laxeme[i];
      }
      
      return a;
	}
	else
	{
		
		return laxeme;
	}
}
int strlen(string str)
{
	char ch='h';
	int i=0;
	while(ch!='\0')
	{
		ch=str[i];
		i++;
	}
	return i-1;
}
void maketokenb()
{
    MyFiletok << "<";
	MyFiletok << ",";
	MyFiletok << -1;
	MyFiletok << ">";
   
	
}