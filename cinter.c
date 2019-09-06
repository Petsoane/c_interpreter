/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpetsoan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 17:59:21 by lpetsoan          #+#    #+#             */
/*   Updated: 2019/09/06 19:14:57 by lpetsoan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cinter.h"

int main(void)
{
	int fd_main = open(MAIN, O_WRONLY | O_TRUNC);
	int fd_tmp = open(TEMPLATE, O_RDONLY);
	char *input[255];
	char *out;
	int i;
	
	// Get the input from the user.
	i = 0;
	while (get_next_line(1, &input[i]) == 1)
	{
		if (ft_strcmp(input[i], "run") == 0)
		{
			input[i] = NULL;
			break;
		}
		i++;
	}
	// Add the input to the file.
	while (get_next_line(fd_tmp, &out) == 1)
	{
		if (ft_strcmp(START, out) == 0)
		{
			int k = 0;
			while (input[k] != NULL)
			{
				ft_putendl_fd(input[k], fd_main);
				free(input[k]);
				k++;
			}
		}
		else
			ft_putendl_fd(out, fd_main);
		free(out);
	}
	// compile the program
	if (fork() == 0)
	{
		char *args[] = {"gcc", ".main.c","libft/libft.a",  NULL};
		if (execve("/usr/bin/gcc", args, NULL) == -1)
			perror("Something is wrong with your code");
		return (0);
	}
	wait(NULL);
	if (fork() == 0)
		execve("a.out", NULL, NULL);
	wait(NULL);
	ft_putstr("Done executing code\n");
	close(fd_tmp);
	close(fd_main);
	return (0);
}
