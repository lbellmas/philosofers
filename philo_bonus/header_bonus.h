/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:03:24 by lbellmas          #+#    #+#             */
/*   Updated: 2025/06/06 14:29:19 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_BONUS_H
# define FT_HEADER_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_rules
{
	sem_t		*general;
	sem_t		*forks;
	int			diner_time;
	int			n_philos;
	int			death_time;
	int			sleepy_time;
	int			n_meals;
	int			deaths;
	long		sim_start;
} t_rules;

typedef struct s_philo
{
	int			n_philo;
	int			dead;
	int			n_meals;
	long		start_time;
	int	pid;
	t_rules		*rules;
} t_philo;

long	ft_get_time(void);
int		ft_atoi(const char *nptr);

#endif
