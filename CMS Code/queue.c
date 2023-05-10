#include<stdio.h>
#include<conio.h>
#define max 3
void ins();
void del();
void dis();
int q[10], f=-1, r=-1;
void main()
{ 
    int ch;
    char c;
    clrscr();
    do
    { 
        printf("1.insert\n2.delete\n3.display\n");
        printf("enter choice\n");
        scanf("%d",&ch);
        switch(ch);
        {
            case1:ins();
                   break;
            case2:del();
                   break;
            cas3:dis();
                   break;
            default:printf("wrong choice\n");
            break;
        }
        printf("do you want to conitnue\n");
        c=getch();
    }
    while(c=='y');
    getch();
}
void ins()
{
    if(r=max-1)
    printf("queue overflow");
    else
    {
        if(f==-1)
        f=0;
        r++;
        printf("enter elements\n");
        scanf("%d",&q[r]);
    }
}
void del()
{
    if(f==-1 || f>r)
    printf("queue underflow\n");
    else
    printf("deleted element is %d", q[f]);
}
void dis()
{
    int i;
    if(f==-1 || f>r)
    printf("queue underflow\n");
    else
    {
        for(i=f;i<=r;i++)
        printf("%d",q[i]);
    }
}