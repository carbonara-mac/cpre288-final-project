/*
 * movement.c
 *
 *  Created on: Nov 16, 2021
 *      Author: dannycao
 */

#include "open_interface.h"
#include "object.h"
#include "Timer.h"
#include "lcd.h"
#include "movement.h"

//#include "mission.h"

//NOTE: MAY HAVE TO REFORMAT CODE STRUCTURE

//TODO: Incorporate while loop into single move function

int moveForward(oi_t *sensor_data, int centimeters)
{
    //Check to see if move forwad 5 cm is actually 5 cm?

    centimeters *= 10; //convert centimeters into millimeters

    double sum = 0;
    oi_update(sensor_data);
    while (sum < (centimeters))
    {
        oi_setWheels(100, 100); //Move forward, "500 is max speed"
        oi_update(sensor_data);

        sum += sensor_data->distance;
    }

    oi_setWheels(0, 0); //STOP once distance has been reached
    return 0;
}

void moveBackward(oi_t *sensor_data, int centimeters)
{

    //Check to see if move backwards is off

    centimeters *= 10; //convert the centimeters into millimeters

    double sum = 0;
    oi_update(sensor_data);
    while (sum < (centimeters))
    {
        oi_setWheels(-100, -100); //Move backwards, "-500 is max speed"
        oi_update(sensor_data);

        sum -= sensor_data->distance;
    }
    oi_setWheels(0, 0); //STOP once distance has been reached
}

void turnRight(oi_t *sensor_data, int degrees)
{
    double sum = 0;
    oi_setWheels(-30, 30); //Rotate clockwise
    while (sum < degrees)
    {
        oi_update(sensor_data);
        sum -= (sensor_data->angle); //Continue to rotate until it has reached target degree
    }
    oi_setWheels(0, 0); //STOP once finished
}

void turnLeft(oi_t *sensor_data, int degrees)
{
    double sum = 0;
    oi_setWheels(30, -30); //Rotate counter clockwise
    while (sum < degrees)
    {
        oi_update(sensor_data);
        sum += (sensor_data->angle); //Continue to rotate until it has reached target degree
    }
    oi_setWheels(0, 0); //STOP once finished
}

int obstacleCheck(oi_t *sensor_data)
{
//**************BUMPER SENSORS*******************************
    if (sensor_data->bumpLeft)
    {
        oi_setWheels(0, 0); //STOP robot as soon as bumpLeft = TRUE
        moveBackward(sensor_data, 3); //move backwards 3 cm

        return 1; //return a 1 if left bump sensor = true
    }
    if (sensor_data->bumpRight)
    {
        oi_setWheels(0, 0); //STOP robot as soon as bumpRight = TRUE
        moveBackward(sensor_data, 3); //move backwards 3 cm

        return 2; //returns a 2 if right bump sensor = true
    }
    //************CLIFF SENSORS*******************************
    if (sensor_data->cliffLeft > 2800 || sensor_data->cliffLeft < 1600)
    {
        //TODO: Implement flag?
        oi_setWheels(0, 0); //STOP, robot sensed white tape or hole
        turnLeft(sensor_data, 45); //Turn left 45 degrees
        moveBackward(sensor_data, 5); //Move back 5 cm
        turnRight(sensor_data, 45); //revert back to original angle

        if (sensor_data->cliffLeft > 2800){
            oi_update(sensor_data);
            return 3; //tape detected for CL
        }
        else{
            oi_update(sensor_data);
            return 4; //hole detected for CL
        }
    }


    if (sensor_data->cliffFrontLeft > 2800 || sensor_data->cliffFrontLeft < 1600)
    {
        //TODO: Implement flag?
        oi_setWheels(0, 0); //STOP, robot sensed white tape or hole
        turnLeft(sensor_data, 60); //Turn left 60 degrees
        moveBackward(sensor_data, 5); //Move back 5 cm
        turnRight(sensor_data, 60); //revert back to original angle

        if (sensor_data->cliffFrontLeft > 2800)
        {
            oi_update(sensor_data);
            return 5; //tape detected for CFL
        }
        else
        {
            oi_update(sensor_data);
            return 6; //hole detected for CFL
        }
    }

    if (sensor_data->cliffFrontRight > 2800 || sensor_data->cliffFrontRight < 1600)
    {
        //TODO: Implement flag?
                oi_setWheels(0, 0); //STOP, robot sensed white tape or hole
                turnRight(sensor_data, 60); //Turn left 60 degrees
                moveBackward(sensor_data, 5); //Move back 5 cm
                turnLeft(sensor_data, 60); //revert back to original angle

                if (sensor_data->cliffFrontRight > 2800)
                {
                    oi_update(sensor_data);
                    return 7; //tape detected for CFR
                }
                else
                {
                    oi_update(sensor_data);
                    return 8; //hole detected for CFR
                }
            }

    if (sensor_data->cliffRight > 2800 || sensor_data->cliffRight < 1600)
    {
        //TODO: Implement flag?
               oi_setWheels(0, 0); //STOP, robot sensed white tape or hole
               turnRight(sensor_data, 45); //Turn left 45 degrees
               moveBackward(sensor_data, 5); //Move back 5 cm
               turnLeft(sensor_data, 45); //revert back to original angle

               if (sensor_data->cliffRight > 2800){
                   oi_update(sensor_data);
                   return 9; //tape detected for CR
               }
               else{
                   oi_update(sensor_data);
                   return 10; //hole detected for CR
               }
           }

    //*************Wheel Drop SENSORS*******************************
   /* DISCONTINUED
    if (sensor_data->wheelDropLeft)
    {
        oi_setWheels(0, 0);
        return 11;
    }

    if (sensor_data->wheelDropRight)
    {
        oi_setWheels(0, 0);
        return 12;
    }
    */

return 0;
}


