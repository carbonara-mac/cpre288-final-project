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
        oi_setWheels(0, 0); //STOP robot as soon as bump sensors are pushed
        /*
         * TODO: Establish a maneuvering standard when bump sensors are pushed
         */
        return 1; //return a 1 if left bump sensor = true
    }
    if (sensor_data->bumpRight)
    {
        oi_setWheels(0, 0);
        /*
         * TODO: Establish a maneuvering standard when bump sensors are pushed
         */
        return 2; //returns a 2 if right bump sensor = true
    }
    //************CLIFF SENSORS*******************************
    if (sensor_data->cliffLeft)
    {
        oi_setWheels(0, 0);
        /*
         * TODO: Establish a maneuvering standard for left cliff sensor
         */
        return 3; //returns a 3 if left cliff sensor = true
    }
    if (sensor_data->cliffFrontLeft)
    {
        oi_setWheels(0, 0);
        /*
         * TODO: Establish a maneuvering standard for left cliff sensor
         */
        return 4; //returns a 3 if left cliff sensor = true
    }
    if (sensor_data->cliffFrontRight)
    {
        oi_setWheels(0, 0);
        /*
         * TODO: Establish a maneuvering standard for left cliff sensor
         */
        return 5; //returns a 3 if left cliff sensor = true
    }
    if (sensor_data->cliffRight)
    {
        oi_setWheels(0, 0);
        /*
         * TODO: Establish a maneuvering standard for left cliff sensor
         */
        return 6; //returns a 3 if left cliff sensor = true
    }

    //*************Wheel Drop SENSORS*******************************
    if (sensor_data->wheelDropLeft)
    {
        oi_setWheels(0, 0);
        /*
         * TODO: Establish a manuvering standard for left wheel drop
         */
        return 7;
    }

    if (sensor_data->wheelDropRight)
    {
        oi_setWheels(0, 0);
        /*
         * TODO: Establish a manuvering standard for right wheel drop
         */
        return 8;
    }
return 0;
}

