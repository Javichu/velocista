/* orangutan_app1 - an application for the Pololu Baby Orangutan B
 *
 * This application uses the Pololu AVR C/C++ Library.  For help, see:
 * -User's guide: http://www.pololu.com/docs/0J20
 * -Command reference: http://www.pololu.com/docs/0J18
 *
 * Created: 1/13/2015 11:17:34 PM
 *  Author: Javier
 */

#include "VelocistaLib.h"

int main()
{
	RobotInit();
	// then start calibration phase and move the sensors over both
	// reflectance extremes they will encounter in your application:
	/*int i;
	for (i = 0; i < 250; i++)  // make the calibration take about 5 seconds
	{
		qtr_calibrate(QTR_EMITTERS_ON);
		delay(20);
	}*/
	
	while (1)
	{
		PID();
	}
	
	return 0;
}
