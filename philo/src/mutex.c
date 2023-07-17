/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:19:57 by rrask             #+#    #+#             */
/*   Updated: 2023/07/16 13:08:57 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	mutex_array_init(int num_philos, pthread_mutex_t *mutexes)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(mutexes + i, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	mutex_init(int num_philos, t_mutex *mutex)
{
	if (mutex_array_init(num_philos, mutex->forks))
	{
		error_handler("Fork init failed.");
		return (3);
	}
	if (mutex_array_init(num_philos, mutex->deaths))
	{
		error_handler("Death init failed.");
		return (3);
	}
	if (pthread_mutex_init(&mutex->gate, NULL) != 0)
	{
		error_handler("Gate init failed.");
		return (3);
	}
	if (pthread_mutex_init(&mutex->print, NULL) != 0)
	{
		error_handler("Print init failed.");
		return (3);
	}
	return (0);
}

static int	mutex_array_destroy(int num_philos, pthread_mutex_t *mutexes)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_destroy(mutexes + i) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	mutex_destroy(int num_philos, t_mutex *mutex)
{
	if (mutex_array_destroy(num_philos, mutex->forks))
	{
		error_handler("Mutex destroy failed.");
		return (4);
	}
	if (mutex_array_destroy(num_philos, mutex->deaths))
	{
		error_handler("Mutex destroy failed.");
		return (4);
	}
	if (pthread_mutex_destroy(&mutex->gate) != 0)
	{
		error_handler("Mutex destroy failed.");
		return (4);
	}
	if (pthread_mutex_destroy(&mutex->print) != 0)
	{
		error_handler("Mutex destroy failed.");
		return (4);
	}
	return (0);
}
