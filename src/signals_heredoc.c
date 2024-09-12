/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:21:18 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/08/30 20:21:19 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// MARC START

#include "minishell.h"

void	handle_sigint_hd(int sig)
{
	g_signal = sig;
	printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	
}

void	setup_heredoc_signals(void)
{
	struct sigaction sa_hd_sigint;
	sa_hd_sigint.sa_handler = &handle_sigint_hd;
	sigaction(SIGINT, &sa_hd_sigint, NULL);
	/* struct sigaction sa_hd_sigquit;
	sa_hd_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_hd_sigquit, NULL); */
}

// MARC END
