/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:13:48 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/14 19:06:27 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	update_workdir(t_shell *shell)
{
	char	*current_pwd;
	char	*tmp;
	int		i;

	i = find_envp_field_index(shell, "PWD");
	current_pwd = ft_strdup(shell->envp[i]);
	tmp = current_pwd;
	current_pwd = ft_strjoin("OLD", current_pwd);
	ft_freethis(&tmp, NULL);
	if (find_envp_field_index(shell, "OLDPWD") != -1)
		replace_env_field(shell, "OLDPWD", current_pwd);
	else
		realloc_env(shell, current_pwd);
	ft_freethis(&current_pwd, NULL);
	tmp = getcwd(NULL, 0);
	current_pwd = ft_strjoin("PWD=/", tmp);
	replace_env_field(shell, "PWD", current_pwd);
	ft_freethis(&tmp, NULL);
	ft_freethis(&current_pwd, NULL);
}

void	ft_cd(t_token *token, t_shell *shell)
{
	char	*destiny;

	if (count_number_of_params(token->cmd) > 2)
	{
		throw_err(shell, "cd: too many arguments", 1);
		return ;
	}
	if (!token->cmd[1])
		destiny = find_envp_field(shell, "HOME");
	else if (!ft_strncmp((char *)token->cmd[1], "-", ft_strlen(token->cmd[1])))
	{
		destiny = find_envp_field(shell, "OLDPWD");
		if (!destiny)
			throw_err(shell, "cd: OLDPWD not set", 1);
		else
			printf("%s\n", destiny);
	}
	else
		destiny = ft_strdup((char *)token->cmd[1]);
	if (!chdir(destiny))
		update_workdir(shell);
	else if (shell->exit_status == 0)
		throw_err_cd(shell, destiny, 1);
	ft_freethis(&destiny, NULL);
}
