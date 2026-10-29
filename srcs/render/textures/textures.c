/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:59:30 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/11 07:05:33 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_tex	*texture_select_for_ray(t_game *game, t_ray *ray)
{
	if (ray->tile == 'X')
		return (&game->assets.tex[TEX_EXIT]);
	if (ray->tile == '2')
		return (select_door_texture(game, ray));
	if (ray->side_hit == 0)
	{
		if (ray->dir.x > 0.0f)
			return (&game->assets.tex[TEX_WEST]);
		return (&game->assets.tex[TEX_EAST]);
	}
	if (ray->dir.y > 0.0f)
		return (&game->assets.tex[TEX_NORTH]);
	return (&game->assets.tex[TEX_SOUTH]);
}

void	slice_prepare_from_distance(t_slice *slice, float perp_dist)
{
	int			line_height;
	const float	min_perp_distance = 0.000001f;

	if (perp_dist < min_perp_distance)
		perp_dist = min_perp_distance;
	line_height = (int)((float)W_HEIGHT / perp_dist);
	slice->line_height = line_height;
	slice->draw_start = -line_height / 2 + W_HEIGHT / 2;
	if (slice->draw_start < 0)
		slice->draw_start = 0;
	slice->draw_end = line_height / 2 + W_HEIGHT / 2;
	if (slice->draw_end >= W_HEIGHT)
		slice->draw_end = W_HEIGHT - 1;
}

int	texture_column_from_impact(t_game *game, t_ray *ray,
			float perp_dist, int texture_width)
{
	float	impact_u;
	int		tex_x;

	if (ray->side_hit == 0)
		impact_u = (game->player->y / (float)BLOCK) + perp_dist * ray->dir.y;
	else
		impact_u = (game->player->x / (float)BLOCK) + perp_dist * ray->dir.x;
	impact_u -= floorf(impact_u);
	tex_x = (int)(impact_u * (float)texture_width);
	if ((ray->side_hit == 0 && ray->dir.x < 0.0f)
		|| (ray->side_hit == 1 && ray->dir.y > 0.0f))
		tex_x = texture_width - tex_x - 1;
	return (tex_x);
}

void	draw_tex_span(t_game *game, t_slice *slice, t_texspan *span,
			t_ray *ray)
{
	int				screen_y;
	int				tex_y;
	unsigned int	argb;
	unsigned int	mask_rgb;
	unsigned int	mask_alpha;

	mask_rgb = (254 << 16) | (254 << 8) | 254;
	mask_alpha = (255u << 24);
	screen_y = slice->draw_start;
	while (screen_y <= slice->draw_end)
	{
		tex_y = (int)span->tex_y_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= span->texture->h)
			tex_y = span->texture->h - 1;
		argb = texture_read_argb(span->texture, span->tex_x, tex_y);
		if (ray->side_hit == 1)
			argb = ((argb & mask_rgb) >> 1) | (argb & mask_alpha);
		ft_pixel_put(game->data_img, span->screen_x, screen_y, argb);
		span->tex_y_pos += span->step_y;
		screen_y++;
	}
}

void	draw_textured_slice(t_game *game, int screen_x,
			float perp_dist, t_ray *ray)
{
	t_slice		slice;
	t_texspan	span;

	span.texture = texture_select_for_ray(game, ray);
	if (!span.texture || !span.texture->addr || !span.texture->img
		|| span.texture->w <= 0 || span.texture->h <= 0)
	{
		draw_flat_slice(game, screen_x, perp_dist, ray->side_hit);
		return ;
	}
	slice_prepare_from_distance(&slice, perp_dist);
	span.screen_x = screen_x;
	span.tex_x = texture_column_from_impact(game, ray, perp_dist,
			span.texture->w);
	span.step_y = (float)span.texture->h / (float)slice.line_height;
	span.tex_y_pos = ((float)slice.draw_start - (float)W_HEIGHT * 0.5f
			+ (float)slice.line_height * 0.5f) * span.step_y;
	draw_tex_span(game, &slice, &span, ray);
}
