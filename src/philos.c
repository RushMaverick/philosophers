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

# include "philosophers.h"

void	philo_even(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork); // protec fork?
	printf("Philosopher %d has taken the left fork.\n", philo->id);
	pthread_mutex_lock(philo->r_fork);// protec fork?
	printf("Philosopher %d has taken the right fork.\n", philo->id);
	eating(philo, philo->attr->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
void	philo_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);// protec fork?
	printf("Philosopher %d has taken the right fork.\n", philo->id);
	pthread_mutex_lock(philo->l_fork);// protec fork?
	printf("Philosopher %d has taken the left fork.\n", philo->id);
	eating(philo, philo->attr->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}


void	*philo_run(void *this)
{
	t_philo	*philo = (t_philo *)this;

	pthread_mutex_lock(philo->gate); // protec mutex?
	pthread_mutex_unlock(philo->gate);
	philo->last_supper = get_time_ms();
	while (1)
	{
		if (philo->attr->times_must_eat >= 0
			&& philo->times_eaten >= philo->attr->times_must_eat)
		{
			printf("Philosopher %d has eaten enough.\n", philo->id);
			return (0);
		}
		// if (is_dead(philo, philo->attr->time_to_die))
		if (philo->is_dead) // mutex?
			break ;
		if (philo->id % 2 == 0)
			philo_even(philo);
		else
			philo_odd(philo);
		sleeping(philo, philo->attr->time_to_sleep);
	}
	return (this);
}

void	philos_init(t_philo *philos, t_attr *attrib, t_mutex *mutex) // change to use t_mutex  pthread_mutex_t *forks
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
		i++;
	}
}

void	philos_spawn(t_philo *philos, pthread_mutex_t *gate, t_mutex *mutex)
{
	int i;

	i = 0;
	// (void)mutex;
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