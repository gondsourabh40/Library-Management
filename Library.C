#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<conio.h>
void string(char*,int,int);
void bar(int,int,int,int);
void rectangle(int,int,int,int);
void windowbar(int,int,int,int,int,int);
typedef struct issue
{
	int bno;
	int uniqueno;
	int dd,mm,yy;
}Issue;
typedef struct book
{
	int no;
	char isbn[11];
	char sub[20];
	char name[20];
	char author[20];
	char publish[20];
	int edition;
	int copies;
	int cost;
}Book;
typedef struct member
{
	char name[20];
	int unique;
	char rollno[13];
	char mobile[11];
	char branch[13];
	int sem;
	int dd,mm,yy;
}Member;
void issueRecord()
{
	FILE *fp=fopen("issue.txt","rb");
	int n=0,i=0,unique;
	char str[10],ch;
	Issue s,*p;
	gotoxy(34,6);
	cprintf("Unique no:");
	gotoxy(45,6);
	string(str,4,0);
	unique=atoi(str);
	while(fread(&s,sizeof(s),1,fp))
	{
		if(unique==s.uniqueno)
		n++;
	}
	p=(Issue*)malloc(n*sizeof(Issue));
	rewind(fp);
	while(fread(&s,sizeof(s),1,fp))
	{
		if(unique==s.uniqueno)
		p[i++]=s;
	}
	textcolor(WHITE);
	//windowbar(15,4,65,24,4,7);
	rectangle(20,7,60,21);
	textcolor(BLACK);
	textbackground(GREEN);
	gotoxy(33,8);
	cprintf("Book no  Date");
	textbackground(RED);
	i=0;
	do
	{
	int ele=10,j=0,num;
	if(ch==80&&ele<n&&i<n)
	{
	ele++;
	i++;
	}
	else if(ch==72&&i>0&&ele>9)
	{
	ele--;
	i--;
	}
	num=i;
	for(j=0;i<ele&&i<n;i++,j++)
	{
		gotoxy(33,10+j);
		cprintf("%d        %d/%d/%d",p[i].bno,p[i].dd,p[i].mm,p[i].yy);
	}
	i=num;
	ch=getch();
	}while(ch!=27);
	fclose(fp);
}
int books(int bno)
{
	Book b;
	int count=0;
	FILE *fp=fopen("Book.txt","rb");
	while(fread(&b,sizeof(b),1,fp))
	{
		if(bno==b.no)
		count+=b.copies;
	}
	fclose(fp);
	return count;
}
int issues(int bno)
{
	Issue s;
	int count=0;
	FILE *fp=fopen("Issue.txt","rb");
	while(fread(&s,sizeof(s),1,fp))
	{
		if(bno==s.bno)
		count++;
	}
	fclose(fp);
	return count;
}
void button(char *s,int x,int y)
{
	gotoxy(x,y);
	textbackground(GREEN);
	textcolor(BLACK);
	cprintf(" %s ",s);
	getch();
	gotoxy(x,y);
	textbackground(RED);
	cprintf(" %s ",s);
	delay(70);

}
void string(char *s,int digit,int flag)
{
	int i=0,x,y;
	char ch;
	textcolor(BLINK);
	cprintf("%c",179);
	while((ch=getch())!=13)
	{
		if(ch==8&&i>0)
		{
			cprintf("\b\b  \b\b");
			textcolor(BLINK);
			cprintf("%c",179);
			i--;;
			textcolor(BLINK);
		}
		else if((flag||(!flag&&isdigit(ch)))&&ch!=8&&i<digit)
		{
		textcolor(WHITE);
		cprintf("\b%c",ch);
		textcolor(BLINK);
		cprintf("%c",179);
		s[i]=ch;
		i++;
		}
		}
		s[i]='\0';
	cprintf("\b ");
}
void issuebook()
{
	int i;
	char str[12];
	struct date d;
	Issue s;
	FILE *fp=fopen("Issue.txt","ab");
	textcolor(BLACK);
	gotoxy(27,8);
	cprintf("Unique no:");
	gotoxy(27,10);
	cprintf("Book no  :");
	gotoxy(27,12);
	cprintf("Date     :");
	textcolor(GREEN);
	textbackground(GREEN);
	bar(39,8,54,9);
	bar(39,10,54,11);
	bar(39,12,54,13);
	textcolor(RED);
	gotoxy(40,12);
	getdate(&d);
	cprintf("%d/%d/%d",d.da_day,d.da_mon,d.da_year);
	textcolor(BLACK);
	gotoxy(40,8);
	string(str,4,0);
	s.uniqueno=atoi(str);
	if(!findmember(s.uniqueno,2))
	{
		windowbar(20,8,60,20,3,7);
		gotoxy(29,10);
		cprintf("Use Another Unique no");
		button("OK",38,15);
		fclose(fp);
		return;
	}
	if((s.bno=findbook(4))==-1)
	{
		windowbar(20,8,60,20,3,7);
		gotoxy(32,10);
		cprintf("Book not present");
		button("OK",38,15);
		fclose(fp);
		return;
	}
	if((books(s.bno)-issues(s.bno))<1)
	{
		windowbar(20,8,60,20,3,7);
		gotoxy(32,10);
		cprintf("Books are issued");
		button("OK",38,15);
		fclose(fp);
		return;
	}
	s.dd=d.da_day;
	s.mm=d.da_mon;
	s.yy=d.da_year;
	fwrite(&s,sizeof(s),1,fp);
	windowbar(20,8,60,20,3,7);
	gotoxy(28,10);
	cprintf("Books Issue Successfully");
	button("OK",38,15);
	fclose(fp);
}
void returnbook()
{
	Issue s;
	int no,flag=1,bno;
	char str[12];
	FILE *fp1=fopen("issue.txt","rb"),*fp2=fopen("temp.txt","wb");
	gotoxy(27,8);
	cprintf("Unique no:");
	gotoxy(27,10);
	cprintf("Book no  :");
	gotoxy(27,12);
	textcolor(GREEN);
	textbackground(GREEN);
	bar(39,8,54,9);
	bar(39,10,54,11);
	textcolor(BLACK);
	gotoxy(40,8);
	string(str,4,0);
	no=atoi(str);
	if(!findmember(no,2))
	{
		windowbar(20,8,60,20,3,7);
		gotoxy(32,10);
		cprintf("Wrong Unique no");
		button("OK",38,15);
		fclose(fp1);
		fclose(fp2);
		return;
	}
	gotoxy(40,10);
	string(str,4,0);
	bno=atoi(str);
	while(fread(&s,sizeof(s),1,fp1))
	{
		if(s.uniqueno==no&&flag&&s.bno==bno)
		{
			windowbar(20,8,60,20,3,7);
			gotoxy(34,10);
			textcolor(WHITE+BLINK);
			textbackground(GREEN);
			cprintf("  Returned  ");
			button("OK",38,15);
			flag=0;
		}
		else
		fwrite(&s,sizeof(s),1,fp2);
	}
	if(flag==1)
	{
		windowbar(20,8,60,20,3,7);
		gotoxy(33,10);
		textcolor(WHITE);
		cprintf("Book not Found");
		button("OK",38,15);
	}
	fclose(fp1);
	fclose(fp2);
	remove("issue.txt");
	rename("temp.txt","issue.txt");
}

