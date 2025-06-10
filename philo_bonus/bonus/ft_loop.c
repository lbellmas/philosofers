/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:44:13 by lbellmas          #+#    #+#             */
/*   Updated: 2025/06/10 15:39:15 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus.h"
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int	ft_loop(t_philo *philo)
{
	while (philo->n_meals != philo->rules->n_meals)
	{
		sem_wait(philo->rules->general);
		if (philo->dead || philo->rules->deaths)
			return (1);
		sem_post(philo->rules->general);
		ft_eat(&philo);
		sem_wait(philo->rules->general);
		if (philo->dead || philo->rules->deaths)
			return (1);
		sem_post(philo->rules->general);
		ft_sleep(&philo);
		sem_wait(philo->rules->general);
		if (philo->dead || philo->rules->deaths)
			return (1);
		sem_post(philo->rules->general);
		ft_think(&philo);
	}
	return (0);
}

void	ft_thread_destructor(t_philo *philosopher, int end)
{
	sem_close(philosopher->rules->forks);
	sem_close(philosopher->rules->general);
	free(philosopher->rules);
	free(philosopher);
	exit(end);
}

void	ft_philos_loop(t_philo *philosopher)
{
	sem_wait(philosopher->rules->general);
	sem_post(philosopher->rules->general);
	if (philosopher->n_philo % 2 != 0)
		usleep(50);
	if (philosopher->rules->n_philos % 2 != 0 && philosopher->n_philo
		== philosopher->rules->n_philos)
		usleep(50);
	philosopher->start_time = ft_get_time();
	if (philosopher->rules->n_philos == 1)
	{
		ft_lonely(philosopher->rules->death_time);
		ft_thread_destructor(philosopher, -2);
	}
	if (ft_loop(philosopher) == 1)
		ft_thread_destructor(philosopher, -1);
	ft_thread_destructor(philosopher, 0);
}
