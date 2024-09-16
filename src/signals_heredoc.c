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

void	handle_sigint_hd_child(int sig)
{
	g_signal = sig;
	/* printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay(); */
	exit (1);
}

void	handle_sigint_hd_main(int sig)
{
	g_signal = sig;
	printf("^C\n");
}

void	setup_heredoc_signals_main(void)
{
	struct sigaction sa_hd_sigint_main;
	sa_hd_sigint_main.sa_handler = &handle_sigint_hd_main;
	sa_hd_sigint_main.sa_flags = 0;
	sigemptyset(&sa_hd_sigint_main.sa_mask);
	sigaction(SIGINT, &sa_hd_sigint_main, NULL);
	/* struct sigaction sa_hd_sigquit;
	sa_hd_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_hd_sigquit, NULL); */
}

void	setup_heredoc_signals_child(void)
{
	struct sigaction sa_hd_sigint_child;
	sa_hd_sigint_child.sa_handler = &handle_sigint_hd_child;
	sa_hd_sigint_child.sa_flags = 0;
	sigemptyset(&sa_hd_sigint_child.sa_mask);
	sigaction(SIGINT, &sa_hd_sigint_child, NULL);
	/* struct sigaction sa_hd_sigquit;
	sa_hd_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_hd_sigquit, NULL); */
}

// MARC END
