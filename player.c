#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"

static player *player_list[100];
static int num_players = 0;

int read_player(char *filename){
    FILE *fin = fopen(filename, "r");
    char name[32];
    char weaponName[32];
    int health,level,damage,block;
    int count = 0;
    player playerz[100], *player_p[100];
    while (fscanf(fin, "%s %d %d %s %d %d",playerz[count].name,&playerz[count].health,&playerz[count].level,playerz[count].weaponName,&playerz[count].damage,&playerz[count].block) != EOF){
        player *pp = &playerz[count];
        add_player(pp->name,pp->health,pp->level,pp->weaponName,pp->damage,pp->block);
    }
    return 0;
    
}
 player *add_player(char *name, int health, int level,char *weapon,int damage, int block){
        player *pp = malloc(sizeof(player));
        strcpy(pp-> name, name);
        pp->health = health;
        pp->level = level;
        strcpy(pp->weaponName, weapon);
        pp->damage = damage;
        pp->block  = block;
        player_list[num_players] = pp;
        num_players++;
     return pp;
    }


//IF USED FOR DAMAGE CONVERT IT TO NEGATIVE BEFORE USING THIS.
player *update_health(player *p, int amount){
    int curr_health = p->health;
    p->health = p->health + amount;
    return p;
}

player *update_level(player *p){
    p->level = p->level + 1;
    return p;
}

//gets the player.
player *getUser(){
    return player_list[0];
}

//FIND oponents based on there level.
player *findOponent(int lev){
    int check = 0;
    player *p;
    for(int i = 0; i < num_players; i++){ //searches player_list 
        p = player_list[i]; 
        int a = p->level; 
        if(a == lev){ //if player p's level == int lev 
            p->level = 0; //set p's level to zero
            check = 1; //end the loop
            return player_list[i]; //return Enemy
        }
}
    if(check == 0){ //if level is empty return null 
        return NULL; // main method increments int lev for next time its 
		     //called.
    }
    return p;
}

void print_stats(player *p){
    
    
    printf("\033[1;37m");
    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n");
    
    printf("\033[1;37m");
    printf("Name: ");
    
    printf("\033[0;37m");
    printf("%s\n",p->name);
    
    printf("\033[1;37m");
    printf("Health: ");
    
    printf("\033[0;37m");
    printf("%d\n",p->health);
    
    printf("\033[1;37m");
    printf("Weapon: ");
    
    printf("\033[0;37m");
    printf("%s\n",p->weaponName);
    
    printf("\033[1;37m");
    printf("Damage: ");
    
    printf("\033[0;37m");
    printf("%d\n", p->damage);
    
    printf("\033[1;37m");
    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n");
    printf("\033[0m");
}

int checkForWin(){
    int num_zeros = 0;
    int vrai = 0;
    for(int i=0; i<num_players; i++){
       if(player_list[i]->level == 0){
          num_zeros++;
       }
    }
    if(num_zeros == num_players){
      vrai = 1;
    }
   return vrai;
}

 















