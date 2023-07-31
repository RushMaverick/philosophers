/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   governor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:51:33 by rrask             #+#    #+#             */
/*   Updated: 2023/07/22 13:54:51 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_dead(t_philo *philo, size_t time_to_die)
{
	if (get_time_ms() - philo->last_supper >= time_to_die)
		return (1);
	return (0);
}

static void	kill_all(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].attr->philo_num)
	{
		pthread_mutex_lock(philos[i].death);
		philos[i].is_dead = 1;
		pthread_mutex_unlock(philos[i].death);
		i++;
	}
}

static int	check_death(t_philo *philos, t_attr *attr)
{
	int	i;

	i = 0;
	while (i < attr->philo_num)
	{
		pthread_mutex_lock(philos[i].death);
		if (is_dead(&philos[i], attr->time_to_die))
		{
			philos[i].is_dead = 1;
			pthread_mutex_unlock(philos[i].death);
			kill_all(philos);
			print_death(philos[i]);
			return (1);
		}
		pthread_mutex_unlock(philos[i].death);
		i++;
	}
	return (0);
}

static int	check_eaten(t_philo *philos)
{
	int	i;
	int	philos_full;

	if (philos[0].attr->times_must_eat == -1)
		return (0);
	i = 0;
	philos_full = 0;
	while (i < philos[0].attr->philo_num)
	{
		pthread_mutex_lock(philos[i].death);
		if (philos[i].times_eaten >= philos[0].attr->times_must_eat)
			philos_full++;
		pthread_mutex_unlock(philos[i].death);
		i++;
	}
	if (philos_full == philos[0].attr->philo_num)
	{
		kill_all(philos);
		return (1);
	}
	return (0);
}

void	governor(t_philo *philos, t_attr *attr)
{
	while (1)
	{
		if (check_death(philos, attr) || check_eaten(philos))
			return ;
	}
}
