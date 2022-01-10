/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:37:46 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/01/09 17:37:49 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int					num_philo;
	int					num_eat_p;
	int					num_t_eat;
	int					time_d;
	int					time_e;
	int					time_s;
	long				time;
	int					death;
	pthread_mutex_t		msg;
	pthread_mutex_t		prog;
	pthread_mutex_t		*forks;
}						t_data;

typedef struct s_philo
{
	t_data	*data;
	int		id;
	long	philo_eat;
	int		num_eat;
}			t_philo;

long		gettime(void);
void		init(char **argv, t_data *data);
int			initphilo(t_data *data, t_philo **philo);
int			initmutex(t_data *data);
int			parsing(char **argv, t_data **data, t_philo **philo);
int			printerror(void);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			ft_strlen(char *str);
int			isalldigit(char **argv);
void		print_infos(char *info, t_philo *philo);

#endif
