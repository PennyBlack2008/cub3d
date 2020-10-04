#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char			*test(char *str)
{
	int			i;

	i = 0;
	while (i < 5)
	{
		str[i] = 32 + i;
		i++;
	}
	return (str);
}

int main(void)
{
	char *str;
	int	i = 0, j = 0;
	str = strdup("Hi i am here");
	
	while (i < 5)
	{
		printf("before str[%d] : %c\n", i, str[i]);
		i++;
	}

	str = test(str);
	i = 0;
	while (i < 8)
	{
		printf("after str[%d] : %c\n", i, str[i]);
		i++;
	}

	return (0);
}

