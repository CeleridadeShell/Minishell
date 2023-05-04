/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:37:56 by mcarecho          #+#    #+#             */
/*   Updated: 2023/05/03 21:16:01 by mcarecho         ###   ########.fr       */
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
# include <errno.h>
# include <fcntl.h>

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
	struct s_token	*next_token;	// pointer to the next token
}	t_token;

typedef struct s_shell
{
	char	**envp;
	char	*prompt;
	int		exit_status;
	int		last_status;
	char	**paths; // saves the paths of the $PATH variable in a matrix
	t_token	*h_token;
}	t_shell;

typedef struct s_token_execution
{
	t_token	*token;
	int		fd[2];
	int		fd_original[2];
	int		fd_in;
	int		cmd_i;
	int		fd_file;
	int 	fd_heredoc;
}	t_tk_exec;

// Functions
// signals
void	handle_signal_child(void);
void	handle_signal(void);

// Inicialization
void	initialize_shell(t_shell *shell, const char **envp);
void	start_tokens(t_shell *shell);

// Closing
void	free_shell(t_shell *shell);
void	free_token(t_token *token);
void	free_paths(char **paths);

// Errors
int		check_quotes(char *argument);
int		is_empty(char *input);
int		check_input(char *input);
void	unexpected_token(t_shell *shell, char *token);
void	throw_err(t_shell *shell, char *err, int status);
void	command_not_found(t_shell *shell, char *cmd);

// Utils
char	*find_envp_field(t_shell *shell, const char *field);
int		find_envp_field_index(t_shell *shell, const char *field);
void	replace_env_field(t_shell *shell, const char *field, \
const char *new_field);
void cmd_expand_str(char *str, t_shell *shell);
void	cmd_expand_var(t_token *token, t_shell *shell);
int		count_number_of_params(char **cmd);
void	remove_quotes(char **str, int i);

// Tokenization
int		is_redirect(char c);
int		is_pipe(char c);
int		is_quote(char c);
int		is_whitespace(char c);
int		is_separator(char c);

t_token	*append_token(t_shell *g, t_token *token, t_token *last_token);
char	*get_value(char **input);
int		is_symbol(char c);
void	lexer(char *input, t_shell *shell);

char	*when_redirect(t_shell *shell, t_token **tmp, char *input);
char	*when_sep_pipe(t_shell *shell, t_token **tmp, char *input, int holder);
char	*when_word(t_shell *shell, t_token **tmp, char *input);
void	normalize(t_shell *shell, t_token *tmp);

char	*ft_strdup_char(char c);
t_token	*parsing(t_token *token, t_shell *shell);
char	**ft_split_pipex(char *argument);

t_token	*get_next_token(char *input, int end_pos);
t_token	*n_token(char *value, int type, int size);
int		verify_unexpecte_token(t_token *current_token, t_token *last_token);

// char	*get_env(t_mini_env *env, char *key);
// char	*sub_error_n(char *str, char *key, int a, t_shell *shell);
// char	*is_key(char *key, char *str, int a, t_shell *shell);
// char	*get_key(char *word, int a, t_shell *shell);

//Builtins
int		check_built_in(t_token *token, t_shell *shell);
void	ft_echo(t_token *token);
void	ft_cd(t_token *token, t_shell *shell);
void	ft_pwd(t_shell *shell);
void	ft_export(t_token *token, t_shell *shell);
void	ft_unset(t_token *token, t_shell *shell);
void	ft_env(t_shell *shell);
void	ft_exit(t_token *token, t_shell *shell);

//Execution
void	execute_token(t_shell *shell);
void	close_custom(int *fd);
void	redirect_outfile(t_tk_exec *exec_vars);
void	run_command(t_tk_exec *exec_vars, t_shell *shell);
void	set_fd_variables(t_tk_exec *exec_vars);
void	set_io_redirection(t_tk_exec *exec_vars, int n_cmds);
void	init_exec_vars(t_tk_exec *exec_vars, t_shell *shell);
void redirect_infile(t_tk_exec *exec_vars, t_shell *shell);

#endif
