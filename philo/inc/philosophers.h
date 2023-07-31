/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrask <rrask@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 21:09:28 by rrask             #+#    #+#             */
/*   Updated: 2023/07/31 15:16:33 by rrask            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# define PHILOSOPHERS_H
# define RAS_MAX 2147483647
# define RAS_MIN -2147483648
# define ARG_MIN 5
# define ARG_MAX 6
# define MAX_PHILO 250

typedef struct s_attr
{
	size_t			start_time;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
}					t_attr;

typedef struct s_philo
{
	int				id;
	int				is_dead;
	int				times_eaten;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*gate;
	pthread_mutex_t	*death;
	pthread_mutex_t	*print;
	size_t			last_supper;
	t_attr			*attr;
}					t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	forks[MAX_PHILO];
	pthread_mutex_t	deaths[MAX_PHILO];
	pthread_mutex_t	gate;
	pthread_mutex_t	print;
}					t_mutex;

/*attr.c*/
int					attr_set(t_attr *attr, int argc, char **argv);

/*philos.c*/
void				*philo_run(void *this);
int					philo_check_death(t_philo *philo);

/*philos_utils.c*/
void				philos_join(t_philo *philos);
void				philos_spawn(t_philo *philos, pthread_mutex_t *gate);
void				philos_init(t_philo *philos, t_attr *attrib,
						t_mutex *mutex);

/*governor.c*/
void				governor(t_philo *philos, t_attr *attr);

/* philo_actions.c */
void				eat(t_philo *philo, size_t time_to_eat);
void				hit_the_hay(t_philo *philo);
void				think(t_philo *philo);

/*mutex.c*/
int					mutex_init(int num_philos, t_mutex *mutex);
int					mutex_destroy(int num_philos, t_mutex *mutex);

/*utils.c*/
size_t				get_time_ms(void);
int					ft_usleep(t_philo *philo, size_t time_to_snooze);
int					ft_strlen(char *str);
int					ft_atoi(const char *str);

/*printing.c*/
void				print_state(t_philo *philo, char *string);
void				print_death(t_philo philo);

/*errors.c*/
void				error_handler(char *str);

#endif
