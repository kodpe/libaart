/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   art_box.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:58:51 by sloquet           #+#    #+#             */
/*   Updated: 2022/02/19 01:58:51 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ART_BOX_H
# define ART_BOX_H

/** ART_BOX_CHARSETS */
typedef enum e_art_color
{
	ART_CH_DEFAULT= 0,
	ART_CH_ASCII = 0,
	ART_CH_U_LIGTH = 2500,
	ART_CH_U_DOUBLE = 2550,
	ART_CH_U_ARC = 2560,
	ART_CH_U_HEAVY = 2510,
	ART_CH_U_BLOCK = 2588
}	t_art_charset;

/** ART_BOX_COLORS */
typedef enum e_art_color
{
	ART_NOCOLOR = 39,
	ART_BLACK = 30,
	ART_RED = 31,
	ART_GREEN = 32,
	ART_YELLOW = 33,
	ART_BLUE = 34,
	ART_MAGENTA = 35,
	ART_CYAN = 36,
	ART_LGRAY = 37,
	ART_DGRAY = 90 ,
	ART_LRED = 91,
	ART_LGREEN = 92,
	ART_LYELLOW = 93,
	ART_LBLUE = 94,
	ART_LMAGENTA = 95,
	ART_LCYAN = 96,
	ART_WHITE = 97
}	t_art_color;

/** ART_BOX_FORMATS */
typedef enum e_art_format
{
	ART_NORMAL = 0,
	ART_BOLD = 1,
	ART_DIM = 2,
	ART_UNDERLINE = 4,
	ART_REVERSE = 7,
	ART_HIDDEN = 8
}	t_art_format;

/** ART_BOX_FILLERS */
typedef enum e_art_filler
{
	ART_NOFILLER = 0,
	ART_BLANK = 32,
	ART_STAR = 42,
	ART_DOT = 46
}	t_art_filler;

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_area
{
	int	ax;
	int	ay;
}		t_area;

typedef struct s_box
{
	int				x;
	int				y;
	int				w;
	int				h;
	t_art_charset	charset;
	t_art_color		charset_color;
	t_art_format	charset_format;
	char
	t_art_filler	filler;
	t_art_color		filler_color;
	t_art_format	filler_format;
}					t_box;

/**
 * Create a box (rectangle) at position (x , y) with specified size (w, h)
 *
 * \param x x box coordinate at the upper left 
 * \param y y box coordinate at the upper left 
 * \param w width of the box
 * \param h height of the box
 *
 * \returns the new box structure that is created or NULL if it fails.
 * 
 * * 02-19-0328
 */
t_box	*box_new(int x, int y, int w, int h);

/* 		move print terminal cursor at (x, y) 02-19-0459 */
void	move_xy(const int x, const int y);
/* 		move print terminal cursor at pos(x, y) 02-19-0525 */
void	move(const t_point pos);
/* 		reset print terminal cursor at (1, 1) 02-19-0525 */
void	move_reset(void);

/* 		print at (x, y) 02-19-0534 */
void	dot_xy(const int x, const int y, const char *c);
/* 		print at pos(x, y) 02-19-0534 */
void	dot(const t_point pos, const char *c);

/** 	draw a horizontal line */
void	line_x(int x, int y, int len_x, char *c);
/** 	draw a vertical line */
void	line_y(int x, int y, int len_y, char *c);
#endif /* ART_BOX_H */
