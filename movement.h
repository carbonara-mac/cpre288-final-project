/*
 * movement.h
 *
 *  Created on: Nov 16, 2021
 *      Author: dannycao
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
int moveForward(oi_t *sensor_data, int centimeters);
void moveBackward(oi_t *sensor_data, int centimeters);
void turnRight(oi_t *sensor_data, int degrees);
void turnLeft(oi_t *sensor_data, int degrees);
int obstacleCheck(oi_t *sensor_data);


#endif /* MOVEMENT_H_ */
