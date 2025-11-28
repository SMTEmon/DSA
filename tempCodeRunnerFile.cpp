if (inp.size() != 0)
        addst('(');

    inp += ')';

    int size_of_inp = inp.size();

    for (int i = 0; i < size_of_inp; i++)
    {
        char cur = inp[i];

        if (cur != '(' && cur != ')' && isChar(cur))
            cout << cur;

        else if (cur == '(' || !isPrec(cur) || isRightPrec(cur))
            addst(cur);

        else if (isPrec(cur))
        {
            while (prec(cur) <= prec(topst()->data) && !isRightPrec(cur))
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