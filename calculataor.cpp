#include<stdio.h>
#include<stdlib.h>
#include<string.h>

class calculation{

struct node{  //stack implementation (FIFO)
    char item; 
    node* next; 

};
    node* top;    // points to the last added node
    node* buttom; // points to the first added node
    int length;   // follow the length of the stack
    char postfixArray[20]; // store postfix
    int j;        // incremented each time we add an element to the postfix array

public:


calculation ()
{
    top=NULL;
    buttom=NULL;
    length=0;
    j=0;
}



void expression(){
    // enter the expression & expression evaluation
    char exp[20];
    printf("enter the expression : ");
    gets(exp);
    if(expEvaluation(exp))
    {
        postfix(exp);
    }
    else
    {
        printf("the expression isn't valid");
    }
}



private:

int expEvaluation(char* exp){
    for(int i=0 ; i<strlen(exp) ; i++)
    {
        /*
        if two successive characters are of the same type (digits or operation)
            -> the expression is wrong
        */
        if(((*(exp+i)>=48)  &&  *((exp)+i+1)>=48)  || ((*(exp+i)<=48)  &&  *((exp)+i+1)<=48))
        {
            return 0;
        }
    }
    return 1;
}

//functions used to convert expression to postfix
void postfix(char* exp)
{
    for(int i=0; i < strlen(exp) ; i++) // loop on the expression was entered
    {
        /* 
        if the ASCII of the element is greater than 48=(number 0) it is added
         to the postfix array , otherwise we have to call
          the operation function
        */ 
        if(*(exp+i)>=48) 
        {
            postfixArray[j]= *(exp+i); 
            j++;
        }
        else
        {
            operation(*(exp+i));
        }
    }
    //this while loop is used to make sure the stack is empty
    while(length!=0)
    {
        postfixArray[j]= top->item;
        j++;
        pop();
    }
    // then the final part is calculation of the postfix
    expCalculation(strlen(exp));
}




void operation (char value)
{
    if(length == 0)
    /* 
     if the stack is empty (length=0), we have to use the push function 
     to insert the character into the stack
    */
    {
        push(value);
            
    }
    /* 
    if (length != 0)-> stack isn't empty so we have to compare the operation that we came  
    with(value) with the operation in the top of the stack.

    In order to compare it we need to rate each operation with its importance for example:
    {(+ , - )-> 1 | (* , /)->2 } so (* , /) are more valuable than (+ , -).
    */
    else
    {
        /*
        if the operation in (value) is less or equal to the operation in the top of the stack:
           we have to push the operation in the top of the stack in the postfix array
           then replace the top with the new operation
        */


        if((value == '+') || (value == '-') )
        {
            postfixArray[j] = top->item;
            j++;
            pop();
            push(value);
        }
        else
        {
        /*
        if the operation in (value) is equal to the operation in the top of the stack:
            We do the same thing we did in the first condition above
        */
            if((value == '*' &&  top->item == '/') || (value == '/' &&  top->item == '*') )
            {
                postfixArray[j] = top->item;
                j++;
                pop();
                push(value);
            } 
        /*
        otherwise: operation in (value) is strictly greater than 
        the operation in the top of the stack:
           - we have to push it to the stack        
        */
            else 
            {
                push(value);
            }
        }

    }
}



//functions to calculate the expression
void expCalculation(int explen){
    // explen -> is the length of the expression

    /*
    the concept of this function is:
            -loop in postfix array
            -if we have a number, we have to push it onto the stack
            -otherwise if it is an operation you must call the last two numbers
                in the stack and calculate them
                then push the value onto the stack
    example: the expression is (1+2)
              the postfix is (1 2 +)
            - you must dial the last two digits 1 and 2
                and calculate them
            - then push the sum 3 to the stack
    */

    for(int i=0 ; i<explen ; i++)
    {
        if(postfixArray[i]>=48)
        {
            push(postfixArray[i]);
        }
        else
        {
            calc(postfixArray[i]);
        }
    }
    printf("%i ",(top->item)-48);//print the result


}

/*
    this function allows you to dial the last two digits
      and calculate the result then push it onto the stack
*/
void calc(int opr){
    int A=top->item;
    pop();
    int B=top->item;
    pop();
    switch (opr)
    {
    case '+':
        push((A-48)+(B-48)+48);
        break;
    
    case '-':
        if(A<=B)
        {
        push((B-48)-(A-48)+48);
        }
        else
        {
            printf("\nerror negatif value\n");
        }
        break;
    
    case '*':
        push((A-48)*(B-48)+48);
        break;
    
    case '/':
        if(A != 48)
        {
        push((B-48)/(A-48)+48);
        }
        else
        {
            printf("im here");
            printf("\nerror null value\n");
        }
        break; 
    }
}





//stack (FIFO) methods push (to insert a value) and pop (to remove the top value)
void push(char value){
    node* newnode = new node;
    newnode->item=value;
    if(length==0)
    {
        top=newnode;
        buttom=newnode;
        newnode->next=NULL;
    }
    else
    {
        top->next=newnode;
        top=newnode;
        newnode->next=NULL;
    }
    length++;
}

void pop(){
    if(length==0)
    {
        printf("\nstack is empty\n");
    }
    else if(length==1)
    {
        buttom=NULL;
        top=NULL;
        length--;
    }
    else
    {
        node* past=buttom;
        node* curr=buttom->next;
        while(curr != top)
        {
            curr=curr->next;
            past=past->next;
        }
        top=past;
        top->next=NULL;
        free(curr);
        length--;
    }
}

};

int main(){  
    calculation  test;
    test.expression();
}