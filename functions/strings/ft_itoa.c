
#include "../../inc/minishell.h"

int	numlen(int num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nbr)
{
	char	*str;
	int		len;
	int		is_negative;

	len = numlen(nbr);
	is_negative = (nbr < 0);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nbr == 0)
		str[0] = '0';
	if (is_negative)
		nbr = -nbr;
	while (nbr != 0)
	{
		str[--len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	if (is_negative)
		str[0] = '-';
	return (str);
}
