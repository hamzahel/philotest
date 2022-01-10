/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:36:47 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/01/09 17:45:37 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(void)
{
	struct timeval	tval;
	struct timezone	tzone;

	gettimeofday(&tval, &tzone);
	return ((tval.tv_sec * 1000) + (tval.tv_usec / 1000));
}

int	printerror(void)
{
	write(1, "Error", ft_strlen("Error"));
	return (1);
}

int	isalldigit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
