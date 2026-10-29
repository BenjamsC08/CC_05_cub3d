/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:59:37 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 13:18:34 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_uint	get_current_time(void)
{
	struct timeval	current_time;
	t_uint			out;

	gettimeofday(&current_time, NULL);
	out = current_time.tv_sec;
	return (out);
}

int	set_start_time(t_game *game)
{
	pthread_mutex_lock(game->timer->mtx_time);
	if (!game->timer->start_time)
		game->timer->start_time = get_current_time();
	return (pthread_mutex_unlock(game->timer->mtx_time), 1);
}

static int	draw_timer(t_game *game, t_rect frame, int size, t_uint time)
{
	char	*str;
	t_text	text;

	str = NULL;
	draw_trect(game->data_img, frame, MLX_GREY);
	draw_rect(game->data_img, frame, game->timer->color);
	str = time_to_str(time);
	if (!str)
		return (0);
	text = get_text(str, size, game->timer->color, frame);
	str_put(game, text);
	free(str);
	return (1);
}

void	put_timer(t_game *game, t_uint size, t_rect frame)
{
	t_uint	time;

	time = get_cd_time(game);
	game->timer->color = MLX_TIMER1;
	if (game->start && time == 0)
	{
		game->start = 2;
		game->minimap->disp_map = FALSE;
	}
	if (time < game->timer->max_time / 2 && time > game->timer->max_time / 4)
		game->timer->color = MLX_TIMER2;
	else if (time <= game->timer->max_time / 4)
		game->timer->color = MLX_TIMER3;
	if (!game->minimap->disp_map)
	{
		if (!draw_timer(game, frame, size, time))
			return ;
	}
}

void	put_endtimer(t_game *game, t_uint size, t_rect frame)
{
	t_uint	time;
	t_text	text;
	char	*str;

	time = get_cd_time(game);
	if (MAX_TIME < TIME_MAX)
		time = MAX_TIME - time;
	else
		time = TIME_MAX - time;
	draw_trect(game->data_img, frame, MLX_GREY);
	draw_rect(game->data_img, frame, game->timer->color);
	str = time_to_str(time);
	text = get_text(str, size, game->timer->color, frame);
	str_put(game, text);
	free(str);
}
