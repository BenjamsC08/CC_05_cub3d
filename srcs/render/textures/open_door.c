/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 08:17:42 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/13 13:33:46 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	door_front_check_cell(t_game *game, t_vec *pos, int *mx, int *my)
{
	int		grid_x;
	int		grid_y;
	char	tile;

	grid_x = (int)(pos->x / BLOCK);
	grid_y = (int)(pos->y / BLOCK);
	if (grid_x < 0 || grid_y < 0)
		return (-1);
	if (grid_y >= game->data_desc->nb_line
		|| grid_x >= game->data_desc->line_length)
		return (-1);
	tile = game->data_desc->map[grid_y][grid_x];
	if (tile == '1')
		return (-1);
	if (tile == '2')
	{
		*mx = grid_x;
		*my = grid_y;
		return (1);
	}
	return (0);
}

int	door_find_in_front(t_game *game, int *mx, int *my)
{
	float	distance;
	t_vec	forward_dir;
	t_vec	check_pos;
	int		cell_state;

	forward_dir.x = cosf(game->player->angle);
	forward_dir.y = sinf(game->player->angle);
	distance = INTERACT_STEP * BLOCK;
	while (distance <= INTERACT_DIST * BLOCK)
	{
		check_pos.x = game->player->x + forward_dir.x * distance;
		check_pos.y = game->player->y + forward_dir.y * distance;
		cell_state = door_front_check_cell(game, &check_pos, mx, my);
		if (cell_state != 0)
			return (cell_state > 0);
		distance += (INTERACT_STEP * BLOCK);
	}
	return (0);
}

void	door_try_open(t_game *game, int door_x, int door_y)
{
	if (game->data_desc->door_anim_on == TRUE)
		return ;
	if (game->data_desc->map[door_y][door_x] != '2')
		return ;
	game->data_desc->door_anim_on = TRUE;
	game->data_desc->door_anim_frame = 0;
	game->data_desc->door_x = door_x;
	game->data_desc->door_y = door_y;
	game->data_desc->door_next_ms = now_ms() + DOOR_FRAME_MS;
}

void	door_anim_update(t_game *game)
{
	unsigned int	now;
	t_data_desc		*data;

	if (game->data_desc->door_anim_on == 0)
		return ;
	now = now_ms();
	if (now < game->data_desc->door_next_ms)
		return ;
	data = game->data_desc;
	data->door_anim_frame++;
	data->door_next_ms += DOOR_FRAME_MS;
	if (data->door_anim_frame >= DOOR_FRAMES)
	{
		data->map[data->door_y][data->door_x] = '3';
		data->door_anim_on = 0;
	}
}

t_tex	*select_door_texture(t_game *game, t_ray *ray)
{
	int	index;

	if (game->data_desc->door_anim_on == TRUE
		&& ray->mapx == game->data_desc->door_x
		&& ray->mapy == game->data_desc->door_y)
	{
		if (game->data_desc->door_anim_frame <= 0)
			return (&game->assets.tex[TEX_DOOR_CLOSED]);
		index = TEX_DOOR_CLOSED1 + (game->data_desc->door_anim_frame - 1);
		if (index > TEX_DOOR_CLOSED7)
			index = TEX_DOOR_CLOSED7;
		return (&game->assets.tex[index]);
	}
	return (&game->assets.tex[TEX_DOOR_CLOSED]);
}
