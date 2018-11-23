while (l < r)
{
    if (l % s || l + s - 1 >= r)
    {
        ans += a[l];
        l++;
    }
    else
    {
        ans += s_dec[l / s];
        l += s;
    }
}