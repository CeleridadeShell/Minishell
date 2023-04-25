/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:10:47 by ccamargo          #+#    #+#             */
/*   Updated: 2023/04/25 16:56:39 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_built_in(t_token *token, t_shell *shell)
{
	if (!ft_strncmp(token->cmd[0], "echo", ft_strlen((char *) token->cmd[0])))
		run_echo(token);
	if (!ft_strncmp(token->cmd[0], "cd", ft_strlen((char *) token->cmd[0])))
		run_cd(token, shell);
	if (!ft_strncmp(token->cmd[0], "pwd", ft_strlen((char *) token->cmd[0])))
		run_pwd(/* token, */ shell);
	if (!ft_strncmp(token->cmd[0], "export", \
	ft_strlen((char *) token->cmd[0])))
		run_export(token, shell);
	if (!ft_strncmp(token->cmd[0], "unset", ft_strlen((char *) token->cmd[0])))
		run_unset(token, shell);
	if (!ft_strncmp(token->cmd[0], "env", ft_strlen((char *) token->cmd[0])))
		run_env(/* token,  */shell);
}
