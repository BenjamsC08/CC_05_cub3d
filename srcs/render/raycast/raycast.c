/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 23:31:42 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/13 08:45:28 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_blocked(t_game *game, float ray_x, float ray_y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)(ray_x / (float)BLOCK);
	grid_y = (int)(ray_y / (float)BLOCK);
	if (grid_x < 0 || grid_y < 0
		|| grid_y >= game->data_desc->nb_line
		|| grid_x >= game->data_desc->line_length)
		return (TRUE);
	if (game->data_desc->map[grid_y][grid_x] == '1'
		|| game->data_desc->map[grid_y][grid_x] == '2'
		|| game->data_desc->map[grid_y][grid_x] == 'X')
		return (TRUE);
	return (FALSE);
}

static void	cast_ray(t_game *game, float angle)
{
	t_vec	ray;
	t_vec	step;
	t_vec	screen;
	int		safety_counter;

	ray.x = game->player->x;
	ray.y = game->player->y;
	step.x = cosf(angle);
	step.y = sinf(angle);
	safety_counter = (int)sqrtf(W_WIDTH * W_WIDTH + W_HEIGHT * W_HEIGHT);
	while (safety_counter > 0 && !is_blocked(game, ray.x, ray.y))
	{
		screen = world_to_minimap(game, ray);
		ft_pixel_put(game->data_img, (int)screen.x, (int)screen.y, MLX_GREEN);
		ray.x += step.x;
		ray.y += step.y;
		safety_counter--;
	}
}

static void	draw_rays(t_game *game)
{
	const int	n_rays = 1000;
	const float	start_angle = game->player->angle
		- (FOV_DEG * DEGREE) * 0.5f;
	const float	angle_step = (FOV_DEG * DEGREE) / (float)n_rays;
	int			i;

	i = -1;
	while (++i < n_rays)
		cast_ray(game, start_angle + angle_step * (float)i);
}

void	draw_player(t_game *game)
{
	t_rect	player_rect;
	t_vec	screen;
	int		cell_w;
	int		cell_h;
	int		size;

	get_map_cell_size(game, &cell_w, &cell_h);
	screen.x = game->player->x;
	screen.y = game->player->y;
	screen = world_to_minimap(game, screen);
	size = cell_w;
	if (cell_h < size)
		size = cell_h;
	player_rect.w = size;
	player_rect.h = size;
	player_rect.x = (int)screen.x - (player_rect.w / 2);
	player_rect.y = (int)screen.y - (player_rect.h / 2);
	draw_rays(game);
	draw_frect(game->data_img, player_rect, MLX_PURPLE);
}
