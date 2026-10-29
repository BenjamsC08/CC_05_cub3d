/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:13:06 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 11:49:05 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_color_block(char c)
{
	if (c == '1')
		return (MLX_GREY);
	if (ft_ischarset(c, "23"))
		return (MLX_BORDEAUX);
	if (ft_ischarset(c, "NSWE"))
		return (MLX_PURPLE);
	if (ft_ischarset(c, "X"))
		return (MLX_ORANGE);
	return (MLX_BLACK);
}

void	get_map(t_game *game, t_data_img *img)
{
	const char	**map = (const char **)game->data_desc->map;
	t_rect		r;
	int			ji[2];

	r.w = BLOCK2;
	r.h = BLOCK2;
	ji[0] = -1;
	while (map[++ji[0]])
	{
		ji[1] = -1;
		while (map[ji[0]][++ji[1]])
		{
			r.x = (ji[1] * BLOCK2);
			r.y = (ji[0] * BLOCK2);
			if (ft_ischarset(map[ji[0]][ji[1]], "3NSWE"))
				draw_rect(img, r, get_color_block(map[ji[0]][ji[1]]));
			else if (ft_ischarset(map[ji[0]][ji[1]], "12X"))
				draw_frect(img, r, get_color_block(map[ji[0]][ji[1]]));
		}
	}
}

static int	get_start_minimap(t_game *game, char c)
{
	int	xy;
	int	wh;

	if (c == 'x')
	{
		xy = (int)(game->player->x) / BLOCK;
		wh = game->minimap->minimap.w / BLOCK2;
	}
	else
	{
		xy = (int)(game->player->y) / BLOCK;
		wh = game->minimap->minimap.h / BLOCK2;
	}
	return (xy - wh / 2);
}

static int	get_small_pixel(t_game *g, int map_xy[2], int i, int j)
{
	int	sp;

	sp = ((map_xy[0] * BLOCK2 + (i % BLOCK2)) * (g->minimap->mmap_img->bpp / 8))
		+ ((map_xy[1] * BLOCK2 + (j % BLOCK2)) * g->minimap->mmap_img->ll);
	return (sp);
}

void	copy_map(t_game *g)
{
	int	i;
	int	j;
	int	big_pixel;
	int	small_pixel;
	int	map_xy[2];

	j = -1;
	while (++j < g->minimap->minimap.h)
	{
		i = -1;
		while (++i < g->minimap->minimap.w)
		{
			map_xy[0] = get_start_minimap(g, 'x') + (i / BLOCK2);
			map_xy[1] = get_start_minimap(g, 'y') + (j / BLOCK2);
			if (map_xy[0] < 0 || map_xy[0] >= g->data_desc->line_length
				|| map_xy[1] < 0 || map_xy[1] >= g->data_desc->nb_line)
				continue ;
			small_pixel = get_small_pixel(g, map_xy, i, j);
			big_pixel = ((g->minimap->minimap.x + i) * (g->data_img->bpp / 8))
				+ ((g->minimap->minimap.y + j) * g->data_img->ll);
			if (i + g->minimap->minimap.x < W_WIDTH
				&& j + g->minimap->minimap.y < W_HEIGHT)
				put_c_pixel(g, big_pixel, small_pixel);
		}
	}
}
