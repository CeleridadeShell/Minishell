/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:12:37 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/13 16:40:16 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	no_args(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		printf("declare -x ");
		printf("%s\n", shell->envp[i]);
		i++;
	}
}

static int	validate_var_name(char arg, int i)
{
	int	j;

	j = 0;
	if (i == 0 && ft_isdigit(arg))
		return (1);
	while (INVALID_CHARS[j])
	{
		if (arg == INVALID_CHARS[j])
			return (1);
		j++;
	}
	return (0);
}

static int	is_arg_valid(char *arg)
{
	int	equals;
	int	i;

	equals = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			equals++;
		if (equals == 0 && validate_var_name(arg[i], i))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	if (equals > 0)
		return (1);
	else
		return (0);
}

void	realloc_env(t_shell *shell, char *env_line)
{
	char	**tmp_env;
	int		line_count;
	int		i;

	line_count = 0;
	i = 0;
	while (shell->envp[line_count])
		line_count++;
	tmp_env = (char **) ft_calloc(line_count + 2, sizeof(char *));
	while (line_count)
	{
		tmp_env[i] = ft_strdup(shell->envp[i]);
		i++;
		line_count--;
	}
	tmp_env[i] = ft_strdup(env_line);
	i = 0;
	while (shell->envp[i])
	{
		ft_freethis(&(*shell).envp[i], NULL);
		i++;
	}
	free(shell->envp);
	shell->envp = tmp_env;
}

void	ft_export(t_token *token, t_shell *shell)
{
	int		i;

	if (count_number_of_params(token->cmd) == 1)
	{
		no_args(shell);
		return ;
	}
	i = 1;
	while (token->cmd[i])
	{
		if (is_arg_valid(token->cmd[i]))
		{
			valid_arg(shell, token, &i);
		}
		else
			shell->exit_status = 1;
		i++;
	}
}
