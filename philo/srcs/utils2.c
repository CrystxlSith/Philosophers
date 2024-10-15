/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 07:48:26 by jopfeiff          #+#    #+#             */
/*   Updated: 2024/10/04 08:01:57 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_print_eat(char *str, t_philo *info)
{
	size_t	a_time;

	pthread_mutex_lock(&info->data->write_lock);
	a_time = get_current_time() - info->start_time;
	if (!dead_philo(info))
		printf("%zu %s %d times\n", a_time, str, info->data->m_eat);
	pthread_mutex_unlock(&info->data->write_lock);
}

void	ft_print(char *str, t_philo *info, int id)
{
	size_t	a_time;

	pthread_mutex_lock(&info->data->write_lock);
	a_time = get_current_time() - info->start_time;
	if (!dead_philo(info))
		printf("%zu %d %s\n", a_time, id, str);
	pthread_mutex_unlock(&info->data->write_lock);
}

void	pair(t_philo *info)
{
	pthread_mutex_lock(info->r_fork);
	ft_print("has taken a fork", info, info->id);
	pthread_mutex_lock(&info->l_fork);
	ft_print("has taken a fork", info, info->id);
}

void	impair(t_philo *info)
{
	pthread_mutex_lock(&info->l_fork);
	ft_print("has taken a fork", info, info->id);
	pthread_mutex_lock(info->r_fork);
	ft_print("has taken a fork", info, info->id);
}

int	solo_philo(t_philo *info)
{
	pthread_mutex_lock(info->r_fork);
	ft_print("has taken a fork", info, info->id);
	ft_usleep(info->data->t_die);
	pthread_mutex_unlock(info->r_fork);
	return (1);
}
