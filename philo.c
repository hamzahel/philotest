/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:36:36 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/01/09 17:45:05 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status(t_philo **philo)
{
	int	next_fork;

	next_fork = (*philo)->id % (*philo)->data->num_philo;
	while (1337)
	{
		pthread_mutex_lock(&(*philo)->data->forks[(*philo)->id - 1]);
		print_infos("has taken a fork", *philo);
		pthread_mutex_lock(&(*philo)->data->forks[next_fork]);
		print_infos("has taken a fork", *philo);
		(*philo)->philo_eat = (gettime() - (*philo)->data->time);
		print_infos("is \e[0;32meating", *philo);
		usleep((*philo)->data->time_e * 1000);
		pthread_mutex_unlock(&(*philo)->data->forks[(*philo)->id - 1]);
		pthread_mutex_unlock(&(*philo)->data->forks[next_fork]);
		print_infos("is \e[0;33msleeping", *philo);
		usleep((*philo)->data->time_s * 1000);
		print_infos("is thinking", *philo);
		if ((*philo)->num_eat > 0)
			(*philo)->num_eat--;
		if ((*philo)->num_eat == 0)
			break ;
	}
}

void	*is_death(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (1337)
	{
		if (ph->num_eat == 0)
			break ;
		if (((gettime() - ph->data->time) - ph->philo_eat) > ph->data->time_d)
		{
			pthread_mutex_lock(&ph->data->msg);
			printf("[%ld] philosopher[%d] \e[0;31mdied\e[0m\n",
				(gettime() - ph->data->time), ph->id);
			pthread_mutex_unlock(&ph->data->prog);
			break ;
		}
	}
	return (NULL);
}

void	*traitment(void *philo)
{
	t_philo		*ph;
	pthread_t	dt;

	ph = (t_philo *)philo;
	pthread_create(&dt, NULL, is_death, ph);
	pthread_detach(dt);
	status(&ph);
	ph->data->num_eat_p--;
	if (ph->data->num_eat_p == 0)
		pthread_mutex_unlock(&ph->data->prog);
	return (NULL);
}

int	start(t_data **data, t_philo **philo)
{
	pthread_t	thread;
	int			i;

	if ((*data)->num_t_eat == 0)
		return (0);
	i = 0;
	pthread_mutex_lock(&(*data)->prog);
	while (i < (*data)->num_philo)
	{
		pthread_create(&thread, NULL, traitment, &(*philo)[i]);
		pthread_detach(thread);
		usleep(100);
		i++;
	}
	pthread_mutex_lock(&(*data)->prog);
	i = -1;
	while (++i < (*data)->num_philo)
		pthread_mutex_destroy(&(*data)->forks[i]);
	pthread_mutex_destroy(&(*data)->msg);
	pthread_mutex_destroy(&(*data)->prog);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philos;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (1);
	*data = (t_data){0};
	data->num_t_eat = -1;
	if ((argc == 5 || argc == 6) && parsing(argv, &data, &philos))
	{
		start(&data, &philos);
		free(data->forks);
		free(data);
		free(philos);
		return (0);
	}
	return (printerror());
}
