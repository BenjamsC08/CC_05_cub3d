/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:34:35 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/11 08:45:06 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief  Compute delta distances for a ray.
 *
 * Sets delta.x and delta.y for the DDA algorithm. These represent the
 * distance a ray must travel in grid units along the x or y axis before
 * crossing to the next grid line. Handles division by zero by assigning
 * FLT_MAX if a direction component is 0.
 *
 * @param  ray  Ray structure containing direction and delta fields.
 * @return None.
 *
 * @note   fabsf(1/dir) ensures positive step sizes for both directions.
 * @warning If ray->dir.x or ray->dir.y is zero, delta is set to FLT_MAX.
 * @pre    ray->dir must be initialized.
 * @post   ray->delta contains valid step lengths for DDA traversal.
 */
static void	ray_set_delta(t_ray *ray)
{
	if (ray->dir.x == 0.0f)
		ray->delta.x = FLT_MAX;
	else
		ray->delta.x = fabsf(1.0f / ray->dir.x);
	if (ray->dir.y == 0.0f)
		ray->delta.y = FLT_MAX;
	else
		ray->delta.y = fabsf(1.0f / ray->dir.y);
}

/**
 * @brief  Initialize ray stepping direction and side distances.
 *
 * Sets the step direction (+1 or -1) for both x and y axes and computes
 * the initial side distances from the ray origin to the first grid boundary.
 * These values are required by the DDA algorithm to know which axis to step
 * first and when to cross cell boundaries.
 *
 * @param  ray     Ray structure to initialize.
 * @param  pos_x   Player’s position in grid units (float).
 * @param  pos_y   Player’s position in grid units (float).
 * @return None.
 *
 * @note   Uses delta.x and delta.y previously computed in ray_set_delta().
 * @warning Caller must ensure pos_x/pos_y and ray->mapx/mapy are consistent.
 * @pre    ray->dir and ray->delta must be valid.
 * @post   ray->stepx/stepy and ray->side.{x,y} are initialized.
 */
static void	ray_set_step_and_side(t_ray *ray, float pos_x, float pos_y)
{
	if (ray->dir.x < 0.0f)
	{
		ray->stepx = -1;
		ray->side.x = (pos_x - ray->mapx) * ray->delta.x;
	}
	else
	{
		ray->stepx = 1;
		ray->side.x = (ray->mapx + 1.0f - pos_x) * ray->delta.x;
	}
	if (ray->dir.y < 0.0f)
	{
		ray->stepy = -1;
		ray->side.y = (pos_y - ray->mapy) * ray->delta.y;
	}
	else
	{
		ray->stepy = 1;
		ray->side.y = (ray->mapy + 1.0f - pos_y) * ray->delta.y;
	}
}

void	ray_setup(t_game *game, t_ray *ray, int screen_col, t_cam *camera)
{
	float	player_grid_x;
	float	player_grid_y;
	float	camera_x;

	player_grid_x = game->player->x / (float)BLOCK;
	player_grid_y = game->player->y / (float)BLOCK;
	camera_x = 2.0f * (float)screen_col / (float)W_WIDTH - 1.0f;
	ray->dir.x = camera->direction.x + camera->plane.x * camera_x;
	ray->dir.y = camera->direction.y + camera->plane.y * camera_x;
	ray->mapx = (int)player_grid_x;
	ray->mapy = (int)player_grid_y;
	ray_set_delta(ray);
	ray_set_step_and_side(ray, player_grid_x, player_grid_y);
}

/**
 * @brief  Compute perpendicular distance from player to wall hit.
 *
 * Calculates the corrected distance to the wall using the final ray position,
 * step direction, and side of impact. This eliminates the fish-eye effect
 * by projecting the hit distance perpendicularly onto the camera plane.
 *
 * @param  game  Global game context with player position.
 * @param  ray   Ray structure containing hit information.
 * @return Perpendicular distance to the wall hit (float).
 *
 * @note   Uses player position in grid units (player.x/BLOCK, player.y/BLOCK).
 * @warning Division by ray->dir.x or ray->dir.y assumes non-zero components.
 * @pre    ray_run_dda() has set ray->mapx, mapy, side_hit, and stepx/stepy.
 * @post   Returns the corrected wall distance for perspective projection.
 */
float	ray_perp_dist(t_game *game, t_ray *ray)
{
	const float	play_grid_x = game->player->x / (float)BLOCK;
	const float	play_grid_y = game->player->y / (float)BLOCK;
	float		dist;

	if (ray->side_hit == 0)
		dist = (ray->mapx - play_grid_x + (1 - ray->stepx) * 0.5f) / ray->dir.x;
	else
		dist = (ray->mapy - play_grid_y + (1 - ray->stepy) * 0.5f) / ray->dir.y;
	return (dist);
}
