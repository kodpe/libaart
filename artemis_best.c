/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   artemis_best.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 19:37:45 by sloquet           #+#    #+#             */
/*   Updated: 2022/02/18 19:37:45 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#define BOX_HEAVY_TOP_LEFT "\u250f"
#define BOX_HEAVY_TOP_RIGHT "\u2513"
#define BOX_HEAVY_BOT_LEFT "\u2517"
#define BOX_HEAVY_BOT_RIGHT "\u251b"

/*
void flu(const char *str, int sleep_seconds)
{
	printf("%s", str);
	fflush(stdout);
	sleep(sleep_seconds);
}

// x column              y line
void fluxy(int y, int x, const char *str)
{
	printf("\033[%d;%dH%s", y, x, str);
	fflush(stdout);
	sleep(1);
}*/


void	box2588(const t_box b)
{
	dot_xy(b.ori.x, b.ori.y, ".");
	dot_xy(b.ori.x + b.size.x, b.ori.y, ".");
	dot_xy(b.ori.x, b.ori.y + b.size.y, ".");
	dot_xy(b.ori.x + b.size.x, b.ori.y + b.size.y, ".");

	line_x(b.ori.x + 1, b.ori.y, b.size.x - 1, ".");
	line_x(b.ori.x + 1, b.ori.y + b.size.y, b.size.x - 1, ".");

	line_y(b.ori.x, b.ori.y + 1, b.size.y - 1, ".");
	line_y(b.ori.x + b.size.x, b.ori.y + 1, b.size.y - 1, ".");
}

void	box(const t_point origin, const t_area size, const char *style, const char *color)
{
	dot_xy(b.ori.x, b.ori.y, "\u250f");
	dot_xy(b.ori.x + b.size.x, b.ori.y, "\u2513");
	dot_xy(b.ori.x, b.ori.y + b.size.y, "\u2517");
	dot_xy(b.ori.x + b.size.x, b.ori.y + b.size.y, "\u251b");

	line_x(b.ori.x + 1, b.ori.y, b.size.x - 1, "\u2501");
	line_x(b.ori.x + 1, b.ori.y + b.size.y, b.size.x - 1, "\u2501");

	line_y(b.ori.x, b.ori.y + 1, b.size.y - 1, "\u2503");
	line_y(b.ori.x + b.size.x, b.ori.y + 1, b.size.y - 1, "\u2503");
}


void	p(int x, int y, char *str, int x_max)
{
	int	i;

	printf("\033[%d;%dH", y, x);
	i = 0;
	while (str[i] && i + x < x_max)
		printf("%c", str[i++]);
}


void	plot_line (int x0, int y0, int x1, int y1, char *c)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2; /* error value e_xy */
	for (;;)
	{
		dot_xy(x0, y0, c);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		} /* e_xy+e_x > 0 */
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		} /* e_xy+e_y < 0 */
	}
}

void plot_ellipse_rect(int x0, int y0, int x1, int y1, char *c)
{
	int a = abs(x1 - x0), b = abs(y1 - y0), b1 = b & 1;		  /* values of diameter */
	long dx = 4 * (1 - a) * b * b, dy = 4 * (b1 + 1) * a * a; /* error increment */
	long err = dx + dy + b1 * a * a, e2;					  /* error of 1.step */

	if (x0 > x1)
	{
		x0 = x1;
		x1 += a;
	} /* if called with swapped points */
	if (y0 > y1)
		y0 = y1; /* .. exchange them */
	y0 += (b + 1) / 2;
	y1 = y0 - b1; /* starting pixel */
	a *= 8 * a;
	b1 = 8 * b * b;
	do
	{
		dot_xy(x1, y0, c); /*   I. Quadrant */
		dot_xy(x0, y0, c); /*  II. Quadrant */
		dot_xy(x0, y1, c); /* III. Quadrant */
		dot_xy(x1, y1, c); /*  IV. Quadrant */
		e2 = 2 * err;
		if (e2 >= dx)
		{
			x0++;
			x1--;
			err += dx += b1;
		} /* x step */
		if (e2 <= dy)
		{
			y0++;
			y1--;
			err += dy += a;
		} /* y step */
	} while (x0 <= x1);
	while (y0 - y1 < b)
	{						   /* too early stop of flat ellipses a=1 */
		dot_xy(x0 - 1, y0, c); /* -> finish tip of ellipse */
		dot_xy(x1 + 1, y0++, c);
		dot_xy(x0 - 1, y1, c);
		dot_xy(x1 + 1, y1--, c);
	}
}

