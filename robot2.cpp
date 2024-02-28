/********************************/
/*      Proteus Test Code       */
/*     OSU FEH Spring 2020      */
/*        Drew Phillips         */
/*    02/03/20  Version 3.0.1     */
/********************************/

// AM 02/03/20

/* Include preprocessor directives */
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHAccel.h>
#include <FEHBattery.h>
#include <FEHBuzzer.h>
#include <FEHRPS.h>
#include <FEHSD.h>
#include <string.h>
#include <stdio.h>

//Encoder has 318 counts per 
//wheel radius and pi can be constants
void goStraight(float inches, int percent, DigitalEncoder right_motor, DigitalEncoder left_motor){
    right_motor.ResetCounts();
    left_motor.ResetCounts();
    float num_Revolutions = inches/(2*3.14*3.5);
    while(left_motor.Counts() < 318 * num_Revolutions){
        right_motor.SetPercent();
        left_motor.SetPercent();
    }
    right_motor.Stop();
    left_motor.Stop();
}

void goBackward(float inches, int percent, DigitalEncoder right_motor, DigitalEncoder left_motor){
    right_motor.ResetCounts();
    left_motor.ResetCounts();
    float num_Revolutions = inches/(2*3.14*3.5);
    while(left_motor.Counts() < 318 * num_Revolutions){
        right_motor.SetPercent();
        left_motor.SetPercent();
    }
    right_motor.Stop();
    left_motor.Stop();
}

/* Main function */
int main(void)
{
    
}
