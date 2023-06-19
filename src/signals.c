/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtoof <mtoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:04:35 by atoof             #+#    #+#             */
/*   Updated: 2023/06/19 21:41:26 by mtoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_enable_echoctl(int enable)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (enable == 0)
		term.c_lflag &= ~(ECHOCTL);
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	sigint_handler(int signum)
{
	(void)signum;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}
