#include "minishell.h"

int	ft_isin(const char *haystack, const char *needle)
{
	int	i;
	int	j;

	if (!*needle)
		return (0);
	i = ft_strlen(haystack) - 1;
	j = ft_strlen(needle) - 1;
	while (haystack[i] == needle[j] && j >= 0)
	{
		i--;
		j--;
	}
	if (j == -1)
		return (1);
	return (0);
}
