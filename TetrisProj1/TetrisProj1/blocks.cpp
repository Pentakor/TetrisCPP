#include "blocks.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include "point.h"
#include "general.h"

char blocks::get_block_three(int i, int j) const
{
    return block_r_three[i][j];
}

char blocks::get_block_four(int i, int j) const
{
    return block_r_four[i][j];
}

void blocks::set_blockarr(int i, int x, int y)
{
    block[i].changepoint(x, y);
}

point blocks::get_blockarr(int i) const
{
    point ret;

    ret.changepoint(block[i].getx(), block[i].gety());

    return ret;
}

void blocks::set_bshape(int shape)
{
    bshape = shape;
}

int blocks::get_bshape() const
{
    return bshape;
}

void blocks::rotate_clock_help()
{
    int temp;

    for (int i = 0; i < BLOCK_MEASURE_THREE / 2; i++)
    {
        for (int j = i; j < BLOCK_MEASURE_THREE - i - 1; j++)
        {
            temp = block_r_three[i][j];
            block_r_three[i][j] = block_r_three[BLOCK_MEASURE_THREE - 1 - j][i];
            block_r_three[BLOCK_MEASURE_THREE - 1 - j][i] = block_r_three[BLOCK_MEASURE_THREE - 1 - i][BLOCK_MEASURE_THREE - 1 - j];
            block_r_three[BLOCK_MEASURE_THREE - 1 - i][BLOCK_MEASURE_THREE - 1 - j] = block_r_three[j][BLOCK_MEASURE_THREE - 1 - i];
            block_r_three[j][BLOCK_MEASURE_THREE - 1 - i] = temp;
        }
    }
}

void blocks::rotate_anticlock_help()
{
    for (int i = 0; i < ANTI; i++)//one anti clock rotation is 3 clock rotations
    {
        rotate_clock();
    }
}

void blocks::rotate_i()
{
    if (block_r_four[0][1] == 'O')
    {
        block_r_four[2][0] = 'O';
        block_r_four[2][1] = 'O';
        block_r_four[2][2] = 'O';
        block_r_four[2][3] = 'O';

        block_r_four[0][1] = '.';
        block_r_four[1][1] = '.';
        block_r_four[3][1] = '.';

    }
    else
    {
        block_r_four[0][1] = 'O';
        block_r_four[1][1] = 'O';
        block_r_four[2][1] = 'O';
        block_r_four[3][1] = 'O';

        block_r_four[2][0] = '.';
        block_r_four[2][2] = '.';
        block_r_four[2][3] = '.';
    }
     
}

void blocks::rotate_clock()
{
    bool flag = false;

    if (bshape != SQRT && bshape != BOMB)//if the shape is square the rotation is irelevant
    {

        if (bshape == I)//for I shape different function
        {
            rotate_i();
        }

        else
        {
            rotate_clock_help();
        }

        for (int i = 0; i < ARRAY_T_LEN; i++)//near the wall rotation stopper. 
        {
            flag = (block[i].gety() == GAME_WIDTH - 1) || (block[i].gety() == 0)
        }

        if (flag)//the function checks if after roation there is block near the wall, if yes it is "cancels" the rotation by completing 360 degree rotation
        {
            for (int j = 0; j < ANTI; j++)
            {
                if (bshape == I)
                {
                    rotate_i();
                }

                else
                {
                    rotate_clock_help();
                }
            }
        }
        else
        {
            matrix_to_point();//getting the new points after rotation
        }
    }
}

void blocks::rotate_anticlock()
{
    if (bshape != SQRT && bshape != BOMB)//not relevant for square
    {
        rotate_anticlock_help();
        matrix_to_point();
    }
}

void blocks::clrblock_three()//clearing the matrix 3x3
{
    for (int i = 0; i < BLOCK_MEASURE_THREE; i++)
    {
        for (int j = 0; j < BLOCK_MEASURE_THREE; j++)
        {
            block_r_three[i][j] = '.';
        }
    }
}

void blocks::clrblock_four()//clearing the matrix 4x4
{
    for (int i = 0; i < BLOCK_MEASURE_FOUR; i++)
    {
        for (int j = 0; j < BLOCK_MEASURE_FOUR; j++)
        {
            block_r_four[i][j] = '.';
        }
    }
}

