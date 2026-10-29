/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 08:45:18 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/11 08:45:31 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_run_dda_wall_only(t_game *game, t_ray *ray)
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
		if (ray->tile == '1' || ray->tile == 'X')
			return ;
	}
}
