/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 23:24:29 by crystal           #+#    #+#             */
/*   Updated: 2024/10/15 15:59:38 by jopfeiff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	init_philo(t_data *data)
{
	int			i;
	pthread_t	veryfier;

	i = 0;
	while (i < data->nb)
	{
		init_philo_data(data, i);
		pthread_create(&(data->philo[i].thread), \
		NULL, &routine, &(data->philo[i]));
		i++;
	}
	pthread_create(&veryfier, NULL, &monitoring, data->philo);
	if (pthread_join(veryfier, NULL) != 0)
		ft_error("Error joining veryfier");
	i = 0;
	while (i < data->nb)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			ft_error("Errror joining threads");
		i++;
	}
}

void	init_data(t_data *data, char *argv[])
{
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	data->nb = ft_atol(argv[1]);
	data->philo = malloc(sizeof(t_philo) * data->nb);
	data->t_die = ft_atol(argv[2]);
	data->t_eat = ft_atol(argv[3]);
	data->t_sleep = ft_atol(argv[4]);
	data->dead = 0;
	if (argv[5])
		data->m_eat = ft_atol(argv[5]);
	else
		data->m_eat = -1;
}

void	check_arg(int ac, char *av[])
{
	int	i;
	int	j;

	i = 1;
	if (ac != 6 && ac != 5)
		ft_error("Invalid number of arguments\n");
	while (av[i])
	{
		j = 0;
		if (ft_atol(av[i]) < 0)
			ft_error("Invalid argument\n");
		if (ft_strlen(av[i]) > 10)
			ft_error("Invalid argument\n");
		if (ft_atol(av[i]) > INT_MAX)
			ft_error("Invalid argument\n");
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				ft_error("Invalid argument\n");
			j++;
		}
		i++;
	}
}

void	fork_init(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb)
	{
		if (i == data->nb - 1)
			data->philo[i].r_fork = &data->philo[0].l_fork;
		else
			data->philo[i].r_fork = &data->philo[i + 1].l_fork;
		pthread_mutex_init(&data->philo[i].l_fork, NULL);
		pthread_mutex_init(&data->philo[i].eat_lock, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;

	check_arg(argc, argv);
	init_data(&data, argv);
	fork_init(&data);
	init_philo(&data);
	free_destroy(&data);
	return (0);
}
