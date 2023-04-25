/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:13:48 by ccamargo          #+#    #+#             */
/*   Updated: 2023/04/25 16:08:30 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	throw_err_cd(/* t_shell *shell,  */char *err)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	//cmd->error = 1; Qual seria a variável equivalente?
}

static void	update_workdir(t_shell *shell, char *destiny)
{
	char	*current_pwd;
	char	*tmp;
	int		i;

	i = find_envp_field_index(shell, "PWD");
	current_pwd = ft_strdup(shell->envp[i]);
	tmp = current_pwd;
	current_pwd = ft_strjoin("OLD", current_pwd);
	ft_freethis(&tmp, NULL);
	replace_env_field(shell, "OLDPWD", current_pwd);
	ft_freethis(&current_pwd, NULL);
	chdir(destiny);
	tmp = getcwd(NULL, 0);
	current_pwd = ft_strjoin("PWD=/", tmp);
	replace_env_field(shell, "PWD", current_pwd);
	ft_freethis(&tmp, NULL);
	ft_freethis(&current_pwd, NULL);
}

void	run_cd(t_token *token, t_shell *shell)
{
	char	*destiny;

	if (token->n_cmds > 2)
	{
		throw_err(/* shell,  */"cd: too many arguments");
		return ;
	}
	if (!token->cmd[1])
		destiny = find_envp_field(shell, "HOME");
	else if (!ft_strncmp((char *) token->cmd[1], "-", ft_strlen(token->cmd[1])))
		destiny = find_envp_field(shell, "OLDPWD");
	else
		destiny = ft_strdup((char *) token->cmd[1]);
	if (!chdir(destiny))
		update_workdir(shell, destiny);
	else
		throw_err_cd(/* shell ,*/ destiny);
	ft_freethis(&destiny, NULL);
	//cmd->builtin = 1;
}
