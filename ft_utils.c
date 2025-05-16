/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbellmas <lbellmas@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:25:35 by lbellmas          #+#    #+#             */
/*   Updated: 2025/05/16 14:26:31 by lbellmas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	p;
	int	sign;
	int	num;

	sign = 1;
	p = 0;
	num = 0;
	while (nptr[p] == 32 || (nptr[p] >= 9 && nptr[p] <= 13))
		p++;
	if (nptr[p] == '-' || nptr[p] == '+')
	{
		if (nptr[p] == '-')
			sign = -sign;
		p++;
	}
	while (nptr[p] >= '0' && nptr[p] <= '9')
	{
		num = num * 10 + (nptr[p] - '0');
		p++;
	}
	return (num * sign);
}
