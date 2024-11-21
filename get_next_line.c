/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakotu <hakotu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:10:06 by hakotu            #+#    #+#             */
/*   Updated: 2024/11/20 14:05:58 by hakotu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_after_space(char *stack)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (stack[i] != '\0' && stack[i] != '\n')
		i++;
	if (!stack[i])
	{
		free(stack);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) + ft_strlen(stack) - i);
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (stack[i + j] != '\0')
	{
		new_str[j] = stack[i + j];
		j++;
	}
	new_str[j] = '\0';
	free(stack);
	return (new_str);
}

char	*get_before_space(char *stack)
{
	int		index;
	char	*new_str;

	index = 0;
	if (!stack[index])
		return (NULL);
	while (stack[index] != '\n' && stack[index] != '\0')
		index++;
	new_str = (char *)malloc(sizeof(char) * index + 2);
	if (!new_str)
		return (NULL);
	index = 0;
	while (stack[index] != '\n' && stack[index] != '\0')
	{
		new_str[index] = stack[index];
		index++;
	}
	if (stack[index] == '\n')
	{
		new_str[index] = '\n';
		index++;
	}
	new_str[index] = '\0';
	return (new_str);
}

char	*get_line(char *stack, int fd)
{
	char	*buff;
	int		line;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	line = 1;
	while (!ft_strchr(stack, '\n') && line != 0)
	{
		line = read(fd, buff, BUFFER_SIZE);
		if (line == -1)
		{
			free(buff);
			free(stack);
			return (NULL);
		}
		buff[line] = '\0';
		stack = ft_strjoin(stack, buff);
	}
	free(buff);
	return (stack);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stack;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stack = get_line(stack, fd);
	if (!stack)
		return (0);
	line = get_before_space(stack);
	stack = get_after_space(stack);
	return (line);
}
