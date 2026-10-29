/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:46:06 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 13:12:49 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	running(t_game *game)
{
	pthread_mutex_lock(game->timer->mtx_run);
	if (game->timer->run == FALSE)
		return (pthread_mutex_unlock(game->timer->mtx_run), FALSE);
	return (pthread_mutex_unlock(game->timer->mtx_run), TRUE);
}

void	*time_job(void *ptr_game)
{
	t_game	*game;

	game = (t_game *)ptr_game;
	while (42)
	{
		usleep(100000);
		if (!running(game))
			return (NULL);
		pthread_mutex_lock(game->timer->mtx_time);
		if (!game->timer->start_time)
		{
			pthread_mutex_unlock(game->timer->mtx_time);
			continue ;
		}
		game->timer->time = get_current_time() - game->timer->start_time;
		if (game->timer->time >= game->timer->max_time)
			return (pthread_mutex_unlock(game->timer->mtx_time),
				pthread_mutex_destroy(game->timer->mtx_run),
				pthread_mutex_destroy(game->timer->mtx_time), NULL);
		pthread_mutex_unlock(game->timer->mtx_time);
	}
	pthread_mutex_destroy(game->timer->mtx_run);
	pthread_mutex_destroy(game->timer->mtx_time);
}

int	start_time(t_game *game)
{
	game->timer = ft_gcalloc(game->gc_head, sizeof(t_timer));
	if (!game->timer)
		return (0);
	game->timer->mtx_time = ft_gcalloc(game->gc_head, sizeof(t_mtx));
	if (!game->timer->mtx_time)
		return (0);
	game->timer->mtx_run = ft_gcalloc(game->gc_head, sizeof(t_mtx));
	if (!game->timer->mtx_run)
		return (0);
	game->timer->run = TRUE;
	game->timer->start_time = 0;
	if (MAX_TIME > TIME_MAX)
		game->timer->max_time = TIME_MAX;
	else
		game->timer->max_time = MAX_TIME;
	if (pthread_mutex_init(game->timer->mtx_time, NULL) != 0)
		return (0);
	if (pthread_mutex_init(game->timer->mtx_run, NULL) != 0)
		return (pthread_mutex_destroy(game->timer->mtx_time), 0);
	if (pthread_create(&game->timer->thread, NULL, time_job, (void *)game) != 0)
		return (pthread_mutex_destroy(game->timer->mtx_run),
			pthread_mutex_destroy(game->timer->mtx_time), 0);
	return (1);
}

t_uint	get_cd_time(t_game *game)
{
	t_uint	time;

	pthread_mutex_lock(game->timer->mtx_time);
	if (!game->timer->start_time)
		time = game->timer->max_time;
	else
		time = game->timer->max_time - game->timer->time;
	pthread_mutex_unlock(game->timer->mtx_time);
	return (time);
}

char	*time_to_str(t_uint time)
{
	char	str[6];
	char	*s;

	str[0] = (time / 600) + 48;
	str[1] = ((time / 60) % 10) + 48;
	str[2] = ':';
	str[3] = ((time % 60) / 10 % 10) + 48;
	str[4] = ((time % 60) % 10) + 48;
	s = ft_strdup(str);
	if (!s)
		return (NULL);
	return (s);
}
