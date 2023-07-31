/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:50:58 by rrask             #+#    #+#             */
/*   Updated: 2023/07/22 13:55:10 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	return (0);
}

static void	philo_eat(t_philo *philo)
{
	if (philo_check_death(philo))
		return ;
	pthread_mutex_lock(philo->r_fork);
	print_state(philo, "has taken a fork");
	if (philo->attr->philo_num == 1)
	{
		ft_usleep(philo, philo->attr->time_to_die + 1);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	if (philo_check_death(philo))
	{
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_state(philo, "has taken a fork");
	eat(philo, philo->attr->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	*philo_run(void *this)
{
	t_philo	*philo;

	philo = (t_philo *)this;
	pthread_mutex_lock(philo->gate);
	pthread_mutex_unlock(philo->gate);
	if (philo->id % 2 == 0)
		ft_usleep(philo, 10);
	while (1)
	{
		if (philo_check_death(philo))
			return (this);
		philo_eat(philo);
		hit_the_hay(philo);
		think(philo);
	}
	return (this);
}
