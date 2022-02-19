/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:58:01 by sloquet           #+#    #+#             */
/*   Updated: 2022/02/19 01:58:01 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "art_box.h"

size_t	art_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	art_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

int	box_destroy(t_box *box)
{
	if (!box)
		return (-1);
	free();
	free(box);
	return (0);
}

t_box	*box_new(int x, int y, int w, int h)
{
	t_box	*box;

	box = malloc(sizeof(t_box));
	if (!box)
		return (NULL);
	box->x = x;
	box->y = y;
	box->w = w;
	box->h = h;
	box->charset = ART_CH_DEFAULT;
	box->charset_color = ART_NOCOLOR;
	box->charset_format = ART_NORMAL;
	box->filler = ART_NOFILLER;
	box->filler_color = ART_NOCOLOR;
	box->filler_format = ART_NORMAL;
	return (box);
}

/** move functions
 *  ! printf
 *  TODO implemente own writting system
 */
void	move_xy(const int x, const int y)
{
	printf("\033[%d;%dH", y, x);
}

void	move(const t_point pos)
{
	printf("\033[%d;%dH", pos.y, pos.x);
}

void	move_reset(void)
{
	move_xy(1, 1);
}

/** dot functions
 *  ! need no printable check
 */
void	dot_xy(const int x, const int y, const char *c)
{
	move_xy(x, y);
	printf("%s", c);
}

void	dot(const t_point pos, const char *c)
{
	move(pos);
	printf("%s", c);
}

/** lines functions */
void	line_x(int x, int y, int len_x, char *c)
{
	int	i;

	i = x;
	while (i < x + len_x)
		dot_xy(i++, y, c);
}

void	line_y(int x, int y, int len_y, char *c)
{
	int	i;

	i = y;
	while (i < y + len_y)
		dot_xy(x, i++, c);
}

/** 
 * draw box functions
 * 
 */
void	box(const t_box b)
{
	dot_xy(b.x, b.y, "\u250f");
	dot_xy(b.x + b.w, b.y, "\u2513");
	dot_xy(b.x, b.y + b.h, "\u2517");
	dot_xy(b.x + b.w, b.y + b.h, "\u251b");

	line_x(b.x + 1, b.y, b.w - 1, "\u2501");
	line_x(b.x + 1, b.y + b.h, b.w - 1, "\u2501");

	line_y(b.x, b.y + 1, b.h - 1, "\u2503");
	line_y(b.x + b.w, b.y + 1, b.h - 1, "\u2503");
	/**
	 * ! choose charset
	 */
	if (b.filler)
		return ;
	 /**
	  * ! if filler > filler */
}
