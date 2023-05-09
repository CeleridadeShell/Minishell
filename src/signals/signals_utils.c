/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcarecho <mcarecho@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:19:33 by mcarecho          #+#    #+#             */
/*   Updated: 2023/05/08 23:08:11 by mcarecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
*@brief Changes the signal behavior, in this case, it changes the signal so that
*it does not close the program (ctrl + c), instead it just prints a new line.
*@param sig the signal to be changed
*@return none.
*/
static void	sigint_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigint_handler_child(int sig)
{
	if(sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		exit(0);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}

}

/**
*@brief Handles the main signals for the minishell (first one tells that the
*signal is ignored, the second one changes the signal behavior)
*@signal SIGINT (ctrl + c) - close the program
*@signal SIGQUIT (crtl + \) - quit the program/SIG_IGN - tells thesignal is to
*be ignored
*@param none
*@return none.
*/
void	fix_sigint_exec(void)
{
	struct sigaction	sig_int;

	sig_int.sa_handler = SIG_IGN;
	sig_int.sa_flags = SA_RESTART;
	sigemptyset(&sig_int.sa_mask);
	sigaction(SIGINT, &sig_int, NULL);
}

void	handle_signal_child(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_handler = &sigint_handler_child;
	sig_int.sa_flags = SA_RESTART;
	sigemptyset(&sig_int.sa_mask);
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = &sigint_handler_child;
	sig_quit.sa_flags = SA_RESTART;
	sigemptyset(&sig_quit.sa_mask);
	sigaction(SIGQUIT, &sig_quit, NULL);
}

// function with sigaction instead of signal
void	handle_signal(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_handler = &sigint_handler;
	sig_int.sa_flags = SA_RESTART;
	sigemptyset(&sig_int.sa_mask);
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = SA_RESTART;
	sigemptyset(&sig_quit.sa_mask);
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void sig_heredoc_exec(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(130);
}

void	handle_signal_heredoc(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_handler = &sig_heredoc_exec;
	sig_int.sa_flags = SA_RESTART;
	sigemptyset(&sig_int.sa_mask);
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = SA_RESTART;
	sigemptyset(&sig_quit.sa_mask);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
