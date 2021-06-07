#include "libft.h"

int	ft_iswhitespace(char const c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		   return (1);
	return (0);
}
