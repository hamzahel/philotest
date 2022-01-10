/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:37:20 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/01/09 17:45:56 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_infos(char *info, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->msg);
	printf("[%ld] philosopher[%d] %s\e[0m\n",
		(gettime() - philo->data->time), philo->id, info);
	pthread_mutex_unlock(&philo->data->msg);
}

void	init(char **argv, t_data *data)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_d = ft_atoi(argv[2]);
	data->time_e = ft_atoi(argv[3]);
	data->time_s = ft_atoi(argv[4]);
	if (argv[5])
		data->num_t_eat = ft_atoi(argv[5]);
	data->time = gettime();
	data->death = 0;
	data->num_eat_p = data->num_philo;
}

int	initphilo(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	(*philo) = malloc(data->num_philo * sizeof(t_philo));
	if (!(*philo))
		return (0);
	while (i < data->num_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].data = data;
		(*philo)[i].num_eat = data->num_t_eat;
		(*philo)[i++].philo_eat = 0;
	}
	return (1);
}

int	initmutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->num_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	while (i < data->num_philo)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->msg, NULL);
	pthread_mutex_init(&data->prog, NULL);
	return (1);
}

int	parsing(char **argv, t_data **data, t_philo **philo)
{
	init(argv, (*data));
	if (!isalldigit(argv))
		return (0);
	if ((*data)->num_philo < 1 || (*data)->time_e < 60 || (*data)->time_s < 60
		|| (*data)->time_d < 60)
		return (0);
	if (!initphilo(*data, philo) || !initmutex(*data))
		return (0);
	return (1);
}
