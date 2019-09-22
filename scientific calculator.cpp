#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include <graphics.h>

#define PI 2*acos(0)

using namespace std;

string to_string(double value) {
    stringstream sstr;
    sstr << value;
    return sstr.str();
}

int getWeight(char ch)
{
   switch (ch)
   {
      case '^': return 3;
      case '/':
      case '*': return 2;
      case '+':
      case '-': return 1;
      default : return 0;
   }
}

double performOperation(double op1, double op2, char op)
{
    double ans;
    switch(op){
    case '+':
        ans = op2 + op1;
        break;
    case '-':
        ans = op2 - op1;
        break;
    case '*':
        ans = op2 * op1;
        break;
    case '/':
        ans = op2 / op1;
        break;
    case '^':
        ans=pow(op2,op1);
        break;
    }
    return ans;
}

double operation(char op[],double num)
{
    double no;

    if(strcmp(op,"sin")==0) no=sin((PI*num)/180);
    else if(strcmp(op,"cos")==0) no=cos((PI*num)/180);
    else if(strcmp(op,"sec")==0) no=1/(cos((PI*num)/180));
    else if(strcmp(op,"cosec")==0) no=1/(sin((PI*num)/180));
    else if(strcmp(op,"tan")==0) no=tan((PI*num)/180);
    else if(strcmp(op,"cot")==0) no=1/(tan((PI*num)/180));
    else if(strcmp(op,"log")==0) no=log10(num);
    else if(strcmp(op,"e")==0) no=exp(num);
    else if(strcmp(op,"ln")==0) no=log(num);

    return no;
}

bool isoperator(char ch)
{
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^') return true;
    return false;
}

int inTOpost(char postfix[],char expression[])
{
    int j=0,l=0,weight,weightOPRTR=0,top=0,len,k=-1,x=0,n;
    double no,num,stack[10000];
    char oprtr,c,stk[100],m[15],op[10];
    string str;
    len=strlen(expression);
    expression[len]=')';
    top++;
    stk[top]='(';
    for(int i=0;i<len+1;i++)
    {
        if(expression[i]=='(') { top++; stk[top]=expression[i]; }
        else if(isoperator(expression[i]))
        {
            weight=getWeight(expression[i]);
            while(1)
            {
                oprtr=stk[top];
                weightOPRTR=getWeight(oprtr);
                if(weightOPRTR<weight) break;
                j++;
                postfix[j]=stk[top];
                top--;
            }
            top++;
            stk[top]=expression[i];
        }
        else if(expression[i]==')')
        {
            while(stk[top]!='(')
            {
                j++;
                postfix[j]=stk[top];
                top--;
            }
            top--;
        }
        else if(isdigit(expression[i])||expression[i]=='.'){
            j++;
            postfix[j]=expression[i];
            if(!isdigit(expression[i+1])&&expression[i+1]!='.')
            {
                j++;
                postfix[j]=' ';
            }
        }
        else
        {
            k=-1;
            while(isalpha(expression[i]))
            {
                k++;
                op[k]=expression[i];
                i++;
            }
            k++;
            op[k]='\0';
            l=-1;
            while(isdigit(expression[i])||expression[i]=='.')
            {
                l++;
                m[l]=expression[i];
                i++;
            }
            i--;
            l++;m[l]='\0';
            num=atof(m);
            no=operation(op,num);
            str=to_string(no);
            for(x=0;x<str.size();x++)
            {
                j++;
                postfix[j]=str[x];
            }
                j++;
                postfix[j]=' ';
        }
   } return j;
}

double calculation(char postfix[],int len)
{
    int j=-1,top=0;
    double num,stack[10000],op1,op2,ans;
    char buffer[15];
    string str;

    for(int i=1;i<=len;i++)
    {
        if(isdigit(postfix[i])||postfix[i]=='.') {
            j++;
            buffer[j] = postfix[i];
        }
        else if(postfix[i]==' ') {
            j++;
            buffer[j]='\0';
            num=atof(buffer);
            top++;
            stack[top]=num;
            j = -1; num=0;
            memset(&buffer[0],0,sizeof(buffer));
            }
        else if(isoperator(postfix[i]))
        {
            op1=stack[top];
            top--;
            op2 = stack[top];
            top--;
            top++;
            ans=performOperation(op1, op2, postfix[i]);
            stack[top]=ans;
        }}
        return stack[top];
}

main()
{
    int len;
    double ans;
    string str;

    char expression[1000],postfix[1000];

    cout<<"Enter :";
        cin>>expression;

    len=inTOpost(postfix,expression);

    ans=calculation(postfix,len);

    cout<<"ANS: "<<ans<<endl;

    return 0;
}
