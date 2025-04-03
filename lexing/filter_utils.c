/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:36:34 by irobinso          #+#    #+#             */
/*   Updated: 2025/04/03 12:40:57 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	process_quote(const char *str, int *i, char quote)
{
	while (str[*i])
	{
		if (str[*i] == quote)
		{
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

//* check si c'est tout est quotes genre, "hello"
int	is_fully_quoted(const char *str, int *quote_type)
{
	int		i;
	int		first_type;
	char	quote;//* for process quote function

	i = 0;
	first_type = 0;
	while (str[i])//*     [H][E][L][L][O]["]["]
	{
		if (str[i] == '"' || str[i] == '\'')
			quote = str[i];//* quote devien la quote quil voit
		//printf("%c", quote);//! c'est pour DEBUG
		i++;//*j'avance
		if (!check_quote_type(quote, &first_type))//* first type devien la valeur 1 = simple, 2 = double
			return (0);
		if (!process_quote(str, &i, quote))//* go to the end
			return (0);
		if (str[i] && str[i] != '"' && str[i] != '\'')//* check if quote
			return (0);
	}
	*quote_type = first_type;//* set quote type
	return (1);
}

/* static void	remove_outer_quotes(char *str)
{
	char	*read;
	char	*write;
	char	current_quote;

	read = str;
	write = str;
	current_quote = 0;
	while (*read)
	{
		if (!current_quote && (*read == '"' || *read == '\''))
			current_quote = *read++;
		else if (current_quote && *read == current_quote)
		{
			current_quote = 0;
			read++;
		}
		else
			*write++ = *read++;
	}
	*write = '\0';
} */

static void	remove_all_quotes(char *str)
{
	char	*read;
	char	*write;

	read = str;
	write = str;
	while (*read)
	{
		if (*read != '"' && *read != '\'')
			*write++ = *read;
		read++;
	}
	*write = '\0';
}

void	remove_useless_quotes(char *str, int *quote_type)
{
	int	detected_quote_type;

	detected_quote_type = 0;
	if (is_fully_quoted(str, &detected_quote_type))
	{
		*quote_type = detected_quote_type;
		if (str[1] == '\0')
			*str = '\0';
		else
			return;
	}
	else
	{
		*quote_type = 0;
		remove_all_quotes(str);
	}
}
