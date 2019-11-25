int a = 123, b, c;
float m = 12.12, n;
char x = 'c';
int len = sizeof("Hello");

int fibo(int a) /* Comment */
{
    if (a == 1 || a == 2)  // inline comment
        return 1;
    return fibo(a - 1) + fibo(a - 2);
}

int main()
{
    int m, n, i;
    m = read();
    i = 1;
    while (i <= m)
    {
        n = fibo(i);
        write(n);
        i = i + 1;
    }
    return 1;
}
