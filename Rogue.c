#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
//403171232

#define MAX_WIDTH  89 //Terminal width
#define MAX_HEIGHT 29 //Terminal height
#define MAX_ROOMS  6    // Number of rooms
#define MIN_DISTANCE 5  // Minimum distance between rooms
typedef struct {
    int x, y;
} pos;

typedef struct {
    int x, y, width, height;
    pos door;
    int chek;
} Room;

typedef struct {
    int Nfood;
    int ALAfood;
    int magicfood;
    int rottenfood;
} foods;
typedef struct player
{
    int xpos;
    int ypos;
    int floor;
    int health;
    int gold;
    int Mace;//      '!'             N
    int Dagger; //   '}'             D
    int arrow; //    '~'             D
    int wand; //     '$'             D
    int sword;//     '%'             N
    char weapon[20];
    int chaHealth; //charm   z
    int chaSpeed;  //charm   x
    int chaDamage; //charm   c
}player;

typedef struct {
    int deamen; // D
    int giant;//   G
    int fire;//    F
    int snake;//   S
    int undeed;//   U
} Monsters;

typedef struct {
    int x;
    int y;
    int health;
}Info;
Info deamen[6];
Info giant[6];
Info fire[6];
Info snake[6];
Info undeed[6];
Room rooms[MAX_ROOMS];
char map[30][90] ={" "};
void next_floor();
void game_menu();
void killMonster(player* user , Monsters * monster){

    int kill;//kill power
    int range;
    int *number;
    if(strcmp(user->weapon , "Mace")==0) kill=5 , range =1; 
    else if(strcmp(user->weapon , "Wand")==0) kill=15 , range =10;
    else if(strcmp(user->weapon , "Arrow")==0) kill=5 , range = 5;
    else if(strcmp(user->weapon , "Sword")==0) kill=10 , range = 1;
    else if(strcmp(user->weapon , "Dagger")==0) kill=12 , range =5;

    int ch= getch();
    
    switch(ch)
    {
        //left
        case 'h':
            for(int i =0 ; i< range &&  user->xpos -i-1 != '|' && user->xpos -i-1 != '-'; i++){
                int chara = mvinch(user->ypos, user->xpos -i -1) & A_CHARTEXT;
                int num;
                switch(chara){
                    case 'D':
                        for(int j =0 ; j< monster->deamen ; j++){
                            if(user->ypos==deamen[j].y && user->xpos -i -1 ==deamen[j].x){
                                num=j;
                                break;
                            }
                        }
                        deamen[num].health -=kill;
                        mvprintw(9 ,93 , "YOU Hit Deamen !!!");
                        if(deamen[num].health <= 0){
                            mvaddch(user->ypos, user->xpos -i -1 ,'.');
                            map[user->ypos][user->xpos -i -1] ='.';
                          //  deamen[num].x=0 ; deamen[num].y=0;
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Deamen !!!");
                            attroff(COLOR_PAIR(2));
                        }

                        break;

                    case 'F':
                        for(int j =0 ; j< monster->fire ; j++){
                            if(user->ypos==fire[j].y && user->xpos -i -1 ==fire[j].x){
                                num=j;
                                break;
                            }
                        }
                        fire[num].health -=kill;
                        mvprintw(9 ,93 , "YOU Hit Fire Breathing Monster !!!");
                        if(fire[num].health <= 0){
                            mvaddch(user->ypos, user->xpos -i -1 ,'.');
                            map[user->ypos][user->xpos -i -1] ='.';
                          //  fire[num].x=0 ; fire[num].y=0;
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Fire Breathing Monster !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;

                    case 'G':
                        for(int j =0 ; j< monster->giant ; j++){
                            if(user->ypos==giant[j].y && user->xpos -i -1 ==giant[j].x){
                                num=j;
                                break;
                            }
                        }
                        giant[num].health -=kill;
                        mvprintw(9 ,93 , "YOU Hit Giant !!!");
                        if(giant[num].health <= 0){
                            mvaddch(user->ypos, user->xpos -i -1 ,'.');
                            map[user->ypos][user->xpos -i -1] ='.';
                            //giant[num].x=0 ; giant[num].y=0;
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Giant !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                    case 'S':
                        for(int j =0 ; j< monster->snake ; j++){
                            if(user->ypos==snake[j].y && user->xpos -i -1 ==snake[j].x){
                                num=j;
                                break;
                            }
                        }
                        snake[num].health -=kill;
                        if(snake[num].health <= 0){
                            mvaddch(user->ypos, user->xpos -i -1 ,'.');
                            map[user->ypos][user->xpos -i -1] ='.';
                           // snake[num].x=0 ; snake[num].y=0;
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Deamen !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                    
                    case 'U':
                        for(int j =0 ; j< monster->undeed ; j++){
                            if(user->ypos==undeed[j].y && user->xpos -i -1 ==undeed[j].x){
                                num=j;
                                break;
                            }
                        }
                        undeed[num].health -=kill;
                        if(undeed[num].health <= 0){
                            mvaddch(user->ypos, user->xpos -i -1 ,'.');
                            map[user->ypos][user->xpos -i -1] ='.';
                            //undeed[num].x=0 ; undeed[num].y=0;
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Undeed !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                }
            }
        //down
        case 'l':
            for(int i =0 ; i< range &&  user->xpos +i+1 != '|' && user->xpos +i+1 != '-'; i++){
                int chara = mvinch(user->ypos, user->xpos -i -1) & A_CHARTEXT;
                int num;
                switch(chara){
                    case 'D':
                        for(int j =0 ; j< monster->deamen ; j++){
                            if(user->ypos==deamen[j].y && user->xpos +i +1 ==deamen[j].x){
                                num=j;
                                break;
                            }
                        }
                        deamen[num].health -=kill;
                        if(deamen[num].health <= 0){
                            mvaddch(user->ypos, user->xpos +i +1 ,'.');
                            map[user->ypos][user->xpos +i +1] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Deamen !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;

                    case 'F':
                        for(int j =0 ; j< monster->fire ; j++){
                            if(user->ypos==fire[j].y && user->xpos +i +1 ==fire[j].x){
                                num=j;
                                break;
                            }
                        }
                        fire[num].health -=kill;
                        if(fire[num].health <= 0){
                            mvaddch(user->ypos, user->xpos -i -1 ,'.');
                            map[user->ypos][user->xpos -i -1] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Fire Breathing Monster !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;

                    case 'G':
                        for(int j =0 ; j< monster->giant ; j++){
                            if(user->ypos==giant[j].y && user->xpos +i +1 ==giant[j].x){
                                num=j;
                                break;
                            }
                        }
                        giant[num].health -=kill;
                        if(giant[num].health <= 0){
                            mvaddch(user->ypos, user->xpos +i +1 ,'.');
                            map[user->ypos][user->xpos +i +1] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Giant !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                    case 'S':
                        for(int j =0 ; j< monster->snake ; j++){
                            if(user->ypos==snake[j].y && user->xpos -i +1 ==snake[j].x){
                                num=j;
                                break;
                            }
                        }
                        snake[num].health -=kill;
                        if(snake[num].health <= 0){
                            mvaddch(user->ypos, user->xpos +i +1 ,'.');
                            map[user->ypos][user->xpos +i +1] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Deamen !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                    
                    case 'U':
                        for(int j =0 ; j< monster->undeed ; j++){
                            if(user->ypos==undeed[j].y && user->xpos +i +1 ==undeed[j].x){
                                num=j;
                                break;
                            }
                        }
                        undeed[num].health -=kill;
                        if(undeed[num].health <= 0){
                            mvaddch(user->ypos, user->xpos +i +1 ,'.');
                            map[user->ypos][user->xpos +i +1] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Undeed !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                }
            }
        //up
        case 'j':
            for(int i =0 ; i< range &&  user->ypos -i-1 != '|' && user->ypos -i-1 != '-'; i++){
                int chara = mvinch(user->ypos -i -1, user->xpos) & A_CHARTEXT;
                int num;
                switch(chara){
                    case 'D':
                        for(int j =0 ; j< monster->deamen ; j++){
                            if(user->ypos-i-1==deamen[j].y && user->xpos  ==deamen[j].x){
                                num=j;
                                break;
                            }
                        }
                        deamen[num].health -=kill;
                        if(deamen[num].health <= 0){
                            mvaddch(user->ypos-i-1, user->xpos  ,'.');
                            map[user->ypos-i-1][user->xpos] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Deamen !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;

                    case 'F':
                        for(int j =0 ; j< monster->fire ; j++){
                            if(user->ypos -i-1==fire[j].y && user->xpos  ==fire[j].x){
                                num=j;
                                break;
                            }
                        }
                        fire[num].health -=kill;
                        if(fire[num].health <= 0){
                            mvaddch(user->ypos-i-1, user->xpos ,'.');
                            map[user->ypos-i-1][user->xpos] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Fire Breathing Monster !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;

                    case 'G':
                        for(int j =0 ; j< monster->giant ; j++){
                            if(user->ypos -i-1==giant[j].y && user->xpos ==giant[j].x){
                                num=j;
                                break;
                            }
                        }
                        giant[num].health -=kill;
                        if(giant[num].health <= 0){
                            mvaddch(user->ypos -i-1, user->xpos  ,'.');
                            map[user->ypos-i-1][user->xpos] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Giant !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                    case 'S':
                        for(int j =0 ; j< monster->snake ; j++){
                            if(user->ypos-i-1==snake[j].y && user->xpos  ==snake[j].x){
                                num=j;
                                break;
                            }
                        }
                        snake[num].health -=kill;
                        if(snake[num].health <= 0){
                            mvaddch(user->ypos-i-1, user->xpos  ,'.');
                            map[user->ypos-i-1][user->xpos] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Deamen !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                    
                    case 'U':
                        for(int j =0 ; j< monster->undeed ; j++){
                            if(user->ypos -i-1 ==undeed[j].y && user->xpos  ==undeed[j].x){
                                num=j;
                                break;
                            }
                        }
                        undeed[num].health -=kill;
                        if(undeed[num].health <= 0){
                            mvaddch(user->ypos-i-1, user->xpos  ,'.');
                            map[user->ypos-i-1][user->xpos] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Undeed !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                }
            }
        //right
        case 'k':
            for(int i =0 ; i< range &&  user->ypos +i+1 != '|' && user->ypos -i-1 != '-'; i++){
                int chara = mvinch(user->ypos +i +1, user->xpos) & A_CHARTEXT;
                int num;
                switch(chara){
                    case 'D':
                        for(int j =0 ; j< monster->deamen ; j++){
                            if(user->ypos+i+1==deamen[j].y && user->xpos  ==deamen[j].x){
                                num=j;
                                break;
                            }
                        }
                        deamen[num].health -=kill;
                        if(deamen[num].health <= 0){
                            mvaddch(user->ypos+i+1, user->xpos  ,'.');
                            map[user->ypos+i+1][user->xpos] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Deamen !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;

                    case 'F':
                        for(int j =0 ; j< monster->fire ; j++){
                            if(user->ypos +i+1==fire[j].y && user->xpos  ==fire[j].x){
                                num=j;
                                break;
                            }
                        }
                        fire[num].health -=kill;
                        if(fire[num].health <= 0){
                            mvaddch(user->ypos+i+1, user->xpos ,'.');
                            map[user->ypos+i+1][user->xpos] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Fire Breathing Monster !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;

                    case 'G':
                        for(int j =0 ; j< monster->giant ; j++){
                            if(user->ypos +i+1==giant[j].y && user->xpos ==giant[j].x){
                                num=j;
                                break;
                            }
                        }
                        giant[num].health -=kill;
                        if(giant[num].health <= 0){
                            mvaddch(user->ypos +i+1, user->xpos  ,'.');
                            map[user->ypos+i+1][user->xpos] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Giant !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                    case 'S':
                        for(int j =0 ; j< monster->snake ; j++){
                            if(user->ypos+i+1==snake[j].y && user->xpos  ==snake[j].x){
                                num=j;
                                break;
                            }
                        }
                        snake[num].health -=kill;
                        if(snake[num].health <= 0){
                            mvaddch(user->ypos+i+1, user->xpos  ,'.');
                            map[user->ypos+i+1][user->xpos] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Deamen !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                    
                    case 'U':
                        for(int j =0 ; j< monster->undeed ; j++){
                            if(user->ypos +i+1 ==undeed[j].y && user->xpos  ==undeed[j].x){
                                num=j;
                                break;
                            }
                        }
                        undeed[num].health -=kill;
                        if(undeed[num].health <= 0){
                            mvaddch(user->ypos+i+1, user->xpos  ,'.');
                            map[user->ypos+i+1][user->xpos] ='.';
                            attron(COLOR_PAIR(2));
                            mvprintw(9 ,93 , "YOU killed Undeed !!!");
                            attroff(COLOR_PAIR(2));
                        }
                        break;
                }
            }

    }


}

void reduce_health_over_time(player * user) {
    time_t start_time, current_time;
    time(&start_time);  // Initialize timer

    while (user->health > 0) {
        time(&current_time);
        
        if (difftime(current_time, start_time) >= 60) {
            (user->health)--;  // Decrease health
            start_time = current_time;  // Reset timer
            mvprintw( 5 , 94, "jooon = ");
            for(int i = 0 ; i < user->health/2 && i < 10 ; i++){
                mvprintw(5 ,102+i ,"*" );
            }
            printf("Health decreased! Current health: %d\n", user->health);
        }
        
        //sleep(1); // Prevent high CPU usage
    }
}
void charm_info(player *user ){
    mvprintw(7 , 94 ,"___Charms___");
    mvprintw(8 , 94 ,"Health  'z' = %d" ,user->chaHealth);
    mvprintw(9 , 94 ,"Speed   'x' = %d", user->chaSpeed);
    mvprintw(10 , 94 ,"Damage  'c' = %d", user->chaDamage);

}
void weapn_info(player * user){
    mvprintw(7 , 96 , "__Close range weapon__");
    mvprintw(8 , 93 , "Mace '!'  | %d |power = 5  | 8 direction",user->Mace );
    mvprintw(9 , 93 , "Sword '%%' | %d |power = 10 | all 8 direction" ,user->sword);
    mvprintw(11, 96 , "__Long range weapon__");
    mvprintw(12, 93 , "Dagger       '}'| %d |power = 12 | 5 " ,user->Dagger);
    mvprintw(13, 93 , "Magic wand   '$'| %d |power = 15 | 10 " , user->wand);
    mvprintw(14, 93 , "Normal arrow '~'| %d |power = 5  | 5 " , user->arrow);

    char weapon[15];
    if(strcmp("Mace" , user->weapon)==0) strcpy(weapon , "Mace");
    else if(strcmp("Dagger" , user->weapon)==0) strcpy(weapon , "Dagger");
    else if(strcmp("Wand" , user->weapon)==0) strcpy(weapon , "Magic wand");
    else if(strcmp("Arrow" , user->weapon)==0) strcpy(weapon , "Normal arrow");
    else if(strcmp("Sword" , user->weapon)==0) strcpy(weapon , "Sword");
    else if(strcmp("nothing" , user->weapon)==0) strcpy(weapon , "nothing");
    mvprintw(16 ,93, "'Weapon in your hand is %s'",weapon );

}
void food_info(foods * foodm ,player * user){
    if(!foodm->Nfood) foodm->Nfood=0;  mvprintw(7 , 94, "1)noraml food = %d" ,foodm->Nfood);
    if(!foodm->ALAfood) foodm->ALAfood=0;  mvprintw(8 , 94, "2)WOW food = %d" ,foodm->ALAfood);
    if(!foodm->magicfood) foodm->magicfood=0;  mvprintw(9 , 94, "3)magic food = %d" ,foodm->magicfood);

    char choice =getch();
    switch(choice){
        case '1':
            user->health+=2;
            foodm->Nfood-=1;
            break;
        case '2':
            user->health+=4;
            foodm->ALAfood-=1;
            break;
        
        case '3':
            user->health+=4;
            foodm->magicfood-=1;
            break;
    }
    mvprintw(5 , 94 ,"Jooon = %d" ,user->health);
    for(int i =0 ; i < user->health/2 && i<10 ; i++){
       mvprintw(5 , 102+i ,"*"); 
    }
}
int playermove(int y , int x , player * user ,const char* element){
    mvprintw(user->ypos , user->xpos , "%s" , element );

    user->ypos=y;
    user->xpos=x;
    attron(COLOR_PAIR(7));
    mvprintw(user->ypos , user->xpos , "@");
    attroff(COLOR_PAIR(7));
    move(user->ypos,user->xpos);
}

int checkposition(int newy, int newx , player * user , foods * foodm , Monsters * monster){
    //DEAMEN
    for(int j = 0 ; j <= monster->deamen ; j++){
        if(deamen[j].y  == newy && deamen[j].x -1 == newx  ||
          deamen[j].y -1 == newy && deamen[j].x  == newx  ||
          deamen[j].y    == newy && deamen[j].x +1 == newx  ||
          deamen[j].y +1 == newy && deamen[j].x  == newx  ||
          deamen[j].y -1 == newy && deamen[j].x +1 == newx  ||
          deamen[j].y -1 == newy && deamen[j].x -1 == newx  ||
          deamen[j].y +1 == newy && deamen[j].x +1 == newx  ||
          deamen[j].y +1 == newy && deamen[j].x -1 == newx  ){
            if(map[deamen[j].y][deamen[j].x]=='.'){
                deamen[j].y=0;
                deamen[j].x=0;
                break;
            }
            user->health -=2;
            attron(COLOR_PAIR(5));
            mvprintw(10 , 93 ,"Deamen hit on you !!!");
            attroff(COLOR_PAIR(5));
          }
    }
    //FIRE BREATHING MONSTER
    for(int j = 0 ; j <= monster->fire ; j++){
        if(fire[j].y  == newy && fire[j].x -1 == newx  ||
          fire[j].y -1 == newy && fire[j].x  == newx  ||
         fire[j].y  == newy && fire[j].x +1 == newx  ||
          fire[j].y +1 == newy && fire[j].x  == newx  ||
          fire[j].y -1 == newy && fire[j].x +1 == newx  ||
          fire[j].y -1 == newy && fire[j].x -1 == newx  ||
          fire[j].y +1 == newy && fire[j].x +1 == newx  ||
          fire[j].y +1 == newy && fire[j].x -1 == newx  ){
            if(map[fire[j].y][fire[j].x]=='.'){
                fire[j].y=0;
                fire[j].x=0;
                break;
            }
            user->health -=2;
            attron(COLOR_PAIR(5));
            mvprintw(10 , 93 ,"Fire Breathing Monster hit on you !!!");
            attroff(COLOR_PAIR(5));
          }
    }
    //SANKE
    for(int j = 0 ; j <= monster->snake ; j++){
        if(snake[j].y  == newy && snake[j].x -1 == newx  ||
          snake[j].y -1 == newy && snake[j].x  == newx  ||
         snake[j].y  == newy && snake[j].x +1 == newx  ||
          snake[j].y +1 == newy && fire[j].x  == newx  ||
          snake[j].y -1 == newy && snake[j].x +1 == newx  ||
          snake[j].y -1 == newy && snake[j].x -1 == newx  ||
          snake[j].y +1 == newy && snake[j].x +1 == newx  ||
          snake[j].y +1 == newy && snake[j].x -1 == newx  ){
            if(map[snake[j].y][snake[j].x]=='.'){
                snake[j].y=0;
                snake[j].x=0;
                break;
            }
            user->health -=2;
            attron(COLOR_PAIR(5));
            mvprintw(10 , 93 ,"Snake hit on you !!!");
            attroff(COLOR_PAIR(5));
          }
    }

    //giant
    for(int j = 0 ; j <= monster->giant ; j++){
        if(giant[j].y  == newy && giant[j].x -1 == newx  ||
          giant[j].y -1 == newy && giant[j].x  == newx  ||
         giant[j].y  == newy && giant[j].x +1 == newx  ||
          giant[j].y +1 == newy && giant[j].x  == newx  ||
          giant[j].y -1 == newy && giant[j].x +1 == newx  ||
          giant[j].y -1 == newy && giant[j].x -1 == newx  ||
          giant[j].y +1 == newy && giant[j].x +1 == newx  ||
          giant[j].y +1 == newy && giant[j].x -1 == newx  ){
            if(map[giant[j].y][giant[j].x]=='.'){
                giant[j].y=0;
                giant[j].x=0;
                break;
            }
            user->health -=2;
            attron(COLOR_PAIR(5));
            mvprintw(10 , 93 ,"Giant hit on you !!!");
            attroff(COLOR_PAIR(5));
          }
    }
    //undeed
    for(int j = 0 ; j <= monster->undeed ; j++){
        if(undeed[j].y  == newy && undeed[j].x -1 == newx  ||
          undeed[j].y -1 == newy && undeed[j].x  == newx  ||
         undeed[j].y  == newy && undeed[j].x +1 == newx  ||
          undeed[j].y +1 == newy && undeed[j].x  == newx  ||
          undeed[j].y -1 == newy && undeed[j].x +1 == newx  ||
          undeed[j].y -1 == newy && undeed[j].x -1 == newx  ||
          undeed[j].y +1 == newy && undeed[j].x +1 == newx  ||
          undeed[j].y +1 == newy && undeed[j].x -1 == newx  ){
            if(map[undeed[j].y][undeed[j].x]=='.'){
                deamen[j].y=0;
                deamen[j].x=0;
                break;
            }
            user->health -=2;
            attron(COLOR_PAIR(5));
            mvprintw(10, 93 ,"Undeed hit on you !!!");
            attroff(COLOR_PAIR(5));
          }
    }

// Get screen bounds
// int max_y, max_x;
// getmaxyx(stdscr, max_y, max_x);

// Read the character at (newy, newx)
int ch = mvinch(newy, newx) & A_CHARTEXT;

// Check for gold
if (ch == '*') {
    playermove(newy, newx, user, ".");
    user->gold++;
    mvprintw(4, 94, "Gold = %d", user->gold);
    attron(COLOR_PAIR(1));
    mvprintw(11 , 94 ,"Gold + +");
    attroff(COLOR_PAIR(1));
}


// Process movement cases
switch (ch) {
    case '.':
        playermove(newy, newx, user, ".");
        break;
    case '#':
        playermove(newy, newx, user, "#");
        break;
    case '+':
        playermove(newy , newx , user , "+");
        break;
    case 'f':
        playermove(newy, newx, user, ".");
        foodm->Nfood++;
        break;
    case '}':
        playermove(newy, newx, user, ".");
        user->Dagger+=10;
        break;
    case '~':
        playermove(newy, newx, user, ".");
        user->arrow+=20;
        break;
    case '$':
        playermove(newy, newx, user, ".");
        user->wand+=8;
        break;
    case '%':
        playermove(newy, newx, user, ".");
        user->sword=1;
        break;  
    case 'z':
        playermove(newy, newx, user, ".");
        user->chaHealth +=1;
        break;
    case 'x':
        playermove(newy, newx, user, ".");
        user->chaSpeed+=1;
        break;
    case 'c':
        playermove(newy, newx, user, ".");
        user->chaDamage+=1;
        break;
    case '>':
        next_floor(user , foodm);
        break;
    default:
        move(user->ypos, user->xpos);
        break;
}

}
int handel_input(int input , player * user, foods *foodm  , Monsters * monster){
    noecho();
    int newx;
    int newy;
    int flag=0;

    switch (input)
    {
        //up
    case 'j':
    case 'J':
        newx=user->xpos;
        newy= user->ypos-1;
        flag=1;
        break;
    //down
    case 'k':
    case 'K':
        newx=user->xpos;
        newy= user->ypos+1;
        flag=1;
        break;
    //right
    case 'l':
    case 'L':
        newx=user->xpos+1;
        newy= user->ypos;
        flag=1;
        break;
    //left
    case 'h':
    case 'H':
        newx=user->xpos-1;
        newy= user->ypos;
        flag=1;
        break;
        //up left
    case 'y':
    case 'Y':
        newx=user->xpos-1;
        newy= user->ypos-1;
        flag=1;
        break;
    //down
    case 'u':
    case 'U':
        newx=user->xpos+1;
        newy= user->ypos-1;
        flag=1;
        break;
    //right
    case 'b':
    case 'B':
        newx=user->xpos-1;
        newy= user->ypos+1;
        flag=1;
        break;
    //left
    case 'n':
    case 'N':
        newx=user->xpos+1;
        newy= user->ypos+1;
        flag=1;
        break;        
    
    case 'e':
    case 'E':
        food_info(foodm , user);
        break;
    case 'i':
        weapn_info(user);
        break;
    case '%':
        if(strcmp("Sword" , user->weapon)==0 && user->sword) strcpy(user->weapon , "nothing");
       else if(strcmp("nothing" , user->weapon)==0) {strcpy(user->weapon , "Sword"); mvprintw(7 ,93, "'Weapon in your hand is Sword'");}
        break;
    case '!':
        if(strcmp("Mace" , user->weapon)==0 && user->Mace) strcpy(user->weapon , "nothing");
        else if(strcmp("nothing" , user->weapon)==0) {strcpy(user->weapon , "Mace"); mvprintw(16 ,93, "'Weapon in your hand is Mace'" );}
        break;
    case '~':
        if(strcmp("Arrow" , user->weapon)==0 && user->arrow) strcpy(user->weapon , "nothing");
       else if(strcmp("nothing" , user->weapon)==0) {strcpy(user->weapon , "Arrow");mvprintw(16 ,93, "'Weapon in your hand is Noramal aroow'" );}
        break;
    case '}':
        if(strcmp("Dagger" , user->weapon)==0 && user->Dagger) strcpy(user->weapon , "nothing");
       else if(strcmp("nothing" , user->weapon)==0) {strcpy(user->weapon , "Dagger"); mvprintw(16 ,93, "'Weapon in your hand is Dagger'" );}
        break;
    case '$':
        if(strcmp("Wand" , user->weapon)==0 && user->wand) strcpy(user->weapon , "nothing");
       else if(strcmp("nothing" , user->weapon)==0) {strcpy(user->weapon , "Wand"); mvprintw(16 ,93, "'Weapon in your hand is  Magic Wand'" );}
        break;
    case 'p':
        charm_info(user);
        break;
    case ' ':
        killMonster(user , monster);
        break;
    default:
        break;
    }
    if(flag)
    checkposition(newy , newx , user ,foodm , monster);

}

void info(player * newplayer){
   // player * user;
    mvprintw(4 , 94 ,"Gold = %d" ,newplayer->gold);
    mvprintw(5 , 94 ,"Jooon = %d" ,newplayer->health);
    for(int i =0 ; i < newplayer->health/2 && i<10 ; i++){
       mvprintw(5 , 102+i ,"*"); 
    }
    //mvprintw(5 , 94 ,"Jooon = **********");
   for(int i =1 ; i<30 ; i++){
    mvaddch(i , 91 , '|');
   }
}
void draw_room(Room * room  ,player* user, Monsters * monster ,int * dagger_count ,int * arow_co , int * wand_co , int * sword_co) {
    // Draw the room walls
    room->chek=1;
    for (int i = room->x ; i < room->x + room->width; i++) {
        mvaddch(room->y, i, '-'); // Top wall
        mvaddch(room->y + room->height-1, i, '-'); // Bottom wall
        map[room->y][i]='-';
        map[room->y + room->height-1][i]='-';
    }

    for (int j = room->y; j < room->y + room->height - 2; j++) {
        mvaddch(j+1, room->x, '|'); // Left wall
        mvaddch(j+1, room->x + room->width-1, '|'); // Right wall
        map[j+1][room->x]='|';
        map[j+1][room->x + room->width-1]='|';
    }

    // Draw the inside of the room (space)
    for (int i = room->x + 1; i < room->x + room->width-1; i++) {
        for (int j = room->y + 1; j < room->y + room->height-1; j++) {
            mvaddch(j, i, '.');
            map[j][i]='.';
        }
    }
    //gold
    int gold_number = rand() % 5 ;
    for(int i =0 ; i< gold_number ; i++){
       int gold_x= room->x+1 + rand()% (room->width-2);
        int gold_y =room->y+1 +rand()% (room->height-2);
        map[gold_y][gold_x]='*';
        attron(COLOR_PAIR(1));
        mvaddch(gold_y , gold_x ,'*');
         attroff(COLOR_PAIR(1));
    }
    //pillar
 int pillar = rand() %((room->height-3 + room->width -4)/2)  ;
    for(int i =0 ; i< pillar ; i++){
       int pillar_x= room->x+1 + rand()% (room->width-2);
        int pillar_y =room->y+1 +rand()% (room->height-2);
        map[pillar_y][pillar_x]='O';
        mvaddch(pillar_y , pillar_x ,'O');
    }

    //food
    int nfood = rand()% 2;
    if(nfood){
       int nfood_x= room->x+1 + rand()% (room->width-2);
        int nfood_y =room->y+1 +rand()% (room->height-2);
        map[nfood_y][nfood_x]='f';
        attron(COLOR_PAIR(2));
        mvaddch(nfood_y , nfood_x ,'f'); 
        attroff(COLOR_PAIR(2));
    }
    // dagger
    //int dagcont= *dagger_count;
    if( room->width > 6){
        int dag = rand()% 2;
    if(dag){
       int dag_x= room->x+1 + rand()% (room->width-2);
        int dag_y =room->y+1 +rand()% (room->height-2);
        map[dag_y][dag_x]='}';
        attron(A_REVERSE);
        mvaddch(dag_y , dag_x ,'}'); 
        attroff(A_REVERSE);
        //(*dagger_count)++;
    }
    }
    // // arow
    // if(*arow_co <1){
         int a = rand()% 2;
    if(a){
       int a_x= room->x+1 + rand()% (room->width-2);
        int a_y =room->y+1 +rand()% (room->height-2);
        map[a_y][a_x]='~';
        attron(A_REVERSE);
        mvaddch(a_y , a_x ,'~'); 
        attroff(A_REVERSE);
    //     *arow_co++;
     }
    // } 
    // //magic wand
     if(room->width >7){
        int w = rand()% 2;
    if(w){
       int w_x= room->x+1 + rand()% (room->width-2);
        int w_y =room->y+1 +rand()% (room->height-2);
        map[w_y][w_x]='$';
        attron(A_REVERSE);
        mvaddch(w_y , w_x ,'$'); 
        attroff(A_REVERSE);
    //     *wand_co++;
     }
     }

    // //sword
     if(room->width > 9 && room->height > 9){
        int s = rand()% 2;
    if(s){
       int s_x= room->x+1 + rand()% (room->width-2);
        int s_y =room->y+1 +rand()% (room->height-2);
        map[s_y][s_x]='%';
        attron(A_REVERSE);
        mvaddch(s_y , s_x ,'%'); 
        attroff(A_REVERSE);
    //     *sword_co++;
     }
     }
     //health charm
    if(room->width > 6){
        int a = rand()% 2;
    if(a){
       int a_x= room->x+1 + rand()% (room->width-2);
        int a_y =room->y+1 +rand()% (room->height-2);
        map[a_y][a_x]='z';
        attron(COLOR_PAIR(3));
        mvaddch(a_y , a_x ,'z'); 
        attroff(COLOR_PAIR(3));
        }
    }
      //speed charm
      if(room->width > 8){
        int a = rand()% 2;
    if(a){
       int a_x= room->x+1 + rand()% (room->width-2);
        int a_y =room->y+1 +rand()% (room->height-2);
        map[a_y][a_x]='x';
        attron(COLOR_PAIR(3));
        mvaddch(a_y , a_x ,'x'); 
        attroff(COLOR_PAIR(3));
        }
    }

    //damage charm
    if(room->width > 9){
        int a = rand()% 2;
    if(a){
       int a_x= room->x+1 + rand()% (room->width-2);
        int a_y =room->y+1 +rand()% (room->height-2);
        map[a_y][a_x]='c';
        attron(COLOR_PAIR(3));
        mvaddch(a_y , a_x ,'c'); 
        attroff(COLOR_PAIR(3));
        }
    }

    // Deamen MONSTER
    if(room->width > 5 && room->height > 6){
        int a = rand()% 2;
    if(a){
       int a_x= room->x+1 + rand()% (room->width-2);
        int a_y =room->y+1 +rand()% (room->height-2);
        map[a_y][a_x]='D';
        monster->deamen++;
        deamen[monster->deamen].health=5;
        deamen[monster->deamen].x=a_x;
        deamen[monster->deamen].y = a_y;
        attron(COLOR_PAIR(4));
        mvaddch(a_y , a_x ,'D'); 
        attroff(COLOR_PAIR(4));
        }
    }

    //Fire Btreathing MONSTER
    if(room->width > 7 && room->height > 8){
        int a = rand()% 2;
    if(a){
       int a_x= room->x+1 + rand()% (room->width-2);
        int a_y =room->y+1 +rand()% (room->height-2);
        if(map[a_y][a_x]!='D'){
        map[a_y][a_x]='F';
        monster->fire++;
        fire[monster->fire].health=10;
        fire[monster->fire].x=a_x;
        fire[monster->fire].y = a_y;
        attron(COLOR_PAIR(4));
        mvaddch(a_y , a_x ,'F'); 
        attroff(COLOR_PAIR(4));
        }
    }
    }
    // Giant MONSTER
    if(room->width > 7 && room->height > 8){
        int a = rand()% 2;
    if(a){
       int a_x= room->x+1 + rand()% (room->width-2);
        int a_y =room->y+1 +rand()% (room->height-2);
        if(map[a_y][a_x]!='D' && map[a_y][a_x]!='F'){
        map[a_y][a_x]='G';
        monster->giant++;
        giant[monster->giant].health=15;
        giant[monster->giant].x=a_x;
        giant[monster->giant].y = a_y;
        attron(COLOR_PAIR(4));
        mvaddch(a_y , a_x ,'G'); 
        attroff(COLOR_PAIR(4));
        }
    }
    }
    // Snak MONSTER
    if(room->width > 6 && room->height > 6){
        int a = rand()% 2;
    if(a){
       int a_x= room->x+1 + rand()% (room->width-2);
        int a_y =room->y+1 +rand()% (room->height-2);
        if(map[a_y][a_x]!='D' && map[a_y][a_x]!='F' && map[a_y][a_x]!='G' ){
        map[a_y][a_x]='S';
        monster->snake++;
        snake[monster->snake].health=20;
        snake[monster->snake].x=a_x;
        snake[monster->snake].y = a_y;
        attron(COLOR_PAIR(5));
        mvaddch(a_y , a_x ,'S'); 
        attroff(COLOR_PAIR(5));
        }
    }
    }

    if(room->width > 8 && room->height > 8){
        int a = rand()% 2;
    if(a){
       int a_x= room->x+1 + rand()% (room->width-2);
        int a_y =room->y+1 +rand()% (room->height-2);
        if(map[a_y][a_x]!='D' && map[a_y][a_x]!='F' && map[a_y][a_x]!='G' && map[a_y][a_x]!='S'){
        map[a_y][a_x]='U';
        monster->undeed ++;
        undeed[monster->undeed].health=30;
        undeed[monster->undeed].x=a_x;
        undeed[monster->undeed].y = a_y;
        attron(COLOR_PAIR(5));
        mvaddch(a_y , a_x ,'U'); 
        attroff(COLOR_PAIR(5));
        }
    }
    }



    // Add a random door on one of the walls
    int door_side = rand() % 4;
    int door_x = room->x + 1 + rand() % (room->width - 2);
    int door_y = room->y + 1 + rand() % (room->height - 2);
 switch (door_side) {
        case 0: room->door.x = door_x;  room->door.y = room->y; break; // Top wall
        case 1: room->door.x = door_x;  room->door.y = room->y + room->height - 1; break; // Bottom wall
        case 2: room->door.x = room->x;  room->door.y = door_y; break; // Left wall
        case 3: room->door.x = room->x + room->width - 1;  room->door.y = door_y; break; // Right wall
    }

    // Draw the door
    mvaddch(room->door.y, room->door.x, '+');
    map[room->door.y][room->door.x] = '+';


    if(rooms[5].chek  && user->floor < 5){
        while(1){
       int s_x= room->x+1 + rand()% (room->width-2);
        int s_y =room->y+1 +rand()% (room->height-2);
        if(map[s_y][s_x]=='.'){
        map[s_y][s_x]='>';
        attron(COLOR_PAIR(1));
        mvaddch(s_y , s_x ,'>'); 
        attroff(COLOR_PAIR(1));
        for(int i =0 ; i < 6 ;i++){
            room[i].chek=0;
        }
        break;
        }
        else continue;
        }
    }

    if(user->floor==5 ){
        //ganj room
    }
}

int check_overlap(Room *new_room) {
    for (int i = 0; i < MAX_ROOMS; i++) {
        Room r = rooms[i];
        int buffer = 6;  // Buffer zone around existing rooms

        if (new_room->x < r.x + r.width + buffer && new_room->x + new_room->width > r.x - buffer &&
            new_room->y < r.y + r.height + buffer && new_room->y + new_room->height > r.y - buffer) {
            return 1; // Overlap or too close
        }
    }
    return 0;
}

void generate_rooms(player * user , Monsters * monster) {
    int room_count = 0;
    while (room_count < MAX_ROOMS) {
        Room new_room;
        new_room.width = 6 + rand() % 9;  
        new_room.height = 6 + rand() % 9;  
        new_room.x = rand() % (MAX_WIDTH - new_room.width - 1);
        new_room.y = rand() % (MAX_HEIGHT - new_room.height - 1);
        // printw("hi");
        //for  counting wepons
        int *dag_co=0;
        int * sward_co=0;
        int* arrow_co=0;
        int *wand_co=0;
        //printw("hiiii");

        if (!check_overlap(&new_room)) {
            rooms[room_count] = new_room;
            draw_room(&rooms[room_count], user,monster , dag_co, wand_co , arrow_co, sward_co);
            room_count++;
        }
    }
}

void connect_points(pos *a, pos *b) {
    int x = a->x, y = a->y;
    // mvprintw(3, 3, "%d %d" , x, y);
    if(map[y-1][x]=='.') y+=1;
    else if(map[y+1][x]=='.') y-=1;
    else if(map[y][x-1]=='.') x+=1;
    else if(map[y][x+1]=='.') x-=1;

    if(map[b->y-1][b->x]=='.') b->y+=1;
    else if(map[b->y+1][b->x]=='.') b->y-=1;
    else if(map[b->y][b->x-1]=='.') b->x+=1;
    else if(map[b->y][b->x+1]=='.') b->x-=1;
    mvaddch(b->y, b->x, '#');
    // Move horizontally first
    do {
        mvaddch(y, x, '#');
        if(map[y][x]=='.') mvaddch(y, x, '.');
        else if(map[y][x]=='|' ||map[y][x]=='-') mvaddch(y, x, '+');
        else if(map[y][x]=='*') {
            attron(COLOR_PAIR(1));
            mvaddch(y , x ,'*');
            attroff(COLOR_PAIR(1)); // black gold
        }
        else if(map[y][x]=='O') mvaddch(y, x, 'O');  
        else if(map[y][x]=='>') {
            attron(COLOR_PAIR(1));
            mvaddch(y , x ,'>');
            attroff(COLOR_PAIR(1));
        }
        else if(map[y][x]=='%') {
            attron(A_REVERSE);
            mvaddch(y , x ,'%');
            attroff(A_REVERSE);
        }
        else if(map[y][x]=='$') {
            attron(A_REVERSE);
            mvaddch(y , x ,'$');
            attroff(A_REVERSE);
        }
        else if(map[y][x]=='}') {
            attron(A_REVERSE);
            mvaddch(y , x ,'}');
            attroff(A_REVERSE);
        }
        else if(map[y][x]=='~') {
            attron(A_REVERSE);
            mvaddch(y , x ,'~');
            attroff(A_REVERSE);
        }
        else if(map[y][x]=='z') {
            attron(COLOR_PAIR(3));
            mvaddch(y , x ,'z');
            attroff(COLOR_PAIR(3));
        }
        else if(map[y][x]=='x') {
            attron(COLOR_PAIR(3));
            mvaddch(y , x ,'x');
            attroff(COLOR_PAIR(3));
        }
        else if(map[y][x]=='c') {
            attron(COLOR_PAIR(3));
            mvaddch(y , x ,'c');
            attroff(COLOR_PAIR(3));
        }
        else if(map[y][x]=='D') {
            attron(COLOR_PAIR(4));
            mvaddch(y , x ,'D');
            attroff(COLOR_PAIR(4));
        }
        else if(map[y][x]=='U') {
            attron(COLOR_PAIR(5));
            mvaddch(y , x ,'U');
            attroff(COLOR_PAIR(5));
        }
        else if(map[y][x]=='G') {
            attron(COLOR_PAIR(4));
            mvaddch(y , x ,'G');
            attroff(COLOR_PAIR(4));
        }
        else if(map[y][x]=='F') {
            attron(COLOR_PAIR(4));
            mvaddch(y , x ,'F');
            attroff(COLOR_PAIR(4));
        }
        else if(map[y][x]=='S') {
            attron(COLOR_PAIR(5));
            mvaddch(y , x ,'S');
            attroff(COLOR_PAIR(5));
        }
        x += (b->x > x) ? 1 : -1;
    }while (x != b->x);

    // Then move vertically
    do {
        mvaddch(y, x, '#');
        if(map[y][x]=='.') mvaddch(y, x, '.');
        else if(map[y][x]=='|' ||map[y][x]=='-' || map[y][x]=='+') mvaddch(y, x, '+');
        else if(map[y][x]=='*') {
            attron(COLOR_PAIR(1));
            mvaddch(y , x ,'*');
            attroff(COLOR_PAIR(1));
        }
        else if(map[y][x]=='O') mvaddch(y, x, 'O'); 
        else if(map[y][x]=='>') {
            attron(COLOR_PAIR(1));
            mvaddch(y , x ,'>');
            attroff(COLOR_PAIR(1));
        }
        else if(map[y][x]=='%') {
            attron(A_REVERSE);
            mvaddch(y , x ,'%');
            attroff(A_REVERSE);
        }
        else if(map[y][x]=='$') {
            attron(A_REVERSE);
            mvaddch(y , x ,'$');
            attroff(A_REVERSE);
        }
        else if(map[y][x]=='}') {
            attron(A_REVERSE);
            mvaddch(y , x ,'}');
            attroff(A_REVERSE);
        }
        else if(map[y][x]=='~') {
            attron(A_REVERSE);
            mvaddch(y , x ,'~');
            attroff(A_REVERSE);
        }
        else if(map[y][x]=='z') {
            attron(COLOR_PAIR(3));
            mvaddch(y , x ,'z');
            attroff(COLOR_PAIR(3));
        }
        else if(map[y][x]=='x') {
            attron(COLOR_PAIR(3));
            mvaddch(y , x ,'x');
            attroff(COLOR_PAIR(3));
        }
        else if(map[y][x]=='c') {
            attron(COLOR_PAIR(3));
            mvaddch(y , x ,'c');
            attroff(COLOR_PAIR(3));
        }
        else if(map[y][x]=='D') {
            attron(COLOR_PAIR(4));
            mvaddch(y , x ,'D');
            attroff(COLOR_PAIR(4));
        }
        else if(map[y][x]=='U') {
            attron(COLOR_PAIR(5));
            mvaddch(y , x ,'U');
            attroff(COLOR_PAIR(5));
        }
        else if(map[y][x]=='G') {
            attron(COLOR_PAIR(4));
            mvaddch(y , x ,'G');
            attroff(COLOR_PAIR(4));
        }
        else if(map[y][x]=='F') {
            attron(COLOR_PAIR(4));
            mvaddch(y , x ,'F');
            attroff(COLOR_PAIR(4));
        }
        else if(map[y][x]=='S') {
            attron(COLOR_PAIR(5));
            mvaddch(y , x ,'S');
            attroff(COLOR_PAIR(5));
        }
        y += (b->y > y) ? 1 : -1;
    }while (y != b->y);
}

void connect_doors() {

    
    for (int i = 0; i < MAX_ROOMS - 1; i++) {

      //  mvprintw(2+i, 3, "%d %d" , rooms[i].door.x , rooms[i].door.y);
        connect_points(&rooms[i].door, &rooms[i + 1].door);
    }
}
void next_floor(player * user , foods *foodm){
    clear();
    Monsters * mmonster;
    mmonster =malloc(sizeof(Monsters));
    for(int i=1 ; i<30 ; i++){
        for(int j =1 ; j<90 ; j++){
            map[i][j]=' ';
        }
    }
    generate_rooms(user ,mmonster);
    connect_doors();
    info(user);
    user->xpos = rooms[0].x +1;
    user->ypos =rooms[0].y +1;
     mvprintw(user->ypos ,  user->xpos  , "@");
    int ch;
    while((ch=getch())!='q'){
        for(int i =93 ; i <136 ; i++){
            for(int j =7 ; j<17 ; j++){
                mvprintw(j , i , " ");
            }
        }
        handel_input(ch , user ,foodm , mmonster);
    }

}

void New_game(){
    clear();
    player * newplayer;
    newplayer =malloc(sizeof(player));
    foods *foodm ;
    foodm =malloc(sizeof(foods));
    Monsters *monster;
    monster = malloc(sizeof(Monsters));
    monster->deamen=-1;
    generate_rooms(newplayer , monster);
    connect_doors();
    //newplayer->weapon= malloc(10 * sizeof(char));
    newplayer->xpos = rooms[0].x +1;
    newplayer->ypos =rooms[0].y +1;
    newplayer->health = 20;
    newplayer->floor=1;
    newplayer->Mace=1;
    newplayer->arrow=0;
    newplayer->Dagger=0;
    newplayer->wand=0;
    newplayer->sword=0;
    strcpy(newplayer->weapon , "Mace");
    info(newplayer);
    //reduce_health_over_time(newplayer);
    attron(COLOR_PAIR(7));
    mvprintw(newplayer->ypos ,  newplayer->xpos  , "@");
    attroff(COLOR_PAIR(7));
    int ch;
    noecho();
    while((ch=getch())!='q' || newplayer->health<=0){
        for(int i =93 ; i <136 ; i++){
            for(int j =4 ; j<17 ; j++){
                mvprintw(j , i , " ");
            }
        }
        handel_input(ch , newplayer ,foodm , monster);
        if(newplayer->health <= 0){
            clear();
            attron(COLOR_PAIR(1));
            mvprintw(14 , 58 , " You Died ;)  bye bye ....." );
            attroff(COLOR_PAIR(1));
            getch();
            break;
        }
        info(newplayer);
    }
}

void resume_game(){

}
void scorebored(){

}
void setting(){
    clear();
    printw("1)level\n");
    printw("2)color\n");
    printw("enter Ur choice:");

    int choice;
    scanw("%d", &choice);

    switch (choice)
    {
    case 1:
        clear();
        printw("1)Easy\n");
        printw("2)Medium\n");
        printw("3)Hard\n");
        printw("enter Ur choice:");
        break;
    case 2:
    clear();
        printw("1)Blue\n");
        printw("2)Dark Blue\n");
        printw("3)Light Blue\n");
        printw("enter Ur choice:");
    default:
        break;
    }
}
void profile(int linenumber , char user[] ,int score  , int num_game){
    clear();
    int choice;
    printw("1)new game\n");
    printw("2)resume game\n");
    printw("3)profile\n");
    printw("4)setting\n");
    printw("5)scorebored\n");
    printw("6)Exit\n");
    printw("enter Ur choice:");

    scanw("%d" , &choice);
    switch (choice)
    {
    case 1:
        New_game();
        break;
    case 2:
        resume_game();
        break;
    case 3:
        clear();
        printw("player : %s\n" , user);
        printw("top score : %d\n" , score);
        printw("num_game : %d\n" , num_game);
        printw("press q to Exit");
        int ch ;
        if((ch = getch())=='q')
        profile(linenumber , user , score, num_game);
        break;
    case 4:
        setting();
        break;
    case 5:
        scorebored();
        break;
    case 6:
        game_menu();
        break;
    default:
        break;
    }
}

void sign_up(){
    clear();
    int ch;
    int flag=1;
    char user[50] , xuser[50] ,pass[20] ;
    FILE *file = fopen("user.txt" , "a+");
    printw("username: ");
    echo();
    scanw("%s" , user);
     while(fscanf(file, "%s" ,xuser) != EOF ){
        if(strcmp(xuser , user)==0){
            flag=0;
       printw("username is used . please try again\n");
       getch();
        }
    }
    if(flag){
        //  password
        printw("password: ");
        while((ch=getch())!= 'q'){
            int flag1=0, flag2=0 , flag3=0;
            scanw("%s" , pass);
            for(int i=0 ; i < sizeof(pass) ; i++){
                if(islower(pass[i])){
                     flag1++;
                     }
                else if(isupper(pass[i])){
                     flag2++;
                     }
                else if(isdigit(pass[i])){
                     flag3++;
                    }
             } 
      if(flag1 && flag2 && flag3 && sizeof(pass)>7){
        fprintf(file, "%s %s\n" , user , pass);
        printw("you signed up seccssfuly");
        profile( 0 , user , 0 , 0);
      }
      else{
        printw("your password should contain lowrcase\n"
               "your password should contain uppercase\n" 
               "your password should contain number\n");
               continue;
      
      }
       // email
        }}
    
    fclose(file);
}

void sign_in(){
    clear();
    int ch ,flag=0 , linenumber=0 , score , num_game;
    char *xuser , *xpass , *xScore , *number_game;
    char  user[50] , pass[50] , line[100];
    FILE * file= fopen("user.txt", "r");
    printw("username: ");
    scanw("%s" , user);
    printw("password: ");
    scanw("%s" , pass);

     while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        // Split the line into tokens (Assuming format: username password score)
        xuser = strtok(line, " ");  // First word = username
        xpass = strtok(NULL, " ");  // Second word = password
        xScore = strtok(NULL, " ");  // Third word = score
        number_game = strtok(NULL, " ");//number of played game by user
        // Convert score to integer
        if (xScore != NULL) {
            score = atoi(xScore);
        } else {
            score = 0;  // Default score if missing
        }
        if (number_game != NULL) {
            num_game = atoi(number_game);
        } else {
            num_game = 0;  // Default score if missing
        }
        linenumber++;
        if(strcmp(xuser , user)==0 && strcmp(xpass , pass)==0){
         profile(linenumber , user , score ,num_game );
            flag=1;
            break;
        }
    }
    if(!flag){
        printw("wrong password or username , try again\n");
        printw("to Exit press 'q'");
        while((ch=getch())!='q'){
            sign_in();
        }
    }

    fclose(file);

}

 
void game_menu(){
    int choice;
    while (1) {
        clear();
        printw("1) Sign in\n");
        printw("2) Sign up\n");
        printw("3) play as guest\n");
        printw("4) Score table\n");
        printw("5) Exit\n");
        printw("Enter your choice: ");
        echo();
        scanw("%d", &choice);

        switch (choice) {
            case 1:
                sign_in();
                break;
            case 2:
                sign_up();
                break;
            case 3:
                New_game();
                break;
            case 4:
                scorebored();
                break;
            case 5:
                clear();
                mvprintw(1, 1, "Exiting... Goodbye!");
                getch();
                return;
            default:
                mvprintw(7, 1, "Invalid choice. Please choose between 1 and 5.");
                getch();
                break;
        }
    }    
}
 
int main() {
    srand(time(NULL)); // Seed for randomness
    initscr(); 
    start_color();        // Initialize ncurses
    noecho();          // Disable echoing
    curs_set(0);       // Hide cursor
    refresh();
   // init_pair(GOLD, COLOR_YELLOW, COLOR_BLACK); 
   // init_pair(NFOOD, COLOR_GREEN, COLOR_BLACK);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3 ,COLOR_MAGENTA , COLOR_BLACK);
    init_pair(4 , COLOR_BLUE, COLOR_BLACK);
    init_pair(5 , COLOR_RED, COLOR_BLACK);
    init_pair(7 , COLOR_CYAN , COLOR_BLACK);
    game_menu();
    endwin(); // Exit ncurses mode
    return 0;
}

