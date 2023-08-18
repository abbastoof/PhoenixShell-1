/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:49:03 by mtoof             #+#    #+#             */
/*   Updated: 2023/08/18 18:29:26 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_value(t_token *token, t_lexer *state)
{
	if (state->res != NULL)
	{
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		token->value = ft_strdup(state->res);
		if (!token->value)
		{
			ft_putstr_fd("Malloc expand_var\n", 2);
			return (-1);
		}
	}
	else
	{
		if (token->value)
			free(token->value);
		token->value = NULL;
	}
	free_state(state);
	return (0);
}

int	need_expantion(t_token *token, t_lexer *state, t_env **env, int var_flag)
{
	if ((token->value[state->i] && state->flag == 0 \
	&& token->value[state->i] != ' ') \
	&& (token->value[state->i] != '\'') && (token->value[state->i] != '\"'))
	{
		if (join_char(token->value, state, env, var_flag) == -1)
			return (-1);
	}
	else if ((token->value[state->i] && (state->flag == 1 \
	&& token->value[state->i] != '\'')) || (token->value[state->i] \
	&& (state->flag == 2 && token->value[state->i] != '\"')))
	{
		if (join_char(token->value, state, env, var_flag) == -1)
			return (-1);
	}
	else if (state->flag == 0 && token->value[state->i] == ' ')
		return (-2);
	return (0);
}

int	expand_var(t_token *token, t_lexer *state, t_env **env, int var_flag)
{
	int	result;

	result = 0;
	state->flag = 0;
	state->i = 0;
	while (token->value[state->i])
	{
		checkquote(token->value, state);
		result = need_expantion(token, state, env, var_flag);
		if (result == -1)
			return (-1);
		else if (result == -2)
			break ;
	}
	replace_value(token, state);
	return (0);
}

void	expand_quotes(t_token **tokens, t_env **env, t_lexer *state)
{
	int		value_indx;
	t_token	*tmp;

	tmp = *tokens;
	while (tmp != NULL)
	{
		value_indx = 0;
		while (tmp->value[value_indx])
		{
			if (tmp->value[value_indx] == '\'')
			{
				expand_var(tmp, state, env, 0);
				break ;
			}
			else if ((tmp->value[value_indx] == '\"') \
			|| (tmp->value[value_indx] == '$'))
			{
				expand_var(tmp, state, env, 1);
				break ;
			}
			value_indx++;
		}
		tmp = tmp->next;
	}
}
