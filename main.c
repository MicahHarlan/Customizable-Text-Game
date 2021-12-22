#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "player.h"

int random_index(int upper){
    int lower = 0;
    int num;
    
    num = (rand() % (upper - lower + 1)) + lower;
    
    if (num == upper){
        num = num - 1;
    }
    return num;
}

static char moves[3][6] = {
    "h",
    "b",
    "g"
};

int moves_size = 0;

static char beforeFight[100][100];
static int size_beforeFight = 0;

static char hit_dialogue[100][100];
static int size_dialogue = 0;

static char defeat_dialogue[100][100];
static int size_defeat = 0;


//READS IN WHAT PEOPLE SAY BEFORE FIGHT.
static void read_before_Fight(){
    FILE *fp = fopen("beforeFight.txt","r");
    char line[100];
    int i = 0;
    while (fgets(line,sizeof(line),fp)){
        strcpy(beforeFight[i], line);
        i++;
        size_beforeFight++;
    }
}

//Reads diologue enemies say to when hit in a fight.
static void read_hit(){
    int i;
    
    FILE *fpp = fopen("hit.txt","r");
    char lines[100];
     i = 0;
    while (fgets(lines,sizeof(lines),fpp)){
        strcpy(hit_dialogue[i], lines);
        i++;
        size_dialogue++;
    }
}

//READS IN DIALOGUE ENEMIES SAY WHEN DEFEATED.
static void read_defeat(){
    int i;
     //This what enemies say when they get defeated.
    FILE *fpc = fopen("defeat_dialogue.txt","r");
    char linez[100];
     i = 0;
    while (fgets(linez,sizeof(linez),fpc)){
        strcpy(defeat_dialogue[i], linez);
        i++;
        size_defeat++;
    }
}

