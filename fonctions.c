#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Si la sauvegarde existe elle retourne 1, sinon 0 .

int Save_Exist()
{
    FILE * save = NULL;
    save = fopen("instance.txt","r");
    if (save != NULL)
    {
        return 1;
    }
    return 0;
}

// Elle sauvegarde l'instance en binaire .

void Save_Instance (CURRENT * instance)
{
    FILE *save = NULL;
    save=fopen("instance.txt","wb");
    if (!save)
    {
        exit(EXIT_FAILURE);
    }
    fwrite(instance,sizeof(CURRENT),1,save);
    fclose(save);
}

// Elle charge depuis le fichier binaire présent sur le dique (bureau), une instance sauvegardée .

void Load_Instance(CURRENT * instance)
{
    FILE * save;
    save=fopen("instance.txt","rb");
    if (save==NULL)
    {
        exit(EXIT_FAILURE);
    }
    fread(instance,sizeof(CURRENT),1,save);
    fclose(save);
}

// Les règles du jeu .

void How_To_Play()
{
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("At the beginning of the game, four seeds are placed in each pit."
    " Each player controls the six pits and their seeds on the player's side of the board\n"
    "Players take turns sowing their seeds. On a turn, the player removes all seeds from one of the pits under their control."
    "\nMoving counter-clockwise, the player drops one seed in each pit in turn, including the player's own store but not their opponent's.\n"
    "If the last sown seed lands in an empty pit owned by the player, and the opposite pit contains seeds,"
    "both the last seed and the opposite seeds are\ncaptured and placed into the player's store.\n"
    "If the last sown seed lands in the player's store, the player gets an additional move.   \n" 
    "There is no limit on the number of moves a player can make in their turn."
    "When one player no longer has any seeds in any of their pits, the game ends."
    "The other player moves all remaining seeds to their store, and the player with the most seeds in their store wins."
    "\n                                                   It is possible for the game to end in a draw.\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

// Permet l'affichage du jeu .

void Display_Instance(CURRENT * instance)
{
    printf("                                                                        %s      \n\n",instance->player_1_name);
    printf("                                                   kalah 1   6     5     4     3     2     1\n");
	printf("                                                   -------------------------------------------------\n");
	printf("                                                   |%5d|%5d|%5d|%5d|%5d|%5d|%5d|%5s|\n", a[0], a[6], a[5], a[4], a[3], a[2], a[1], "");
	printf("                                                          -----------------------------------\n");
	printf("                                                   |%5s|%5d|%5d|%5d|%5d|%5d|%5d|%5d|\n", "", b[6], b[5], b[4], b[3], b[2], b[1], b[0]);
	printf("                                                   -------------------------------------------------\n");
	printf("                                                             6     5     4     3     2     1 kalah 2\n\n");
	printf("                                                                        %s      \n",instance->player_2_name);
}

// Initialise le jeu, le menu du jeu dépendamment du choix du joueur et de l'existence du fichier sauvegarde .
int  init()
{
    char key;
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                   Welcome To The Kalah Game \n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                                                   Press ENTER key to Continue \n");
    getchar();
    printf("-----------------------------------------------------------Game Menu---------------------------------------------------------------------------------\n");
    printf("0-Play.\n"
           "1-How to play ?\n"
           "2-exit.\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    switch(getchar()-'0')
    {
        case 0:
            break;
        case 1:
            {
                How_To_Play();
                init();
                break;
            }
        case 2:
            printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("                                                   Have A Nice Day !");
            printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
            exit(EXIT_SUCCESS);
        default :
            exit(EXIT_FAILURE);
    }
    switch(Save_Exist())
    {
        case 0 :
        {
            printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("Press 0 to play a new game :\n");
            printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
            do 
            {
                key = getchar();
            }
            while (key != '0');
            return 0;
        }
        case 1 :
        {
            printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
            printf("0-Press 0 to play a new game. \n1-Press 1 to load a save game. \n");
            printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
            do
            {
                key = getchar();
            } 
            while (key != '0' && key != '1');
            return key - '0';
        }       
    }
}

// Génère soit 0 ou 1 au hasard (il nous sera utile pour sélectionner le joueur au début du jeu) .

int Random_Number()
{
    srand(time(NULL));
    int Max=1,Min=0;
    int Random=(rand()%(Max-Min+1))-Min;
    return Random;
}

// Initialise une instance (cas de nouvelle partie) .

void init_Instance(CURRENT * instance)
{   
    int seeds;
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Enter your names\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Player 1 :");
    scanf("%s",&instance->player_1_name);
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Player 2 :");
    scanf("%s",&instance->player_2_name);
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("How many seeds ? : ");
    scanf("%d",&seeds);
    instance -> player_1[0] = instance -> player_2[0] = 0;
    for(int i=1;i<7;i++)
    {
        instance -> player_1[i] = instance -> player_2[i] = seeds;
    }   
    instance->role = Random_Number();
}

// Teste si le jeu est terminé ou non .

int End_Game(CURRENT * instance)
{
    int player_1,player_2 = 1;
    for(int i=1;i<7;i++)
    {
        if (instance->player_1 [i] != 0)
            player_1 = 0;
        if (instance->player_2 [i] != 0)
            player_2 = 0;
    }
    if (player_1 || player_2)
        return 1;
    return 0;
}

// Il permet d'associer le role (à qui le role dans le jeu) au piles et le kalah des joueur .

int * Role_Player(CURRENT * instance)
{
    switch(instance->role)
    {
        case 0 :
            return a;
        case 1 :
            return b;
    }
}

// Valide le choix du joueur . 

int Pit_Choice(CURRENT * instance)
{
    int pit;
    switch(instance->role)
    {
        case 0 :
            printf("\n                                                   It's your turn %s \n",instance->player_1_name);
            break;
        case 1 :
            printf("\n                                                   What do you wish %s \n",instance->player_2_name);
            break;
    }
    getchar(); // pause / wait
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\nChoose a pit :");
    scanf("%d",&pit);
    switch(pit)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            {
                if (Role_Player(instance) [pit])
                    return pit;
                printf("\nEmpty Pit ! Choose another one :");
                Pit_Choice(instance);
                break;
            }
        default :
            printf("\nWrong Pit !");
            Pit_Choice(instance);
    }
}

// Permet d'annuler/continuer un tour dans le jeu .

void Cancel_Continue(CURRENT * instance)
{
    int cc;
    Display_Instance(instance);
    getchar(); 
    printf("\n1-Press 0 to cancel move.\n2-Press 1 to continue.\n ");
    scanf("%d",&cc);
    switch(cc)
    {
        case 0 :
        {
            Load_Instance(instance);
            Game(instance);
            break;
        }
        case 1 :
            break;
    }
    Save_Instance(instance); 
}

// Sens Trigonométrique => besoin d'un modulo positive .

int Positive_Modulo(int i, int n) 
{
    return (i % n + n) % n;
}

// La fonction motrice du code  et fonctionnelle du jeu (elle applique la logique du jeu) .

void Game(CURRENT * instance)
{
    Display_Instance(instance);
    do
    {
       int pocket,kalah;
       switch(instance->role)
       {
           case 0 :          // decreasing pits_number (tigonometry)
            {
                int pit = Pit_Choice(instance);
                pocket = Role_Player(instance) [pit];
                Role_Player(instance) [pit] = 0;
                pit = Positive_Modulo(pit-1,7);
                while (pocket)
                {
                    Role_Player(instance) [pit] +=1;
                    pocket --;
                    pit = Positive_Modulo(pit-1,7);
                }
                pit = Positive_Modulo(pit+1,7);
                if (! pit)                                                           // replay
                {
                    Cancel_Continue(instance);
                    Game(instance);
                    break;
                }
                if (Role_Player(instance) [pit] == 1)                                // capture
                {
                    kalah = instance->player_1 [pit] + instance->player_2 [pit];
                    instance->player_1 [pit] = instance->player_2 [pit] = 0;
                    Role_Player(instance) [0] += kalah;
                }
                Cancel_Continue(instance);
                break;
            }
            case 1 :         // increasing pits_number (tigonometry)
            {
                int pit = Pit_Choice(instance);
                pocket = Role_Player(instance) [pit];
                Role_Player(instance) [pit] = 0;
                pit = Positive_Modulo(pit+1,7);
                while (pocket)
                {
                    Role_Player(instance) [pit] +=1;
                    pocket --;
                    pit = Positive_Modulo(pit+1,7);
                }
                pit = Positive_Modulo(pit+1,7);
                if (! pit)                                                           // replay
                {
                    Cancel_Continue(instance);
                    Game(instance);
                    break;
                }
                if (Role_Player(instance) [pit] == 1)                                // capture
                {
                    kalah = instance->player_1 [pit] + instance->player_2 [pit];
                    instance->player_1 [pit] = instance->player_2 [pit] = 0;
                    Role_Player(instance) [0] += kalah;
                }
                Cancel_Continue(instance);
                break;
            }
       }
       instance->role = (instance->role + 1) % 2;
    } while (!End_Game(instance));
    for(int i=1 ; i<7 ; i++)
    {
        if (instance->player_1 [i])
            printf("\n                                                   winner : %s !\n",instance->player_2_name);
            main();
            //exit(EXIT_SUCCESS);
        if (instance->player_2 [i])
            printf("\n                                                   winner : %s !\n",instance->player_1_name);
            main();
            //exit(EXIT_SUCCESS);
    }
    printf("\n                                                   And the winner is ........ :\n");
    if ( instance->player_1 [0] > instance->player_2 [0] )
    {
        printf("\n                                                   winner : %s !\n",instance->player_1_name);
        main();
        //exit(EXIT_SUCCESS);        
    }
    else if  ( instance->player_1 [0] < instance->player_2 [0] )
    {
        printf("\n                                                   winner : %s !\n",instance->player_2_name);
        main();
        //exit(EXIT_SUCCESS);
    }
    else 
    {
        printf("\n                                                   Draw Game !\n");
        main();
        //exit(EXIT_SUCCESS);
    }
}

