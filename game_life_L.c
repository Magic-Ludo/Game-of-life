/******************************************************************************
 *                              ██╗      ██████╗                              *
 *                              ██║     ██╔════╝                              *
 *                              ██║     ██║                                   *
 *                              ██║     ██║                                   *
 *                              ███████╗╚██████╗                              *
 *                              ╚══════╝ ╚═════╝                              *
 *                                                                            *
 *                                                                            *
 *      ██████╗ ██████╗  ██████╗  ██████╗ ██████╗  █████╗ ███╗   ███╗         *
 *      ██╔══██╗██╔══██╗██╔═══██╗██╔════╝ ██╔══██╗██╔══██╗████╗ ████║         *
 *      ██████╔╝██████╔╝██║   ██║██║  ███╗██████╔╝███████║██╔████╔██║         *
 *      ██╔═══╝ ██╔══██╗██║   ██║██║   ██║██╔══██╗██╔══██║██║╚██╔╝██║         *
 *      ██║     ██║  ██║╚██████╔╝╚██████╔╝██║  ██║██║  ██║██║ ╚═╝ ██║         *
 *      ╚═╝     ╚═╝  ╚═╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝         *
 *                                                                            *   
 *                                                                            *         
 *      Auteur : Corcos  Ludovic                                              *                
 *                                                                            *
 *      Université Clermont Auvergne | L2 Informatique                        *
 *                                                                            *
 *      Date : 25/03/2020                                                     *
 *                                                                            *
 *      Programme : game_life.c                                               *
 *                                                                            *
 *      Description :                                                         *
 *      Ce progremme permet de générer un jeu de la vie directement dans le   *
 *      terminal. Un menu permet à l'utilisateur de choisir ce qu'il veut     *
 *      afficher à l'écran. Les informations complémentaires sont dans le     *
 *      fichier pdf joint au programme. De plus, les fichiers *.lif sont les  *
 *      fichiers permetant le bon fonctionnement du programme. Merci de ne    *
 *      PAS LES MODIFIER, sauf le fichier "alea.lif" qui permet une           *
 *      configuration personalisé à l'utilisateur.                            *
 *                                                                            *
 *      Il se compile comme suit :                                            *
 *      gcc -Wall game_life_L.c -o game_life                                  *
 *      Puis :                                                                *
 *      ./game_life                                                           *
 *                                                                            *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE_MAT 50

/* -------------------------------------------------------------------------- */
/*                          Prototypes des fonctions                          */
/* -------------------------------------------------------------------------- */

void AfficheTab(int **tableau, int generation);

int **TabLife(FILE *fichier, int taille);

int Voisinage(int **tableau, int pos_x, int pos_y, int retrait);

int Mod(int nb_1, int nb_2);

int **InitTab(int size);

void **CopyTab(int **tab_a_copier, int **tab_result);

void Jeu(int **tab_init);

void Sierpinski(int **tab_init, int taille);

int Voisinage_Sierpinski(int **tableau, int pos_x, int pos_y, int retrait, int taille);

/* -------------------------------------------------------------------------- */
/*                         Fonction 'main' principale                         */
/* -------------------------------------------------------------------------- */