void addmember()
{
	Member m;
	char s[14];
	int i;
	FILE *fp=fopen("member.txt","ab");
	textcolor(BLACK);
	gotoxy(10,8);
	cprintf("Name     :");
	gotoxy(10,10);
	cprintf("Unique id:");
	gotoxy(10,12);
	cprintf("Roll no  :");
	gotoxy(10,14);
	cprintf("Branch   :");
	gotoxy(10,16);
	cprintf("Mobile no:");
	gotoxy(10,18);
	cprintf("D O B    :");
	textcolor(GREEN);
	textbackground(GREEN);
	for(i=0;i<12;i+=2)
	bar(20,8+i,35,9+i);
	gotoxy(21,8);
	string(m.name,10,1);
	gotoxy(21,10);
	string(s,4,0);
	m.unique=atoi(s);
	if(findmember(m.unique,2))
	{
		windowbar(20,8,60,20,3,7);
		gotoxy(30,10);
		textcolor(WHITE);
		cprintf("Write another Unique no");
		button("OK",38,15);
		fclose(fp);
		return;
	}
	gotoxy(21,12);
	string(m.rollno,12,1);
	gotoxy(21,14);
	string(m.branch,10,1);
	gotoxy(21,16);
	string(m.mobile,10,0);
	gotoxy(21,18);
	textcolor(RED);
	cprintf("   /   /  ");
	textcolor(BLACK+BLINK);
	gotoxy(21,18);
	string(s,2,0);
	m.dd=atoi(s);
	gotoxy(25,18);
	string(s,2,0);
	m.mm=atoi(s);
	gotoxy(29,18);
	string(s,2,0);
	m.yy=atoi(s);
	fwrite(&m,sizeof(m),1,fp);
	fclose(fp);
}
int findmember(int unique,int opt)
{
	Member m;
	FILE *fp=fopen("member.txt","rb+");
	if(fp==NULL)
	{
	fclose(fp);
	return 0;
	}
	while(fread(&m,sizeof(m),1,fp))
	{
		if(unique==m.unique)
		{
			 if(opt==2)
			 {
			 fclose(fp);
			 return 1;
			 }
			 if(!opt)
			 {
			gotoxy(33,8);
			textcolor(BLINK+BLACK);
			cprintf(" Record Found ");
			}
			else
			{
			opt=20;
			textcolor(WHITE);
			textbackground(CYAN);
			rectangle(48,5,74,24);
			gotoxy(55,7);
			cprintf("<Old Record>");
			}
			textbackground(RED);
			textcolor(BLACK);
			gotoxy(31+opt,10);
			cprintf("Name    : %s",m.name);
			gotoxy(31+opt,12);
			cprintf("Roll no : %s",m.rollno);
			gotoxy(31+opt,14);
			cprintf("Branch  : %s",m.branch);
			gotoxy(31+opt,16);
			cprintf("Mobile  : %s",m.mobile);
			gotoxy(31+opt,18);
			cprintf("DOB     : %d/%d/%d",m.dd,m.mm,m.yy);
			if(opt)
			{
			int i;
			char s[10];
			fseek(fp,-(long int)sizeof(m),1);
			textcolor(BLACK);
			textbackground(RED);
			gotoxy(10,10);
			cprintf("Name     :");
			gotoxy(10,12);
			cprintf("Roll no  :");
			gotoxy(10,14);
			cprintf("Branch   :");
			gotoxy(10,16);
			cprintf("Mobile no:");
			gotoxy(10,18);
			cprintf("D O B    :");
			textcolor(GREEN);
			textbackground(GREEN);
			for(i=0;i<10;i+=2)
			bar(20,10+i,35,11+i);
			gotoxy(21,10);
			string(m.name,12,1);
			gotoxy(21,12);
			string(m.rollno,12,1);
			gotoxy(21,14);
			string(m.branch,10,1);
			gotoxy(21,16);
			string(m.mobile,10,0);
			gotoxy(21,18);
			textcolor(RED);
			cprintf("   /   /  ");
			textcolor(BLACK+BLINK);
			gotoxy(21,18);
			string(s,2,0);
			m.dd=atoi(s);
			gotoxy(25,18);
			string(s,2,0);
			m.mm=atoi(s);
			gotoxy(29,18);
			string(s,2,0);
			m.yy=atoi(s);
			fwrite(&m,sizeof(m),1,fp);
			}
			fclose(fp);
			getch();
			return 1;
		}
	}
	if(opt!=2)
	printf("Record not found");
	fclose(fp);
	return 0;
}

