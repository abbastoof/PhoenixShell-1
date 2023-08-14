/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:43:35 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/14 22:53:08 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putstr_fd(cwd, 1);
		write(1, "\n", 2);
		if (cwd)
			free(cwd);
	}
	else
	{
		ft_putstr_fd("Minishell: getcwd() error\n", 2);
		return (1);
	}
	return (0);
}
