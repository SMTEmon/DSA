#include <bits/stdc++.h>

#include "stack.cpp"

using namespace std;

bool isRightPrec(char c)

{

    return c == '^';
}

int prec(char c)

{

    if (c == '+' || c == '-')

        return 1;

    else if (c == '*' || c == '/' || c == '%')

        return 2;

    else if (c == '^')

        return 3;

    return 0;
}

bool isPrec(char c)

{

    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%')

        return true;

    return false;
}

bool isChar(char c)

{

    if ((c >= 'a' && c <= 'z') ||

        (c >= 'A' && c <= 'Z') ||

        (c >= '0' && c <= '9'))

        return true;

    return false;
}

void soln(string inp)

{

    if (inp.size() != 0)

        addst('(');

    inp += ')';

    int size_of_inp = inp.size();

    for (int i = 0; i < size_of_inp; i++)

    {

        char cur = inp[i];
        if (cur == ' ')
            continue;

        if (cur != '(' && cur != ')' && isChar(cur))

            cout << cur;

        else if (cur == '(' || isRightPrec(cur))

            addst(cur);

        else if (isPrec(cur))

        {

            while (!isEmpty() && topst()->data != '(' && prec(cur) <= prec(topst()->data) && !isRightPrec(cur))

            {

                cout << topst()->data;

                popst();
            }

            addst(cur);
        }

        else if (cur == ')')

        {

            while (!isEmpty() && topst()->data != '(')

            {

                cout << topst()->data;

                popst();
            }

            popst();
        }
    }
}

int main()

{
    soln("A-(B/C+(D%E*F)/G)*H");
}