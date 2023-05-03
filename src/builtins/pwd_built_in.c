/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:54:49 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/03 19:00:24 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_pwd(t_shell *shell)
{
	char	*found_field;
	char	*found_field_no_extra_slash;

	found_field = find_envp_field(shell, "PWD");
	found_field_no_extra_slash = ft_substr(found_field, 1, \
	ft_strlen(found_field));
	printf("%s\n", found_field_no_extra_slash);
	ft_freethis(&found_field, NULL);
	ft_freethis(&found_field_no_extra_slash, NULL);
}
