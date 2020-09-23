
#include "minishell.h"

char	*ft_strncat(char *dest, char *src, int dstsize)
{
	size_t		i;
	size_t		o;

	o = 0;
	i = 0;
	while (dest[i])
		i++;
	while (src[o] && o < dstsize)
	{
		dest[i + o] = src[o];
		o++;
	}
	if (o != dstsize)
		dest[i + o] = '\0';
	return (dest);
}