static void fight(player *user, player *enemy){
    //FIGHT FUNCTION STARTS HERE.
    printf("\033[1;37m");
    printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX \n");
    printf("\033[0m");
    
    //MAKE RED.
    

 
    print_stats(user);		
    print_stats(enemy);
    printf("\033[1;34m");    
    printf("Your are fighting: %s \n",enemy->name);    


    printf("When you are ready to fight you will have 5 seconds to react to an enemy hitting, blocking\n");
    printf("\033[1;37m"); 
    printf("h = hit\n");
    printf("b = block\n");
    printf("Press any key when you are ready to fight!!\n");
    
    char mov[10];
    char ans[10];
    
    scanf("%s",ans);
    printf("\033[0m");
    //COUNT DOWN.
     printf("\033[1;37m"); 
    printf("3\n");
    sleep(1);
    printf("\33[2K");
    printf("2\n");
    sleep(1);
    printf("\33[2K");
    printf("1\n");
    sleep(1);
    printf("\33[2K");
    printf("\033[0m");
    system("clear");
   
    //printf("%d \n" ,user_health);

    //printf("%d \n" ,enemy_health);
    printf("\033[1;37m");  
    printf("XXXXXXXXXXXXXXX \n");
    printf("\033[0m");
    
    int zeroHealth = 1;
    while(zeroHealth == 1){
        int enemy_mov = random_index(2);
        int a = random_index(size_beforeFight);
        
        printf("\033[1;31m");
        printf("%s: ",enemy->name);
        printf("%s",beforeFight[a]);
        printf("\033[0m");
        
        //ENEMIES MOVE WHEN CHOOSING TO HIT.
        if(strcmp(moves[enemy_mov],"h") == 0){
            
            printf("\033[1;31m");
            printf("%s used his %s!\n",enemy->name,enemy->weaponName); //change this to say somehting better.
            printf("\033[0m");
            
            time_t user_input_time, input_start, input_end;
            input_start = time(NULL);
            scanf("%s",mov);
            input_end = time(NULL);
            user_input_time = input_end - input_start;
            
          
            printf("\033[1;37m");
            printf("Reaction Time: ");
        
            printf("\033[1;34m");
            printf("%d seconds\n",(int)user_input_time);
            printf("\033[0m");
            
            if(user_input_time > 5) { //NOT REACTING IN TIME.
                
                printf("%s hit was successful!\n", enemy->name);
                int dam = 0 - enemy->damage;
                update_health(user,dam);
                
                printf("\033[1;31m");
                printf("You took %d damage!\n",dam);
                printf("\033[0m");
        
            } else if(strcmp(mov, "h") == 0) { //ENEMY HITS AND USER HITS.
                
                printf("\033[1;37m");
                printf("You both hit each other!\n");
                int b = random_index(size_dialogue);
                
                printf("\033[1;34m");
                printf("%s: ", enemy->name);
                printf("%s ",hit_dialogue[b]);
                printf("\033[0m");
                
                
                int dam = 0 - enemy->damage;
                update_health(user,dam);
                
                printf("\033[1;31m");
                printf("You took %d damage!\n",dam);
                printf("\033[0m");
                
                        
                dam = 0 - user->damage;
                update_health(enemy,dam);
                
                printf("\033[1;31m");
                printf("%s took %d damage! \n",enemy->name,dam);
                printf("\033[0m");
                
            } else if(strcmp(mov,"b")==0){ //ENEMY HITS AND USER BLOCKS.
                
                int randNum = random_index(3);
                if(randNum == 0){
                    //RED
                    printf("\033[1;31m");
                    printf("Successfully blocked %s's attack!\n", enemy->name);
                    printf("\033[0m");


                } else if(randNum == 1){
                    float b = (user->block);
                    b = b /enemy->damage;
                    int block = b * enemy->damage;
                    block = 0 - block;
                    update_health(user,block);
                    printf("\033[1;31m");
                    printf("Your block reduced %s's attack damage only taking %d health!\n",enemy->name, block);
                    printf("\033[0m");
                } else if(randNum == 2){
                    
                    printf("\033[1;31m");
                    printf("Block failed, %s successfully hit you! \n", enemy->name);
                    printf("\033[0m");
                    
                    int dam = 0 - enemy->damage;
                    update_health(user,dam);
                    printf("\033[1;31m");
                    printf("You took %d damage! \n",enemy->damage);
                    printf("\033[0m");
                }
                
            } else { //INVALID COMMAND.
                
                printf("\033[1;37m");
                printf("Invalid option!!\n");
                printf("\033[0m");
                
                
                printf("\033[1;31m");
                printf("You took %d damage!\n",enemy->damage);
                printf("\033[0m");
                int dam = enemy->damage;
                dam = 0 - dam;
                update_health(user, dam);
            }
        
            sleep(2);
            
            
            //ENEMY USES BLOCK.
        } else if (strcmp(moves[enemy_mov],"b") == 0){
            
            printf("\033[1;31m");
            printf("%s chose to block!\n", enemy->name);
            printf("\033[0m");
            
            time_t user_input_time, input_start, input_end;
            
            input_start = time(NULL);
            scanf("%s",mov);
            input_end = time(NULL);
            user_input_time = input_end - input_start;
            
            printf("\033[1;37m");
            printf("Reaction Time: ");
        
            printf("\033[1;34m");
            printf("%d seconds\n",(int)user_input_time);
            printf("\033[0m");
            
            if(user_input_time > 5){
                
                printf("\033[1;31m");
                printf("You were too slow!\n");
                printf("\033[0m");
                
            } else if(strcmp(mov, "b") == 0 || strcmp(mov, "h") != 0){
                //RED
                printf("\033[1;31m");
                printf("Nothing happened! \n");
                printf("\033[0m");
                
            } else if(strcmp(mov, "h") == 0){
                int randNum = random_index(3);
                        
                if(randNum == 0){
                    //RED
                    printf("\033[1;31m");
                    printf("%s Successfully blocked your attack!\n", enemy->name);
                    printf("\033[0m");
                    
                } else if(randNum == 1){
                    float b = (enemy->block);
                    b = b /user->damage;
                    int block = b * user->damage;
                    block = 0 - block;
                    update_health(enemy,block);
                    
                    printf("\033[1;31m");
                    printf("%s's block reduced your attack damage! %s only took %d health!\n",enemy->name,enemy->name, block);
                    printf("\033[0m");
                    
            
                } else if(randNum == 2){
                    printf("You successfully hit %s! \n", enemy->name);
                    int dam = 0 - user->damage;
                    update_health(enemy,dam);
                    printf("\033[1;31m");
                    printf("%s took %d damage! \n",enemy->name,user->damage);
                    printf("\033[0m");
                }
                
            }
            sleep(2);
        }
    
        printf("\033[1;37m");
        printf("XXXXXXXXXXXXXXX \n");
        //printf("\033[0m");
        //MAKE BLUE
        printf("\033[1;34m");
        printf("%s's HEALTH: %d\n",user->name,user->health);
        
        //MAKE RED
        printf("\033[1;31m");
        printf("%s's HEALTH: %d\n",enemy->name,enemy->health);
        
        printf("\033[1;37m");
        printf("XXXXXXXXXXXXXXX \n");
        printf("\033[0m");
        

        if(user->health <=0 && enemy->health<=0){
         sleep(2);
	 system("clear");
         zeroHealth = 0;
         print_stats(user);
	 print_stats(enemy); 	
         printf("\033[1;31m");
         printf("DRAW!!\n");
         printf("\033[0m"); 
       } else  if (enemy->health <= 0){
            sleep(2);
            system("clear");
            zeroHealth = 0;
            print_stats(user);
            print_stats(enemy);
            int rand = random_index(size_defeat); //Calling random index
	    printf("\033[1;31m"); //Set output text to red.
	    printf("%s: %s \n",enemy->name,defeat_dialogue[rand]); //prints random output		            
            printf("\033[1;34m");
            printf("YOU WON!!\n");
            printf("\033[0m");
        } else  if(user->health <= 0){
            sleep(2);
            system("clear");
            print_stats(user);   
            print_stats(enemy);
            zeroHealth = 0;
            printf("\033[1;31m");
            printf("%s has won!\n",enemy->name);
            printf("\033[0m");
            printf("\033[0m");
            
        }
        
    
    }


}
static int player_level = 1;

//End of static
int main(int argc, char **argv) {
    system("clear");
    srand(time(0));

  int check = read_player(argv[1]);    
  check = 0;
    read_before_Fight();
    read_hit();
    read_defeat();
    
    player *user;
    user = getUser();
    
    player *enemy;
    
    int end = 0;
 
 
    while(end != 1){  
	if(user->health <= 0){
         end = 1; 
       }	
        enemy = findOponent(player_level);
	if(enemy == NULL){
         player_level++;
         end  = checkForWin();
} 
       if(end != 1 && enemy != NULL ){ 
       fight(user,enemy);
      }     
}

 if (user->health <= 0){ 
     printf("\033[1;31m");
     printf("You reached level %d \n",player_level); 
     printf("Game Over!!!!\n");
     printf("\033[0m"); 
} else if (user->health > 0){
    printf("\033[1:31m");
    printf("Congratulations You beat the game!!!\n");
    printf("\033[0m");
}       
   
  }
