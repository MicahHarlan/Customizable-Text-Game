Game Rules: 
The point of this game is to beat each level with out dying once. If you reach a health of 0 or lower
You lose the game. 

A hit can be blocked by an opponent.
A block can fail, partially be successful, or block all damage.
A partially successful block results only taking a percentage of damage.

COMMANDS:
 'h'+enter = hit
 'b'+ enter = block 

File Format: player.txt
This file reads in the NPCs of the game.
The first player in the file must be the users player.
The rest of the players are people who the user will fight. 
**The users level must be set to 0 or else the game won't work*
The level of the other players are the level that those players will appear on.
A level is only complete when all the players of a level have reached a health of 0. Then the user can move to the next level.    
Block is the percentage of damage a user will take if the block partially fails. 

FILE FORMAT FOR: player.txt
String NAME
int health
int level
String name of weapon
int weapon damage
int block 
name health level weapon damage block

ex. player.txt file any text after and including // is not in the file.
Micah 300 0 sword 25 8 //This is the user 
Skeleton 30 1 katana 10 8
Skeleton 30 1 katana 10 8
Skeleton 30 1 katana 10 8 //All level 1 are going to appear on level 1
Draugr 20 2 axe 10 8
Draugr 25 2 axe 12 8
Draugr 30 2 axe 15 8
Draugr 35 2 axe 20 8

FILE FORMAT FOR: hit.txt, defeat_dialogue.txt. beforeFight.txt
These 3 files all have the same format, each line is a quote an enemy can say.
The hit.txt is quotes enemies say when they get hit by the user
The defeat_dialogue.txt is quotes enemies say when they lose
The beforeFight.txt is quotes enemies use to taunt before a fight and right before the enemy choses their moves.
The file format is quotes on each line. Each line is a different quote.



