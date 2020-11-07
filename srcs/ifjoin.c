
#include "../incs/minishell.h"

int		ifjoininit(char *buff, int quote, int i)
{
	i = 2;
	while (buff[i] != quote)
		i++;
//	printf("ifjoin buff avant = [%s] et %d\n", buff  + 2, i );
	return (i);
}

int		ifjoin(t_all *all, char *buff, int *inc, char quote)
{
	int		i;

	i = ifjoininit(buff, quote, i);
	croco(all, buff, i, *inc);
	buff = tokla(all, buff, &i, 0);
	if (all->diff == -666)
	{
		(*inc)--;
		return (i);
	}
	if (*inc > 0 && (buff[0] == ' ' || buff[0] == '<' || buff[0] == '>')
			&& buff[2] != quote)
	{
		all->dir[*inc] = malloc(sizeof(char) * i);
		all->dir[*inc] = ft_strncpy(all->dir[*inc], buff + 2, i - 2);
	}
	else if (*inc > 0 && buff[0] != ' ' && i != 2)
		joinjoin(all, buff, inc, i);
	else
	{
		all->dir[*inc] = malloc(sizeof(char) * i);
		all->dir[*inc] = ft_strncpy(all->dir[*inc], buff + 2, i - 2);
	}
	return (i);
}
