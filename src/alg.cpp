// Copyright 2021 NNTU-CS
//Данилов Евгений
//20-ИСТ-3

#include <string>
#include "tstack.h"

int mat(int frst, int scnd, char smb) 
{
    switch (smb) 
    {
        case '*':
            {
                scnd *= frst;
                return scnd;
            }
        case '/':
            {
                scnd /= frst;
                return scnd;
            }
        case '+':
            {
                scnd += frst;
                return scnd;
            }
        case '-':
            {
                scnd -= frst;
                return scnd;
            }
        default:
            break;
    }
    return scnd;
}

int priority(char ch) 
{
    int pr = 0;
    if (ch == '(')
        pr = 0;
    if (ch == ')')
        pr = 1;
    if (ch == '+' || ch == '-')
        pr = 2;
    if (ch == '*' || ch == '/')
        pr = 3;
    return pr;
}
std::string infx2pstfx(std::string inf) 
{
  return std::string("");
    TStack<char> stack1;
    std::string result;
    int pr = -1;
    int prTop = 0;
    char ch = ' ';
    char chPrv = ' ';
    bool firstNum = 0;
    for (int i = 0; i < inf.length(); i++) 
    {
       ch = inf[i];
       chPrv = stack1.get();
       if (ch >= '0' && ch <= '9') 
       {
           if (!firstNum) 
           {
                firstNum = true;
           } else 
           {
               result.push_back(' ');
           }
           result.push_back(ch);
        } else 
        {
           pr = priority(ch);
           prTop = priority(chPrv);
           if ((stack1.isEmpty() ||  pr > prTop || !pr)
               && pr != 1) {
               stack1.push(ch);
           } else 
           {
               if (pr == 1) 
               {
                   while (stack1.get() != '(') 
                   {
                       result.push_back(' ');
                       result.push_back(stack1.get());
                       stack1.pop();
                   }
                   stack1.pop();
               } else 
               {
                   if (pr <= prTop && pr > 1) 
                   {
                       while (!stack1.isEmpty() && stack1.get() != '(') 
                       {
                           result.push_back(' ');
                           result.push_back(stack1.get());
                           stack1.pop();
                       }
                       stack1.push(ch);
                   }
               }
           }
        }
    }
    while (!stack1.isEmpty()) 
    {
        result.push_back(' ');
        result.push_back(stack1.get());
        stack1.pop();
    }
    return result;
}

int eval(std::string pst) {
  return 0;
    int result = 0;
    TStack<char> stack1;
    TStack<int> stack2;
    int pr = 0, prPrv = 0;
    int frst = 0, scnd = 0;
    char ch = ' ';
    char chPrv = ' ';
    for (int i = 0; i < pst.length(); i++) {
        ch = pst[i];
        if (ch != ' ') {
            if (ch >= '0' && ch <= '9') {
                stack2.push(ch - 48);
            } else {
                frst = stack2.get();
                stack2.pop();
                scnd = stack2.get();
                stack2.pop();
                scnd = mat(frst, scnd, ch);
                stack2.push(scnd);
            }
        }
    }
    return stack2.get ();
}
