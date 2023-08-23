/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:43:23 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/23 16:34:34 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	return_exit_status(t_lexer *state)
{
	char	*str_exit_status;

	str_exit_status = ft_itoa(g_exit_status);
	if (!str_exit_status)
	{
		ft_putstr_fd("Malloc dollar_sign\n", 2);
		return (-1);
	}
	state->res = ft_strnjoin(state->tmp, str_exit_status,
			ft_strlen(str_exit_status));
	if (!state->res)
	{
		ft_putstr_fd("Malloc dollar_sign\n", 2);
		return (-1);
	}
	if (state->tmp)
		free(state->tmp);
	state->tmp = state->res;
	state->i += 2;
	return (0);
}

static int	result_join(t_lexer *state, char *str)
{
	state->res = ft_strnjoin(state->tmp, str + state->i, 1);
	if (!state->res)
	{
		ft_putstr_fd("Malloc dollar_sign\n", 2);
		return (-1);
	}
	if (state->tmp)
		free(state->tmp);
	state->tmp = state->res;
	state->i++;
	return (0);
}

static int	dollar_handler_util(t_lexer *state, int var_flag)
{
	if (state->path != NULL)
	{
		if (state->path[0] == '=')
			state->path++;
		state->res = ft_strjoin(state->tmp, state->path);
		if (!state->res)
		{
			ft_putstr_fd("Malloc dollar_sign\n", 2);
			return (-1);
		}
		if (state->tmp)
			free(state->tmp);
		state->tmp = state->res;
		if (state->path && var_flag == 0)
			free(state->path);
	}
	return (0);
}

static int	handle_special_character(char *str, t_lexer *state)
{
	if (str[state->i + 1] == '\\')
	{
		state->res = ft_strnjoin(state->tmp, str + state->i, 1);
		if (!state->res)
		{
			ft_putstr_fd("Malloc dollar_sign\n", 2);
			return (-1);
		}
		if (state->tmp)
			free(state->tmp);
		state->tmp = state->res;
		state->i += 2;
	}
	if (result_join(state, str) == -1)
	{
		ft_putstr_fd("Malloc dollar_sign\n", 2);
		return (-1);
	}
	return (0);
}

int	check_dollar_sign(char *str, t_lexer *state, t_env **env, int var_flag)
{
	state->condition_result = dollar_with_character(str, state);
	if (state->condition_result == 1 && state->flag != 1)
	{
		state->path = var_finder(str, state, env, var_flag);
		if (dollar_handler_util(state, var_flag) == -1)
			return (-1);
	}
	else if (state->condition_result == 2 && state->flag != 1)
	{
		if (return_exit_status(state))
			return (-1);
	}
	else if (state->condition_result == 3 && state->flag != 1)
	{
		if (handle_special_character(str, state) == -1)
			return (-1);
	}
	else if (state->condition_result == 4 && state->flag != 1)
		state->i++;
	else
	{
		if (result_join(state, str) == -1)
			return (-1);
	}
	return (0);
}
