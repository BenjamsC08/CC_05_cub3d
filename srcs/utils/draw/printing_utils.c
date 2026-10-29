/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 13:33:20 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/15 12:56:31 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_action(t_game *game, t_uint size, int color, char *s)
{
	t_rect			area;
	const int		vertical_offset = 42;
	const int		margin = 20;

	area.x = (W_WIDTH / 2) - (((5 * size) * (ft_strlen(s)) / 2));
	area.y = (W_HEIGHT / 2) - (5 * (size / 2)) + vertical_offset;
	area.w = (5 * size) * ft_strlen(s) + margin;
	area.h = 5 * size + (margin / 2);
	draw_trect(game->data_img, area, MLX_GREY);
	str_put(game, get_text(s, size, color, area));
}

void	draw_interact_hint(t_game *game)
{
	int	door_x;
	int	door_y;

	if (game->data_desc->door_anim_on == TRUE)
		return ;
	if (door_find_in_front(game, &door_x, &door_y))
		print_action(game, 2, MLX_WHITE, "press e");
}

static void	print_best_time_msg(t_game *game, char **msg,
	const int area_size, const int font_size)
{
	*msg = ft_strjoin("new best time : ",
			game->data_desc->last_best_time);
	if (!*msg)
		return ;
	*msg = ft_strfjoin(*msg, " ! last was ");
	if (!*msg)
		return ;
	*msg = ft_strfjoin(*msg, game->data_desc->prev_best_time);
	if (!*msg)
		return ;
	*msg = ft_strfjoin(*msg, "... gg !");
	if (!*msg)
		return ;
	str_put(game, get_text(*msg, font_size / 2, MLX_GREY,
			get_rect(W_WIDTH / 2 - area_size / 2,
				W_HEIGHT / 2 + (font_size * 5),
				area_size, area_size / 6)));
}

static void	print_not_best_time_msg(t_game *game, char **msg,
	const int area_size, const int font_size)
{
	*msg = ft_strjoin("you win, but it is not enough !"
			" best time : ", game->data_desc->prev_best_time);
	if (!*msg)
		return ;
	str_put(game, get_text(*msg, font_size / 2, MLX_GREY,
			get_rect(W_WIDTH / 2 - area_size / 2,
				W_HEIGHT / 2 + (font_size * 5),
				area_size, area_size / 6)));
}

void	print_score(t_game *game, const int area_size, const int font_size)
{
	char	*msg;

	msg = NULL;
	if (game->data_desc->score_checked == FALSE)
	{
		(void)handle_score_history(game);
		game->data_desc->score_checked = TRUE;
	}
	if (game->data_desc->prev_best_time)
	{
		if (game->data_desc->new_best_time)
			print_best_time_msg(game, &msg, area_size, font_size);
		else
			print_not_best_time_msg(game, &msg, area_size, font_size);
	}
	if (msg)
		free(msg);
}
