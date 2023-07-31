/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:23:43 by rrask             #+#    #+#             */
/*   Updated: 2023/07/22 13:55:02 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo, size_t time_to_eat)
{
	pthread_mutex_lock(philo->death);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(philo->death);
		return ;
	}
	philo->last_supper = get_time_ms();
	philo->times_eaten += 1;
	pthread_mutex_unlock(philo->death);
	print_state(philo, "is eating");
	ft_usleep(philo, time_to_eat);
}

void	hit_the_hay(t_philo *philo)
{
	if (philo_check_death(philo))
		return ;
	print_state(philo, "is sleeping");
	ft_usleep(philo, philo->attr->time_to_sleep);
}

void	think(t_philo *philo)
{
	if (philo_check_death(philo))
		return ;
	print_state(philo, "is thinking");
}
