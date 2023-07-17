/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:11:24 by tspoof            #+#    #+#             */
/*   Updated: 2023/07/16 13:08:42 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(t_philo *philo, size_t time_to_snooze)
{
	size_t	the_time;

	the_time = get_time_ms();
	while (!philo_check_death(philo)
		&& (get_time_ms() - the_time) < time_to_snooze)
	{
		usleep(500);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				sign;
	unsigned long	val;

	sign = 1;
	val = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\n')
	{
		val = val * 10 + (str[i] - '0');
		if (sign == 1 && val > 9223372036854775807)
			return (-1);
		if (sign == -1 && val > 9223372036854775807)
			return (0);
		i++;
	}
	return ((int)(sign * val));
}
