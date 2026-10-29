/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 07:27:41 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/13 08:40:25 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_cell_size(t_game *game, int *cell_w, int *cell_h)
{
	*cell_w = W_HEIGHT / game->data_desc->nb_line;
	*cell_h = W_HEIGHT / game->data_desc->nb_line;
	if (game->data_desc->line_length > game->data_desc->nb_line)
	{
		*cell_w = W_WIDTH / game->data_desc->line_length;
		*cell_h = W_WIDTH / game->data_desc->line_length;
	}
}

t_vec	world_to_minimap(t_game *game, t_vec world)
{
	int		cell_w;
	int		cell_h;
	t_vec	screen;

	get_map_cell_size(game, &cell_w, &cell_h);
	screen.x = game->minimap->map.x
		+ (world.x / (float)BLOCK) * (float)cell_w;
	screen.y = (float)game->minimap->map.y
		+ (world.y / (float)BLOCK) * (float)cell_h;
	return (screen);
}
