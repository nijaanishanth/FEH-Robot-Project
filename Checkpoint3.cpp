/* Include preprocessor directives */
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHAccel.h>
#include <FEHBattery.h>
#include <FEHBuzzer.h>
#include <FEHRCS.h>
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

// speed
#define straight_speed 35
#define turn_speed 25

// turns
#define left90 240.0
#define left45 120.0
#define right90 295.0
#define right45 147.5

// declare motors & cds cell
FEHMotor right_motor(FEHMotor :: Motor0, 9.0);
FEHMotor left_motor(FEHMotor :: Motor2, 9.0);
FEHMotor vex_motor(FEHMotor :: Motor3, 9.0);
AnalogInputPin Cds_cell(FEHIO :: P1_0);
DigitalEncoder right_encoder(FEHIO :: P0_0);
 DigitalEncoder left_encoder(FEHIO :: P3_0);

//Encoder has 318 counts per revolution
//wheel radius and pi can be constants
void goStraight(float inches, int percent){
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    float num_revolutions = inches/(circ);
    while(right_encoder.Counts() < 318 * num_revolutions){
        right_motor.SetPercent(-percent);
        left_motor.SetPercent(percent);
    }
    right_motor.Stop();
    left_motor.Stop();
}

void goBackward(float inches, int percent){
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    float num_revolutions = inches/(circ);
    while(right_encoder.Counts() < 318 * num_revolutions){
        right_motor.SetPercent(-percent);
        left_motor.SetPercent(percent);
    }
    right_motor.Stop();
    left_motor.Stop();
}

// turn right function
void turnRight(float counts, int percent_right, int percent_left){
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    while(right_encoder.Counts() < counts){
        right_motor.SetPercent(-percent_right);
        left_motor.SetPercent(-percent_left);
    }
    right_motor.Stop();
    left_motor.Stop();
}

// turn left function
void turnLeft(float counts, int percent_right, int percent_left){
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    while(right_encoder.Counts() < counts){
        right_motor.SetPercent(percent_right);
        left_motor.SetPercent(percent_left);
    }
    right_motor.Stop();
    left_motor.Stop();
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

// rack and pinion go up function
void goUp(float time)
{
    float start_time = TimeNow();
    while(TimeNow() - start_time < time)
    {
        vex_motor.SetPercent(25);
    }
}

// rack and pinion go down function
void goDown(float time)
{
    float start_time = TimeNow();
    while(TimeNow() - start_time < time)
    {
        vex_motor.SetPercent(-25);
    }
}

/* Main function */
int main(void)
{

    // CHECKPOINT 3
    //initialize the RCS
    // team key: D30D1Hj1u
    /*RCS.InitializeTouchMenu("D30D1Hj1u");

    // Check which lever to flip and perform some action
    int correctLever = RCS.GetCorrectLever();
    if(correctLever == 0)
    {
        // Perform actions to flip left lever
    } 
    else if(correctLever == 1)
    {
        // Perform actions to flip middle lever
    }
    else if(correctLever == 2)
    {
       // Perform actions to flip right lever
    }*/

    goDown(1.0);
    
    // start hook at the top of rack

    // turn left

    // go straight till fuel levers

    // move hook down

    // wait 5 seconds

    // move hook back up


}
