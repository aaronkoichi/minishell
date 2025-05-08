#include "wildcard.h"

int main(void)
{
	char *word = "Hello World";
	char *pattern = "He**ld";
	int num = ft_fnmatch(pattern, word);
	ft_printf("%d\n", num);
}
