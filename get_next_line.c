/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:21:19 by hrother           #+#    #+#             */
/*   Updated: 2023/09/27 16:46:11 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_after_newline(char **str, int len)
{
	int		i;
	int		j;
	char	*res;
	char	*remainder;

	i = 0;
	j = 0;
	if (len < 0)
		len = ft_strlen(*str);
	res = malloc((len + 2) * sizeof(char));
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
	remainder[j] = '\0';
	free(*str);
	*str = remainder;
	return (res);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	static char	*str = NULL;
	int			nl_i;
	void		*ptr;

	if (!str)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
	}
	nl_i = get_i_of_newline(str);
	while (nl_i < 0)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
		{
			if (*str)
				return (trim_after_newline(&str, nl_i));
			else
				return (free(str), str = NULL, NULL);
		}
		ptr = str;
		str = ft_strjoin(str, buffer);
		free(ptr);
		nl_i = get_i_of_newline(str);
	}
	return (trim_after_newline(&str, nl_i));
}