void delbook()
{
	int no,flag=0;
	char ch[6];
	Book b;
	FILE *fp1=fopen("Book.txt","rb");
	FILE *fp2=fopen("temp.txt","wb");
	gotoxy(27,6);
	cprintf("Book no:");
	textcolor(GREEN);
	textbackground(GREEN);
	bar(37,6,49,7);
	gotoxy(39,6);
	string(ch,4,0);
	no=atoi(ch);
	while(fread(&b,sizeof(b),1,fp1))
	{
		if(no!=b.no)
		fwrite(&b,sizeof(b),1,fp2);
		else
		flag=1;
	}
	fclose(fp1);
	fclose(fp2);
	remove("Book.txt");
	if(rename("temp.txt","Book.txt")==-1)
	printf("Failed");
	gotoxy(31,14);
	windowbar(20,8,60,20,3,7);
	gotoxy(32,10);
	textcolor(WHITE);
	if(flag==1)
	cprintf("  Book deleted  ");
	else
	cprintf("  Book not found ");
	button("OK",38,15);
}
int findbook(int opt)
{
	Book b;
	char ch[6];
	int no;
	FILE *fp=fopen("Book.txt","rb+");
	textbackground(LIGHTGRAY);
	textcolor(BLACK);
	gotoxy(34,4);
	if(opt)
	cprintf("Book/Update");
	else
	cprintf("Book/Fnd");
	textbackground(RED);
	if(opt!=4)
	{
	gotoxy(27,6);
	if(opt!=3)
	{
	cprintf("Book no:");
	textcolor(GREEN);
	textbackground(GREEN);
	bar(37,6,49,7);
	gotoxy(39,6);
	}
	else
	gotoxy(21,6);
	}
	if(opt==4)
	gotoxy(40,10);
	textbackground(GREEN);
	string(ch,4,0);
	no=atoi(ch);
	while(fread(&b,sizeof(b),1,fp))
	{
		if(no==b.no)
		{
			if(opt==1)
			{
				int i;
				fseek(fp,-(long int)sizeof(b),1);
				textcolor(WHITE);
				textbackground(CYAN);
				rectangle(50,5,74,24);
				textbackground(RED);
			textcolor(BLACK);
			//gotoxy(33,10);
			//cprintf("Book no: %d",b.no);
			gotoxy(54,6);
			cprintf("<<Old Record>>");
			gotoxy(53,8);
			cprintf("ISBN no  :%s",b.isbn);
			gotoxy(53,10);
			cprintf("Subject  :%s",b.sub);
			gotoxy(53,12);
			cprintf("Book name:%s",b.name);
			gotoxy(53,14);
			cprintf("Author   :%s",b.author);
			gotoxy(53,16);
			cprintf("Edition= :%s",b.publish);
			gotoxy(53,18);
			cprintf("Publisher:%d",b.edition);
			gotoxy(53,20);
			cprintf("Copies   :%d",b.copies);
			gotoxy(53,22);
			cprintf("Cost     :%d",b.cost);

				gotoxy(35,4);
				textcolor(BLACK);
				textbackground(15);
				textbackground(RED);
				textcolor(BLACK);
				gotoxy(10,8);
				cprintf("ISBN NO:");
				gotoxy(10,10);
				cprintf("Subject:");
				gotoxy(10,12);
				cprintf("Book Name:");
				gotoxy(10,14);
				cprintf("Author:");
				gotoxy(10,16);
				cprintf("Publisher:");
				gotoxy(10,18);					cprintf("Edition:");
				gotoxy(10,20);
				cprintf("Copies:");
				gotoxy(10,22);
				cprintf("Cost:");
				textcolor(GREEN);
				for(i=2;i<18;i+=2)
				bar(20,6+i,32,7+i);
				textcolor(WHITE);
				textbackground(GREEN);
				gotoxy(21,8);
				string(b.isbn,10,1);
				gotoxy(21,10);
				string(b.sub,10,1);
				gotoxy(21,12);
				string(b.name,10,1);
				gotoxy(21,14);
				string(b.author,10,1);
				gotoxy(21,16);
				string(b.publish,10,1);
				gotoxy(25,18);
				textcolor(RED);
				cprintf("th");
				gotoxy(21,18);
				string(ch,2,0);
				b.edition=atoi(ch);
				gotoxy(21,20);
				string(ch,4,0);
				b.copies=atoi(ch);
				gotoxy(21,22);
				string(ch,4,0);
				b.cost=atoi(ch);
				fwrite(&b,sizeof(b),1,fp);
				windowbar(20,8,60,20,3,7);
				gotoxy(33,10);
				textcolor(WHITE);
				cprintf("Record Updated");
				button("OK",38,15);
				fclose(fp);
				return 1;
			}
			else if(opt==4)
			{
			fclose(fp);
			return no;
			}
			else if(opt==3)
			{
			fclose(fp);
			return -1;
			}
			else
			{
			gotoxy(34,8);
			cprintf("Record Found");
			textbackground(RED);
			textcolor(BLACK);
			//gotoxy(33,10);
			//cprintf("Book no: %d",b.no);
			gotoxy(18,10);
			cprintf("ISBN no: %s",b.isbn);
			gotoxy(18,12);
			cprintf("Subject:  %s",b.sub);
			gotoxy(18,14);
			cprintf("Book name:%s",b.name);
			gotoxy(18,16);
			cprintf("Author   :%s",b.author);
			gotoxy(48,10);
			cprintf("Edition= :%s",b.publish);
			gotoxy(48,12);
			cprintf("Publisher :%d",b.edition);
			gotoxy(48,14);
			cprintf("Copies :%d",b.copies);
			gotoxy(48,16);
			cprintf("Cost=%d",b.cost);
			fclose(fp);
			getch();
			return 1;
			}
		}
	}
	fclose(fp);
	if(opt==4)
	return -1;
	if(opt==3)
	return no;
	windowbar(20,8,60,20,3,7);
	gotoxy(32,10);
	textcolor(WHITE);
	cprintf("Record Not Found");
	button("OK",38,15);
	return 0;
}
void addbook()
{
	Book b;
	int i;
	char ch[12];
	FILE *fp1=fopen("Book.txt","ab");
	gotoxy(35,4);
	textcolor(BLACK);
	textbackground(15);
	cprintf("Book/Add");
	textbackground(RED);
	textcolor(BLACK);
	gotoxy(10,6);
	cprintf("Book no:");
	gotoxy(10,8);
	cprintf("ISBN NO:");
	gotoxy(10,10);
	cprintf("Subject:");
	gotoxy(10,12);
	cprintf("Book Name:");
	gotoxy(10,14);
	cprintf("Author:");
	gotoxy(10,16);
	cprintf("Publisher:");
	gotoxy(10,18);
	cprintf("Edition:");
	gotoxy(10,20);
	cprintf("Copies:");
	gotoxy(10,22);
	cprintf("Cost:");
	textcolor(GREEN);
	for(i=0;i<18;i+=2)
	bar(20,6+i,32,7+i);
	textcolor(WHITE);
	textbackground(GREEN);
	gotoxy(21,6);
	if((b.no=findbook(3))==-1)
	{
		windowbar(20,8,60,20,3,7);
		gotoxy(30,10);
		textcolor(WHITE);
		cprintf("Write Another Book no");
		button("OK",37,15);
		fclose(fp1);
		return;
	}
	//string(ch,4);
	gotoxy(21,8);
	string(b.isbn,10,1);
	gotoxy(21,10);
	string(b.sub,10,1);
	gotoxy(21,12);
	string(b.name,10,1);
	gotoxy(21,14);
	string(b.author,10,1);
	gotoxy(21,16);
	string(b.publish,10,1);
	gotoxy(25,18);
	textcolor(RED);
	cprintf("th");
	gotoxy(21,18);
	string(ch,2,0);
	b.edition=atoi(ch);
	gotoxy(21,20);
	string(ch,4,0);
	b.copies=atoi(ch);
	gotoxy(21,22);
	string(ch,4,0);
	b.cost=atoi(ch);
	fwrite(&b,sizeof(b),1,fp1);
	fclose(fp1);
}
void bar(int left,int top,int right,int bottom)
{
	int i,j;
	for(i=0;i<bottom-top;i++)
	{
	gotoxy(left,top+i);
	for(j=0;j<right-left;j++)
	cprintf("%c",219);
	}
}
void rectangle(int l,int lt,int r,int rb)
{
	int i;
	gotoxy(l,lt);
	cprintf("%c",218);
	for(i=0;i<r-l-2;i++)
	cprintf("%c",196);
	cprintf("%c",191);
	for(i=0;i<rb-lt-2;i++)
	cprintf("\n\b%c",179);
	gotoxy(l,lt+1);
	for(i=0;i<rb-lt-2;i++)
	cprintf("%c\n\b",179);
	cprintf("%c",192);
	for(i=0;i<r-l-2;i++)
	cprintf("%c",196);
	cprintf("%c",217);
	/*printf("%c%c%c",218,196,191);
	printf("\n%c %c",179,179);
	printf("\n%c%c%c",192,196,217);*/
}

