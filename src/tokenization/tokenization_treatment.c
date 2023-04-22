/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_treatment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:02:50 by mcarecho          #+#    #+#             */
/*   Updated: 2023/04/22 19:22:00 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// char	*get_env(t_mini_env *env, char *key)
// {
// 	t_mini_env	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->name, key, ft_strlen(key) + 1))
// 			return (tmp->value);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// char	*sub_error_n(char *str, char *key, int a, t_global *g)
// {
// 	char	*final;
// 	char	*tmp;

// 	tmp = ft_itoa(g->last_status);
// 	final = malloc(sizeof(char) * (ft_strlen(str) - 2 + ft_strlen(tmp) + 1));
// 	ft_bzero(final, ft_strlen(str) - 2 + ft_strlen(tmp) + 1);
// 	ft_strlcpy(final, str, ft_strchr(&str[a], '$') - str + 1);
// 	ft_strlcat(final, tmp, (ft_strlen(str) - 2 + ft_strlen(tmp)) + 1);
// 	ft_strlcat(final, ft_strchr(&str[a], '$') + 2, (ft_strlen(str)
// 			- 2 + ft_strlen(tmp) + 1));
// 	free(tmp);
// 	free(str);
// 	free(key);
// 	return (final);
// }

// char	*is_key(char *key, char *str, int a, t_global *g)
// {
// 	char	*value;
// 	char	*final;

// 	value = get_env(g->mini_env, key);
// 	if (value == NULL)
// 	{
// 		if (!ft_strncmp(key, "?", 2))
// 			return (sub_error_n(str, key, a, g));
// 		return (str);
// 	}
// 	final = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen(key) + ft_strlen
// 				(value) + 1));
// 	ft_bzero(final, ft_strlen(str) - ft_strlen(key) + ft_strlen(value) + 1);
// 	ft_strlcpy(final, str, ft_strchr(&str[a], '$') - str + 1);
// 	ft_strlcat(final, value, ft_strlen(final) + ft_strlen(value) + 1);
// 	ft_strlcat(final, ft_strchr(&str[a], '$') + ft_strlen(key) +1, ft_strlen
// 		(str) - ft_strlen(key) + ft_strlen(value) + 1);
// 	final[ft_strlen(str) - ft_strlen(key) + ft_strlen(value) - 1] = '\0';
// 	free(key);
// 	free(str);
// 	return (final);
// }

// char	*get_key(char *word, int a, t_global *g)
// {
// 	char	*tmp;
// 	char	*key;
// 	int		i;

// 	i = -1;
// 	tmp = ft_strtrim(word, "\"");
// 	free(word);
// 	word = ft_strchr(&tmp[a], '$');
// 	key = NULL;
// 	while (++i < 2)
// 	{
// 		if (ft_strchr(word, CHARS_WHITESPACES[i]))
// 		{
// 			key = ft_strchr(word, CHARS_WHITESPACES[i]);
// 			break ;
// 		}
// 	}
// 	if (key != NULL)
// 		i = key - word - 1;
// 	else
// 		i = ft_strlen(word) - 1;
// 	key = ft_substr(tmp, word - tmp + 1, i);
// 	return (is_key(key, tmp, a, g));
// }
