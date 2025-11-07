 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafioron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:08:16 by mafioron          #+#    #+#             */
/*   Updated: 2025/11/07 20:10:19 by mafioron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../full_libft/include/libft.h"
# include "../full_libft/include/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define NO_TEXT 0
# define SO_TEXT 1
# define WE_TEXT 2
# define EA_TEXT 3
# define FLOOR 4
# define CEILING 5

typedef struct s_cub
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;

	char	**map;
	char	**textures;
	int		height;
	int		width;
	int		map_height;
	int		map_width;
	int		player_row;
	int		player_col;
	char	player_dir;
}	t_cub;


/*****		a trier		*******/
int		check_textures(char **cub, t_cub *vars);
void	flood_fill(char **map, int row, int col, bool *is_valid);
int		only_textures(char *texture);
int		check_wall(char **map, int row, int col);
int		check_map(char **cub_file, t_cub *cub);
int		test_image(t_cub *cub, char *texture);
int		check_colors(char *texture);
t_cub	*inits(void);
int		set_texture(char *cub, char **texture, int *text_count, int *count_cub);
char	**init_textures(char **cub);
int		check_double(char **cub, int i);
int		check_errors(int fd, t_cub *cub);
void free_cub(t_cub *cub);








#endif
