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

void	*philo_run(void *this)
{
	/* Start the philosopher logic here (Grab forks if odd number,
		eat if two forks, die if death is due, wait if only one fork.) */
	t_philo	*philo = (t_philo *)this;
	
	if (philo->id % 2 == 0)
		printf("I am philosopher %d, I am even.\n", philo->id);
		//lock the right fork first.
	// else
		//Lock the left fork first.
	
	// pthread_mutex_lock(philo->gate);
	//eating function if two forks
	//sleeping function if no forks
	// pthread_mutex_unlock(philo->gate);
	return (this);
}
	//if(start_time - philos[i].last_supper >= time_to_die)	condition of dying
	//	philo dies

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
		philos[i].id = i;
		philos[i].last_supper = get_time_ms();
		i++;
	}
}

void	philos_spawn(t_philo *philos, pthread_mutex_t *gate)
{
	int i;

	i = 0;
	
	// lock philos here
	pthread_mutex_lock(gate);
	while (i < philos->attr->philo_num)
	{
		pthread_create(&philos[i].thread, NULL, &philo_run, philos + i);
		i++;
	}
	// unlock philos here
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