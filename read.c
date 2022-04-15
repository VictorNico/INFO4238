
// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototype
void read(char *path, int **Image);

// Driver code
int main()
{
    // read with passing the matrix
    // read("./images/img.ppm");
    printf("hjds\n");
    int **Image;

    read("./images/img.ppm", Image);
    printf("nbfdskjfd");
    exit(0);
    int rows = (sizeof(Image) / sizeof(Image[0]));
    int cols = (sizeof(Image) / sizeof(Image[0][0])) / rows;
    printf("rows:%d cols:%d", rows, cols);
    // afficher la matrice
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d\t", Image[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void read(char *path, int **Image)
{
    // File pointer to read from file
    FILE *inf;
    // open file
    printf("ok0");
    inf = fopen(path, "r");
    // catch error in file opening operation
    if (inf == NULL)
    {
        fprintf(stderr,
                "\nError to open the file\n");
        exit(1);
    }
    printf("ok");
    // get the type of image in first line of image
    char *format;
    fscanf(inf, "%s %*s", format);
    //char fileType[] = {format[0], format[1]};
    //strcat(fileType, a);
    //memcpy(fileType, type, 2);
    printf("ok1 %s %ld\n", format, sizeof(format));
    char P3[] = "P3";
    char P2[] = "P2";
    // manage type of image
    if (strcmp(format, P3) == 0)
    {
        // instructions
        // get the comment header of image in first line of image
        char comment[100];
        fgets(comment, 100, inf);
        //fscanf(inf, "%s %*s", comment);
        //fread(&comment, sizeof(char*), 1, inf);
        printf("ok3 %s\n", comment);
        // get the image matrix informations
        int rows = 0, cols = 0;
        fscanf(inf, "%d %d", &cols, &rows);
        //fread(&details, sizeof(struct ImageDetails), 1, inf);
        printf("ok4 cols:%d rows:%d\n", cols, rows);
        Image = (int **)malloc(rows * sizeof(int *));
        printf("00\n");
        //exit(0);
        // initialise the matrice to 0
        for (int i = 0; i < rows; i++)
        {
            Image[i] = (int *)malloc(cols * sizeof(int));
            for (int j = 0; j < cols; j++)
            {
                Image[i][j] = 0;
            }
        }
        printf("0\n");
        // get image matrice color code and save in our custom image matrice
        int color;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                //fread(&color, sizeof(struct ColorCode), 1, inf);
                fscanf(inf, "%d", &color);
                Image[i][j] = color;
            }
        }
        // afficher la matrice
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                printf("%d\t", Image[i][j]);
            }
            printf("\n");
        }
    }
    else if (strcmp(format, P2) == 0)
    {
        // instructions
    }
}
