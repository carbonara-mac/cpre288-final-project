/*
 * displayinfo.c
 *
 *  Created on: Dec 4, 2021
 *      Author: Ainara Machargo
 */
 
 #include "lcd.h"
 #include "open_interface.h"
 #include "movement.h"
 #include "Timer.h"
 #include "user_input.h"
 
void displayStats(void){
	
	oi_t *sensor_data = oi_alloc(); // Allocating space for open interface struct
    oi_init(sensor_data); // Filling sensor data struct with initial data

	lcd_init();
    timer_init();
    lcd_clear();
    oi_update(sensor_data);


	while (1){
		
		//to display bump sensing
		char bump [5];
		//when left bumper is detected
		if (sensor_data->bumpLeft == 1 ){
		sprintf(bump, "Left");
		}
		//when right bumper is detected
		else if (sensor_data->bumpRight == 1 ){
		sprintf(bump, "Right");
		
		//when both bumpers is detected
		else if (sensor_data->bumpLeft == 1 && sensor_data->bumpRight == 1)
		sprintf(bump, "Both");
		}
		//when no bumper is detected
		else {
		sprintf(bump, "None");	
		}
		
		//for distance travelled
		while (parameter > 0){
		int distTravelled;
		
		if (!sensor_data->bumpRight == 1 || !sensor_data->bumpLeft == 1  || !(sensor_data->bumpLeft == 1 && sensor_data->bumpRight == 1)){
			oi_update(sensor); 
			distTravelled += sensor->distance; 
			
				if (distTravelled == parameter){
					distTravelled =0;
		}
		} 
		else{
			distTravelled =0;
		}	
		char stats [100]; 
		
		sprintf(stats, "Battery: %.2f%%\nBump: %s\nCliff:%d\nDistance:%d", (float) (sensor_data->batteryCharge * (1.0) / sensor_data->batteryCapacity) * 100.0, bump, sensor_data->cliffFrontLeftSignal,distTravelled);
		lcd_clear();
        lcd_puts(stats);

	}


}