int main()
{

    int     choix;
    FILE   *fichier;
    int   **tab_life_init;

    //  Affichage du menu principal
    printf("\n\t\tMENU JEU DE LA VIE\n");
    printf("--------------------------------------------------\n\n\n");
    printf("1)\tCanon à planeur de Gosper\n");                 //Ok
    printf("2)\tFormes stables\n");                            // OK
    printf("3)\tFormes oscillantes\n");                        // Ok
    printf("4)\tEvolution ruche et escalier\n");               // Ok
    printf("5)\tLes pulsars\n");                               // OK
    printf("6)\tLes vaisseaux\n");                             // Ok
    printf("7)\tLe mangeur de planeurs\n");                    //Ok
    printf("8)\tCroissance infinie\n");                        //Ok
    printf("9)\tConfiguration aléatoire - personnalisable\n"); //ok
    printf("10)\tLe triangle de Sierpinski\n");
    printf("\t(Automate cellulaire - règle 126)\n");
    printf("11)\tQuitter\n\n");

    printf("Votre choix : ");
    scanf("%d", &choix);

    //  Traitement en fonction du choix de l'utilisateur
    switch (choix)
    {
    case 1:
        fichier = fopen("Canon.lif", "r");
        tab_life_init = TabLife(fichier, TAILLE_MAT);
        break;

    case 2:
        fichier = fopen("Stable.lif", "r");
        tab_life_init = TabLife(fichier, TAILLE_MAT);
        break;

    case 3:
        fichier = fopen("Oscil.lif", "r");
        tab_life_init = TabLife(fichier, TAILLE_MAT);
        break;

    case 4:
        fichier = fopen("Evol_r_e.lif", "r");
        tab_life_init = TabLife(fichier, TAILLE_MAT);
        break;

    case 5:
        fichier = fopen("Puls.lif", "r");
        tab_life_init = TabLife(fichier, TAILLE_MAT);
        break;

    case 6:
        fichier = fopen("Vaisseaux.lif", "r");
        tab_life_init = TabLife(fichier, TAILLE_MAT);
        break;

    case 7:
        fichier = fopen("Mange.lif", "r");
        tab_life_init = TabLife(fichier, TAILLE_MAT);
        break;

    case 8:
        fichier = fopen("Croissance.lif", "r");
        tab_life_init = TabLife(fichier, TAILLE_MAT);
        break;

    case 9:
        fichier = fopen("Alea.lif", "r");
        tab_life_init = TabLife(fichier, TAILLE_MAT);
        break;

    case 10:
        fichier = fopen("Sierpinski.lif", "r");
        tab_life_init = TabLife(fichier, 100);
        Sierpinski(tab_life_init, 100);
        break;

    case 11:
        printf("Au revoir :)\n");
        return EXIT_SUCCESS;

    default:
        break;
    }

    if (choix != 10)
    {
        Jeu(tab_life_init);
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                       Fonctions servant au programme                       */
/* -------------------------------------------------------------------------- */

/******************************************************************************
 *                                                                            *
 * Fonction : void AfficheTab(int **tableau, int generation)                  *
 *                                                                            *
 * Permet simplement d'afficher un tableau en 2 dimenssions.                  *
 * Là où une case est "1", affcihe ██ et si la case est "0", affcihe ░░.      *
 * Permet de construire l'affichage du jeu de la vie.                         *
 *                                                                            *
 * En entrée : Un tableau à 3 dimensions.                                     *
 *             Le nombre d'années sur lesquelles ont doit afficher le tableau.*
 *                                                                            *
 * En sortie : Rien, cette fonction ne fait que de l'affichage.               *
 *                                                                            *
 ******************************************************************************/

void AfficheTab(int **tableau, int generation)
{

    int i, j;
    int vie = 0;

    //  Efface l'écran
    system("clear");

    for (i = 0; i < TAILLE_MAT; i++)
    {
        for (j = 0; j < TAILLE_MAT; j++)
        {

            if (tableau[i][j] == 0)
            {
                printf("░░");
                // Ou bien :
                //printf("  ");
            }

            else if (tableau[i][j] == 1)
            {
                printf("██");
                vie++;
            }
        }

        printf("\n");
    }

    printf("\nGénération : %d\t\t\t", generation);
    printf("Population : %d\n\n", vie);
}

/******************************************************************************
 *                                                                            *
 * Fonction : int **TabLife(FILE *fichier, int taille)                        *
 *                                                                            *
 * Permet de remplir un tableau à 2 dimensions où sont stocké soit des "0"    *
 * soit des "1", lu préalablement dans un fichier *.lif.                      *
 *                                                                            *
 * En entrée : Un fichier.                                                    *
 *             La taille (nombre de lignes = nombre de colonnes), on part du  *
 *             principe que le tableau est carré et que la taille représente  *
 *             soit le nombre de ligne, soit le nombre de colonne.            *
 *                                                                            *
 * En sortie : Un tableau à 2 dimensions rempli de 0 ou de 1.                 *
 *                                                                            *
 ******************************************************************************/

int **TabLife(FILE *fichier, int taille)
{

    int     i, j, cell;
    int   **tab_life = InitTab(taille);

    if (fichier == NULL)
    {
        fprintf(stderr, "Le fichier *.lif n'a pas pu être ouvert\n");
        return (int **)EXIT_FAILURE;
    }

    //  On parcourt chaque caractère du fichier et on le met dans une case
    //  du tableau.
    for (i = 0; i < taille; i++)
    {
        for (j = 0; j < taille; j++)
        {

            fscanf(fichier, "%d", &cell);
            tab_life[i][j] = cell;
        }
    }

    if (fclose(fichier) == EOF)
    {
        fprintf(stderr, "Erreur lors de la fermeture du flux\n");
        return (int **)EXIT_FAILURE;
    }

    return tab_life;
}

/******************************************************************************
 *                                                                            *
 * Fonction : int Voisinage(int **tableau, int pos_x, int pos_y, int retrait) *
 *                                                                            *
 * Permet de calculer le voisinage d'une case d'un tableau suivant les règles *
 * du jeu de la vie. Voir le fichier joint pour plus d'explication.           *
 *                                                                            *
 * En entrée : Un tableau à 2 dimensions.                                     *
 *             La position de la case sur l'axe des abscisses.                *
 *             La position de la case sur l'axe des ordonnées.                *
 *             Le retrait (si la case est à 1 dès le départ, on ne veux pas   *
 *             la compter et on l'enlève).                                    *
 *                                                                            *
 * En sortie : Le nombre de voisins de la case.                               *
 *                                                                            *
 ******************************************************************************/

int Voisinage(int **tableau, int pos_x, int pos_y, int retrait)
{
    int i, j;
    int voisinage = 0;

    for (i = -1; i < 2; i++)
    {
        for (j = -1; j < 2; j++)
        {

            //  On utilise le modulo de manière à avoir un tableau torique.
            //  C'est à dire, que la case -1 par exemple correspondra à la
            //  case 49.
            int x = Mod(pos_x + (i), TAILLE_MAT);
            int y = Mod(pos_y + (j), TAILLE_MAT);

            //  On compte le nombre total de voisins
            if (tableau[x][y] == 1)
            {

                voisinage++;
            }
        }
    }

    return voisinage - retrait;
}

/******************************************************************************
 *                                                                            *
 * Fonction : int Mod(int nb_1, int nb_2)                                     *
 *                                                                            *
 * Permet de calculer le modulo mathématique de deux nombres.                 *
 *                                                                            *
 * En entrée : Un premier nombre.                                             *
 *             Un deuxième nombre.                                            *
 *                                                                            *
 * En sortie : Leurs modulo.                                                  *
 *                                                                            *
 ******************************************************************************/

int Mod(int nb_1, int nb_2)
{
    return (((nb_1 % nb_2) + nb_2) % nb_2);
}

/******************************************************************************
 *                                                                            *
 * Fonction : int **InitTab(int size)                                         *
 *                                                                            *
 * Permet d'initialiser un tableau carré à 2 dimensions.                      *
 *                                                                            *
 * En entrée : La taille du tableau.                                          *
 *                                                                            *
 * En sortie : Le tableau alloué dynamiquement.                               *
 *                                                                            *
 ******************************************************************************/

int **InitTab(int size)
{
    int     i;
    int   **tableau = (int **)malloc(size * sizeof(int *));

    for (i = 0; i < size; i++)
    {
        tableau[i] = (int *)malloc(size * sizeof(int));
    }

    return tableau;
}

/******************************************************************************
 *                                                                            *
 * Fonction : void **CopyTab(int **tab_a_copier, int **tab_result)            *
 *                                                                            *
 * Permet de copier un tableau à 2 dimensions dans un autre tableau déjà      *
 * initialisé.                                                                *
 *                                                                            *
 * En entrée : Le tableau à copier.                                           *
 *             Le tableau de destination.                                     *
 *                                                                            *
 * En sortie : Le tableau copié alloué dynamiquement.                         *
 *                                                                            *
 ******************************************************************************/

void **CopyTab(int **tab_a_copier, int **tab_result)
{
    int i, j;

    for (i = 0; i < TAILLE_MAT; i++)
    {
        for (j = 0; j < TAILLE_MAT; j++)
        {
            tab_result[i][j] = tab_a_copier[i][j];
        }
    }

    return tab_result;
}

/******************************************************************************
 *                                                                            *
 * Fonction : void Jeu(int **tab_init)                                        *
 *                                                                            *
 * Permet de lancer une simulation de jeu de la vie.                          *
 *                                                                            *
 * En entrée : Un tableau rempli de "0" ou de "1".                            *
 *                                                                            *
 * En sortie : La fonction main(), en effet, une fois que la simulation est   *
 * finie, on laisse la choix à l'utilisateur d'en lancer une nouvelle.        *
 *                                                                            *
 ******************************************************************************/

void Jeu(int **tab_init)
{
    int     gene = 0;
    int     i, j, voisins, generations;
    int   **tab_life_evol = InitTab(TAILLE_MAT);

    //  On demande à l'utilisateur combien de générations il souhaite simuler.
    printf("\nSaisir le nombre de génération à simuler : ");
    scanf("%d", &generations);

    while (gene <= generations)
    {

        //  On fait une pause de 100ms pour créer une annimation.
        //  Si on n'en met pas, on aurai juste le résultat final qui s'afficherai.
        usleep(100000);
        AfficheTab(tab_init, gene);

        for (i = 0; i < TAILLE_MAT; i++)
        {

            for (j = 0; j < TAILLE_MAT; j++)
            {

                //  On calcule le nombre de voisins.
                voisins = Voisinage(tab_init, i, j, tab_init[i][j]);

                //  Vérification et applications des règles du jeu de la vie
                //  en fonction du nombre de voisins de la case.
                //  Le résultat se trouve dans le tableau tab_life_evol.
                if (tab_init[i][j] == 1)
                {
                    if (voisins < 2 || voisins > 3)
                    {
                        tab_life_evol[i][j] = 0;
                    }

                    else
                    {
                        tab_life_evol[i][j] = 1;
                    }
                }

                else
                {

                    if (voisins == 3)
                    {
                        tab_life_evol[i][j] = 1;
                    }
                    else
                    {
                        tab_life_evol[i][j] = 0;
                    }
                }
            }
        }

        //  On copie le tableau tab_life_evol dans le tableau d'origine
        //  tab_init et on recommence la vérifications des voisins et
        //  l'application dans le tableau tab_life_evol jusqu'à ce qu'on
        //  ai fini le nombre de simulations à générer.
        tab_init = CopyTab(tab_life_evol, tab_init);

        gene++;
    }

    for (i = 0; i < TAILLE_MAT; i++)
    {

        free(tab_life_evol[i]);
    }

    free(tab_life_evol);

    main();
}

/******************************************************************************
 *                                                                            *
 * Fonction : void Sierpinski(int **tab_init, int taille)                     *
 *                                                                            *
 * Permet de lancer une simulation d'automate cellulaire avec la règle 126.   *
 * Cf : https://mathworld.wolfram.com/Rule126.html                            *
 *                                                                            *
 * En entrée : Un tableau rempli de "0" ou de "1".                            *
 *             La taille.                                                     *
 *                                                                            *
 * En sortie : La fonction main(), en effet, une fois que la simulation est   *
 * finie, on laisse la choix à l'utilisateur d'en lancer une nouvelle.        *
 *                                                                            *
 ******************************************************************************/

void Sierpinski(int **tab_init, int taille)
{
    int i, j, voisins;

    //  Pas de boucle while ici, car le voisinage est définie seulement sur la
    //  même ligne, pas besoin non plus d'un autre tableau.
    for (i = 0; i < taille - 1; i++)
    {

        for (j = 0; j < taille; j++)
        {

            voisins = Voisinage_Sierpinski(tab_init, i, j, tab_init[i][j], taille);

            //  Application de la règle 126.
            if (tab_init[i][j] == 1)
            {
                if (voisins == 2)
                {
                    tab_init[i + 1][j] = 0;
                }

                else
                {
                    tab_init[i + 1][j] = 1;
                }
            }

            else
            {

                if (voisins == 1 || voisins == 2)
                {
                    tab_init[i + 1][j] = 1;
                }
                else
                {
                    tab_init[i + 1][j] = 0;
                }
            }
        }
    }

    //  On affiche le tableau ligne par ligne une fois qu'il a été complétement
    //  rempli.
    for (i = 0; i < taille; i++)
    {
        for (j = 0; j < taille; j++)
        {

            if (tab_init[i][j] == 0)
            {
                printf("░░");

                // Ou bien :
                //printf("  ");
            }

            else if (tab_init[i][j] == 1)
            {
                printf("██");
            }
        }

        usleep(100000);
        printf("\n");
    }

    for (i = 0; i < taille; i++)
    {

        free(tab_init[i]);
    }

    free(tab_init);

    main();
}

/******************************************************************************
 *                                                                            *
 * Fonction :                                                                 *
 * int Voi...ki(int **tableau, int pos_x, int pos_y, int retrait, int taille) *
 *                                                                            *
 * Permet de calculer le voisinage d'une case d'un tableau suivant les règles *
 * d'un automate cellulaire avec la règle 126.                                *
 * Voir le fichier joint pour plus d'explication.                             *
 *                                                                            *
 * En entrée : Un tableau à 2 dimensions.                                     *
 *             La position de la case sur l'axe des abscisses.                *
 *             La position de la case sur l'axe des ordonnées.                *
 *             Le retrait (si la case est à 1 dès le départ, on ne veux pas   *
 *             la compter et on l'enlève).                                    *
 *                                                                            *
 * En sortie : Le nombre de voisins de la case.                               *
 *                                                                            *
 ******************************************************************************/

int Voisinage_Sierpinski(int **tableau, int pos_x, int pos_y, int retrait, int taille)
{
    int voisinage = 0;
    int i;

    for (i = -1; i < 2; i++)
    {

        int y = Mod(pos_y + (i), taille);

        if (tableau[pos_x][y] == 1)
        {

            voisinage++;
        }
    }

    return voisinage - retrait;
}
