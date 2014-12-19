#include<PONG.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

/* PONG Library code 
   Opensource under the lisence of GNU-GPL.
   The author is not responsible for any problem.
   Requires : 16 Compiler.
   */

#define INT_STRING(INT_NUM) #INT_NUM

char * lost_message;

void loadMenu( )
{
   int gd = DETECT,gm;

   initgraph(&gd,&gm,"C:\\TC\\BGI");
}

char checkInput( )
{
   if (kbhit( ))
   {
	return getch( );
   }

   return 0;
}

void drawMenu( )
{
    cleardevice( );

    int screen_width = getmaxx( );
    int screen_height = getmaxy( );

    outtextxy((screen_width / 2),(screen_height / 2),"PONG");
    outtextxy((screen_width / 2) - 50,(screen_height / 2) - 50,"1.Start Game");
    outtextxy((screen_width / 2) - 50,(screen_height / 2) - 100,"2.Exit");
}

void loadGame(struct Player *player,struct Opponent *opponent,struct Ball *ball)
{
    int screen_width  = getmaxx( );
    int screen_height = getmaxy( );
    srand(time(NULL));
    player->x = (screen_width / 2) - 100;
    player->y = (screen_height / 2);
    player->points = 0;

    opponent->x = (screen_width - 100);
    opponent->y = (screen_height / 2);
    opponent->points = 0;
    opponent->shot_type = 0;

    ball->x = (screen_width / 2);
    ball->y = (screen_height / 2);

    ball->direction = rand() % 2;
    ball->speed = 6;
}

void movePlayerUP(struct Player *player,int speed)
{
    player->y -= speed;
}

void movePlayerDOWN(struct Player * player,int speed)
{
    player->y += speed;
}

void checkPlayerBounds(struct Player * player)
{
    if ((player->y + 100) > (getmaxy() - 10))
    {
	player->y = (getmaxy() - 10) - 100;
    }
    else if (player->y < 100)
    {
	player->y = 100;
    }
}

void checkOpponentBounds(struct Opponent * opponent)
{
    if ((opponent->y + 100) > (getmaxy() - 10))
    {
	opponent->y = (getmaxy() - 10) - 100;
    }
    else if (opponent->y < 100)
    {
	opponent->y = 100;
    }
}

void checkPlayerCollision(struct Player *player,struct Ball *ball)
{
    if (player->x + 50 > ball->x && player->x < ball->x + 20 && player->y + 100 > ball->y && player->y < ball->y + 20)
    {
	int rand_pos = rand() % 3;

	if (rand_pos == 0)
	{
	    ball->direction = 2;
	}
	else if (rand_pos == 1)
	{
	    ball->direction = 1;
	}
	else if (rand_pos == 2)
	{
	    ball->direction = 3;
	}
    }
}

void checkOpponentCollision(struct Opponent *opponent,struct Ball *ball)
{
    if (opponent->x + 50 > ball->x && opponent->x < ball->x + 20 && opponent->y + 100 > ball->y && opponent->y < ball->y + 20)
    {
	int rand_pos = rand() % 3;

	if (rand_pos == 0)
	{
	    ball->direction = 4;
	}
	else if (rand_pos == 1)
	{
	    ball->direction = 0;
	}
	else if (rand_pos == 2)
	{
	    ball->direction = 5;
	}
    }
}

void checkBallCollision(struct Ball *ball)
{
    if (ball->y > (getmaxy() - 10))
    {
	ball->y = (getmaxy( ) - 10);

	if (ball->direction == 3)
	{
	    ball->direction = 2;
	}
	else if (ball->direction == 5)
	{
	    ball->direction = 4;
	}
    }
    else if (ball->y < 100 )
    {
	ball->y = 100;

	if (ball->direction == 2)
	{
	    ball->direction = 3;
	}
	else if (ball->direction == 4)
	{
	    ball->direction = 6;
	}
    }
}

void calculateOpponentMovement(struct Opponent *opponent,struct Ball *ball,int speed)
{
    if (opponent->y < ball->y)
    {
	opponent->y += speed;
    }
    else if (opponent->y > ball->y)
    {
	opponent->y -= speed;
    }
}

