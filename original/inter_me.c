/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_me.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 12:40:44 by knabouss          #+#    #+#             */
/*   Updated: 2020/12/10 10:26:45 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int     main(int argc, char **argv)
{
    unsigned char used[255];
    int i;
    int j;

    if (argc == 3)
    {
        i = 0;
        while(i < 255)
        {
            used[i] = 0;
            i++;
        }
        i = 2;
        while(i > 0)
        {
            j = 0;
            while(argv[i][j])
            {
                if (i == 2 && used[(unsigned char) argv[i][j]] == 0)
                    used[(unsigned char) argv[i][j]] = 1;
                else if (i == 1 && used[(unsigned char) argv[i][j]] == 1)
                {
                    write(1, &argv[i][j], 1);
                    used[(unsigned char) argv[i][j]] = 2;
                }
                j++;
            }
            i--;
        }
    }
    write (1, "\n", 1);
    return (0);
}