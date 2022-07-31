#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max 256//최대크기 
typedef struct//구조체형 스택 타입 
{
    char data[max];
    int top;
}stackType;
 
int check(char* exp);//괄호체크 
void init(stackType* s);//초기화 
void push(stackType* s, int x);//넣기 
int pop(stackType* s);//빼기 
int is_full(stackType* s);//꽉찼는지 
int is_empty(stackType* s);//비었는지 
int main()
{
    stackType s;
    char exp[20];
    fgets(exp, sizeof(exp), stdin);
    if (check(exp) == 1)
        puts("true!");
    else
        puts("false!");
    return 0;
}
void init(stackType* s)
{
    s->top = -1;//-1로 초기화 
}
int is_full(stackType* s)
{
    return s->top == max - 1;//꽉 찼을 때 
}
int is_empty(stackType* s)
{
    return s->top == -1;//비었을 때 
}
void push(stackType* s, int x)
{
    if (is_full(s))
    {
        fprintf(stderr, "원소가 다 찼습니다.\n");//오류출력 
        return;
    }
    s->data[++(s->top)] = x;//넣기 
}
int pop(stackType* s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "원소가 없습니다\n");//오류출력 
        exit(1);
    }
    return s->data[(s->top)--];//빼내기 
}
int check(char* exp)
{
    stackType s;
    char ch, open_ch;//ch는 문자열 저장, open_ch는 열린괄호 갯수 저장 
    int n = strlen(exp);//배열의 크기만큼 
    int i;
    init(&s);//스택초기화 
    for (i = 0; i < n; i++)//배열의 크기만큼 반복 
    {
        ch = exp[i];
        switch (ch)
        {
        case '(':case '[':case'{':
            push(&s, ch);
            break;
        case ')':case']':case'}':
            if (is_empty(&s))return 0;
            else
            {
                open_ch = pop(&s);
                if ((open_ch == '(' && ch != ')') || (open_ch == '{' && ch != '}') ||
                    (open_ch == '[' && ch != ']'))//짝이 안맞을때 
                    return 0;
                
            }
            break;
        }
    }
    //괄호검사 다했는데 스택에 원소가 남아있다면? => 잘못된 수식
    if (!is_empty(&s))return 0;
    return 1;//성공하면 1리턴, 실패시 0리턴 
}