void moveBall(struct Ball *ball)
{
    if (ball->direction == 0)
    {
	int rand_inc_dec = rand() % 2;

	if (rand_inc_dec == 0)
	{
	    ball->x -= (ball->speed + 1);
	}
	else
	{
	    ball->x -= (ball->speed - 1);
	}
    }
    else if (ball->direction == 1)
    {
	int rand_inc_dec = rand() % 2;

	if (rand_inc_dec == 0)
	{
	    ball->x += (ball->speed + 1);
	}
	else
	{
	    ball->x += (ball->speed - 1);
	}
    }
    else if (ball->direction == 2)
    {
	int rand_inc_dec = rand() % 2;

	if (rand_inc_dec == 0)
	{
	    ball->x += (ball->speed + 1);
	    ball->y -= (ball->speed + 1);
	}
	else
	{
	    ball->x += (ball->speed - 1);
	    ball->y -= (ball->speed - 1);
	}
    }
    else if (ball->direction == 3)
    {
	int rand_inc_dec = rand() % 2;

	if (rand_inc_dec == 0)
	{
	    ball->x += (ball->speed + 1);
	    ball->y += (ball->speed + 1);
	}
	else
	{
	    ball->x += (ball->speed - 1);
	    ball->y += (ball->speed - 1);
	}
    }
    else if (ball->direction == 4)
    {
	int rand_inc_dec = rand() % 2;

	if (rand_inc_dec == 0)
	{
	    ball->x -= (ball->speed + 1);
	    ball->y -= (ball->speed + 1);
	}
	else
	{
	    ball->x -= (ball->speed - 1);
	    ball->y -= (ball->speed - 1);
	}
    }
    else if (ball->direction == 5)
    {
	int rand_inc_dec = rand() % 2;

	if (rand_inc_dec == 0)
	{
	    ball->x -= (ball->speed + 1);
	    ball->y += (ball->speed + 1);
	}
	else
	{
	    ball->x -= (ball->speed - 1);
	    ball->y += (ball->speed - 1);
	}
    }
}

void drawGame(struct Player *player,struct Opponent *opponent,struct Ball *ball)
{
   cleardevice();

   char * player_score_txt = "Player Score : ";
   char * opponent_score_txt = "Opponent Score : ";

   strcat(player_score_txt,INT_STRING(player->points));
   strcat(opponent_score_txt,INT_STRING(opponent->points));

   outtextxy(10,10,player_score_txt);
   outtextxy(10,20,opponent_score_txt);

   setcolor(RED);

   line(0,100,getmaxx(),getmaxy());
   line(0,getmaxy() - 10,getmaxx(),getmaxy() - 10);

   setcolor(WHITE);

   line(player->x,player->y,player->x + 50,player->y);
   line(player->x,player->y,player->x,player->y + 100);
   line(player->x,player->y + 100,player->x + 50,player->y + 100);
   line(player->x + 50,player->y,player->x + 50,player->y + 100);

   line(opponent->x,opponent->y,opponent->x + 50,opponent->y);
   line(opponent->x,opponent->y,opponent->x,opponent->y + 100);
   line(opponent->x,opponent->y + 100,opponent->x + 50,opponent->y + 100);
   line(opponent->x + 50,opponent->y,opponent->x + 50,opponent->y + 100);

   circle(ball->x,ball->y,10);
}

int getLooser(struct Player *player,struct Opponent *opponent,struct Ball *ball)
{
    if (player->x < ball->x)
    {
	return 1;
    }
    else if (ball->x > opponent->x)
    {
	return 2;
    }

    return 0;
}

void gameLost(int id)
{
    if (id == 1)
    {
        lost_message = "PLAYER LOST!";
    }
    else
    {
        lost_message = "OPPONENT LOST!";
    }
}

void drawLostScreen()
{
    setcolor(RED);
    outtextxy(getmaxx() / 2,getmaxy() / 2,lost_message);
}
