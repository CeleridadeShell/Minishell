/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 17:55:58 by ccamargo          #+#    #+#             */
/*   Updated: 2023/04/22 19:19:26 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	replace_cmd_typed(char *cmd, char *found_var, int i, int j)
{
	char	*str_part1;
	char	*str_part2;
	char	*tmp_cmd_typed;

	str_part1 = ft_substr(cmd, 0, i);
	str_part2 = ft_substr(cmd, i + j, ft_strlen(cmd));
	tmp_cmd_typed = ft_strjoin(str_part1, found_var);
	ft_freethis(&cmd, NULL);
	cmd = ft_strjoin(tmp_cmd_typed, str_part2);
	ft_freethis(&str_part1, NULL);
	ft_freethis(&tmp_cmd_typed, NULL);
	ft_freethis(&str_part2, NULL);
}

static void	search_env_vars(t_shell *shell, char *cmd, int i)
{
	char	*env_var;
	char	*found_var;
	int		j;

	j = 1;
	found_var = NULL;
	while (cmd[i + j] && !found_var)
	{
		if (cmd[i + j] == ' ')
		{
			env_var = ft_substr(cmd, i + 1, j - 1);
			found_var = find_envp_field(shell, env_var);
			ft_freethis(&env_var, NULL);
		}
		j++;
	}
	replace_cmd_typed(cmd, found_var, i, j);
	ft_freethis(&found_var, NULL);
}

void	cmd_expand_var(t_token *token, t_shell *shell)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*token->cmd[i])
	{
		while (token->cmd[i][j])
		{
			if (token->cmd[i][j] == '$')
				search_env_vars(shell, token->cmd[i], j);
			j++;
		}
		i++;
	}
}

