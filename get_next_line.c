/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:21:19 by hrother           #+#    #+#             */
/*   Updated: 2023/09/28 16:48:59 by hrother          ###   ########.fr       */
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

char	*read_next_buffer(int fd, char *str)
{
	char	buffer[BUFFER_SIZE];
	int		bytes_read;
	char	*result;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == 0)
	{
		if (*str)
			return (str);
		else
			return (free(str), NULL);
	}
	else if (bytes_read < 0)
		return (NULL);
	result = ft_strjoin(str, buffer);
	free(str);
	if (!result)
		return (NULL);
	return (result);
}

char	*get_next_line(int fd)
{
	//char		buffer[BUFFER_SIZE];
	static char	*str = NULL;
	int			nl_i;
	//void		*ptr;

	str = init_str(str);
	nl_i = get_i_of_newline(str);
	while (nl_i < 0)
	{
		/*ft_bzero(buffer, BUFFER_SIZE);
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
		{
			if (*str)
				return (trim_after(&str, nl_i + 1));
			else
				return (free(str), str = NULL, NULL);
		}
		ptr = str;
		str = ft_strjoin(str, buffer);
		if (!str)
			return (NULL);
		free(ptr);*/
		str = read_next_buffer(fd, str);
		if (!str)
			return (NULL);
		nl_i = get_i_of_newline(str);
	}
	return (trim_after(&str, nl_i + 1));
}
