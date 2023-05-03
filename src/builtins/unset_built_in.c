/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:59:29 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/03 19:00:38 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	feed_tmp_env(t_shell *shell, char **tmp_env, char *var_name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->envp[i])
	{
		if (i == find_envp_field_index(shell, var_name))
			i++;
		if (!shell->envp[i])
			break ;
		tmp_env[j] = ft_strdup(shell->envp[i]);
		i++;
		j++;
	}
}

static void	clear_envp(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		ft_freethis(&(*shell).envp[i], NULL);
		i++;
	}
	free(shell->envp);
}

void	ft_unset(t_token *token, t_shell *shell)
{
	int		i;
	char	**tmp_env;
	int		line_count;

	i = 1;
	while (token->cmd[i])
	{
		line_count = 0;
		while (shell->envp[line_count])
			line_count++;
		tmp_env = (char **) ft_calloc(line_count, sizeof(char *));
		feed_tmp_env(shell, tmp_env, token->cmd[i]);
		clear_envp(shell);
		shell->envp = tmp_env;
		i++;
	}
}
