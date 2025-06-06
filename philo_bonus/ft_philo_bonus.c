/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:02:16 by lbellmas          #+#    #+#             */
/*   Updated: 2025/06/06 15:43:42 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

void	ft_death(t_philo **philo)
{
	(*philo)->dead = 1;
	sem_wait((*philo)->rules->general);
	if ((*philo)->rules->deaths == 0)
		printf("%ld %d died\n", ft_get_time(), (*philo)->n_philo);
	(*philo)->rules->deaths += 1;
	sem_post((*philo)->rules->general);
}

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
		return (sem_post((*philo)->rules->forks), sem_post((*philo)->rules->forks), ft_death(philo));
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

void	ft_philos_loop(t_philo *philosopher)
{
	sem_wait(philosopher->rules->general);
	sem_post(philosopher->rules->general);	
	printf("filo start\n");
	if (philosopher->n_philo % 2 != 0)
		usleep(50);
	if (philosopher->rules->n_philos % 2 != 0 && philosopher->n_philo == philosopher->rules->n_philos)
		usleep(50);
	philosopher->start_time = ft_get_time();
	if (philosopher->rules->n_philos == 1)
	{
		ft_lonely(philosopher->rules->death_time);
		free(philosopher);
		exit(-2);
	}
	if (ft_loop(philosopher) == 1)
	{
		sem_post(philosopher->rules->general);
		free(philosopher);
		exit(-1);
	}
	printf("philosopher: %d ate %d times\n", philosopher->n_philo, philosopher->n_meals);
	free(philosopher);
	exit(0);
}

t_philo	**ft_philos_create(int n_philos, t_rules *rules)
{
	int	p;
	t_philo **philos;

	if (n_philos == 0)
		return (NULL);
	philos = (t_philo **)malloc(sizeof(t_philo *) * n_philos);
	p = 0;
	while (p < n_philos)
	{
		philos[p] = (t_philo *)malloc(sizeof(t_philo));
		(philos[p])->n_philo = p + 1;
		(philos[p])->dead = 0;
		(philos[p])->n_meals = 0;
		(philos[p])->rules = rules;
		(philos[p])->pid = fork();
		if (philos[p]->pid == 0)
			ft_philos_loop(philos[p]);
		p++;
	}
	sem_post(rules->general);
	printf ("finish create\n");
	return (philos);
}

t_philo	**ft_philos_destructor(t_philo **philos, int n_philos)
{
	int	p;

	p = 0;
	while (p++ < n_philos)
		wait(NULL);
	p = 0;
	while (p < n_philos)
	{
		free(philos[p]);
		philos[p++] = NULL;
	}
	free(philos);
	return (NULL);
}

t_rules	*ft_rule_maker(char **argv)
{
	t_rules	*rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (!rules)
		return (NULL);
	rules->deaths = 0;
	rules->diner_time = ft_atoi(argv[3]);
	rules->n_philos = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->sleepy_time = ft_atoi(argv[4]);
	sem_unlink("/forks");
	sem_unlink("/general");
	rules->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, rules->n_philos);
	rules->general = sem_open("/general", O_CREAT | O_EXCL, 0644, 0);
	if (argv[5])
		rules->n_meals = ft_atoi(argv[5]);
	else
		rules->n_meals = -1;
	return (rules);
}

int	main(int argc, char **argv)
{
	t_philo	**philos;
	t_rules	*rules;

	if (argc > 6 || argc < 5)
		return (printf("invalid args\n"), 0);
	rules = ft_rule_maker(argv);
	if (!rules)
		return (0);
	philos = ft_philos_create(ft_atoi(argv[1]), rules);
	if (!philos)
		return (printf("no philosophers\n"), 0);
	philos = ft_philos_destructor(philos, rules->n_philos);
	free(rules);
	rules = NULL;
	return (printf("end\n"), 0);
}
