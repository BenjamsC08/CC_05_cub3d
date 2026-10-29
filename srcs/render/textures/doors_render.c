/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 08:39:38 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/11 09:18:35 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_tex_span_masked(t_game *game, t_slice *slice,
		t_texspan *span, t_ray *ray)
{
	int				screen_y;
	int				tex_y;
	unsigned int	argb;
	unsigned int	rgb;

	screen_y = slice->draw_start;
	while (screen_y <= slice->draw_end)
	{
		tex_y = (int)span->tex_y_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= span->texture->h)
			tex_y = span->texture->h - 1;
		argb = texture_read_argb(span->texture, span->tex_x, tex_y);
		rgb = argb & 0x00FFFFFFu;
		if (rgb != CHROMA_RGB)
		{
			if (ray->side_hit == 1)
				argb = ((argb & 0xFEFEFEu) >> 1) | (argb & 0xFF000000u);
			ft_pixel_put(game->data_img, span->screen_x, screen_y, argb);
		}
		span->tex_y_pos += span->step_y;
		screen_y++;
	}
}

static void	draw_textured_slice_masked(t_game *game, t_drawctx *mask)
{
	t_slice		slice;
	t_texspan	span;

	if (!mask || !mask->tex)
		return ;
	if (!mask->tex->addr || !mask->tex->img)
		return ;
	if (mask->tex->w <= 0 || mask->tex->h <= 0)
		return ;
	slice_prepare_from_distance(&slice, mask->perp_dist);
	span.texture = mask->tex;
	span.screen_x = mask->screen_x;
	span.tex_x = texture_column_from_impact(game, mask->ray,
			mask->perp_dist, mask->tex->w);
	span.step_y = (float)mask->tex->h / (float)slice.line_height;
	span.tex_y_pos = ((float)slice.draw_start - (float)W_HEIGHT * 0.5f
			+ (float)slice.line_height * 0.5f) * span.step_y;
	draw_tex_span_masked(game, &slice, &span, mask->ray);
}

void	render_anim_door_column(t_game *game, t_cam *cam, int x)
{
	t_ray		ray;
	float		perp_dist;
	t_tex		*door_tex;
	t_drawctx	mask;

	ray_setup(game, &ray, x, cam);
	ray_run_dda_door_only(game, &ray);
	if (ray.tile != '2')
		return ;
	if (ray.mapx != game->data_desc->door_x
		|| ray.mapy != game->data_desc->door_y)
		return ;
	door_tex = select_door_texture(game, &ray);
	if (!door_tex || !door_tex->img || !door_tex->addr)
		return ;
	perp_dist = ray_perp_dist(game, &ray);
	mask.screen_x = x;
	mask.perp_dist = perp_dist;
	mask.ray = &ray;
	mask.tex = door_tex;
	draw_textured_slice_masked(game, &mask);
}

void	render_closed_door_column(t_game *game, t_cam *cam, int x)
{
	t_ray	ray;
	float	perp_dist;
	t_tex	*tex;

	ray_setup(game, &ray, x, cam);
	ray_run_dda_door_only(game, &ray);
	if (ray.tile != '2')
		return ;
	tex = &game->assets.tex[TEX_DOOR_CLOSED];
	if (!tex || !tex->img || !tex->addr)
		return ;
	perp_dist = ray_perp_dist(game, &ray);
	draw_textured_slice(game, x, perp_dist, &ray);
}
