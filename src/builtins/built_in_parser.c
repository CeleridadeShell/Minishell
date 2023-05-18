/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:10:47 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/18 20:26:30 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_built_in(t_token *token, t_shell *shell)
{
	if (!ft_strncmp(token->cmd[0], "echo", ft_strlen((char *) token->cmd[0])))
		ft_echo(token);
	else if (!ft_strncmp(token->cmd[0], "cd", \
	ft_strlen((char *) token->cmd[0])))
		ft_cd(token, shell);
	else if (!ft_strncmp(token->cmd[0], "pwd", \
	ft_strlen((char *) token->cmd[0])))
		ft_pwd(shell);
	else if (!ft_strncmp(token->cmd[0], "export", \
	ft_strlen((char *) token->cmd[0])))
		ft_export(token, shell);
	else if (!ft_strncmp(token->cmd[0], "unset", \
	ft_strlen((char *) token->cmd[0])))
		ft_unset(token, shell);
	else if (!ft_strncmp(token->cmd[0], "env", \
	ft_strlen((char *) token->cmd[0])))
		ft_env(shell);
	else if (!ft_strncmp(token->cmd[0], "exit", \
	ft_strlen((char *) token->cmd[0])))
		ft_exit(token, shell);
	else
		return (1);
	return (0);
}
