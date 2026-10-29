/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:10:04 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/15 11:56:15 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_2d(t_game *game, t_text text, t_rect frame, char k)
{
	int		**tab;
	t_uint	i;
	t_uint	h;

	tab = game->tab_num[(int)k];
	frame.w = text.size;
	frame.h = text.size;
	i = -1;
	while (++i < 5)
	{
		h = -1;
		while (++h < 5)
		{
			if (tab[i][h] == 1)
			{
				frame.x += text.size * h;
				frame.y += text.size * i;
				draw_frect(game->data_img, frame, text.color);
				frame.x -= text.size * h;
				frame.y -= text.size * i;
			}
		}
	}
}

void	str_put(t_game *game, t_text text)
{
	int			i;
	int			start_x;
	const int	digit_width = text.size * 5;
	const int	spacing = text.size;
	int			text_width;

	text_width = ft_strlen(text.str) * digit_width
		+ (ft_strlen(text.str) - 1) * spacing;
	i = -1;
	start_x = text.frame.x + (text.frame.w - text_width) / 2;
	while (text.str[++i])
	{
		put_2d(game, text,
			get_rect(start_x + i * (digit_width + text.size), text.frame.y
				+ text.frame.h / 2 - ((text.size * 5) / 2),
				digit_width, text.frame.h), text.str[i]);
	}
}
