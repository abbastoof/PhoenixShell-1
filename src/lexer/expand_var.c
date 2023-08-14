/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:24:16 by atoof             #+#    #+#             */
/*   Updated: 2023/08/15 00:03:42 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handledquote(char *str, t_lexer *state)
{
	if (str[state->i] == '\"' && !state->inquote)
	{
		if (str[state->i] == '\"' && state->flag == 0)
		{
			state->flag = 2;
			state->i++;
			state->indquote = 1;
		}
		if (str[state->i] == '\"' && state->flag == 2)
		{
			state->flag = 0;
			state->i++;
			state->indquote = 0;
		}
	}
}

void	handlequote(char *str, t_lexer *state)
{
	if (str[state->i] == '\'' && !state->indquote)
	{
		if (str[state->i] == '\'' && state->flag == 0)
		{
			state->flag = 1;
			state->i++;
			state->inquote = 1;
		}
		if (str[state->i] == '\'' && state->flag == 1)
		{
			state->flag = 0;
			state->i++;
			state->inquote = 0;
		}
	}
	handledquote(str, state);
}

int	join_char(char *str, t_lexer *state, t_env **env, int var_flag)
{
	if (!state->tmp)
	{
		state->tmp = ft_calloc(sizeof(char), 2);
		if (!state->tmp)
		{
			ft_putstr_fd("Malloc expand_var\n", 2);
			return (-1);
		}
	}
	if (check_dollar_sign(str, state, env, var_flag) == -1)
		return (-1);
	return (0);
}
