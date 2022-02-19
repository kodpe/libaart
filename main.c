/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 01:59:25 by sloquet           #+#    #+#             */
/*   Updated: 2022/02/18 01:59:25 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "artemis.h"

void	update_screen(char **screen, char **layer_1)
{
	int	i;
	int	k;

	i = 0;
	while (screen[i])
	{
		k = 0;
		while (screen[i][k])
		{
			if (layer_1[i][k] != 32)
				printf("%c", layer_1[i][k]);
			else
				printf("%c", screen[i][k]);
			k++;
		}
		i++;
		printf("\n");
	}
}

void	screen_set_border(char **screen)
{
	int	x;
	int	y;

	x = 0;
	while (screen[0][x + 1])
		screen[0][x++] = 196;
	y = 0;
	while (screen[y + 1])
	{
		screen[y][0] = 179;
		screen[y++][x] = 179;
	}
	x = 0;
	while (screen[y][x + 1])
		screen[y][x++] = 196;
	screen[0][0] = 218;
	screen[0][x] = 191;
	screen[y][x] = 217;
	screen[y][0] = 192;
}

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
}

void	clear_stdin(void)
{
	int	c;

	c = getchar();
	while (c != '\n' && c != EOF)
		c = getchar();
}

// return -1 on EOF
char	*get_input(const char *prompt, const char *re)
{
	char	buf[4];
	char	*input;

  	flu(prompt, 0);
  	while (fgets(buf, sizeof buf, stdin))
	{
		printf("\nbuf size: %ld\n", strlen(buf));
		input = (char *)malloc(sizeof(char) * 4);
		if (!input)
			return (NULL);
    	if (sscanf(buf, "%s", input) && strlen(buf) == 3)
		{
			clear_stdin();
			return (input);
		}
		flu(re, 0);
		flu(input, 0);
		flu("\n", 0);
		flu(prompt, 0);
		free(input);
		input = NULL;
    }
	return (NULL);
}

int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

static char	sc_getc(int win_y)
{
	char	c;

	printf("\033[%d;0H\033[K\033[%d;0H$ ", win_y, win_y);
	c = (char)getchar();
	if (!ft_isprint(c))
		return (42);
	return (c);
}

static char	*sc_getstr(int win_y, int len)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	new_str[len] = 0;
	i = 0;
	while (i < len)
	{
		new_str[i] = sc_getc(win_y);
		i++;
	}
	return (new_str);
}

int	iscmd(char *cmd)
{
	if (! strncmp(cmd, "hey", 3))
		return (1);
	if (! strncmp(cmd, "cat", 3))
		return (1);
	return (0);
}

char	*secure_getcmd(int screen_y, int len)
{
	char	*cmd;

	while (1)
	{
		cmd = sc_getstr(screen_y, len);
		if (!cmd)
			return (NULL);
		if (iscmd(cmd))
			break ;
		printf("\033[%d;0H\033[K\033[%d;0H", screen_y + 1, screen_y + 1);
		printf("unknown (%s)", cmd);
		printf("\033[%d;0H\033[K\033[%d;0H$ ", screen_y, screen_y);
		free(cmd);
		cmd = NULL;
		clear_stdin();
	}
	printf("\033[%d;0H\033[K\033[%d;0H$ ", screen_y, screen_y);
	printf("%s > done", cmd);
	// clear_stdin();
	return (cmd);
}

void	p(int x, int y, char *str, int x_max)
{
	int	i;

	printf("\033[%d;%dH", y, x);
	i = 0;
	while (str[i] && i + x < x_max)
		printf("%c", str[i++]);
}


void	draw_box()

int	main(void)
{
	struct winsize	window;

	if (-1 == ioctl(STDOUT_FILENO, TIOCGWINSZ, &window))
	{
		perror("ERR ioctl");
		exit(1);
	}
	printf("win x %d\n", window.ws_col);
	printf("win y %d\n", window.ws_row);
	printf("Press a key for start..\n");
	getchar();
	printf("\033[2J");
	printf("\033[%d;%dH%s", window.ws_row, window.ws_col, "\u251B");
	printf("\033[%d;%dH%s", window.ws_row, window.ws_col - 1, "\u2501");
	printf("\033[%d;%dH%s", window.ws_row, window.ws_col - 2, "\u2501");
	char emp = '.';
	int	speed = 5;
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
	char	*c;


	printf("\033[2J");
	int	screen_y = 1;
	printf("\033[%d;0Henter a command:\n", screen_y);

	screen_y = 2;
	c = secure_getcmd(screen_y, 3);
	if (!c)
		printf("no input\n");
	free(c);

	screen_y = 3;
	c = secure_getcmd(screen_y, 3);
	if (!c)
		printf("no input\n");
	free(c);
	printf("\033[%d;2H", 2);
	getchar();
	getchar();

	return (0);
	char	**screen;
	char	**layer_1;

	char *input = get_input("\n cmd: ", "\ninvalid cmd: ");
	if (!input)
		flu("error input", 0);
	else
		printf("La commande est : %s\n", input);
	free(input);
	input = NULL;
	// clear_stdin();
	input = get_input("\n cmd : ", "invalid cmd");
	if (!input)
		flu("error input", 0);
	else
		printf("La commande est : %s\n", input);
	free(input);
	input = NULL;

	return (0);


	printf("\033[2J");
	fluxy(0, 10, "0 2 4 6 8 11 14 17 20 23 26 29 32 35 38 41");
	fluxy(2, 10, "| | | | |  |  |  |  |  |  |  |  |  |  |  |");
	fluxy(3, 10, "hello");
	fluxy(4, 10, "Entrer une commande svp : ");
	printf("\033[5C");
	fluxy(3, 10, "world");
	// flu("\n");
	// flu("\n");
	// Usage

	// char cmd[3];
	// fgets(cmd, 3, stdin);
	// printf("La commande est : %s\n", cmd);
	// fgets(cmd, 3, stdin);
	// printf("La commande est : %s\n", cmd);
	return (0);
	screen = new_screen(62, 22, ' ');
	if (!screen)
		return (1);
	layer_1 = new_screen(60, 20, '.');
	if (!layer_1)
		return (1);

	update_screen(screen, layer_1);
	screen_set_border(screen);
	printf("\n--------------------------------\n\n");
	update_screen(screen, layer_1);

	int	i;

	i = 0;
	while (screen[i])
		free(screen[i++]);
	free(screen);
	i = 0;
	while (layer_1[i])
		free(layer_1[i++]);
	free(layer_1);
	return (0);
}
