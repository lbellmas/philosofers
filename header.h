/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:28:32 by lbellmas          #+#    #+#             */
/*   Updated: 2025/05/16 18:03:27 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H
# define FT_HEADER_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h> 

typedef struct s_philo
{
	int			n_philo;
	t_mtx		r_fork;
	t_mtx		*l_fork;
	int			dead;
	int			n_meals;
	int			start_time;
	pthread_t	thread;
	t_rules		*rules;
} t_philo;

typedef struct s_rules
{
	int		diner_time;
	int		n_philos;
	int		death_time;
	int		sleepy_time;
	int		n_meals;
} t_rules;

int	ft_atoi(const char *nptr);

#endif
