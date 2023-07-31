/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 09:51:23 by rrask             #+#    #+#             */
/*   Updated: 2023/07/22 13:54:55 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_attr	attributes;
	t_mutex	mutex;
	t_philo	philos[MAX_PHILO];

	if (argc < ARG_MIN || argc > ARG_MAX)
	{
		error_handler("Try again, punk.");
		return (1);
	}
	if (attr_set(&attributes, argc, argv))
		return (2);
	if (mutex_init(attributes.philo_num, &mutex))
		return (3);
	philos_init(philos, &attributes, &mutex);
	philos_spawn(philos, &mutex.gate);
	governor(philos, philos->attr);
	philos_join(philos);
	if (mutex_destroy(attributes.philo_num, &mutex))
		return (4);
	return (0);
}
