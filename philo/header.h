/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:28:32 by lbellmas          #+#    #+#             */
/*   Updated: 2025/06/03 15:35:43 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h> 

typedef struct s_rules
{
	pthread_mutex_t	general;
	int				diner_time;
	int				n_philos;
	int				death_time;
	int				sleepy_time;
	int				n_meals;
	int				deaths;
	long			sim_start;
}	t_rules;

typedef struct s_philo
{
	int					n_philo;
	pthread_mutex_t		r_fork;
	pthread_mutex_t		*l_fork;
	int					dead;
	int					n_meals;
	long				start_time;
	pthread_t			thread;
	t_rules				*rules;
}	t_philo;

long	ft_get_time(void);
int		ft_atoi(const char *nptr);
void	ft_death(t_philo **philosofer);
void	ft_think(t_philo **philosofer);
void	ft_sleep(t_philo **philosofer);
void	ft_odd_number(t_philo **philosofer);
void	ft_even_number(t_philo **philosofer);
void	ft_eat(t_philo **philosofer);
void	ft_lonely(int death_time);
int		ft_loop(t_philo *philosofer);
void	*ft_philo_loop(void *cast);

#endif
