/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:05:56 by ccamargo          #+#    #+#             */
/*   Updated: 2022/08/25 22:32:06 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_calclen(int n)
{
	size_t	charlen;

	charlen = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		charlen++;
	while (n != 0)
	{
		n = n / 10;
		charlen++;
	}
	return (charlen);
}

char	*ft_itoa(int n)
{
	char		*nbr;
	long int	ncpy;
	size_t		nlen;
	size_t		i;	

	nlen = ft_calclen(n);
	i = 1;
	ncpy = n;
	nbr = (char *) malloc((nlen + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	if (n < 0)
		ncpy = ncpy * (-1);
	while (i <= nlen)
	{
		nbr[nlen - i] = (ncpy % 10) + '0';
		ncpy = ncpy / 10;
		i++;
	}
	if (n < 0)
		nbr[0] = '-';
	nbr[nlen] = '\0';
	return (nbr);
}
