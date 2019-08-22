#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void chopN(char *str, size_t n)
{
    assert(n != 0 && str != 0);
    size_t len = strlen(str);
    if (n > len)
        return;  // Or: n = len;
    memmove(str, str+n, len - n + 1);
}

int main(){

	char sal[4];
    char *nou;

    strcpy(sal,"toni");
    printf("%s\n",sal);

    chopN(sal,2);
    printf("%s\n",sal);

	return 0;
}