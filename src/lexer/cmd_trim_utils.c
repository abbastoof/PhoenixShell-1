/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_trim_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:46:24 by mtoof             #+#    #+#             */
/*   Updated: 2023/06/09 14:33:07 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirectors(char *str, int i)
{
	if (ft_strncmp(str + i, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(str + i, ">>", 2) == 0)
		return (TOKEN_OUTPUT_APPEND);
	else if (ft_strncmp(str + i, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strncmp(str + i, "<", 1) == 0)
		return (TOKEN_INPUT);
	else if (ft_strncmp(str + i, ">", 1) == 0)
		return (TOKEN_OUTPUT);
	else if (str[i] == '$')
	{
		if (ft_strncmp(str + i, "$?", 2) == 0)
			return (TOKEN_EXIT_STATUS);
	}
	return (0);
}

void	init_cmdsplit(t_cmdsplit *cmd)
{
	cmd->index = 0;
	cmd->index = 0;
	cmd->quote = 0;
	cmd->res = 0;
	cmd->wd_count = 0;
}

void	check_redirectors(char *str, t_cmdsplit *cmd, int indx)
{
	cmd->res = redirectors(str, indx);
	if (cmd->res == TOKEN_OUTPUT_APPEND || cmd->res == TOKEN_HEREDOC
		|| cmd->res == TOKEN_EXIT_STATUS)
		indx++;
}

void	check_isquote(char *str, t_cmdsplit *cmd, int indx)
{
	cmd->quote = str[indx];
	indx++;
	while (str[indx] != '\0')
	{
		if (str[indx] == cmd->quote && (ft_isspace(str[indx
						+ 1]) || str[indx + 1] == '\0'
				|| redirectors(str, indx + 1)))
			break ;
		indx++;
	}
}

int	words_count(char *str, t_cmdsplit *cmd, int indx)
{
	while (str[indx] != '\0')
	{
		if (!ft_isspace(str[indx]) && redirectors(str, indx) == 0)
		{
			while (str[indx] != '\0' && !ft_isspace(str[indx])
				&& redirectors(str, indx) == 0)
				indx++;
			cmd->wd_count++;
		}
		if (redirectors(str, indx) != 0)
		{
			check_redirectors(str, cmd, indx);
			cmd->wd_count++;
		}
		if (ft_isquote(str[indx]))
		{
			check_isquote(str, cmd, indx);
			cmd->wd_count++;
		}
		if (str[indx] != '\0')
			indx++;
	}
	return (cmd->wd_count);
}
