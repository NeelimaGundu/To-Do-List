#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
int count=0;
string ReadNthLine(int);
string ReadNthLine(int N)
{
   ifstream in;
   string s;
   in.open("todo.txt");
   if(in.fail())
   {
       cout<<"error opening file";
   }
   else 
   {
   s.reserve();    
   for(int i = 0; i < N; i++)
   {
       getline(in, s);
   }
   }
   in.close();
   return s;
}
void counting()
{
    ifstream in;
    string line;
    in.open("todo.txt");
    while (getline(in, line))
    count++;
    in.close();
}

int deleteline(int);
int deleteline(int number)
{
    if(number==1)
    {
        string s;
        ifstream in;
        ofstream out;
        in.open("todo.txt");
        out.open("out.txt");
        getline(in,s);
        while(getline(in,s))
        {
            out<<s<<endl;
        }
        in.close();
        out.close();
        remove("todo.txt");
        rename("out.txt","todo.txt");
    }
    else 
    {
        ifstream is("todo.txt"); 
        ofstream ofs; 
        ofs.open("temp.txt", ofstream::out); 
  
        char c; 
        int line_no = 1; 
        while (is.get(c)) 
        { 
        if (c == '\n') 
        line_no++; 
  
        if (line_no != number) 
            ofs << c; 
        } 
  
        ofs.close(); 
  
        is.close(); 
   
        remove("todo.txt"); 
  
        rename("temp.txt", "todo.txt");
    }
        return 0;
}
int main(int argc, char* argv[])
{   
    if(strcmp(argv[1],"add")==0)
    {
        ofstream outfile;
        string line;
        outfile.open("todo.txt",ios_base::app);
        outfile<<argv[2]<<"\n";
        outfile.close();
        counting();
        cout<<"Added todo: \""<<ReadNthLine(count);
        cout<<"\""<<endl;
        cout<<count;

    }
    else if(strcmp(argv[1],"ls")==0)
    {      
        counting();
        for(int i=count;i>0;i--)
        {
            cout<<"["<<i<<"]"<<" ";
            cout<<ReadNthLine(i);
            cout<<endl;
        }    
    
    }
    else if(strcmp(argv[1],"del")==0)
    {
        int number;
        number = atoi(argv[2]);
        counting();
        if(number>count)
        {
            cout<<"Error: todo #"<<number<<" does not exist. Nothing deleted."<<endl;
            exit(0);
        }
        else
        {
            deleteline(number);
            cout<<"Delted todo #"<<number<<endl;
        }
      
    }   
    else if(strcmp(argv[1],"done")==0)
    {
        int number;
        number = atoi(argv[2]);
        counting();
        if(number>count)
        {
            cout<<"Error: todo #"<<number<<" does not exist."<<endl;
            exit(0);
        }
        else
        {
            time_t now = time(0);
            tm * ltm = localtime(&now);
            string doneline;
            doneline= ReadNthLine(number);
            deleteline(number);
            cout<<"Marked todo #"<<number<<" as done."<<endl;
            ofstream donefile;
            donefile.open("done.txt",ios_base::app);
            donefile<<"x "<<1900+ltm->tm_year<<"-"<<1+ltm->tm_mon<<"-"<<ltm->tm_mday<<" "<<doneline<<endl;
            donefile.close();

        }
    }
    else if(strcmp(argv[1],"report")==0)
    {
        time_t now = time(0);
        tm * ltm = localtime(&now);
        ifstream in,in2;
        string line;
        int todocount=0,donecount=0;
        in.open("todo.txt");
        while (getline(in, line))
        todocount++;
        in.close();
        in2.open("done.txt");
        while(getline(in2,line))
        donecount++;
        in2.close();
        cout<<1900+ltm->tm_year<<"-"<<1+ltm->tm_mon<<"-"<<ltm->tm_mday<<" ";
        cout<<"Pending : "<<todocount<<" Completed : "<<donecount<<endl;
    }
    else
    {
        cout<<"Usage :-"<<endl;
        cout<<"$ ./todo add \"todo item\"# Add a new todo"<<endl;
        cout<<"$ ./todo ls               # Show remaining todos"<<endl;
        cout<<"$ ./todo del NUMBER       # Delete a todo"<<endl;
        cout<<"$ ./todo done NUMBER      # Complete a todo"<<endl;
        cout<<"$ ./todo help             # Show usage"<<endl;
        cout<<"$ ./todo report           # Statistics"<<endl;   
    }
    
     return 0;
}
