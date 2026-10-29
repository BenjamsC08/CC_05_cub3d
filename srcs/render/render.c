/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:35:10 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/13 13:37:02 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_wall_column(t_game *game, t_cam *cam, int x)
{
	t_ray	ray;
	float	perp_dist;
	int		anim_on;

	anim_on = game->data_desc->door_anim_on;
	ray_setup(game, &ray, x, cam);
	if (anim_on == 1)
		ray_run_dda_backdrop_skip_cell(game, &ray,
			game->data_desc->door_x, game->data_desc->door_y);
	else
		ray_run_dda_wall_only(game, &ray);
	if (ray.tile != '1' && ray.tile != '2' && ray.tile != 'X')
		return ;
	perp_dist = ray_perp_dist(game, &ray);
	draw_textured_slice(game, x, perp_dist, &ray);
}

void	render_frame(t_game *game)
{
	t_cam	camera;
	int		screen_x;
	int		screen_w;
	int		anim_on;

	camera_build_from_player(game->player, &camera);
	screen_x = 0;
	screen_w = W_WIDTH;
	anim_on = game->data_desc->door_anim_on;
	while (screen_x < screen_w)
	{
		render_wall_column(game, &camera, screen_x);
		if (anim_on == 1)
			render_anim_door_column(game, &camera, screen_x);
		else
			render_closed_door_column(game, &camera, screen_x);
		screen_x++;
	}
	draw_interact_hint(game);
}
