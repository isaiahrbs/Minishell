/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irobinso <irobinso@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:02:17 by irobinso          #+#    #+#             */
/*   Updated: 2025/03/16 16:56:22 by irobinso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

//* function en dessous c chatgpt, comment tu veux que je trouve ca
void	init_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;  // disables printing control characters (^C, etc.)
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	fprintf(stdout, "\n");//* prints a new line when ctrl + c is pressed

	rl_on_new_line(); //* tells readline that we are on a newline
	rl_replace_line("", 0);//* Clears the current input buffer (removes the user's input)
	rl_redisplay();//* Redisplay the prompt
}

void	init_signal_handlers(void)
{
	struct sigaction	sa;//* setup the struct that will handle signals

	//* setup the ctrl + c. | SIGINT = ctrl + c
	sa.sa_handler = handle_sigint;//* set the function handle_sigint to handle when ctrl + c
	sigemptyset(&sa.sa_mask);//* i set mask to empty, meaning i dont want to block other signals while handling one

	sa.sa_flags = SA_RESTART;//* to make readline restart instead of making it crash
	sigaction(SIGINT, &sa, NULL);//* registers handle_sigint to handle SIGINT signals

	signal(SIGQUIT, SIG_IGN);//* ignores sigquit (CTRL + \)
}

