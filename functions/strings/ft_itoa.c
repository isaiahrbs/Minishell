/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< Updated upstream
/*   Created: 2025/02/27 12:40:43 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/07 14:30:35 by irobinso         ###   ########.fr       */
=======
/*   Created: 2025/04/02 01:10:56 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/07 12:50:02 by dimatayi         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	change_n(int *n, int *sign, unsigned int *nb)
{
	if (*n < 0)
	{
		*sign = 1;
		*nb = -(*n);
	}
	else
	{
		*nb = *n;
		*sign = 0;
	}
}

static int	ft_digits(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	char			*str;
	int				digits;
	int				sign;
	int				i;

	change_n(&n, &sign, &nb);
	digits = ft_digits(nb);
	str = malloc(sizeof(char) * (digits + sign + 1));
	if (!str)
		return (NULL);
	if (sign)
	{
		str[0] = '-';
		i = digits;
	}
	else
		i = digits - 1;
	while (i >= sign)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	str[digits + sign] = '\0';
	return (str);
}
