/********************************/
/*      Proteus Test Code       */
/*     OSU FEH Spring 2020      */
/*        Drew Phillips         */
/*    02/03/20  Version 3.0.1     */
/********************************/

// AM 02/03/20

/* Include preprocessor directives */
#include <FEHLCD.h>
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

void goStraight(FEHMotor rm, FEHMotor lm, int speed, float time){
    float t_now = TimeNow();
    while(TimeNow() - t_now <= time){
        rm.SetPercent(speed);
        lm.SetPercent(speed);
    }

}

void turnRight(FEHMotor rm, FEHMotor lm, int speedRM, int speedLM, float time){
    float t_now = TimeNow();
    while(TimeNow() - t_now <= time){
        rm.SetPercent(speedRM);
        lm.SetPercent(speedLM);
    }
}

void turnLeft(FEHMotor rm, FEHMotor lm, int speedRM, int speedLM, float time){
    float t_now = TimeNow();
    while(TimeNow() - t_now <= time){
        rm.SetPercent(speedRM);
        lm.SetPercent(speedLM);
    }
}

float DisplayCdSValue(AnalogInputPin Cds_cell){
    return Cds_cell.value();
}

void checkLight(AnalogInputPin Cds_cell){

}

/* Main function */
int main(void)
{
    
}
