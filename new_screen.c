/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 03:40:52 by sloquet           #+#    #+#             */
/*   Updated: 2022/02/18 03:40:52 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>

static int	init_screen(char **screen, struct winsize win, char background_char)
{
	int	x;
	int	i;
	int	k;

	x = win.ws_col;
	i = 0;
	while (i < win.ws_row)
	{
		screen[i] = (char *)malloc(sizeof(char) * (x + 1));
		if (!screen[i])
		{
			while (i--)
				free(screen[i]);
			return (-1);
		}
		screen[i][x] = 0;
		k = 0;
		while (k < x)
			screen[i][k++] = background_char;
		i++;
	}
	return (0);
}

char	**new_screen(char background_char)
{
	char			**screen;
	struct winsize	window;

	if (-1 == ioctl(STDOUT_FILENO, TIOCGWINSZ, &window))
	{
		perror("ERR new_screen()");
		return (NULL);
	}
	screen = (char **)malloc(sizeof(char *) * (window.ws_row + 1));
	if (!screen)
		return (NULL);
	screen[window.ws_row] = 0;
	if (-1 == init_screen(screen, window, background_char))
	{
		free(screen);
		return (NULL);
	}
	return (screen);
}
