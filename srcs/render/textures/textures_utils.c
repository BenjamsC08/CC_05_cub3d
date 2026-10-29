/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:54:53 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/11 07:18:32 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	define_hard_tex_paths(t_game *game)
{
	game->bonus_paths[TEX_DOOR_CLOSED - 4] = ft_gc_addnode(game->gc_head,
			ft_strdup(TEX_PTH_DOOR));
	game->bonus_paths[TEX_DOOR_CLOSED1 - 4] = ft_gc_addnode(game->gc_head,
			ft_strdup(TEX_PTH_DOOR1));
	game->bonus_paths[TEX_DOOR_CLOSED2 - 4] = ft_gc_addnode(game->gc_head,
			ft_strdup(TEX_PTH_DOOR2));
	game->bonus_paths[TEX_DOOR_CLOSED3 - 4] = ft_gc_addnode(game->gc_head,
			ft_strdup(TEX_PTH_DOOR3));
	game->bonus_paths[TEX_DOOR_CLOSED4 - 4] = ft_gc_addnode(game->gc_head,
			ft_strdup(TEX_PTH_DOOR4));
	game->bonus_paths[TEX_DOOR_CLOSED5 - 4] = ft_gc_addnode(game->gc_head,
			ft_strdup(TEX_PTH_DOOR5));
	game->bonus_paths[TEX_DOOR_CLOSED6 - 4] = ft_gc_addnode(game->gc_head,
			ft_strdup(TEX_PTH_DOOR6));
	game->bonus_paths[TEX_DOOR_CLOSED7 - 4] = ft_gc_addnode(game->gc_head,
			ft_strdup(TEX_PTH_DOOR7));
	game->bonus_paths[TEX_EXIT - 4] = ft_gc_addnode(game->gc_head,
			ft_strdup(TEX_PTH_EXIT));
}

unsigned int	texture_read_argb(const t_tex *texture, int x, int y)
{
	char	*pixel_ptr;

	pixel_ptr = texture->addr + (y * texture->ll + x * (texture->bpp / 8));
	return (*(unsigned *)pixel_ptr);
}

void	draw_flat_slice(t_game *game, int screen_x,
			float perp_distance, int side_hit)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	screen_y;
	int	slice_color;

	if (perp_distance < 0.000001f)
		perp_distance = 0.000001f;
	line_height = (int)((float)W_HEIGHT / perp_distance);
	draw_start = -line_height / 2 + W_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + W_HEIGHT / 2;
	if (draw_end >= W_HEIGHT)
		draw_end = W_HEIGHT - 1;
	if (side_hit == 1)
		slice_color = 0x007700;
	else
		slice_color = 0x00AA00;
	screen_y = draw_start;
	while (screen_y <= draw_end)
	{
		ft_pixel_put(game->data_img, screen_x, screen_y, slice_color);
		screen_y++;
	}
}
