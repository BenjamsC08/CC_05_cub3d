/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:09:59 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 11:09:59 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_pixel_put(t_data_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= W_WIDTH || x < 0 || y >= W_HEIGHT || y < 0)
		return ;
	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_clear_background(t_game *game, t_data_img *img, int color)
{
	int		y;
	int		x;

	y = -1;
	while (++y < W_HEIGHT)
	{
		x = -1;
		while (++x < W_WIDTH)
			ft_pixel_put(img, x, y, color);
	}
	mlx_put_image_to_window(game->mlx, game->win, img->img, 0, 0);
}

t_uint	ft_pixel_get(t_data_img *img, int x, int y)
{
	char			*dst;
	unsigned int	color;

	if (x >= W_WIDTH || x < 0 || y >= W_HEIGHT || y < 0)
		return (0);
	dst = img->addr + (y * img->ll + x * (img->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

t_uint	ft_pixel_get2(char *addr)
{
	return (*(unsigned int *)addr);
}
