bool next(string & S)
{
    int op = 0, cl = 0, i;
    for (i = S.size() - 1; i >= 0; --i)
    {
        if (S[i] == '(')
            ++op;
        else
            ++cl;
        if (S[i] == '(' && op < cl)
            break;
    }
    if (i == -1)
        return false;
    S[i] = ')';
    ++i;
    while (op > 0)
    {
        S[i] = '(';
        ++i;
        --op;
    }
    while (i < S.size())
    {
        S[i] = ')';
        ++i;
    }
    return true;
}

bool prev(string & S)
{
    int op = 0, cl = 0, i;
    for (i = S.size() - 1; i >= 0; --i)
    {
        if (S[i] == '(')
            ++op;
        else
            ++cl;
        if (S[i] == '(')
            break;
    }
    --i;
    for (; i >= 0; --i)
    {
        if (S[i] == '(')
            ++op;
        else
            ++cl;
        if (S[i] == ')')
            break;
    }
    if (i < 0)
        return false;
    S[i] = '(';
    --op;
    ++i;
    while (op != cl)
    {
        S[i] = ')';
        --cl;
        ++i;
    }
    while (i < S.size())
    {
        S[i] = '(';
        S[i + 1] = ')';
        i += 2;
    }
    return true;
}

int amount_of_seq(int pairs)
{
    C[0] = 1;
    for (int n = 1; n <= pairs; ++n)
    {
        C[n] = 0;
        for (int k = 0; k < n; ++k)
            C[n] += C[k] * C[n - 1 - k];
    }
    return C[pairs];
}