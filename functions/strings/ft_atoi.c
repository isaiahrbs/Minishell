/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:13:42 by irobinso          #+#    #+#             */
/*   Updated: 2024/10/05 18:55:00 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

/*int	main(void)
{
	const char	*str1 = "-1234";
	const char	*str2 = "0";
	const char	*str3 = "1234";
	const char	*str4 = "+   not a number 1234";

	printf("str1 output: %d\n", ft_atoi(str1));
	printf("str2 output: %d\n", ft_atoi(str2));
	printf("str3 output: %d\n", ft_atoi(str3));
	printf("str4 output: %d\n", ft_atoi(str4));
	return (0);
}*/
