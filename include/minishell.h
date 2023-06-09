/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:37:56 by mcarecho          #+#    #+#             */
/*   Updated: 2023/05/18 21:06:08 by ccamargo         ###   ########.fr       */
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
# define QUOTE 4
# define WHITESPACE 5
# define CHARS_WHITESPACES " \t\n"
# define TEMP_SPACE 1
# define INVALID_CHARS "!#$%^&*()-+={}[]| :;\"\\<>,?/\0"

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
	t_type_t		type;
	int				n_cmds;
	int				n_tokens;
	char			*value;
	char			**cmd;
	struct s_token	*next_token;
}	t_token;

typedef struct s_shell
{
	char	**envp;
	char	*prompt;
	int		exit_status;
	int		last_status;
	char	**paths;
	t_token	*h_token;
}	t_shell;

typedef struct s_token_execution
{
	pid_t	*pids;
	t_token	*token;
	int		fd[2];
	int		fd_original[2];
	int		fd_in;
	int		cmd_i;
	int		fd_file;
	int		fd_heredoc;
}	t_tk_exec;

// Functions
// signals
void	handle_signal_child(void);
void	handle_signal(void);
void	fix_sigint_exec(void);
void	handle_signal_heredoc(void);
void	sigint_handler_child(int sig);

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
void	throw_err_cd(t_shell *shell, char *err, int status);
void	command_not_found(t_shell *shell, char *cmd);

// Utils
char	*find_envp_field(t_shell *shell, const char *field);
int		find_envp_field_index(t_shell *shell, const char *field);
void	replace_env_field(t_shell *shell, const char *field, \
const char *new_field);
void	cmd_expand_str(char **str, t_shell *shell);
void	found_dollar_sign(t_shell *shell, char **str, int i, char quote);
void	cmd_expand_var(t_token *token, t_shell *shell);
void	search_env_vars(char **str, t_shell *shell, int i);
void	replace_cmd_typed(char **str, char *found_var, int i, int j);
int		count_number_of_params(char **cmd);
void	remove_quotes(char **str, int i);
void	realloc_env(t_shell *shell, char *env_line);

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

t_token	*get_next_token(char *input, int end_pos, t_token *last_token);
t_token	*n_token(char *value, int type, int size);
int		verify_unexpecte_token(t_token *current_token, t_token *last_token);

//Builtins
int		check_built_in(t_token *token, t_shell *shell);
void	ft_echo(t_token *token);
void	ft_cd(t_token *token, t_shell *shell);
void	ft_pwd(t_shell *shell);
void	ft_export(t_token *token, t_shell *shell);
void	valid_arg(t_shell *shell, t_token *token, int *i);
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
void	redirect_infile(t_tk_exec *exec_vars, t_shell *shell);

#endif
