#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>
class variablelengthbuffer;
class music
{
	char ino[10],name[30],qun[20],price[20];
	public:
	       void input();
	       void output();
	       void display();
	       friend void show(char *filename);
	       friend void search(char *filename);
	       friend void modify(char *filename);
	       friend void deletion(char *filename);
	       friend class variablelengthbuffer;
};
class variablelengthbuffer
{
	char buffer[160];
	public:
	       void unpack(music &p);
	       void pack(music &p);
	       void read(fstream &fs);
	       void write(char *filename);
	       variablelengthbuffer();
};
void music::input()
{
	cout<<"Enter the intrument number\n";
	cin>>ino;
	cout<<"Enter the name of the instrument\n";
	cin>>name;
	cout<<"Enter the quantity of the instrument\n";
	cin>>qun;
	cout<<"Enter the price of the instrument\n";
	cin>>price;
}
void music::output()
{
	cout<<"INO: "<<ino<<endl;
	cout<<"NAME: "<<name<<endl;
	cout<<"QUANTITY: "<<qun<<endl;
	cout<<"PRICE: "<<price<<endl;
}
void music::display()
{
	cout<<ino<<"\t"<<name<<"\t"<<qun<<"\t"<<price<<"\n";
}
void variablelengthbuffer::variablelengthbuffer()
{
     for(int i=0;i<160;i++)
     buffer[i]='\0';
}
void variablelengthbuffer::pack(music &p)
{
	strcpy(buffer,p.ino);strcat(buffer,"|");
	strcat(buffer,p.name);strcat(buffer,"|");
	strcat(buffer,p.qun);strcat(buffer,"|");
	strcat(buffer,p.price);strcat(buffer,"|");
	strcat(buffer,"*");
}
void variablelengthbuffer::unpack(music &p)
{
	char *ptr=buffer;
	while(*ptr)
	{
	   if(*ptr=='|')
	       *ptr='\0';
	   ptr++;
	}
	ptr=buffer;
	strcpy(p.ino,ptr);
	ptr=ptr+strlen(ptr)+1;
	strcpy(p.name,ptr);
	ptr=ptr+strlen(ptr)+1;
	strcpy(p.qun,ptr);
	ptr=ptr+strlen(ptr)+1;
	strcpy(p.price,ptr);
}
void variablelengthbuffer::read(fstream &fs)
{
	fs.getline(buffer,160,'*');
}
void variablelengthbuffer::write(char *filename)
{
	fstream os(filename,ios::out|ios::app);
	os.write(buffer,strlen(buffer));
	os.close();
}
void search(char *filename)
{
	int found=0;
	char key[30];
	variablelengthbuffer b;
	music p;
	fstream is(filename,ios::in);
	if(!is||is.eof())
	{
	      cout<<"Instrument does not exists\n";
	      return;
	}
	cout<<"Enter the name of instrument to be searched\n";
	cin>>key;
	while(!is.eof()&&!found)
	{
	      b.read(is);
	      b.unpack(p);
	      if(strcmp(p.name,key)==0)
	      {
		  cout<<"Instrument found!!!\n";
		  p.output();
		  found=1;
	      }
	}
	if(!found)
	    cout<<"Instrument not found\n";
	is.close();
}
void modify(char *filename)
{
      char key[30];
      variablelengthbuffer b;
      music p;
      char tempfile[]="temp.txt";
      int found=0;
      fstream is(filename,ios::in);
      if(!is||is.eof())
      {
	 cout<<"Instrument does not exist for modification\n";
	 return;
      }
      fstream tfile(tempfile,ios::out|ios::app);
      cout<<"Enter the name of the instruments to be modified:"<<endl;
      cin>>key;
      b.read(is);
      while(!is.eof())
      {
	  b.unpack(p);
	  if(strcmp(p.name,key)==0)
	  {
	      cout<<"\nEnter the new entry:"<<endl;
	      p.input();
	      b.pack(p);
	      b.write(tempfile);
	      found=1;
	  }
	  else
	  {
	     b.pack(p);
	     b.write(tempfile);
	  }
	  b.read(is);
      }
      if(!found)
	    cout<<"The Instrument with given name does not exist"<<endl;
      is.close();
      tfile.close();
      remove(filename);
      rename(tempfile,filename);
}
void show(char *filename)
{
	music p;
	variablelengthbuffer b;
	fstream data(filename,ios::in);
	if(!data||data.eof())
	{
	    cout<<"NO Instrument in file\n";
	    return;
	}
	cout<<"INO\tNAME\tQUNT\tPRICE\n";
	    b.read(data);
	while(!data.eof())
	{
	    b.unpack(p);
	    p.display();
	    b.read(data);
	}
	data.close();
}
void deletion(char *filename)
{
    char name[30];
    variablelengthbuffer b;
    music p;
    char datatemp[]="datatemp.txt";
    int found=0;
    fstream data(filename,ios::in);
    if(!data||data.eof())
    {
	 cout<<"No Instruments present\n";
	 return;
    }
    cout<<"Enter the name of the instrument to be deleted\n";
    cin>>name;
    b.read(data);
    while(!data.eof())
    {
	b.unpack(p);
	if(strcmp(p.name,name)==0)
	{
	    found=1;
	}
	else
	{
	      b.pack(p);
	      b.write(datatemp);
	}
	b.read(data);
    }
    if(found==1)
	cout<<"Instrument deleted successfully\n";
    else
	cout<<"The instrument"<<name<<"does not exists\n";
    data.close();
    remove(filename);
    rename(datatemp,filename);
}
void main()
{
      int choice;
      music ob;
      variablelengthbuffer b;
      char filename[]="store.txt";
      clrscr();
      while(1)
      {
	    cout<<"1.Insert an instrument"<<endl;
	    cout<<"2.Search an instrument"<<endl;
	    cout<<"3.Modify an instrument"<<endl;
	    cout<<"4.Show an instrument"<<endl;
	    cout<<"5.Delete an instrument"<<endl;
	    cout<<"6.Exit"<<endl;
	    cout<<"Enter your choice:"<<endl;
	    cin>>choice;
	    switch(choice)
	    {
		   case 1:ob.input();b.pack(ob);
			  b.write(filename);
			  break;
		   case 2:search(filename);
			  break;
		   case 3:modify(filename);
			  break;
		   case 4:show(filename);
			  break;
		   case 5:deletion(filename);
			  break;
		   case 6:exit(0);
		  default:cout<<"Invalid choice\n";
	    }
      }
}

