/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_loose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 04:22:08 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/15 12:48:41 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	defeat_screen(t_game *game)
{
	const int	area_size = (W_WIDTH / 3.2f);
	const int	font_size = area_size / 60;

	draw_trect(game->data_img, get_rect(0, 0, W_WIDTH, W_HEIGHT), MLX_BLACK);
	str_put(game, get_text("you loose!", font_size, MLX_RED,
			get_rect(W_WIDTH / 2 - (area_size / 2),
				W_HEIGHT / 2 - (font_size * 5), area_size, area_size / 6)));
	str_put(game, get_text("(press space to retry)", 5, MLX_GREY,
			get_rect(W_WIDTH / 2 - (area_size / 2),
				W_HEIGHT / 2 + (font_size * 5), area_size, area_size / 6)));
}

void	victory_screen(t_game *game)
{
	const t_uint	area_size = (t_uint)(W_WIDTH / 3.2f);
	const t_uint	font_size = (t_uint)area_size / 60;

	draw_frect(game->data_img, get_rect(0, 0, W_WIDTH, W_HEIGHT), MLX_BLACK);
	print_score(game, area_size, font_size);
	put_endtimer(game, font_size, get_rect(W_WIDTH / 2 - (area_size / 4),
			(W_HEIGHT / 4) - ((font_size * 7) / 2),
			area_size / 2, font_size * 7));
	str_put(game, get_text("you win!", font_size, MLX_GREEN,
			get_rect(W_WIDTH / 2 - (area_size / 2),
				W_HEIGHT / 2 - (font_size * 5), area_size, area_size / 6)));
	str_put(game, get_text("(press space to retry)", font_size / 2, MLX_GREY,
			get_rect(W_WIDTH / 2 - area_size / 2,
				W_HEIGHT / 2 + (5 * (font_size * 5)), area_size,
				area_size / 6)));
}

int	is_win(t_game *game)
{
	const char	cell = game->data_desc->map[(int)(game->player->y
			/ BLOCK)][(int)(game->player->x / BLOCK)];

	if (cell == 'X')
	{
		game->start = 3;
		stop_thread(game);
		return (TRUE);
	}
	return (FALSE);
}
