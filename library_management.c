#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define IN 1
#define OUT 0

void addBooks();
void searchBooks();
void display();
void stock();
void issueBooks();
void returnBooks();
void addMember();
void Exit();

struct Books
{
	long int bid;
	char bname[30];
	char author[30];
	int status;
}b;
struct Member
{
   int mid;
   char mname[30] ;
   char department[30];
   int availibcards;
}m;

FILE *librecord;
FILE *memrecord;
FILE *fp1;
FILE *fp2;
FILE *temp1;
FILE *temp2;

char info[500];

int main()
{
	int choice=0;
    do
	{
		printf("\n\t\t\xDB\xDB\xDB\xDB\xDBMENU\xDB\xDB\xDB\xDB\xDB\n 1. Add A New Book\n 2. Search a book \n 3. Display Complete Information\n 4. Total Count of Books (Issued & On Stock)\n 5. Issue a Book \n 6. Return a Book \n 7. Add Members\n 8. Exit \n\n\t Enter your choice:  ");
		scanf("%d",&choice);
                             
        switch(choice)
		{
			case 1: 
			addBooks();
			break;
			case 2:
			searchBooks();
			break;
			case 3:
			display();
			break;
			case 4:
			stock();
			break;
			case 5:
			issueBooks();
			break;
			case 6:
			returnBooks();
			break;
			case 7:
			addMember();
			break;
			case 8:
			Exit();
	        default: 
	        printf("Invalid Input");	
			break;				 
		}                     
	}while(choice!=8);
	return 0;
	
}

void addBooks()
{
	b.status=IN;        
    librecord = fopen("librecord.txt","a+");
    printf("Enter The ID Of The Book : \n");
    scanf("%d",&b.bid);
    printf("Enter The Name of The Book :\n");
    scanf("%s",b.bname);
    printf("Enter The Name of Author :\n");
    scanf("%s",b.author);
    fprintf(librecord,"\n%d\t%s\t%s\t%d\t",b.bid,b.bname,b.author,b.status);
    fclose(librecord);
    printf("A New Book has been Added Successfully!! \n");

}

void display()
{
    librecord = fopen("librecord.txt","r");
    printf("BookID\tBookName\tAuthor\tStatus\t\n",info);
    do
    {
        fgets(info,500,librecord);
        printf("%s\n",info);
    }while(!feof(librecord));
    fclose(librecord);
    memrecord = fopen("memberRecord.txt","r");
    printf("MemberID\tMemberName\tDepartment\t\n");
 
    do
    {
        fgets(info,500,memrecord);
        printf("%s\n",info);
    }while(!feof(memrecord));
    fclose(memrecord);
}

void searchBooks()
{
    char Target[25],stats[3];
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
        printf("The File is Empty.\n\n");
    else
    {
        printf("\nEnter The Name Of Book : ");
            scanf("%s",Target);
        while(!feof(librecord)&& Found==0)
        {
        fscanf(librecord,"%d %s %s %d ", &b.bid,b.bname,b.author,&b.status);
            if(strcmp(Target,b.bname)==0)
                Found=1;
                    
		}
        if(Found)
        {
            if(b.status==IN)
                strcpy(stats,"IN");
            else
                strcpy(stats,"OUT");
            
            printf("\nThe Unique ID of The Book:  %ld\nThe Name of Book is:  %s\nThe Author is:  %s\nThe Book Status:%s\n\n",b.bid,b.bname,b.author,stats);
            }
        else if(!Found)
            printf("There is no such Entry.\n");
        fclose(librecord);
    }

}
void stock()
{
    int issuecount=0,stockcount=0;    
    int Found=0;
    if((librecord=fopen("librecord.txt","r"))==NULL)
         printf(" The File is Empty! \n");
    else
    {
        while(!feof(librecord))
        {
            fscanf(librecord,"%d %s %s %d",&b.bid,b.bname,b.author,&b.status);
            if(b.status==1)
            {
                stockcount++;
            }
            else if(b.status==0)
            {
                issuecount++;
            }
            
        }
        printf("\nCount of issued Books:%d\nCount of Books in Stock:%d\n",issuecount,stockcount);
        fclose(librecord);
    
    }

}
void issueBooks()
{
    int mid,Found1=0,Found2=0;char issuebookname[20];
        printf("\nEnter The userid of the Member : \n");
        scanf("%d",&mid);
    if((memrecord=fopen("memberRecord.txt","r"))==NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(memrecord)&& Found1==0)
        {
            fscanf(memrecord,"%d %s %s %d ",&m.mid,m.mname,m.department,&m.availibcards);
            if(mid==m.mid)
            {
                Found1=1;
            }
        }
        if(Found1)
        {
            if(m.availibcards<1)
            {
                printf(" ! Library card not available...\n");
            }
            else
            {    printf("\nEnter The Name of book :");
                scanf("%s",issuebookname);
    
                if((librecord=fopen("librecord.txt","r"))==NULL)
                    printf("The file is empty...\n\n");
                else
                {
                    while(!feof(librecord)&& Found2==0)
                    {
                        fscanf(librecord,"%d %s %s %d %d", &b.bid,b.bname,b.author,&b.status);
                        if(strcmp(issuebookname,b.bname)==0)
                            Found2=1;
                        
                    }
                    if(Found2)
                    {
                        if(b.status==0)
                        {
                            printf("Book already issued...\n");
                        }
                        else
                        {    
                            
                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("memberRecord.txt","r"))==NULL)
                                printf("The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d ",&m.mid,m.mname,m.department,&m.availibcards);
                            
                                    
                                    if(mid==m.mid)
                                    {
                                        m.availibcards--;
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t",m.mid,m.mname,m.department,m.availibcards);
                                    }
                                    else{
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t",m.mid,m.mname,m.department,m.availibcards);
										}
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);
                            

                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librecord.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &b.bid,b.bname,b.author,&b.status);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(issuebookname,b.bname)==0)
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d    \t",b.bid,b.bname,b.author,b.status);
                                        break;
                                    }
                                    else
                                    {
                                        //fprintf(fp1,"\n%d\t%s\t%s\t%d\t",b.bid,b.bname,b.author,0);
                                    }
                                    
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);
                            fclose(memrecord);
                            remove("librecord.txt");
                            rename("fp1.txt","librecord.txt");
                            remove("memberRecord.txt");
                            rename("fp2.txt","memberRecord.txt");
                            printf(" Book Successfully issued...\n");
                        }                
                    }
                    else if(!Found2)
                        printf("There is no such Book...\n");
                
                }
            }
        }
        else
            printf("Invalid User id...\n");
        

    }
    
}

