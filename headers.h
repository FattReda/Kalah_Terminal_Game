#ifndef headers
#define headers

// Les constantes .

#define a instance->player_1
#define b instance->player_2

// La structure de l'instance (sauvegarde) .

typedef struct CURRENT
{
    char player_1_name [50];        // le nom du joueuer 1 .
    int  player_1 [7];              // la première case (0) : kalah / les autres cases : piles .
    char player_2_name [50];        // le nom du joueur 2 .
    int  player_2 [7];              // la première case (0) : kalah / les autres cases : piles .
    int  role;                      // le role de quel joueuer 1 ou 2 en 0 pour joueur 1 ou 1 pour joueur 2 .
}CURRENT;

// Les prototypes des fonctions .

int Save_Exist();
void Save_Instance (CURRENT * instance);
void Load_Instance(CURRENT * instance);
void How_To_Play();
void Display_Instance(CURRENT * instance);
int  init();
int Random_Number();
void init_Instance(CURRENT * instance);
int End_Game(CURRENT * instance);
int * Role_Player(CURRENT * instance);
int Pit_Choice(CURRENT * instance);
void Cancel_Continue(CURRENT * instance);
int Positive_Modulo(int i, int n) ;
void Game(CURRENT * instance);




#endif