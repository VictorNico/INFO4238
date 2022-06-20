int **convolution(int **image, int nblig, int nbcol)
{
    // Construction du filtre
    int val, nbLigFil, nbColFil;
    printf("Entrer le nombre de lignes de votre filtre : ");
    scanf("%d", &nbLigFil);
    printf("Entrer le nombre de colonnes de votre filtre : ");
    scanf("%d", &nbColFil);
    int filtre[nbLigFil][nbColFil], info = 0;

    printf("Type de filtre à appliquer : 1 pour moyenneur, 2 pour gaussien et 3 pour autre :");
    scanf("%d", &info);
    if (info == 1)
    {
        for (int i = 0; i < nbLigFil; i++)
        {
            for (int j = 0; j < nbColFil; j++)
            {
                filtre[i][j] = 1;
            }
        }
    }
    else if (info == 2 || info == 3)
    {
        printf("Entrer les valeurs du filtre\n");
        for (int i = 0; i < nbLigFil; i++)
        {
            printf("Entrer les valeurs de la ligne %d séparées un espace : ", i + 1);
            for (int j = 0; j < nbColFil; j++)
            {
                scanf("%d", &val);
                filtre[i][j] = val;
            }
        }
    }

    // Creation du tableau qui sera retourné
    int **imageT = NULL;
    imageT = malloc(nblig * sizeof(int *));
    for (int i = 0; i < nblig; i++)
    {
        imageT[i] = malloc(nbcol * sizeof(int));
    }

    int tmp, lig_trans, col_trans, sum = 0, fl = 0, fc = 0, tl = 0, tc = 0, sumf = 0;

    // Creation d'une matrice intermédiaire
    tmp = nbLigFil / 2;
    lig_trans = nblig + (tmp * 2);
    col_trans = nbcol + (tmp * 2);

    int tab_trans[lig_trans][col_trans];
    for (int i = 0; i < lig_trans; i++)
    {
        for (int j = 0; j < col_trans; j++)
        {
            if (i < tmp || i >= tmp + nblig || j < tmp || j >= tmp + nbcol)
            {
                tab_trans[i][j] = 257;
            }
            else
            {
                tab_trans[i][j] = image[i - tmp][j - tmp];
            }
        }
    }

    // Convolution proprement dite
    for (int i = tmp; i < tmp + nblig; i++)
    {
        for (int j = tmp; j < tmp + nbcol; j++)
        {
            int k = i - tmp;
            int l = j - tmp;
            sum = 0;
            sumf = 0;
            fl = 0;
            fc = 0;

            for (int li = k; li < k + nbLigFil; li++)
            {
                for (int co = l; co < l + nbLigFil; co++)
                {
                    if (tab_trans[li][co] != 257)
                    {
                        sum = sum + (tab_trans[li][co] * filtre[fl][fc]);
                        sumf = sumf + filtre[fl][fc];
                    }

                    fc = fc + 1;
                }
                fl = fl + 1;
                fc = 0;
            }

            imageT[tl][tc] = sum / sumf;
            tc = tc + 1;
        }
        tl = tl + 1;
        tc = 0;
    }

    return imageT;
}