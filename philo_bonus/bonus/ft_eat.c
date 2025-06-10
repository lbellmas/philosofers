/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:39:56 by lbellmas          #+#    #+#             */
/*   Updated: 2025/06/09 13:49:50 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus.h"
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_taking_forks(t_philo **philo)
{
	sem_wait((*philo)->rules->forks);
	sem_wait((*philo)->rules->general);
	if ((*philo)->rules->deaths == 0)
		printf("%ld %d took a fork\n", ft_get_time(), (*philo)->n_philo);
	sem_post((*philo)->rules->general);
	sem_wait((*philo)->rules->forks);
	if ((ft_get_time() - (*philo)->start_time
			>= (*philo)->rules->death_time))
		return (sem_post((*philo)->rules->forks), ft_death(philo));
	sem_wait((*philo)->rules->general);
	if ((*philo)->rules->deaths == 0)
		printf("%ld %d took a fork\n", ft_get_time(), (*philo)->n_philo);
	sem_post((*philo)->rules->general);
}

void	ft_eat(t_philo **philo)
{
	if ((*philo)->rules->n_philos % 2 != 0
		&& (ft_get_time() - (*philo)->start_time)
		< ((*philo)->rules->death_time / 3 * 2))
		usleep(100);
	ft_taking_forks(philo);
	if ((ft_get_time() - (*philo)->start_time)
		>= (*philo)->rules->death_time)
		return (sem_post((*philo)->rules->forks),
			sem_post((*philo)->rules->forks), ft_death(philo));
	(*philo)->start_time = ft_get_time();
	sem_wait((*philo)->rules->general);
	if ((*philo)->rules->deaths == 0)
		printf("%ld %d is eating\n", ft_get_time(), (*philo)->n_philo);
	sem_post((*philo)->rules->general);
	usleep((*philo)->rules->diner_time * 1000);
	sem_post((*philo)->rules->forks);
	sem_post((*philo)->rules->forks);
	(*philo)->n_meals += 1;
}

void	ft_lonely(int death_time)
{
	printf("%ld %d has taken a fork\n", ft_get_time(), 1);
	usleep(death_time * 1000);
	printf("%ld %d died\n", ft_get_time(), 1);
}
