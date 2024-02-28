// AM 02/03/20

/* Include preprocessor directives */
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHAccel.h>
#include <FEHBattery.h>
#include <FEHBuzzer.h>
// #include <FEHRPS.h>
#include <FEHSD.h>
#include <string.h>
#include <stdio.h>
#include <FEHLCD.h>

// define circumference
#define circ 10.995565

// define light values
#define red 0.328

// 5 counts = 1 ft movement
#define foot 5.0

//Encoder has 318 counts per 
//wheel radius and pi can be constants
void goStraight(float inches, int percent, DigitalEncoder re, DigitalEncoder le, FEHMotor lm, FEHMotor rm){
    re.ResetCounts();
    le.ResetCounts();
    float num_revolutions = inches/(circ);
    while(re.Counts() < 318 * num_revolutions){
        rm.SetPercent(percent);
        lm.SetPercent(-percent);
    }
    rm.Stop();
    lm.Stop();
}

void goBackward(float inches, int percent, DigitalEncoder re, DigitalEncoder le, FEHMotor rm, FEHMotor lm){
    re.ResetCounts();
    le.ResetCounts();
    float num_revolutions = inches/(circ);
    while(re.Counts() < 318 * num_revolutions){
        rm.SetPercent(percent);
        lm.SetPercent(-percent);
    }
    rm.Stop();
    lm.Stop();
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
    FEHMotor right_motor(FEHMotor :: Motor0, 9.0);
    FEHMotor left_motor(FEHMotor :: Motor3, 9.0);
    AnalogInputPin Cds_cell(FEHIO :: P1_0);
    DigitalEncoder right_encoder(FEHIO :: P0_0);
    DigitalEncoder left_encoder(FEHIO :: P3_0);

    // goStraight(12.0, 25, right_encoder, left_encoder, left_motor, right_motor);
    goBackward(12.0, 25, right_encoder, left_encoder, left_motor, right_motor);

    /* test code
    while(true)
    {
        if(Cds_cell.Value() < 1.0)
        {
            rm.SetPercent(25);
            lm.SetPercent(25);
        }
    }
    */

    // checkpoint 1 directions
    // change times
    /*goStraight(rm, lm, straightSpeed, 10);
    turnLeft(rm, lm, rmLeftSpeed, lmLeftSpeed, 10);
    goStraight(rm, lm, straightSpeed, 10);
    turnRight(rm, lm, rmRightSpeed, lmRightSpeed, 10);
    goStraight(rm, lm, straightSpeed, 10);
    turnRight(rm, lm, rmRightSpeed, lmRightSpeed, 10);
    goStraight(rm, lm, straightSpeed, 10);
    turnLeft(rm, lm, rmLeftSpeed, lmLeftSpeed, 10);
    goStraight(rm, lm, straightSpeed, 10);*/
}
