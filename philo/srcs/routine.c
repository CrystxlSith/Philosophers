/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:02:24 by crystal           #+#    #+#             */
/*   Updated: 2024/10/15 15:58:47 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	think_rest(t_philo *data)
{
	if (!dead_philo(data))
	{
		ft_print("is sleeping", data, data->id);
		ft_usleep(data->data->t_sleep);
		ft_print("is thinking", data, data->id);
	}
}

int	dead_philo(t_philo *info)
{
	if (info == NULL)
		return (1);
	pthread_mutex_lock(&info->data->dead_lock);
	if (info->data->dead == 1)
	{
		pthread_mutex_unlock(&info->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&info->data->dead_lock);
	return (0);
}

void	eat(t_philo *info)
{
	if (info->data->nb == 1 && solo_philo(info))
		return ;
	else if (info->id % 2 == 0)
		pair(info);
	else
		impair(info);
	info->eat = 1;
	ft_print("is eating", info, info->id);
	pthread_mutex_lock(&info->eat_lock);
	info->last_meal = get_current_time();
	info->nb_times_eat += 1;
	pthread_mutex_unlock(&info->eat_lock);
	ft_usleep(info->data->t_eat);
	info->eat = 0;
	if (info->id % 2 == 0)
	{
		pthread_mutex_unlock(&info->l_fork);
		pthread_mutex_unlock(info->r_fork);
	}
	else
	{
		pthread_mutex_unlock(info->r_fork);
		pthread_mutex_unlock(&info->l_fork);
	}
}

void	*routine(void *data)
{
	t_philo	*info;

	info = (t_philo *)data;
	if (info->id % 2 == 0)
		ft_usleep(1);
	while (!dead_philo(info))
	{
		eat(info);
		think_rest(info);
	}
	return (data);
}
