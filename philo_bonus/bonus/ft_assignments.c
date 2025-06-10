/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assignments.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:42:13 by lbellmas          #+#    #+#             */
/*   Updated: 2025/06/10 15:37:37 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus.h"
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_kill_all(t_philo **philos, int n_philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		kill(philos[i]->pid, SIGKILL);
		i++;
	}
}

void	ft_death(t_philo **philo)
{
	(*philo)->dead = 1;
	sem_wait((*philo)->rules->general);
	if ((*philo)->rules->deaths == 0)
		printf("%ld %d died\n", ft_get_time(), (*philo)->n_philo);
	(*philo)->rules->deaths += 1;
	sem_post((*philo)->rules->general);
}

void	ft_think(t_philo **philo)
{
	if ((ft_get_time() - (*philo)->start_time)
		>= (*philo)->rules->death_time)
		return (ft_death(philo));
	sem_wait((*philo)->rules->general);
	if ((*philo)->rules->deaths == 0)
		printf("%ld %d is thinking\n", ft_get_time(), (*philo)->n_philo);
	sem_post((*philo)->rules->general);
}

void	ft_sleep(t_philo **philo)
{
	if ((ft_get_time() - (*philo)->start_time)
		>= (*philo)->rules->death_time)
		return (ft_death(philo));
	sem_wait((*philo)->rules->general);
	if ((*philo)->rules->deaths == 0)
		printf("%ld %d is sleeping\n", ft_get_time(), (*philo)->n_philo);
	sem_post((*philo)->rules->general);
	usleep((*philo)->rules->sleepy_time * 1000);
}
