/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:25:03 by lbellmas          #+#    #+#             */
/*   Updated: 2025/05/16 18:20:42 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_philo_loop(phtread_t *philosofer)
{
	while (!philosofer->dead || philosofer->n_meals == philosofer->rules->n_meals)
	{
		check_death;
		eat;
		sleep;
		check_death;
		think;
	}
	if (philosofer->dead)
		printf("philosofer number: %d died\n", philosofer->n_philo);
	else
		printf("philosofer number: %d ate %d times", philosofer->n_meals);
}

pthread_t	*ft_philos_create(int num_philos, t_rules *rules)
{
	int	p;
	t_philo	**philos;

	if (num_philos == 0)
		return (NULL);
	philos = (pthread_t **)malloc(sizeof(pthread_t *) * num_philos);
	p = 0;
	while (p < num_philos)
	{
		philos[p] = (pthread_t *)malloc(sizeof(pthread_t));
		(philos[p])->n_philo = p + 1;
		(philos[p])->dead = 0;
		(philos[p])->n_meals = 0;
		pthread_mutex_init(&(philos[p])->r_fork, NULL);
		(philos[p])->rules = rules;
		p++;
	}
	p = 0;
	while (p < num_philos)
	{
		if (p == 0)
			(philos[p])->l_fork = (philos[num_philos - 1])->r_fork;
		else
			(philos[p])->l_fork = (philos[p - 1])->r_fork;
	//	(philos[p])->start_time = gettimeofday();
		pthread_create((philos[p])->thread, NULL, ft_philo_loop, philo[p]);
		p++;
	}
}

pthread_t	*ft_philos_destructor(phtread_t **philos)
{
	int	p;

	p = 0;
	while (philos[p])
	{
		phtread_join((philos[p])->thread, NULL);
		free(philos[p]);
		philos[p] = NULL;
		p++;
	}
	free(philos);
	return (NULL);
}

t_rules	*ft_rule_maker(char **argv)
{
	t_rules	*rules;

	rules = (t_rules *)malloc(sizeof(t_rules));
	rules->diner_time = ft_atoi(argv[3]);
	rules->n_philos = ft_atoi(argv[1]);
	rules->death_time = ft_atoi(argv[2]);
	rules->sleepy_time = ft_atoi(argv[4]);
	if (argv[5])
		rules->n_meals = ft_atoi(argv[5]);
	else
		rules->n_meals = 0;
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
		return (printf("no philosofers\n"), 0);
	philosofers = ft_philos_destructor(philosofers);
	return (printf("finish\n"), 0);
}
