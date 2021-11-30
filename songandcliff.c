
#include "open_interface.h"
#include "lcd.h"
#include "timer.h"
/**
 * main.c
 */
int main(void)
{
    // ISSUE WITH oi_init() function. Program stops there...THIS ONLY HAPPENS WHEN ROOMBA IS OFF (PRESS "CLEAN" BUTTON)
        oi_t *sensor_data = oi_alloc();
        oi_init(sensor_data);
        lcd_init();
        oi_update(sensor_data);

        // G-F#-E-D-E-E
        unsigned char notes [7] = {67, 66, 64, 62, 64, 0, 64};
        unsigned char duration[7] =  {45, 40, 45, 40, 15, 1, 15};
        oi_loadSong(1, 7, notes, duration);
        oi_play_song(1);

        while (1){


            char cliffNum [100] ;
            sprintf(cliffNum, "FrontL: %d           Signal: %d", sensor_data->cliffFrontLeft, sensor_data->cliffFrontLeftSignal );
            lcd_clear();
            lcd_puts(cliffNum);
            timer_waitMillis(100);
            oi_update(sensor_data);
            // for cybot 10
            // 2800 or above = white tape
            //gray floor = 2000-2500
            //black 1500-1600, ie anything < 2000
        }

	return 0;
}
