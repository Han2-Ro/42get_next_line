/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:21:19 by hrother           #+#    #+#             */
/*   Updated: 2023/09/25 19:43:16 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_after_newline(char **str)
{
	int		i;
	int 	j;
	char	*res;
	char	*remainder;

	i = 0;
	j = 0;
	res = malloc((get_i_of_newline(*str) + 2) * sizeof(char));
	while ((*str)[i])
	{
		res[i] = (*str)[i];
		if ((*str)[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	res[i] = '\0';
	remainder = malloc((ft_strlen(*str) - i + 1) * sizeof(char));
	while ((*str)[i + j])
	{
		remainder[j] = (*str)[i + j];
		j++;
	}
	remainder[i] = '\0';
	free(*str);
	*str = remainder;
	return (res);
}

char	*get_next_line(int fd)
{
	static int	x = 0;
	char		*buffer;
	static char	*str = NULL;
	int			nl_i;
	void		*ptr;

	if (!str)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	nl_i = -1;
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	while (nl_i < 0)
	{
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
		{
			if (*str)
				return (free(buffer), trim_after_newline(&str));
			else
				return (free(buffer), free(str), NULL);
		}
		ptr = str;
		str = ft_strjoin(str, buffer);
		free(ptr);
		nl_i = get_i_of_newline(str);
	}
	return (free(buffer), trim_after_newline(&str));
}
