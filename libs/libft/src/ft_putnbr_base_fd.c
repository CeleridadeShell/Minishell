/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:19:57 by ccamargo          #+#    #+#             */
/*   Updated: 2022/08/25 22:33:52 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_is_base_valid(char *base)
{
	size_t	i;

	i = 0;
	if (ft_strlen(base) >= 2)
	{
		while (base[i])
		{
			if (base[i] == base[i + 1] || base[i] == '-' || base[i] == '+')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_putnbr_base_fd(int nbr, char *base, int fd)
{
	int		base_size;
	long	new_nbr;

	base_size = ft_strlen(base);
	if (ft_is_base_valid(base))
	{
		if (nbr < 0)
		{
			ft_putchar_fd('-', fd);
			new_nbr = nbr;
			new_nbr = new_nbr * (-1);
		}
		else
			new_nbr = nbr;
		if (new_nbr >= base_size)
			ft_putnbr_base_fd((new_nbr / base_size), base, fd);
		ft_putchar_fd(base[new_nbr % base_size], fd);
	}
}
