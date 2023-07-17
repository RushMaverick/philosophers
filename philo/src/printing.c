/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 05:48:40 by tspoof            #+#    #+#             */
/*   Updated: 2023/07/16 13:08:36 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_philo *philo, char *string)
{
	size_t	lapsed_time;

	pthread_mutex_lock(philo->print);
	if (philo_check_death(philo))
	{
		pthread_mutex_unlock(philo->print);
		return ;
	}
	lapsed_time = get_time_ms() - philo->attr->start_time;
	printf("%zu %d %s\n", lapsed_time, philo->id, string);
	pthread_mutex_unlock(philo->print);
}

void	print_death(t_philo philo)
{
	size_t	lapsed_time;

	pthread_mutex_lock(philo.print);
	lapsed_time = get_time_ms() - philo.attr->start_time;
	printf("%zu %d %s\n", lapsed_time, philo.id, "died");
	pthread_mutex_unlock(philo.print);
}
