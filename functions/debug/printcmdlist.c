#include "../../inc/minishell.h"

static const char	*get_command_type_str(t_type type)
{
    if (type == WORD)
        return ("WORD");
    else if (type == SIMPLE_QUOTE)
        return ("SIMPLE_QUOTE");
    else if (type == DOUBLE_QUOTE)
        return ("DOUBLE_QUOTE");
    else if (type == PIPE)
        return ("PIPE");
    else if (type == ARGUMENT)
        return ("ARGUMENT");
    else if (type == REDIRECT_IN)
        return ("REDIRECT_IN");
    else if (type == REDIRECT_OUT)
        return ("REDIRECT_OUT");
    else if (type == APPEND)
        return ("APPEND");
    else if (type == HERE_DOC)
        return ("HERE_DOC");
	else
		return ("Kendrick Lamar");
}

void	print_command_list(t_command *head)
{
    while (head)
    {
        printf("-----------------\n");
        printf("|");
        // Assuming BLUE and RESET are defined in your minishell.h
        printf(BLUE " %s, (%s) " RESET, head->value, get_command_type_str(head->type));
        printf("|");
        if (head->next)
            printf(" ->");
        printf("\n-----------------\n");
        head = head->next;
    }
}
