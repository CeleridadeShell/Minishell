/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 18:10:47 by ccamargo          #+#    #+#             */
/*   Updated: 2023/04/26 18:47:09 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_built_in(t_token *token, t_shell *shell)
{
	int i;

	i = 0;
	if (!ft_strncmp(token->cmd[0], "echo", ft_strlen((char *) token->cmd[0])))
		ft_echo(token);
	else if (!ft_strncmp(token->cmd[0], "cd", ft_strlen((char *) token->cmd[0])))
		ft_cd(token, shell);
	else if (!ft_strncmp(token->cmd[0], "pwd", ft_strlen((char *) token->cmd[0])))
		ft_pwd(/* token, */ shell);
	else if (!ft_strncmp(token->cmd[0], "export", \
	ft_strlen((char *) token->cmd[0])))
		ft_export(token, shell);
	else if (!ft_strncmp(token->cmd[0], "unset", ft_strlen((char *) token->cmd[0])))
		ft_unset(token, shell);
	else if (!ft_strncmp(token->cmd[0], "env", ft_strlen((char *) token->cmd[0])))
		ft_env(/* token,  */shell);
	else
		i = 1;
	return(i);
}
