/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:02:16 by lbellmas          #+#    #+#             */
/*   Updated: 2025/06/10 15:39:06 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header_bonus.h"
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

t_philo	*ft_clean_philos(t_philo **philos, int n_philo)
{
	int		p;
	t_philo	*save;

	p = 0;
	while (philos && p < n_philo)
	{
		free(philos[p]);
		p++;
	}
	save = philos[p];
	free(philos);
	return (save);
}

t_philo	**ft_philos_create(int n_philos, t_rules *rules)
{
	int		p;
	t_philo	**philos;

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
			ft_philos_loop(ft_clean_philos(philos, p));
		p++;
	}
	sem_post(rules->general);
	return (philos);
}

t_philo	**ft_philos_destructor(t_philo **philos, int n_philos)
{
	int	p;
	int	status;

	p = 0;
	status = 0;
	while (p++ < n_philos && status != -1)
	{
		wait(&status);
		if (status != 0)
			break ;
	}
	if (status != 0)
		ft_kill_all(philos, n_philos);
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
	sem_close(rules->forks);
	sem_close(rules->general);
	sem_unlink("/forks");
	sem_unlink("/general");
	free(rules);
	rules = NULL;
	return (0);
}
