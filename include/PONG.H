#ifndef PONG_H
#define PONG_H

#include<graphics.h>
#include<conio.h>

struct Player
{
   int x;
   int y;
   int points;
};

struct Opponent
{
   int x;
   int y;
   int points;
};

struct Ball
{
  int x;
  int y;
  int direction;
  int speed;
};

void loadMenu();
char checkInput( );
void drawMenu( );
void loadGame(struct Player *player,struct Opponent *opponent,struct Ball *ball);
void movePlayerUP(struct Player *player,int speed);
void movePlayerDOWN(struct Player *player,int speed);
void checkPlayerBounds(struct Player *player);
void checkOpponentBounds(struct Opponent *opponent);
void checkPlayerCollision(struct Player *player,struct Ball *opponent);
void checkOpponentCollision(struct Player *player,struct Ball *opponent);
void checkBallCollision(struct Ball *ball);
void calculateOpponentMovement(struct Opponent *opponent,struct Ball *ball,int speed);
void moveBall(struct Ball *ball);
void drawGame(struct Player *player,struct Opponent *opponent,struct Ball *ball);
int getLooser(struct Player *player,struct Opponent *opponent,struct Ball *ball);
void gameLost(int id);
void drawLostScreen( );
#endif