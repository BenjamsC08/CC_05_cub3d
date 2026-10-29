/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:38:54 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/13 07:31:44 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_map_row(t_game *game, const char **map, int row)
{
	t_rect	cell;
	int		col;

	get_map_cell_size(game, &cell.w, &cell.h);
	col = 0;
	while (map[row][col])
	{
		cell.x = col * cell.w;
		cell.y = row * cell.h;
		if (map[row][col] == '1')
			draw_frect(game->data_img, cell, MLX_GREY);
		if (map[row][col] == '2')
			draw_frect(game->data_img, cell, MLX_BORDEAUX);
		if (map[row][col] == '3')
			draw_rect(game->data_img, cell, MLX_BORDEAUX);
		if (ft_ischarset(map[row][col], "NSWE"))
			draw_rect(game->data_img, cell, MLX_PURPLE);
		col++;
	}
}

void	draw_map(t_game *game)
{
	const char	**map = (const char **)game->data_desc->map;
	int			row;

	row = -1;
	while (map[++row])
		draw_map_row(game, map, row);
	draw_player(game);
	draw_rect(game->data_img, game->minimap->map, MLX_YELLOW);
}

/**
 * @brief  Initialize the minimap geometry to the window size.
 *
 * Sets the minimap rectangle origin to (0,0) and sizes it to the
 * full window dimensions (W_WIDTH x W_HEIGHT). This defines the area
 * later used by draw_minimap() for framing and placement.
 *
 * @param  game  Global game context containing the minimap struct.
 * @return None.
 *
 * @note   This only sets the rectangle; it does not allocate images.
 * @warning Assumes game->minimap is allocated and not NULL.
 * @pre    game and game->minimap must be valid pointers.
 * @post   game->minimap->minimap reflects the window-sized rectangle.
 */
void	init_minimap(t_game *game)
{
	game->minimap->map.x = 0;
	game->minimap->map.y = 0;
	game->minimap->map.w = W_WIDTH;
	game->minimap->map.h = W_HEIGHT;
}
