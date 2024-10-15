/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:54:29 by crystal           #+#    #+#             */
/*   Updated: 2024/10/15 15:59:58 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_philo_data(t_data *data, int i)
{
	data->philo[i].id = i + 1;
	data->philo[i].nb_times_eat = 0;
	data->philo[i].data = data;
	data->philo[i].eat = 1;
	data->philo[i].dead = &data->dead;
	data->philo[i].start_time = get_current_time();
	data->philo[i].last_meal = get_current_time();
}

int	dead_philo_monitoring(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_lock);
	if ((get_current_time() - philo->last_meal) > philo->data->t_die)
	{
		pthread_mutex_unlock(&philo->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_lock);
	return (0);
}

int	dead_one(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].data->nb)
	{
		if (dead_philo_monitoring(&philo[i]))
		{
			ft_print("died", &philo[i], philo[i].id);
			pthread_mutex_lock(&philo[0].data->dead_lock);
			philo[0].data->dead = 1;
			pthread_mutex_unlock(&philo[0].data->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	eat_reached(t_philo *philo)
{
	int	complete_meals;
	int	i;

	complete_meals = 0;
	i = 0;
	if (philo->data->m_eat == -1)
		return (0);
	while (i < philo->data->nb)
	{
		pthread_mutex_lock(&philo[i].eat_lock);
		if (philo[i].nb_times_eat >= philo->data->m_eat)
			complete_meals++;
		pthread_mutex_unlock(&philo[i].eat_lock);
		i++;
	}
	if (complete_meals >= philo->data->nb)
	{
		pthread_mutex_lock(&philo[0].data->dead_lock);
		philo[0].data->dead = 1;
		pthread_mutex_unlock(&philo[0].data->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitoring(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (dead_one(philo) == 1 || eat_reached(philo) == 1)
			break ;
	}
	return (data);
}
