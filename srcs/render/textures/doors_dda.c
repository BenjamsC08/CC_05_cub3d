/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_dda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 05:37:05 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/11 08:47:58 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ray_out_of_bounds(t_game *game, t_ray *ray)
{
	if (ray->mapx < 0 || ray->mapy < 0)
		return (1);
	if (ray->mapy >= game->data_desc->nb_line
		|| ray->mapx >= game->data_desc->line_length)
		return (1);
	return (0);
}

static void	ray_step_advance(t_ray *ray)
{
	if (ray->side.x < ray->side.y)
	{
		ray->side.x += ray->delta.x;
		ray->mapx += ray->stepx;
		ray->side_hit = 0;
		return ;
	}
	ray->side.y += ray->delta.y;
	ray->mapy += ray->stepy;
	ray->side_hit = 1;
}

void	ray_run_dda_backdrop_skip_cell(t_game *game, t_ray *ray,
			int skip_x, int skip_y)
{
	while (1)
	{
		ray_step_advance(ray);
		if (ray_out_of_bounds(game, ray))
		{
			ray->tile = 0;
			return ;
		}
		ray->tile = game->data_desc->map[ray->mapy][ray->mapx];
		if (ray->tile == '1')
			return ;
		if (ray->tile == '2'
			&& !(ray->mapx == skip_x && ray->mapy == skip_y))
			return ;
	}
}

void	ray_run_dda_door_only(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->mapx += ray->stepx;
			ray->side_hit = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->mapy += ray->stepy;
			ray->side_hit = 1;
		}
		if (ray->mapx < 0 || ray->mapy < 0
			|| ray->mapy >= game->data_desc->nb_line
			|| ray->mapx >= game->data_desc->line_length)
		{
			ray->tile = 0;
			return ;
		}
		ray->tile = game->data_desc->map[ray->mapy][ray->mapx];
		if (ray->tile == '2' || ray->tile == '1' || ray->tile == 'X')
			return ;
	}
}
