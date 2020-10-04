#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct			s_2d
{
	char				*hi_2d;
	int					i;
	int					j;
}						t_2d;


typedef struct			s_1d
{
	char				*hi_1d;
	t_2d				*t2d;
}						t_1d;

int						change_str(t_1d *m)
{
	m->t2d->i = 1;
	m->t2d->j = 2;
	return (0);
}

int						initialize(t_1d *one_d)
{
	one_d = malloc(sizeof(t_1d));
	one_d->t2d = malloc(sizeof(t_2d));
	one_d->t2d->i = 1;
	one_d->t2d->j = 7;
	return (0);
}

int main(void)
{
	t_1d		*one_d;

	one_d->hi_1d = strdup("hi_1d is completed\n");
	printf("%s\n", one_d->hi_1d);

	one_d->t2d->hi_2d = strdup("hi_2d is completed\n");
	printf("%s\n", one_d->t2d->hi_2d);

	printf("%d\n", one_d->t2d->j);
	change_str(one_d);

	printf("%d %d\n", one_d->t2d->i, one_d->t2d->j);
	return (0);
}