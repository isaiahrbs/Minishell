/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:13:22 by dimatayi          #+#    #+#             */
/*   Updated: 2025/04/11 00:33:15 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	*ft_memsets(void *s, int c, size_t n)
{
	while (n--)
		((char *)s)[n] = c;
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memsets(s, 0, n);
}

void	*ft_calloc(size_t elem, size_t size)
{
	void	*p;

	p = malloc(elem * size);
	if (!p)
		return (NULL);
	ft_bzero(p, elem * size);
	return (p);
}
