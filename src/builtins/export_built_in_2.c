/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_built_in_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:39:46 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/13 16:40:20 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	valid_arg(t_shell *shell, t_token *token, int *i)
{
	char	*var_name;
	char	*tmp_found_field;

	var_name = ft_substr(token->cmd[*i], 0, \
	ft_strchr(token->cmd[*i], '=') - token->cmd[*i]);
	tmp_found_field = find_envp_field(shell, var_name);
	if (tmp_found_field == NULL)
		realloc_env(shell, token->cmd[*i]);
	else
		replace_env_field(shell, var_name, token->cmd[*i]);
	ft_freethis(&var_name, NULL);
	ft_freethis(&tmp_found_field, NULL);
}
