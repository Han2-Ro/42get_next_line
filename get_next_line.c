/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:21:19 by hrother           #+#    #+#             */
/*   Updated: 2023/09/29 15:53:11 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_after(char **str, int len)
{
	char	*res;
	char	*remainder;

	if (len <= 0)
		len = ft_strlen(*str);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, *str, len + 1);
	remainder = malloc((ft_strlen(*str) - len + 1) * sizeof(char));
	if (!remainder)
		return (NULL);
	ft_strlcpy(remainder, *str + len, ft_strlen(*str) - len + 1);
	free(*str);
	*str = remainder;
	return (res);
}

char	*init_str(char *str)
{
	if (!str)
	{
		str = malloc(sizeof(char));
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	return (str);
}

int	add_next_buffer(int fd, char **str)
{
	char	*buffer;
	int		bytes_read;
	char	*result;

	buffer = malloc(BUFFER_SIZE * sizeof(char));
	ft_bzero(buffer, BUFFER_SIZE);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == 0)
		return (free(buffer), bytes_read);
	else if (bytes_read < 0)
	{
		free(*str);
		*str = NULL;
		return (free(buffer), bytes_read);
	}
	result = ft_strjoin(*str, buffer);
	free(*str);
	*str = result;
	return (free(buffer), bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	int			nl_i;

	str = init_str(str);
	nl_i = get_i_of_newline(str);
	while (nl_i < 0)
	{
		if (add_next_buffer(fd, &str) <= 0)
			break ;
		if (!str)
			return (NULL);
		nl_i = get_i_of_newline(str);
	}
	if (str && *str)
		return (trim_after(&str, nl_i + 1));
	else
		return (free(str), str = NULL, NULL);
}
