/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 06:46:04 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/07 07:58:44 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief  Check if a map cell blocks movement.
 *
 * Returns 1 if the given grid cell is outside map bounds or contains a
 * blocking tile ('1' = wall, '2' = closed door). Returns 0 otherwise.
 *
 * @param  game     Global game context with map data.
 * @param  grid_x   Grid coordinate (column index).
 * @param  grid_y   Grid coordinate (row index).
 * @return 1 if blocked, 0 if free.
 *
 * @note   Boundary checks are performed before tile lookup.
 * @warning Accesses map[grid_y][grid_x]; indices must be within bounds.
 * @pre    game->data_desc->map, nb_line, and line_length are valid.
 * @post   None.
 */
static int	is_cell_blocking(t_game *game, int grid_x, int grid_y)
{
	char	tile;

	if (grid_x < 0 || grid_y < 0)
		return (TRUE);
	if (grid_y >= game->data_desc->nb_line)
		return (TRUE);
	if (grid_x >= game->data_desc->line_length)
		return (TRUE);
	tile = game->data_desc->map[grid_y][grid_x];
	if (tile == '1')
		return (TRUE);
	if (tile == '2')
		return (TRUE);
	return (FALSE);
}

/**
 * @brief  Test if a world point collides with a wall.
 *
 * Converts world-space coordinates into grid indices (with COLLISION_PAD
 * adjustment) and checks if the corresponding cell is blocking.
 *
 * @param  game      Global game context with map data.
 * @param  world_x   World X position in pixels.
 * @param  world_y   World Y position in pixels.
 * @return 1 if point lies in a blocking cell, 0 otherwise.
 *
 * @note   COLLISION_PAD helps avoid floating-point rounding issues.
 * @warning Precision issues may occur near map boundaries.
 * @pre    game->data_desc is valid.
 * @post   Returns collision status for the given point.
 */
static int	point_hits_wall(t_game *game, float world_x, float world_y)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)((world_x + COLLISION_PAD) / (float)BLOCK);
	grid_y = (int)((world_y + COLLISION_PAD) / (float)BLOCK);
	return (is_cell_blocking(game, grid_x, grid_y));
}

int	collide_circle(t_game *game, float world_x, float world_y)
{
	if (point_hits_wall(game, world_x - (BLOCK * PLAYER_RADIUS),
			world_y - (BLOCK * PLAYER_RADIUS)))
		return (TRUE);
	if (point_hits_wall(game, world_x + (BLOCK * PLAYER_RADIUS),
			world_y - (BLOCK * PLAYER_RADIUS)))
		return (TRUE);
	if (point_hits_wall(game, world_x - (BLOCK * PLAYER_RADIUS),
			world_y + (BLOCK * PLAYER_RADIUS)))
		return (TRUE);
	if (point_hits_wall(game, world_x + (BLOCK * PLAYER_RADIUS),
			world_y + (BLOCK * PLAYER_RADIUS)))
		return (TRUE);
	return (FALSE);
}