void blocks::initialize()
{
    int shape = rand() % AMOUNT_FIGURES;//randomizing the shape from 7 different shapes
    int rotation = rand() % AMOUNT_ROTATIONS;//randomizing the spawn rotation condition
    int bomb_chance = rand() % BOMB_CHANCE;

    bshape = shape;//naming the block shape
    clrblock_three();//clearing the rotation matrix 3x3
    clrblock_four();//clearing the rotation matrix 4x4

    if (bomb_chance == 0)
    {
        bshape = BOMB;
    }

    switch (shape) {//creting the rotation matrix fot the block
    case L:
        block_r_three[0][1] = 'O';
        block_r_three[1][1] = 'O';
        block_r_three[2][1] = 'O';
        block_r_three[2][2] = 'O';
        break;
    case LREV:
        block_r_three[0][1] = 'O';
        block_r_three[1][1] = 'O';
        block_r_three[2][1] = 'O';
        block_r_three[2][0] = 'O';
        break;
    case Z:
        block_r_three[0][1] = 'O';
        block_r_three[0][2] = 'O';
        block_r_three[1][0] = 'O';
        block_r_three[1][1] = 'O';
        break;
    case ZREV:
        block_r_three[0][0] = 'O';
        block_r_three[0][1] = 'O';
        block_r_three[1][1] = 'O';
        block_r_three[1][2] = 'O';
        break;
    case T:
        block_r_three[0][1] = 'O';
        block_r_three[1][0] = 'O';
        block_r_three[1][1] = 'O';
        block_r_three[1][2] = 'O';
        break;
    case I:
        block_r_four[0][1] = 'O';
        block_r_four[1][1] = 'O';
        block_r_four[2][1] = 'O';
        block_r_four[3][1] = 'O';
        break;
    default:
        break;
    }
    //initisalizing the coordination saving
    if ((bshape != SQRT) && (bshape != BOMB))
    {
        for (int i = 0; i < rotation; i++)//rotating the matrix according to randomized condition
        {
            rotate_clock();
        }
       
        block[4].changepoint(0, 4);
        matrix_to_point();//getting the poins values from the patrix
    }

    else if(bshape==SQRT)
    {
        block[0].changepoint(0, 4);
        block[1].changepoint(0, 5);
        block[2].changepoint(1, 4);
        block[3].changepoint(1, 5);
        block[4].changepoint(0, 4);
    }
    else
    {
        block[0].changepoint(0, 5);
        block[1].changepoint(0, 5);
        block[2].changepoint(0, 5);
        block[3].changepoint(0, 5);
        block[4].changepoint(0, 5);
    }
}

void blocks::matrix_to_point()
{
    point p0;
    point p1;
    point p2;
    point p3;
    int counter = 0;

    block[0] = p0;     
    block[1] = p1;
    block[2] = p2;
    block[3] = p3;
    if ((bshape != SQRT && bshape != I)&&bshape!=BOMB)//in that case the work is with 3x3 rotation matrix
    {
        for (int i = 0; i < BLOCK_MEASURE_THREE; i++)
        {
            for (int j = 0; j < BLOCK_MEASURE_THREE; j++)
            {
                if (block_r_three[i][j] == 'O')
                {                  
                    block[counter].changepoint(i+block[ARRAY_T_LEN].getx(), j + block[ARRAY_T_LEN].gety());
                    counter++;
                }
            }
        }
    }
    else if(bshape == I) //in that case working with 4x4 matrix if its I shape
    {
        for (int i = 0; i < BLOCK_MEASURE_FOUR; i++)
        {
            for (int j = 0; j < BLOCK_MEASURE_FOUR; j++)
            {
                if (block_r_four[i][j] == 'O')
                {
                   /* block[counter].x = i + block[4].x;
                    block[counter].y = j + block[4].y;*/
                    block[counter].changepoint(i + block[ARRAY_T_LEN].getx(), j + block[ARRAY_T_LEN].gety());
                    counter++;
                }
            }
        }
    }//if the block is SQUARE there is easier way implemented in initialize function  
}

void blocks::moveleft(const char(*board)[GAME_WIDTH])
{
    bool flag = false;
    for (int i = 0; i < ARRAY_T_LEN; i++)//checks for walls (in original tetris it does not comes from the other side)
    {
        flag = block[i].gety() == 0;
    }

    if (!flag)//check for collusion
    {
        for (int i = 0; i < ARRAY_T_LEN; i++)
        {
            flag = board[block[i].getx()][block[i].gety() - 1] == '0';
        }
    }

    if (!flag)
    {
        for (int i = 0; i <= ARRAY_T_LEN; i++)//changes points values
        {
            block[i].changey(block[i].gety() - 1);
        }
    }
}
void blocks::moveright(const char(*board)[GAME_WIDTH])
{
    bool flag = false;

    for (int i = 0; i < ARRAY_T_LEN; i++)
    {
        flag = block[i].gety() == GAME_WIDTH - 1;
    }

    if (!flag)//check for collusion
    {
        for (int i = 0; i < ARRAY_T_LEN; i++)
        {
            flag = board[block[i].getx()][block[i].gety() + 1] == '0';
        }
    }

    if (!flag)
    {
        for (int i = 0; i <= ARRAY_T_LEN; i++)
        {
            block[i].changey(block[i].gety() + 1);
        }
    }
}
bool blocks::movedown(const char(*board)[GAME_WIDTH])
{
   
    bool flag = false;

    for (int i = 0; i <= ARRAY_T_LEN; i++)//checks for the ground
    {
        falg = block[i].getx() == GAME_HEIGHT - 1;
    }
    if (!flag)//check for collusion
    {
        for (int i = 0; i < ARRAY_T_LEN; i++)
        {
            flag = board[block[i].getx() + 1][block[i].gety()] == '0';
        }
    }

    if (!flag)
    {
        for (int i = 0; i <= ARRAY_T_LEN; i++)
        {
            block[i].changex(block[i].getx() + 1);
        }
    }
    return flag;
}
void blocks::drop(const char(*board)[GAME_WIDTH])
{
    bool flag = false;

    while (!flag)
    {
       flag= movedown(board);
    }
}
