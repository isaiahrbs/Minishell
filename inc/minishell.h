#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
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

/* typedef enum s_f
{
	WORD,
	BLANK,
	COMMAND,
}	t_f; */

typedef enum e_type
{
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
	int				quote_type;//* 0 = none, 1 = single😔, 2 = not single😎
	int				index;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_command
{
	char				*value;
	t_type				type;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_data
{
	t_token		*token;
	t_token		*temporary_var;
	t_token		*env_list;
	t_command	*commands;
	char		*input;
	char		**envp;
	int			activation_key;
}	t_data;

/* typedef struct s_variable
{
	char				*name;
	char				*value;
	struct s_variable	*prev;
	struct s_variable	*next;
}	t_variable; */

//*----debugging----*//

void	print_list(char **list);
void	print_chained_list(t_token *head);
void	print_variable_list(t_token *head);
void	print_command_list(t_command *head);

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
int		expand(t_token *token, t_token *var);
void	*ft_calloc(size_t elem, size_t size);
char	*ft_strncat(char *dst, const char *src, size_t n);
int		ft_len(char *s, char c);
int		ft_len2(char *s);
int		ft_len3(char *s);
int		check_assignment(const char *s);
int		is_special_char(char c);
int		get_operator_len(const char *s);
void	free_token_array(char **tokens, int count);
int		process_quotes(const char *s, int *i, char quote);
int		ft_env(t_data *data);
t_token	*form_token_list(char **token_list);
t_token	*create_var(char *name, char *content);
char	*ft_content(char *s);
char	*ft_name(char *s);
int		ft_assign(char *s, t_token **var);
char	**real_split(const char *s, char c);
int		executing(t_data *data);
int		ft_exec(char *executable, char **cmd, char **envp);
int		ft_fork(pid_t *pid, int *prev_pipe_read, int *fd);
int		ft_pipe(t_command *tmp, int *fd);
void	edit_pipe_fd(int infile, int outfile, int *prev_pipe_read, int *fd);
int		is_cmd(t_command *tmp, char **executable, char ***cmd);
int		is_redirection(t_command *tmp, char **executable, char ***cmd);
int		redirout_append(t_command *tmp, int *outfile, char **executable, char ***cmd);
int		redirect_in(t_command *tmp, int *infile, char **executable, char ***cmd);
void	free_double_ptr(char **args);
void	ft_free(char **executable, char ***cmd);
void	free_command_list(t_data *data);

//*----minishell----*//

char	*get_input(void);
t_token	*tokenize(t_data *data);
void	init_signal_handlers(void);
void	filter(t_token *head);
void	remove_useless_quotes(char *str, int *quote_type);
int		check_quote_type(char quote, int *first_type);
void	init_terminal(void);
void	check_if_valid(t_data *data);
int		is_metachar(int type);
void	command_list(t_data *data);

#endif
