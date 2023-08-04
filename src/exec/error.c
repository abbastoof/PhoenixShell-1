/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:19:47 by atoof             #+#    #+#             */
/*   Updated: 2023/08/04 15:03:20 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *error)
{
	perror(error);
	exit(1);
}

void	error_access_filename(char *file_name)
{
	if (access(file_name, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_tree.exit_status = 1;
		exit(1);
	}
	else if ((access(file_name, W_OK) != 0) || access(file_name, R_OK) != 0 \
			|| access(file_name, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_tree.exit_status = 1;
		exit(1);
	}
}
