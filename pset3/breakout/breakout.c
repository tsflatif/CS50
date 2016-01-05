//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle size
#define PADDLE_WIDTH 60
#define PADDLE_HEIGHT 10

// ball size
#define BALL_DIAMETER 20

// list of colors
char* colors[12] = {
"BLUE",
"RED",
"ORANGE",
"GREEN",
"MAGENTA",
"DARK_GRAY",
"GRAY",
"LIGHT_GRAY",
"PINK",
"CYAN",
"WHITE",
"YELLOW"};

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    double xVelocity = drand48()*4;
    double yVelocity = drand48()*4;
    
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        move(ball, xVelocity, yVelocity);
        
         // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
            xVelocity = -xVelocity;

        // bounce off left edge of window
        else if (getX(ball) <= 0)
            xVelocity = -xVelocity;
        
        // bounce off top edge of window
        else if (getY(ball) <= 0)
            yVelocity = -yVelocity;    
            
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            waitForClick();
            setLocation(ball, (getWidth(window) - BALL_DIAMETER) / 2, (getHeight(window) - BALL_DIAMETER)/ 2);
            setLocation(paddle, (getWidth(window) - PADDLE_WIDTH) / 2, (getHeight(window) - 3*PADDLE_HEIGHT));
        }

        GObject object = detectCollision(window, ball);    
        if (object != NULL)
        {
            if (object == paddle)
            {
               yVelocity = -yVelocity; 
            }   
        
            else if (strcmp(getType(object), "GRect") == 0)
            {
               removeGWindow(window, object);
               yVelocity = -yVelocity;
               points++;
               bricks--;
               updateScoreboard(window, label, points); 
            } 
        }
        
        pause(10);
        
         // wait for event
        GActionEvent event = getNextEvent(MOUSE_EVENT + ACTION_EVENT);
        
        if (event != NULL){
        
        // if window was closed
            if (getEventType(event) == WINDOW_CLOSED)
            {            
                goto game_over;         
            }
        
            else if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure paddle follows top cursor
                double x = getX(event) - getWidth(paddle) / 2;
            
                if (x < 0) 
                    x = 0;
                else if (x > (getWidth(window) -getWidth(paddle)))
                    x = getWidth(window) - getWidth(paddle);
                
                setLocation(paddle, x, getY(paddle));
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    game_over:
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int brickWidth = ((getWidth(window) / COLS) - 8);
    int brickHeight = PADDLE_HEIGHT;
    int buffer = 4;
    
    for (int i = 0; i < COLS; i++){
        for (int j = 0; j < ROWS; j++){
            GRect brick = newGRect(buffer + (brickWidth+8)*i, (brickHeight+8)*(4+j), brickWidth, brickHeight);
            setColor(brick, colors[j%12]);
            setFilled(brick, true);
            add(window, brick);
        }    
    }    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    int xBall = (getWidth(window) - BALL_DIAMETER) / 2;
    int yBall = (getHeight(window) - BALL_DIAMETER)/ 2;
    
    GRect ball = newGOval(xBall, yBall, 20, 20);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    int xPaddle = ((getWidth(window) - PADDLE_WIDTH) / 2);
    int yPaddle = (getHeight(window) - (3*PADDLE_HEIGHT));
    
    GRect paddle = newGRect(xPaddle, yPaddle, PADDLE_WIDTH, PADDLE_HEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-50");
    setColor(label, "C0C0C0");
    add(window, label);
    setLocation(label, (getWidth(window) - getWidth(label)) / 2, (getHeight(window) - getHeight(label)) / 2);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
