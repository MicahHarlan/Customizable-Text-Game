#define MAX_NAME_CHAR 32
#include <stdio.h>
#include <string.h>
//#include "weapon.h"
//#include "level.h"



typedef struct {
  char name[MAX_NAME_CHAR];
  int health;
  int level;
  char weaponName[MAX_NAME_CHAR];
  int damage;
  int block; 
    
    
} player;

int read_player(char *filename);

int write_player(char *filename);

void print_stats(player *p);

player *add_player(char *name,int health, int level,char *weapon,int damage, int block);

player *update_health(player *p, int amount);

player *update_level(player *p);

player *getUser(); //GETS THE PLAYER.

char get_name(player *p); //figure out how to make this return a String.

player *findOponent(int lev); //given an int this finds the hostiles that are on each level, returns it then sets there level to 0, if null the player has beaten the level.

int checkForWin();//Checks if all the players in player list have been beaten.

