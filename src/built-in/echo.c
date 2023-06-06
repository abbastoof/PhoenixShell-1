/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:22:43 by atoof             #+#    #+#             */
/*   Updated: 2023/06/06 22:08:26 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (args[i])
	{
		if (flag == 0)
		{
			if (ft_strcmp(args[0], "-n") == 0)
			{
				i++;
				flag = 1;
			}
		}
		if (args[i + 1] != (void *)0)
			printf("%s ", args[i]);
		else if ((args[i + 1] == (void *)0) && !(ft_strcmp(args[0], "-n")))
			printf("%s", args[i]);
		else if ((args[i + 1] == (void *)0) && (ft_strcmp(args[0], "-n")) != 0)
			printf("%s\n", args[i]);
		i++;
	}
}
