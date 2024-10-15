/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:27:09 by crystal           #+#    #+#             */
/*   Updated: 2024/10/04 07:54:51 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_destroy(t_data *data)
{
	long int	i;

	i = 0;
	while (i < data->nb)
	{
		pthread_mutex_destroy(data->philo[i].r_fork);
		pthread_mutex_destroy(&data->philo[i].eat_lock);
		i++;
	}
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	free(data->philo);
}