void returnBooks()
{
int mid,Found1=0,Found2=0;
char retbookname[30];
   // temp1=librecord;
   // temp2=memrecord;
    printf("\nEnter The user ID of the Member :\n");
        scanf("%d",&mid);
    if((memrecord=fopen("memberRecord.txt","r"))==NULL)
        printf(" ! The file is empty...\n\n");
    else
    {
        while(!feof(memrecord)&& Found1==0)
        {
            fscanf(memrecord,"%d %s %s %d ",&m.mid,m.mname,m.department,&m.availibcards);
            if(mid==m.mid)
            {
                Found1=1;
            }
        }
        if(Found1==1)
        
            {
			    printf("\nEnter The Name of book :");
                scanf("%s",retbookname);
                if((librecord=fopen("librecord.txt","r"))==NULL)
                    printf(" ! The file is empty\n\n");
                else
                {
                    while(!feof(librecord)&& Found2==0)
                    {
                        fscanf(librecord,"%d %s %s %d", &b.bid,b.bname,b.author,&b.status);
                        if(strcmp(retbookname,b.bname)==0)
                        Found2=1;
                         
                    }
                    if(Found2==1)
                    {
                        if(b.status==1)
                        {
                            printf(" ! Book successfully returned!! \n");
                        }
                        else
                        {    
                            
                            fp2=fopen("fp2.txt","w");
                            if((temp2=fopen("memberRecord.txt","w"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            { 
                                while(!feof(temp2))
                                {
                                    fscanf(temp2,"%d %s %s %d ",&m.mid,m.mname,m.department,&m.availibcards);
                            
                                    
                                    if(mid==m.mid)
                                    {
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t",m.mid,m.mname,m.department,m.availibcards);
                                    }
                                    else
                                    {
                                        fprintf(fp2,"\n %d\t%s\t%s\t%d\t",m.mid,m.mname,m.department,m.availibcards);
                                    }
                                    if(feof(temp2))
                                        break;
                                }
                            }
                            fclose(temp2);
                            fclose(fp2);
                            

                            fp1=fopen("fp1.txt","w");
                            if((temp1=fopen("librecord.txt","r"))==NULL)
                                printf(" ! The file is empty...\n\n");
                            else
                            {
                                while(!feof(temp1))
                                {
                                      fscanf(temp1,"%d %s %s %d %d", &b.bid,b.bname,b.author,&b.status);
                                    if(feof(temp1))
                                        break;
                                    if(strcmp(retbookname,b.bname)==0)
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d    \t",b.bid,b.bname,b.status,b.status);
                                    }
                                    else
                                    {
                                        fprintf(fp1,"\n%d\t%s\t%s\t%d\t%d\t",b.bid,b.bname,b.author,1);
                                    }
                                    
                                }
                            }
                            fclose(temp1);
                            fclose(fp1);
                            fclose(librecord);
                            fclose(memrecord);
                            printf("('') Book Successfully Returned...\n");
                            remove("librecord.txt");
                            rename("fp1.txt","librecord.txt");
                            remove("memberRecord.txt");
                            rename("fp2.txt","memberRecord.txt");

                        }                
                    }
                    else if(!Found2==1)
                        printf("! There is no such Book...\n");
                
                }
            }
        
        else if(!Found1==1)
            printf("! Invalid User id...\n");
       }

    }
    


void addMember()
{
    memrecord = fopen("memberRecord.txt","a+");
    printf("Enter The User ID Of The Member:\n");
        scanf("%d",&m.mid);
    printf("Enter The Name of the Member:\n");
        scanf("%s",m.mname);
    printf("Enter The Department: \n");
        scanf("%s",m.department);
        m.availibcards=5;
    fprintf(memrecord,"\n%d\t%s\t%s\t%d\t",m.mid,m.mname,m.department,m.availibcards);
    fclose(memrecord);
    printf("\nAdded  A New member Successfully!! \n");
}
 
void Exit()
{
	exit(0);
	}    
    
    

	
	
	