void windowbar(int l,int lt,int r,int rb,int b,int rec)
{
	textcolor(rec);
	bar(l,lt,r,lt+1);
	textcolor(b);
	bar(l,lt+1,r,rb);
	textcolor(WHITE);
	textbackground(b);
	rectangle(l+1,lt+1,r-1,rb);
}
void frontpage()
{
	textbackground(LIGHTGRAY);
	textcolor(BLACK);
	gotoxy(2,2);
	cprintf("  %c  ",240);
	//cprintf("%c",179);
	cprintf("  BOOK  ");
	//cprintf("%c  ",179);
	cprintf("  MEMBER  ");
	//cprintf("%c  ",179);
	cprintf("  ISSUE  ");
       //	cprintf("%c  ",179);
	cprintf("  ABOUT  ");
	//cprintf("%c",179);
}
void quit()
{
	textcolor(CYAN);
	textbackground(CYAN);
	bar(2,3,10,6);
	textcolor(BLACK);
	rectangle(2,3,10,6);
	gotoxy(4,4);
	cprintf("Quit");
}
void book()
{
	textcolor(CYAN);
	textbackground(CYAN);
	bar(7,3,20,9);
	textcolor(BLACK);
	rectangle(7,3,20,9);
	gotoxy(10,4);
	cprintf("Add");
	gotoxy(10,5);
	cprintf("Find");
	gotoxy(10,6);
	cprintf("Update");
	gotoxy(10,7);
	cprintf("Remove");
}
void member()
{
	textcolor(CYAN);
	bar(15,3,27,8);
	textbackground(CYAN);
	textcolor(BLACK);
	rectangle(15,3,27,8);
	gotoxy(18,4);
	cprintf("Add");
	gotoxy(18,5);
	cprintf("Find");
	gotoxy(18,6);
	cprintf("Update");
}
void issue()
{
	textcolor(CYAN);
	textbackground(CYAN);
	bar(25,3,37,8);
	textcolor(BLACK);
	rectangle(25,3,37,8);
	gotoxy(28,4);
	cprintf("Issue");
	gotoxy(28,5);
	cprintf("Return");
	gotoxy(28,6);
	cprintf("Record");
}
void option()
{
	int i=0,j=0;
	char ch;
	while(i!=-2)
	{
		textcolor(BLUE);
		if(j==0)
		bar(2,3,80,25);
		textcolor(LIGHTGRAY);
		frontpage();
		textcolor(GREEN);
		textbackground(GREEN);
		if(i==5)
		i=0;
		else if(i==-1)
		i=4;
		if(i==0)
		{
		bar(2,2,7,3);
		textcolor(BLACK);
		gotoxy(4,2);
		cprintf("%c",240);
		quit();
		}
		else if(i==1)
		{
		bar(7,2,15,3);
		textcolor(BLACK);
		gotoxy(9,2);
		cprintf("BOOK");
		book();
		}
		else if(i==2)
		{
		bar(15,2,25,3);
		textcolor(BLACK);
		gotoxy(17,2);
		cprintf("MEMBER");
		member();
		}
		else if(i==3)
		{
		bar(25,2,34,3);
		textcolor(BLACK);
		gotoxy(27,2);
		cprintf("ISSUE");
		issue();
		}
		else if(i==4)
		{
		bar(34,2,43,3);
		textcolor(BLACK);
		gotoxy(36,2);
		cprintf("ABOUT");
		}
		textcolor(BROWN);
		textbackground(BROWN);
		if(i==0)
		{
			if(j==2)
			j=0;
			if(j==-1)
			j=1;
			if(j==1)
			{
			bar(3,4,9,5);
			textcolor(BLACK);
			gotoxy(4,4);
			cprintf("Quit");
			if(!kbhit())
			{
				if((ch=getch())==13)
				{
				system("cls");
				exit(0);
				}
			}
			}
		}
		else if(i==1)
		{
			if(j==5)
			j=1;
			if(j==-1)
			j=4;
			if(j==1)
			{
			bar(8,4,19,5);
			textcolor(BLACK);
			gotoxy(10,4);
			cprintf("Add");
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				windowbar(5,3,75,24,1,1);
				windowbar(5,4,75,24,4,7);
				textcolor(BLUE);
				addbook();
				textcolor(BLUE);
				bar(5,3,75,25);
			}
			}
			}
			else if(j==2)
			{
			bar(8,5,19,6);
			textcolor(BLACK);
			gotoxy(10,5);
			cprintf("Find");
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				windowbar(5,3,75,24,1,1);
				windowbar(5,4,75,24,4,7);
				textcolor(BLUE);
				findbook(0);
				textcolor(BLUE);
				bar(5,3,75,25);
			}
			}

			}
			else if(j==3)
			{
			bar(8,6,19,7);
			textcolor(BLACK);
			gotoxy(10,6);
			cprintf("Update");
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				windowbar(5,3,75,24,1,1);
				windowbar(5,4,75,24,4,7);
				textcolor(BLUE);
				findbook(1);
				textcolor(BLUE);
				bar(5,3,75,25);
			}
			}
			}
			else if(j==4)
			{
			bar(8,7,19,8);
			textcolor(BLACK);
			gotoxy(10,7);
			cprintf("Remove");
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				windowbar(5,3,75,24,1,1);
				windowbar(5,4,75,24,4,7);
				textcolor(BLUE);
				delbook();
				textcolor(BLUE);
				bar(5,3,75,25);
			}
			}
			}
		}
		else if(i==2)
		{
			if(j==-1)
			j=3;
			if(j==4)
			j=1;
			if(j==1)
			{
			bar(16,4,26,5);
			gotoxy(18,4);
			textcolor(BLACK);
			cprintf("Add");
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				windowbar(5,3,75,24,1,1);
				windowbar(5,4,75,24,4,7);
				textcolor(BLUE);
				addmember();
				textcolor(BLUE);
				bar(5,3,75,25);
			}
			}
			}
			else if(j==2)
			{
			bar(16,5,26,6);
			gotoxy(18,5);
			textcolor(BLACK);
			cprintf("Find");
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				char s[6];
				int no;
				windowbar(5,3,75,24,1,1);
				windowbar(5,4,75,24,4,7);
				textcolor(BLACK);
				gotoxy(25,6);
				cprintf("Unique no:");
				textcolor(GREEN);
				textbackground(GREEN);
				bar(36,6,50,7);
				gotoxy(37,6);
				string(s,4,0);
				no=atoi(s);
				findmember(no,0);
				textcolor(BLUE);
				bar(5,3,75,25);
			}
			}

			}
			else if(j==3)
			{
			bar(16,6,26,7);
			gotoxy(18,6);
			textcolor(BLACK);
			cprintf("Update");
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				char s[6];
				int no;
				windowbar(5,3,75,24,1,1);
				windowbar(5,4,75,24,4,7);
				textcolor(BLACK);
				gotoxy(22,6);
				cprintf("Unique no:");
				textcolor(GREEN);
				textbackground(GREEN);
				bar(33,6,47,7);
				gotoxy(34,6);
				string(s,4,0);
				no=atoi(s);
				findmember(no,1);
				textcolor(BLUE);
				bar(5,3,75,25);
			}
			}

			}
		}
		else if(i==3)
		{
			if(j==4)
			j=1;
			if(j==-1)
			j=3;
			if(j==1)
			{
			bar(26,4,36,5);
			textcolor(BLACK);
			gotoxy(28,4);
			cprintf("Issue");
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				windowbar(15,3,65,24,1,1);
				windowbar(15,4,65,24,4,7);
				textcolor(BLUE);
				issuebook();
				textcolor(BLUE);
				bar(5,3,75,25);
			}
			}
			}
			else if(j==2)
			{
			bar(26,5,36,6);
			textcolor(BLACK);
			gotoxy(28,5);
			cprintf("Return");
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				windowbar(15,3,65,24,1,1);
				windowbar(15,4,65,24,4,7);
				textcolor(BLUE);
				returnbook();
				textcolor(BLUE);
				bar(5,3,75,25);
			}
			}
			}
			else if(j==3)
			{
			bar(26,6,36,7);
			textcolor(BLACK);
			gotoxy(28,6);
			cprintf("Record");
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				windowbar(15,3,65,24,1,1);
				windowbar(15,4,65,24,4,7);
				textcolor(BLUE);
				issueRecord();
				textcolor(BLUE);
				bar(5,3,75,25);
			}
			}
			}
		}
		else if (i==4)
		{
			if(!kbhit())
			{
			ch=getch();
			if(ch==13)
			{
				windowbar(10,5,70,24,1,1);
				windowbar(10,5,70,24,4,7);
				gotoxy(36,5);
				textbackground(LIGHTGRAY);
				cprintf("About");
				textbackground(RED);
				textcolor(YELLOW);
				gotoxy(32,7);
				cprintf("<<Version 1.0>>");
				gotoxy(28,9);
				cprintf("Make by : Sourabh gond");
				gotoxy(28,11);
				cprintf("Project : Library Management");
				gotoxy(28,13);
				cprintf("College : SISTec");
				gotoxy(28,15);
				cprintf("Branch  : CSE");
				gotoxy(28,17);
				cprintf("Semester: 3rd sem");
				gotoxy(28,19);
				cprintf("Start   :19/07/2017");
				gotoxy(28,21);
				cprintf("End     :22/07/2017");
			}
			}
		}
		ch=getch();
		switch(ch)
		{
		case 77:
		i++;
		j=0;
		break;
		case 75:
		i--;
		j=0;
		break;
		case 80:
		j++;
		break;
		case 72:
		j--;
		};
		if(ch==27)
		i=-2;
	}
}

void main()
{
	_setcursortype(_NOCURSOR);
	clrscr();
	textbackground(RED);
	clrscr(); //240
	textcolor(CYAN);
	//returnbook();
	windowbar(2,2,80,25,1,7);
	frontpage();
	//bar(1,1,81,2);
	textcolor(WHITE);
	textbackground(BLUE);
	//window(2,2,80,25);    //219,186
	//frontpage();
	gotoxy(30,1);
	textbackground(MAGENTA);
	textcolor(BLACK);
	cprintf("%cLIBRARY MANAGEMENT%c",179,179);
	option();
	getch();
	system("cls");
}
