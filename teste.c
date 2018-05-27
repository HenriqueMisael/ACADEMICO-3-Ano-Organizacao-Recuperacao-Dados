#include<stdio.h>
#include<string.h>

int main(int argc , char *argv[])
{
    char a[2] = { 'a', '\0' };
    char b[2] = { 'b', '\0' };

    printf("%s%s\n", a, b);
    strcat(a, b);
    printf("%s %s\n", a, b);

    return 0;
}