void plot_circle(int xm, int ym, int r, char *c)
{
	int x = -r, y = 0, err = 2 - 2 * r; /* II. Quadrant */
	do
	{
		dot_xy(xm - x, ym + y, c); /*   I. Quadrant */
		dot_xy(xm - y, ym - x, c); /*  II. Quadrant */
		dot_xy(xm + x, ym - y, c); /* III. Quadrant */
		dot_xy(xm + y, ym + x, c); /*  IV. Quadrant */
		r = err;
		if (r > x)
			err += ++x * 2 + 1; /* e_xy+e_x > 0 */
		if (r <= y)
			err += ++y * 4 + 1; /* e_xy+e_y < 0 */
	} while (x < 0);
}
/**
 *  P1 define position of box
 *  P2 define the size of box
 */

/**
 * Set coordinates of a box point p1
 * x2 and y2 are automatically adjusted
 * - The size is preserved 
 * - 2D-box 02-19-0142
 */
void	box_size(t_rect *r, int x, int y)
{
	r->size_x = size_x;
	r->size_y = size_y;
	r->x2 = r->x1 + r->size_x;
	r->y2 = r->y1 + r->size_y;
}

/**
 * Set size of a box
 * x2 and y2 are automatically adjusted
 * 2D-box 02-19-0142
 */
void	box_size(t_rect *r, int size_x, int size_y)
{
	r->size_x = size_x;
	r->size_y = size_y;
	r->x2 = r->x1 + r->size_x;
	r->y2 = r->y1 + r->size_y;
}


void	rect_pnts(t_rect *r, int x1, int y1, int x2, int y2)
{
	r->x1 = x1;
	r->y1 = y1;
	r->x2 = x2;
	r->y2 = y2;
}

int main(void)
{
	struct winsize wio;

	if (-1 == ioctl(STDOUT_FILENO, TIOCGWINSZ, &wio))
	{
		perror("ERR ioctl");
		exit(1);
	}
	printf("\033[2J");
	move_xy(1, 1);
	printf("win x %d\n", wio.ws_col);
	printf("win y %d\n", wio.ws_row);
	printf("Press a key for start..\n");
	getchar();

	int save_x = wio.ws_col;
	int save_y = wio.ws_row;

	t_box 	w;
	t_rect	my_rectangle;

	box_siz
	set_rect()

	int k = 201;
	while (k--)
	{
		if (-1 == ioctl(STDOUT_FILENO, TIOCGWINSZ, &wio))
		{
			perror("ERR ioctl");
			exit(1);
		}
		if (k == 100 || wio.ws_col != save_x || wio.ws_row != save_y || k % 50 == 0)
		{
			save_x = wio.ws_col;
			save_y = wio.ws_row;
			printf("\033[2J");
			for (int i = 2; i <= wio.ws_row / 2; i++)
			{
				w.ori.x = i;
				w.ori.y = i;
				w.size.x = wio.ws_col - (2 * i - 1);
				w.size.y = wio.ws_row - (2 * i - 1);
				printf("\033[38;5;23%dm", i % 3 + 3);
				box2588(w);
				printf("\033[0m");
			}
			plot_line(1, 1, 22, 22, ".");
			plot_line(1, 40, 22, 22, ".");
			plot_line(40, 1, 22, 22, ".");
			plot_line(40, 40, 9, 22, ".");
			plot_line(10, 10, 32, 22, ".");
			plot_line(10, 4, 32, 2, ".");
			plot_line(4, 10, 38, 22, ".");
			plot_line(4, 4, 3, 22, ".");
			plot_circle(50, 20, 12, ",");
			plot_ellipse_rect(80, 30, 29, 50, "*");
			w.ori.x = 74;
			w.ori.y = 4;
			w.size.x = 20;
			w.size.y = 10;
			box(w);
			move_xy(1, 1);
			fflush(stdout);
			// usleep(200000);
		}
		usleep(200000);
		// sleep(1);
	}
	printf("\033[2J");
	return (0);

	// printf("\033[%d;%dH%s", window.ws_row, window.ws_col, "\u251B");
	// printf("\033[%d;%dH%s", window.ws_row, window.ws_col - 1, "\u2501");
	// printf("\033[%d;%dH%s", window.ws_row, window.ws_col - 2, "\u2501");
	char emp = '.';
	int speed = 5;
	for (int i = 1; i < 80; i += speed)
	{
		// printf("\033[1;1H\033[K");
		if (i - speed > 0)
		{
			printf("\033[1;%dH", i - speed);
			for (int k = 0; k < speed; k++)
				printf("%c", emp);
			// printf("\033[1;%dH*****", i - speed);
		}
		p(i, 1, "Salut les amis !", 80); // window size
		// printf("\033[1;%dHSalut les amis !", i);
		// printf("\033[2;%dH     ", 21 - i);
		// printf("\033[2;%dHSalut", 20 - i);
		printf("\033[0;0H");
		fflush(stdout);
		usleep(200000);
	}

	printf("\n-- end \n\n");
	return (0);
}
