


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

// define speeds
#define straightSpeed 25
#define rmRightSpeed 25
#define lmRightSpeed 25
#define rmLeftSpeed 25
#define lmLeftSpeed 25

// define light values
#define red 0.328

// straight function
void goStraight(FEHMotor rm, FEHMotor lm, int speed, float time){
    float t_now = TimeNow();
    while(TimeNow() - t_now <= time){
        rm.SetPercent(speed);
        lm.SetPercent(speed);
    }

}

// turn right function
void turnRight(FEHMotor rm, FEHMotor lm, int speedRM, int speedLM, float time){
    float t_now = TimeNow();
    while(TimeNow() - t_now <= time){
        rm.SetPercent(speedRM);
        lm.SetPercent(speedLM);
    }
}

// turn left function
void turnLeft(FEHMotor rm, FEHMotor lm, int speedRM, int speedLM, float time){
    float t_now = TimeNow();
    while(TimeNow() - t_now <= time){
        rm.SetPercent(speedRM);
        lm.SetPercent(speedLM);
    }
}

// display cds value function
float DisplayCdSValue(AnalogInputPin Cds_cell){
    return Cds_cell.Value();
}

// checks if light is on
// returns 0 if no light, otherwise 1
int checkLight(AnalogInputPin Cds_cell){
    if(Cds_cell.Value() > red)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Main function */
int main(void)
{
    // declare motors & cds cell
    FEHMotor rm(FEHMotor :: Motor1, 9.0);
    FEHMotor lm(FEHMotor :: Motor0, 9.0);
    AnalogInputPin Cds_cell(FEHIO :: P0_3);

    // checkpoint 1 directions
    // change times
    goStraight(rm, lm, straightSpeed, 10);
    turnLeft(rm, lm, rmLeftSpeed, lmLeftSpeed, 10);
    goStraight(rm, lm, straightSpeed, 10);
    turnRight(rm, lm, rmRightSpeed, lmRightSpeed, 10);
    goStraight(rm, lm, straightSpeed, 10);
    turnRight(rm, lm, rmRightSpeed, lmRightSpeed, 10);
    goStraight(rm, lm, straightSpeed, 10);
    turnLeft(rm, lm, rmLeftSpeed, lmLeftSpeed, 10);
    goStraight(rm, lm, straightSpeed, 10);
}
