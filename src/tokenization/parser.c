/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 19:08:57 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/11 20:28:37 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strdup_char(char c)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

t_token	*parsing(t_token *token, t_shell *shell)
{
	t_token		*temp;
	t_type_t	last_type;
	int			index;

	index = 0;
	temp = token;
	last_type = SEPARATOR;
	while (index < token->n_tokens)
	{
		if (temp->type == WORD && last_type != REDIRECT)
		{
			cmd_expand_var(temp, shell);
			temp->cmd = ft_split_pipex(temp->value);
		}
		else if (temp->type == WORD && last_type == REDIRECT)
		{
			cmd_expand_str(&temp->value, shell);
		}
		index++;
		last_type = temp->type;
		temp = temp->next_token;
	}
	return (token);
}
