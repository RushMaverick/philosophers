/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tn-denpoof <tn-denpoof@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:50:58 by rrask             #+#    #+#             */
/*   Updated: 2023/06/16 14:13:27 by tn-denpoof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philos_init(t_philo *philos, t_attr *attrib, t_mutex *mutex)
{
	int i;

	i = 0;
	while (i < attrib->philo_num)
	{
		philos[i].attr = attrib;
		philos[i].l_fork = &mutex->forks[i];
		if (i == attrib->philo_num - 1)
			philos[i].r_fork = &mutex->forks[0];
		else
			philos[i].r_fork = &mutex->forks[i + 1];
		philos[i].gate = &mutex->gate;
		philos[i].death = &mutex->death;
		philos[i].id = i;
		philos[i].is_dead = 0;
		philos[i].times_eaten = 0;
		philos[i].last_supper = get_time_ms();
		i++;
	}
}

void	philos_spawn(t_philo *philos, pthread_mutex_t *gate)
{
	int i;

	i = 0;
	pthread_mutex_lock(gate);
	while (i < philos->attr->philo_num)
	{
		pthread_create(&philos[i].thread, NULL, &philo_run, philos + i);
		i++;
	}
	pthread_mutex_unlock(gate);
}

void	philos_join(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos->attr->philo_num)
	{
		pthread_join(philos[i].thread, NULL);
		printf("Philosopher %d has been terminated.\n", i);
		i++;
	}
}
