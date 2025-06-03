/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:25:03 by lbellmas          #+#    #+#             */
/*   Updated: 2025/06/03 15:35:25 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <pthread.h>
#include <unistd.h>

t_philo	**ft_fork_set(t_philo **philos, int num_philos)
{
	int	p;

	p = 0;
	while (p < num_philos)
	{
		if (p == 0)
			(philos[p])->l_fork = &(philos[num_philos - 1])->r_fork;
		else
			(philos[p])->l_fork = &(philos[p - 1])->r_fork;
		pthread_create(&(philos[p])->thread, NULL, ft_philo_loop, philos[p]);
		p++;
	}
	return (philos);
}

t_philo	**ft_philos_create(int num_philos, t_rules *rules)
{
	int		p;
	t_philo	**philos;

	if (num_philos == 0)
		return (NULL);
	pthread_mutex_lock(&rules->general);
	philos = (t_philo **)malloc(sizeof(t_philo *) * num_philos);
	p = 0;
	while (p < num_philos)
	{
		philos[p] = (t_philo *)malloc(sizeof(t_philo));
		(philos[p])->n_philo = p + 1;
		(philos[p])->dead = 0;
		(philos[p])->n_meals = 0;
		pthread_mutex_init(&(philos[p])->r_fork, NULL);
		(philos[p])->rules = rules;
		p++;
	}
	philos = ft_fork_set(philos, num_philos);
	rules->sim_start = ft_get_time();
	pthread_mutex_unlock(&rules->general);
	return (philos);
}

t_philo	**ft_philos_destructor(t_philo **philos, int n_philos)
{
	int	p;

	p = 0;
	while (p < n_philos)
		pthread_join((philos[p++])->thread, NULL);
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
	rules->deaths = 0;
	pthread_mutex_init(&rules->general, NULL);
	rules->diner_time = ft_atoi(argv[3]);
	rules->n_philos = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->sleepy_time = ft_atoi(argv[4]);
	if (argv[5])
		rules->n_meals = ft_atoi(argv[5]);
	else
		rules->n_meals = -1;
	return (rules);
}

int	main(int argc, char **argv)
{
	t_philo	**philosofers;
	t_rules	*rules;

	if (argc > 6 || argc < 5)
		return (printf("invalid args\n"), 0);
	rules = ft_rule_maker(argv);
	philosofers = ft_philos_create(ft_atoi(argv[1]), rules);
	if (!philosofers)
		return (printf("no philosophers\n"), 0);
	philosofers = ft_philos_destructor(philosofers, rules->n_philos);
	free (rules);
	rules = NULL;
	return (0);
}
