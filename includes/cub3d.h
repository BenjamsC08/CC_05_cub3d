/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 08:33:42 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/13 13:34:17 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <float.h>
# include <math.h>
# include <sys/time.h>
# include <errno.h>
# include <pthread.h>
# include "libft.h"

# include "cub3d_def.h"

/*													*/
/*						UTILS						*/
/*													*/
//						Colors
int				encode_rgb(t_byte r, t_byte g, t_byte b);
t_byte			get_r(int rgb);
t_byte			get_g(int rgb);
t_byte			get_b(int rgb);
int				get_tcolor(t_data_img *img, int x, int y, t_uint color);

//						Gameplay
void			back_to_home(t_game *game);
void			set_angle(t_game *game, int keycode);
int				is_win(t_game *game);
void			reset_game(t_game *game);

//						Disp
void			ft_pixel_put(t_data_img *img, int x, int y, int color);
void			put_c_pixel(t_game *game, int big_pixel, int small_pixel);
t_uint			ft_pixel_get(t_data_img *img, int x, int y);
t_uint			ft_pixel_get2(char *addr);
void			ft_clear_background(t_game *game, t_data_img *img, int color);
void			str_put(t_game *game, t_text text);
void			defeat_screen(t_game *game);
void			victory_screen(t_game *game);
void			draw_interact_hint(t_game *game);
void			print_score(t_game *game, const int area_size,
					const int font_size);
//						Figures
t_rect			get_rect(int x, int y, int width, int height);
void			draw_rect(t_data_img *img, t_rect rect, int color);
void			draw_frect(t_data_img *img, t_rect rect, int color);
void			draw_trect(t_data_img *img, t_rect rect, int color);
t_text			get_text(char *str, t_uint size, int color, t_rect frame);
//						ASCII
int				create_num(t_game *game);
int				get_alpha1(t_game *game);
int				get_alpha6(t_game *game);
int				get_special(t_game *game);
//						Key hook
int				key_pressed(int keycode, t_game *game);
int				key_released(int keycode, t_game *game);
void			enable_mouse_capture(t_game *game);
//						Moves/Rotations
void			moves(t_game *g);
void			apply_mouse_rotate(t_game *game);
void			apply_rotate(t_game *game);
int				collide_circle(t_game *game, float world_x, float world_y);
//						Time
unsigned int	now_ms(void);
int				set_start_time(t_game *game);
t_uint			get_current_time(void);
int				start_time(t_game *game);
t_uint			get_cd_time(t_game *game);
char			*time_to_str(t_uint time);
void			put_timer(t_game *game, t_uint size, t_rect frame);
void			put_endtimer(t_game *game, t_uint size, t_rect frame);
void			stop_thread(t_game *game);
//						Score history
int				handle_score_history(t_game *game);
int				load_score_history(t_game *game, char *map_name);
int				write_best_time_in_score_history(t_game *game, char *new);
int				is_time_format(char *line);
int				is_better_time(t_game *game, char *new);
/*													*/
/*						PARSING						*/
/*													*/
int				init_parser(t_game *game);
//						Base
int				good_file_ext(char *str, const char *ext);
int				convert_colors(char **strs, t_game *game, char c);
int				load_cub_file(t_game *game, char *str);
int				assets_load_all(t_game *game, const char **paths);
//						Error
int				not_a_good_file(int k);
int				error_map(char **map, int j, int i);
//						Line
int				check_line(char *line, t_game *game);
//						Map
int				extract_map(t_game *game, int fd);
int				config_is_complete(t_game *game);
void			define_hard_tex_paths(t_game *game);
int				check_map(t_game *game);

/*													*/
/*						RENDER						*/
/*													*/
int				assets_paths_ready(t_game *game);
void			slice_prepare_from_distance(t_slice *slice, float perp_dist);
void			draw_flat_slice(t_game *g, int x, float pd, int side_hit);
unsigned int	texture_read_argb(const t_tex *texture, int x, int y);
int				texture_column_from_impact(t_game *game, t_ray *ray,
					float perp_dist, int texture_width);
void			draw_textured_slice(t_game *game, int screen_x,
					float perp_dist, t_ray *ray);
//						Digital Differential Analyzer
void			ray_run_dda_wall_only(t_game *game, t_ray *ray);
void			ray_run_dda_backdrop_skip_cell(t_game *game, t_ray *ray,
					int skip_x, int skip_y);
//						Doors handling and utils
int				door_find_in_front(t_game *game, int *mx, int *my);
void			door_try_open(t_game *game, int door_x, int door_y);
void			door_anim_update(t_game *game);
void			ray_run_dda_door_only(t_game *game, t_ray *ray);
void			render_anim_door_column(t_game *game, t_cam *cam, int x);
void			render_closed_door_column(t_game *game, t_cam *cam, int x);
t_tex			*select_door_texture(t_game *game, t_ray *ray);

/*													*/
/*						MINIMAP						*/
/*													*/
void			init_map(t_game *game);
void			init_minimap(t_game *game);
//						Draw
t_vec			world_to_minimap(t_game *game, t_vec world);
void			get_map_cell_size(t_game *game, int *cell_w, int *cell_h);
void			draw_map(t_game *game);
void			draw_minimap(t_game *game);
void			get_map(t_game *game, t_data_img *img);
void			copy_map(t_game *g);
//						Raycast
void			camera_build_from_player(t_player *player, t_cam *camera);
void			draw_player(t_game *game);
void			ray_setup(t_game *game, t_ray *ray, int screen_col,
					t_cam *camera);
void			render_frame(t_game *game);
float			ray_perp_dist(t_game *game, t_ray *r);

/*													*/
/*						INIT						*/
/*													*/
int				init_base(t_game *game);
int				init_maps(t_game *game);
int				init_player(t_game *game);
void			assets_zero(t_game *game);

/*													*/
/*						DESTROY						*/
/*													*/
int				close_all(t_game *game, int exit_code);
void			assets_destroy_all(t_game *game);

#endif
