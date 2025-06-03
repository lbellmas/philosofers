/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:35:26 by lbellmas          #+#    #+#             */
/*   Updated: 2025/06/03 14:45:11 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include <pthread.h>
#include <unistd.h>

void	ft_death(t_philo **philosofer)
{
	(*philosofer)->dead = 1;
	pthread_mutex_lock(&(*philosofer)->rules->general);
	if ((*philosofer)->rules->deaths == 0)
		printf("%ld %d died\n", ft_get_time(), (*philosofer)->n_philo);
	(*philosofer)->rules->deaths += 1;
	pthread_mutex_unlock(&(*philosofer)->rules->general);
}

void	ft_think(t_philo **philosofer)
{
	if (ft_get_time() - (*philosofer)->start_time
		>= (*philosofer)->rules->death_time)
		return (ft_death(philosofer));
	pthread_mutex_lock(&(*philosofer)->rules->general);
	if ((*philosofer)->rules->deaths == 0)
		printf("%ld %d is thinking\n", ft_get_time(), (*philosofer)->n_philo);
	pthread_mutex_unlock(&(*philosofer)->rules->general);
}

void	ft_sleep(t_philo **philosofer)
{
	if ((ft_get_time() - (*philosofer)->start_time)
		>= (*philosofer)->rules->death_time)
		return (ft_death(philosofer));
	pthread_mutex_lock(&(*philosofer)->rules->general);
	if ((*philosofer)->rules->deaths == 0)
		printf("%ld %d is sleeping\n", ft_get_time(), (*philosofer)->n_philo);
	pthread_mutex_unlock(&(*philosofer)->rules->general);
	usleep((*philosofer)->rules->sleepy_time * 1000);
}

int	ft_loop(t_philo *philosofer)
{
	while (!philosofer->dead && philosofer->n_meals
		!= philosofer->rules->n_meals)
	{
		pthread_mutex_lock(&philosofer->rules->general);
		if (philosofer->dead || philosofer->rules->deaths)
			return (1);
		pthread_mutex_unlock(&philosofer->rules->general);
		ft_eat(&philosofer);
		pthread_mutex_lock(&philosofer->rules->general);
		if (philosofer->n_meals == philosofer->rules->n_meals
			&& philosofer->rules->n_meals != 0)
			return (1);
		pthread_mutex_unlock(&philosofer->rules->general);
		ft_sleep(&philosofer);
		pthread_mutex_lock(&philosofer->rules->general);
		if (philosofer->dead || philosofer->rules->deaths)
			return (1);
		pthread_mutex_unlock(&philosofer->rules->general);
		ft_think(&philosofer);
	}
	return (0);
}

void	*ft_philo_loop(void *cast)
{
	t_philo	*philosofer;

	philosofer = (t_philo *)cast;
	pthread_mutex_lock(&philosofer->rules->general);
	pthread_mutex_unlock(&philosofer->rules->general);
	if (philosofer->n_philo % 2 != 0)
		usleep(50);
	if (philosofer->rules->n_philos % 2 != 0 && philosofer->n_philo
		== philosofer->rules->n_philos)
		usleep(50);
	philosofer->start_time = ft_get_time();
	if (philosofer->rules->n_philos == 1)
		return (ft_lonely(philosofer->rules->death_time), NULL);
	if (ft_loop(philosofer) == 1)
		pthread_mutex_unlock(&philosofer->rules->general);
	if (philosofer->n_meals == philosofer->rules->n_meals)
	{
		pthread_mutex_lock(&philosofer->rules->general);
		if (philosofer->rules->deaths == 0)
			printf("philosofer number: %d ate %d times\n", philosofer->n_philo, philosofer->n_meals);
		pthread_mutex_unlock(&philosofer->rules->general);
	}
	return (NULL);
}
