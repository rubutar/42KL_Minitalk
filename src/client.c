/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutarbu <rbutarbu@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:29:52 by rbutarbu          #+#    #+#             */
/*   Updated: 2023/03/23 10:44:54 by rbutarbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void ft_confirm (int signal)
{
    if (signal == SIGUSR1)
    	ft_printf("sent!\n", 1);
    else
		ft_printf("sent!\n", 1);
}

void ft_send_bits(int pid, char i)
{
    int bit;

    bit = 0;
    while (bit < 8)
    {
        if ((i & (0x01 << bit)) != 0)
            kill (pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(100);
        bit++;
    }
    
}

int main (int argc, char **argv)
{
    int pid;
    int i;

    i = 0;
    if (argc == 3)
    {
        pid = ft_atoi(argv[1]);
        while (argv[2][i] != '\0')
        {
            signal(SIGUSR1, ft_confirm);
            signal(SIGUSR2, ft_confirm);
            ft_send_bits(pid, argv[2][i]);
            i++;
        }
        ft_send_bits(pid, '\n');
    }
    else
    {
        ft_printf("WRONG FORMAT. Try ./client_bonus <PID> <MESSAGE> \n");
        return (1);
    }
    return (0);
}