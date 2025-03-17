/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_metachar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:12:04 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/16 17:12:30 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_metachar(int type)
{
	if (type == PIPE || type == REDIRECT_IN || type == REDIRECT_OUT)
		return (1);
	if (type == APPEND || type == HERE_DOC)
		return (1);
	return (0);
}
