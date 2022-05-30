
// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // sleep exec thread
#include <sys/ioctl.h> // get winsize
// prototype


// Driver code
int main()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);

    for(int i=1; i<=2; i++)
    {
        for(int j=1; j<=w.ws_col; j++)
        {
            
            printf("");usleep(5000);
        }
        

        printf("\n");
    }
    for(int x =1; x <= 10 ; x++)
    {
        // V pattern
        for(int y =1; y <= 12 ; y++)
        {
            if(y <= x+2)
            {printf("");usleep(5000);}
            else
            {printf(" ");usleep(5000);}
        }
        for(int y = 12; y >= 1;y--)
        {
            if(y <= x+2)
            {printf("");usleep(5000);}
            else
            {printf(" ");usleep(5000);}
        }

        printf(" ");usleep(5000);
        // D pattern
        for(int j=1; j<=7; j++)
            {printf("");usleep(5000);}
        if (x<=6)
        {
            for(int j=1; j<=8; j++)
            {
                printf("");usleep(5000);
            }

            for(int j=1; j<=8; j++)
            {
                if(j<=x)
                    {printf("");usleep(5000);}
                else
                    {printf(" ");usleep(5000);}
            }
            for(int j=1; j<=28; j++)
            {
                printf("");usleep(5000);
            }
        }
        if (x>6 && x<=8)
        {
            for(int j=1; j<=16; j++)
            {
                if(j>=x && ((x==7 && j != 16) || (x == 8)))
                    {printf("");usleep(5000);}
                else
                    {printf(" ");usleep(5000);}
            }
            for(int j=1; j<=28; j++)
            {
                if(j>=10 && j<=18)
                    {printf("");usleep(5000);}
                else
                    {printf(" ");usleep(5000);}
            }
        }
        if (x>8){
            for(int j=1; j<=16; j++)
            {
                if(j>=x)
                    {printf("");usleep(5000);}
                else
                    {printf(" ");usleep(5000);}
            }
            for(int j=1; j<=28; j++)
            {
                if(j>=10 && j<=18)
                    {printf("");usleep(5000);}
                else
                    {printf(" ");usleep(5000);}
            }
        }
        printf(" ");usleep(5000);
        // V pattern
        for(int y =1; y <= 12 ; y++)
        {
            if(y <= x+2)
            {printf("");usleep(5000);}
            else
            {printf(" ");usleep(5000);}
        }
        for(int y = 12; y >= 1;y--)
        {
            if(y <= x+2)
            {printf("");usleep(5000);}
            else
            {printf(" ");usleep(5000);}
        }
        printf("\n");usleep(5000);
    }
    for(int x =1; x <= 10 ; x++)
    {
        // V pattern
        for(int y =1; y <= 12 ; y++)
        {
            if(y > x || y <= 2)
            {printf("");usleep(5000);}
            else
            {printf(" ");usleep(5000);}
        }
        for(int y = 12; y >= 1;y--)
        {
            if(y > x)
            {printf("");usleep(5000);}
            else
            {printf(" ");usleep(5000);}
        }

        printf(" ");usleep(5000);
        // D pattern
        for(int j=1; j<=7; j++)
            printf("");usleep(5000);
        if (x<=6)
        {

            for(int j=1; j<=16; j++)
            {
                if(j>9)
                    {printf("");usleep(5000);}
                else
                    {printf(" ");usleep(5000);}
            }
            for(int j=1; j<=28; j++)
            {
                if(j>=10 && j<=18)
                    {printf("");usleep(5000);}
                else
                    {printf(" ");usleep(5000);}
            }
        }
        // if (x>6 && x<=8)
        // {
        //     for(int j=1; j<=16; j++)
        //     {
        //         if(j>=x && ((x==7 && j != 16) || (x == 8)))
        //             {printf("");usleep(5000);}
        //         else
        //             {printf(" ");usleep(5000);}
        //     }
        // }
        if (x>6)
        {
            for(int j=1; j<=16; j++)
            {
                printf("");usleep(5000);
            }
            for(int j=1; j<=28; j++)
            {
                if(j>=10 && j<=18)
                    {printf("");usleep(5000);}
                else
                    {printf(" ");usleep(5000);}
            }
        }
        printf(" ");usleep(5000);
        // V pattern
        for(int y =1; y <= 12 ; y++)
        {
            if(y > x )
            {printf("");usleep(5000);}
            else
            {printf(" ");usleep(5000);}
        }
        for(int y = 12; y >= 1;y--)
        {
            if(y > x)
            {printf("");usleep(5000);}
            else
            {printf(" ");usleep(5000);}
        }
        printf("\n");usleep(5000);
    }
    for(int i=1; i<=2; i++)
    {
        for(int j=1; j<=w.ws_col; j++)
        {
            
            printf("");usleep(5000);
        }
        

        printf("\n");
    }
    
    return 0;
}
