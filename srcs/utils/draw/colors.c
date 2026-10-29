/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:09:53 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 11:09:53 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	encode_rgb(t_byte r, t_byte g, t_byte b)
{
	return (*(int *)(t_byte[4]){b, g, r, 0});
}

t_byte	get_r(int rgb)
{
	return (((t_byte *)&rgb)[2]);
}

t_byte	get_g(int rgb)
{
	return (((t_byte *)&rgb)[1]);
}

t_byte	get_b(int rgb)
{
	return (((t_byte *)&rgb)[0]);
}

int	get_tcolor(t_data_img *img, int x, int y, t_uint color)
{
	t_uint	color1;
	t_uint	color2;

	color1 = ft_pixel_get(img, x, y);
	color2 = (get_r(color1) + get_r(color)) / 2;
	color2 <<= 8;
	color2 += (get_g(color1) + get_g(color)) / 2;
	color2 <<= 8;
	color2 += (get_b(color1) + get_b(color)) / 2;
	return (color2);
}
