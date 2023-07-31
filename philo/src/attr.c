/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:08:08 by tspoof            #+#    #+#             */
/*   Updated: 2023/07/31 15:18:10 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	attr_set(t_attr *attr, int argc, char **argv)
{
	attr->philo_num = ft_atoi(argv[1]);
	attr->time_to_die = ft_atoi(argv[2]);
	attr->time_to_eat = ft_atoi(argv[3]);
	attr->time_to_sleep = ft_atoi(argv[4]);
	attr->times_must_eat = -1;
	if (argc == ARG_MAX)
	{
		attr->times_must_eat = ft_atoi(argv[5]);
		if (attr->times_must_eat <= 0)
		{
			error_handler("Arguments are invalid.");
			return (1);
		}
	}
	attr->start_time = get_time_ms();
	if (attr->philo_num <= 0 || attr->time_to_die <= 0 || attr->time_to_eat <= 0
		|| attr->time_to_sleep <= 0)
	{
		error_handler("Arguments are invalid.");
		return (1);
	}
	return (0);
}
