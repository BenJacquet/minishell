
#include "minishell.h"

char	*ft_strncat(char *dest, char *src, int dstsize)
{
	int		i;
	int		o;

	o = 0;
	i = 0;
	while (dest[i])
		i++;
	while (src[o] && o < dstsize)
	{
		dest[i + o] = src[o];
		o++;
	}
	dest[i + o] = '\0';
	return (dest);
}
