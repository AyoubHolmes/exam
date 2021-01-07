#include <unistd.h>

int main(int argc, char const *argv[])
{
    int used[255];
    int i;
    int j;

    i = 0;
    while(i < 255)
    {
        used[i] = 0;
        i++;
    }
    i = 2;
    while(i > 0)
    {
        if(i == 2 && used[(unsigned char)argv[i][j]] == 0)
            used[(unsigned char)argv[i][j]] = 1;
        else if (i == 1 && used[(unsigned char)argv[i][j]] == 1)
        {
            write(1, &argv[i][j], 1);
            used[(unsigned char)argv[i][j]] = 2;
        }
    }
    return 0;
}
