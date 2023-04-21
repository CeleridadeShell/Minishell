/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:37:56 by mcarecho          #+#    #+#             */
/*   Updated: 2023/04/20 21:27:09 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Native libraries

# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>

// Non-native libraries

# include <libft.h>


// Define

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define TRUE 1
# define FALSE 0
# define QUOTE 4 // uma aspas simples ou dupla
# define WHITESPACE 5 // um espaço em branco
# define CHARS_WHITESPACES " \t\n"
# define TEMP_SPACE 1

// structs

typedef enum e_type_token
{
	WORD,
	PIPE,
	REDIRECT,
	SEPARATOR,
}	t_type_t;

/**
 * @brief token structure
 */
typedef struct s_token
{
	t_type_t		type;	// the token type, e.g. WORD, PIPE, REDIRECT
	int				n_cmds;	// number of commands
	int				n_tokens; // number of tokens
	char			*value; // the value of the token, eg "ls", ">", "file.txt"
	char			**cmd; //the command split by spaces and parsed
	char			**paths; // saves the paths of the $PATH variablein a matrix
	struct s_token	*next_token;	// pointer to the next token
}	t_token;

typedef struct s_shell
{
	char	**envp;
	char	*prompt;
	int 	exit_status;
	int		last_status;
	t_token			*h_token;
}	t_shell;


// Functions


// signals
static void	sigint_handler(int sig);
static void	sigint_handler_child(int sig);
void		handle_signal_child(void);
void		handle_signal(void);

// Inicialization
void	initialize_shell(t_shell *shell, const char **envp);
void	start_tokens(t_token **tokens, t_shell *shell);

// Closing
void	free_shell(t_shell *shell);
void	free_cmd(t_cmd *cmd);

// Errors
int	check_quotes(char *argument);
int	is_empty(char *input);
int	check_input(char *input);
void	error_handler(t_global *g);

// Utils
char	*find_envp_field(t_shell *shell, const char *field);
int	find_envp_field_index(t_shell *shell, const char *field);
void	replace_env_field(t_shell *shell, const char *field, const char *new_field)

// Tokenization
int	is_redirect(char c);
int	is_pipe(char c);
int	is_quote(char c);
int	is_whitespace(char c);
int	is_separator(char c);

t_token	*append_token(t_shell *g, t_token *token, t_token *last_token);
char	*get_value(char **input);
int		is_symbol(char c);
void	lexer(char *input, t_global *g);

char	*when_quotes(t_global *g, t_token **tmp, char *input);
char	*when_redirect(t_global *g, t_token **tmp, char *input);
char	*when_sep_pipe(t_global *g, t_token **tmp, char *input, int holder);
char	*when_word(t_global *g, t_token **tmp, char *input);
void	normalize(t_global *g);

char	*ft_strdup_char(char c);
t_token	*parsing(t_token *token, t_global *g);
static char	ft_expander(char *argument, char previous, char after);
static void	ft_reswitch(char **cmd, t_global *g);
char	**ft_split_pipex(char *argument, t_global *g);

t_token	*get_next_token(char *input, int end_pos);
t_token	*n_token(char *value, int type, int size);
int	verify_unexpecte_token(t_token *current_token, t_token *last_token);

char	*get_env(t_mini_env *env, char *key);
char	*sub_error_n(char *str, char *key, int a, t_global *g);
char	*is_key(char *key, char *str, int a, t_global *g);
char	*get_key(char *word, int a, t_global *g);



#endif
