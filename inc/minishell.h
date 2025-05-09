/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatayi <dimatayi@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:40:43 by dimatayi          #+#    #+#             */
/*   Updated: 2025/05/06 16:03:50 by dimatayi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WHITE   "\033[97m"
# define BLUE    "\033[94m"
# define RED     "\033[91m"
# define GREEN   "\033[92m"
# define PINK    "\033[95m"
# define RESET   "\033[0m"

# define TOKEN_NO_QUOTE 0
# define TOKEN_SQUOTE 1
# define TOKEN_DQUOTE 2

typedef enum e_type
{
	MALLOC_ERROR,
	WORD,
	AND,
	OR,
	BACKGROUND,
	CMD,
	VARIABLE,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
	WHITESPACES,
	PIPE,
	FILENAME,
	ASSIGNMENT,
	SUBSTITUTION,
	EXPANSION,
	ARGUMENT,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HERE_DOC,
	INVALID,
	EMPTY,
	INCOMPLETE_STRING,
	NO_TYPE,
}	t_type;

typedef struct s_token
{
	char			*value;
	char			*name;
	char			*content;
	t_type			type;
	int				quote_type;
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			*value;
	t_type			type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_data
{
	t_token		*token;
	t_token		*temporary_var;
	t_token		*env_list;
	t_token		*export_list;
	t_cmd		*commands;
	char		*input;
	char		**envp;
	int			fd[2];
	int			activation_key;
	t_type		error;
	int			created_new_env;
	int			exit_code;
	bool		exit_request;
	pid_t		*children_pid;
}	t_data;

//*----debugging----*//

void	print_list(char **list);
void	print_chained_list(t_token *head);
void	print_variable_list(t_token *head);
void	print_command_list(t_cmd *head);

//*----functions----*//

void	ft_lstadd_back(t_token **head, t_token *new);
t_token	*create_token(char *value);
int		ft_isspace(char c);
char	**metachar_split(char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		is_equal(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
void	free_list(char **list);
void	free_token_list(t_token **head);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
char	*is_var(char *value, int *index);
int		is_assignment(char *s);
int		is_valid_name(char *s);
int		is_expansion(char *s);
int		is_substitution(char *s);
char	*ft_strndup(char *s1, size_t n);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
char	*ft_strchr(char *s, int c);
void	init_type(t_token *token);
int		assign_var(t_data *data);
int		expand(t_token *token, t_token *var, t_data *data);
void	*ft_calloc(size_t elem, size_t size);
char	*ft_strncat(char *dst, const char *src, size_t n);
int		ft_len(char *s, char c);
int		is_single_quote(char *s, int dollar_index);
int		check_assignment(const char *s);
int		is_special_char(char c);
int		get_operator_len(const char *s);
void	free_token_array(char **tokens, int count);
int		process_quotes(const char *s, int *i, char quote);
int		env_to_token_list(t_data *data);
t_token	*form_token_list(char **token_list);
t_token	*create_var(char *name, char *content);
char	*ft_content(char *s);
char	*ft_name(char *s);
int		ft_assign(char *s, t_token **var);
char	**real_split(const char *s, char c);
int		executing(t_data *data);
int		ft_exec(char *executable, char **cmd, t_data *data);
int		ft_fork(pid_t *pid, int *prev_pipe_read, int *fd);
int		ft_pipe(t_cmd *tmp, int *fd);
void	edit_pipe_fd(int infile, int outfile, int *prev_pipe_read, int *fd);
int		is_cmd(t_cmd *tmp, char **executable, char ***cmd);
int		is_redirection(t_cmd *tmp, char **executable, char ***cmd);
int		redirout_append(t_cmd *tmp, int *outfil, char **exec, char ***cmd);
int		redir_in(t_cmd *tmp, int *infile, char **executable, char ***cmd);
void	free_double_ptr(char **args);
void	ft_free(char **executable, char ***cmd);
int		invalid_var(t_token *token);
void	free_token(t_token **temp);
int		unset_var(t_data *data);
char	*ft_itoa(int n);
void	ft_echo(char **executable, char ***cmd, t_data *data);
void	ft_env(t_data *data, char **executable, char ***cmd);
int		ft_exit_code(t_data *data, t_token *token);
int		scan_var_list(t_token *var, char **value, char *v_strt, t_data *data);
int		clean_var(int i, int j, t_token *tmp);
char	*search_replace(t_token *tmp, char *old, char *var_start);
char	*search_exit_code(char *old, char *var_start, t_data *data);
int		here_doc(t_cmd **tmp, int *infile, t_data *data);
void	ft_free(char **executable, char ***cmd);
void	init_var(char ***cmd, char **executable, int *infile, int *outfile);
void	cmd_add_arg(t_cmd *cmd, char *arg);
void	cmd_list_add_back(t_cmd **head, t_cmd *new);
t_cmd	*cmd_new(char *val, int type);
void	update_token_types(t_data *data);
void	free_command_list(t_data *data);
void	*ft_memset(void *s, int c, size_t n);
int		increment_shlvl(t_token *env_list);
int		ft_atoi(const char *str);
int		env_list_into_char_table(t_data *data);
int		free_dbl_ptr_and_tkn_list(t_data *data);
int		handle_quotes(const char *s, int *i);
int		handle_word(const char *s, int is_assign);
int		get_token_length(const char *s);

//*----minishell----*//

char	*get_input(t_data *data);
t_token	*tokenize(t_data *data);
void	init_signal_handlers(void);
void	filter(t_token *head);
void	remove_useless_quotes(char *str, int *quote_type);
int		check_quote_type(char *str);
void	init_terminal(void);
void	check_if_valid(t_data *data);
int		is_metachar_type(int type);
int		is_metachar_value(char *s);
void	command_list(t_data *data);
void	ft_export(t_data *data, char **executable, char ***cmd);
void	handle_heredoc(char *delimiter, int *infile, t_data *data);
void	set_var(char **envp, t_data *data);
void	handle_cd_command(t_data *data);
void	handle_sigint(int sig);
void	parent_signals_restore(void);
void	parent_signals_ignore(void);
void	handle_child_status(int status, t_data *data);
void	child_signals(void);
void	handle_sigquit_child(int sig);
void	filter(t_token *token);
void	exit_handling(t_data *data);
void	exit_with_code(t_data *data);
void	grab_exit_code(t_data *data, int status);
void	free_end_process(t_data *data);
void	free_end_loop(t_data *data);
void	change_env_list(t_data *data, char *replace_str, char *oldpwd);
int		handle_word(const char *s, int is_assign);
int		get_token_length(const char *s);

#endif
