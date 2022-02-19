/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_screen_withsize.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sloquet <sloquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 03:58:59 by sloquet           #+#    #+#             */
/*   Updated: 2022/02/18 03:58:59 by sloquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static int	init_screen(char **screen, int x, int y, char background_char)
{
	int	i;
	int	k;

	i = 0;
	while (i < y)
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

char	**new_screen(int x, int y, char background_char)
{
	char			**screen;

	if (x < 2 || y < 2)
		return (NULL);
	screen = (char **)malloc(sizeof(char *) * (y + 1));
	if (!screen)
		return (NULL);
	screen[y] = 0;
	if (-1 == init_screen(screen, x, y, background_char))
	{
		free(screen);
		return (NULL);
	}
	return (screen);
}
