/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:36:56 by lbellmas          #+#    #+#             */
/*   Updated: 2025/06/03 14:45:22 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <pthread.h>
#include <unistd.h>

void	ft_odd_number(t_philo **philosofer)
{
	pthread_mutex_lock((*philosofer)->l_fork);
	pthread_mutex_lock(&(*philosofer)->rules->general);
	if ((*philosofer)->rules->deaths == 0)
		printf("%ld %d took a fork\n", ft_get_time(), (*philosofer)->n_philo);
	pthread_mutex_unlock(&(*philosofer)->rules->general);
	pthread_mutex_lock(&(*philosofer)->r_fork);
	if ((ft_get_time() - (*philosofer)->start_time)
		>= (*philosofer)->rules->death_time)
		return (pthread_mutex_unlock(&(*philosofer)->r_fork),
			pthread_mutex_unlock((*philosofer)->l_fork), ft_death(philosofer));
	pthread_mutex_lock(&(*philosofer)->rules->general);
	if ((*philosofer)->rules->deaths == 0)
		printf("%ld %d took a fork\n", ft_get_time(), (*philosofer)->n_philo);
	pthread_mutex_unlock(&(*philosofer)->rules->general);
}

void	ft_even_number(t_philo **philosofer)
{
	pthread_mutex_lock(&(*philosofer)->r_fork);
	pthread_mutex_lock(&(*philosofer)->rules->general);
	if ((*philosofer)->rules->deaths == 0)
		printf("%ld %d took a fork\n", ft_get_time(), (*philosofer)->n_philo);
	pthread_mutex_unlock(&(*philosofer)->rules->general);
	pthread_mutex_lock((*philosofer)->l_fork);
	if ((ft_get_time() - (*philosofer)->start_time)
		>= (*philosofer)->rules->death_time)
		return (pthread_mutex_unlock((*philosofer)->l_fork),
			pthread_mutex_unlock(&(*philosofer)->r_fork), ft_death(philosofer));
	pthread_mutex_lock(&(*philosofer)->rules->general);
	if ((*philosofer)->rules->deaths == 0)
		printf("%ld %d took a fork\n", ft_get_time(), (*philosofer)->n_philo);
	pthread_mutex_unlock(&(*philosofer)->rules->general);
}

void	ft_eat(t_philo **philosofer)
{
	if ((*philosofer)->rules->n_philos % 2 != 0
		&& (ft_get_time() - (*philosofer)->start_time)
		< ((*philosofer)->rules->death_time / 3 * 2))
		usleep(100);
	if ((*philosofer)->n_philo % 2 != 0)
		ft_odd_number(philosofer);
	else
		ft_even_number(philosofer);
	if ((ft_get_time() - (*philosofer)->start_time)
		>= (*philosofer)->rules->death_time)
		return (ft_death(philosofer));
	(*philosofer)->start_time = ft_get_time();
	pthread_mutex_lock(&(*philosofer)->rules->general);
	if ((*philosofer)->rules->deaths == 0)
		printf("%ld %d is eating\n", ft_get_time(), (*philosofer)->n_philo);
	pthread_mutex_unlock(&(*philosofer)->rules->general);
	usleep((*philosofer)->rules->diner_time * 1000);
	pthread_mutex_unlock(&(*philosofer)->r_fork);
	pthread_mutex_unlock((*philosofer)->l_fork);
	(*philosofer)->n_meals += 1;
}

void	ft_lonely(int death_time)
{
	printf("%ld %d has taken a fork\n", ft_get_time(), 1);
	usleep(death_time * 1000);
	printf("%ld %d died\n", ft_get_time(), 1);
}
