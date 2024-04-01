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
#define left90 195.0
#define left45 95.0
#define right90 150.0
#define right45 80.0

// right and left motors are flipped
// declare motors & cds cell
FEHMotor right_motor(FEHMotor :: Motor2, 9.0);
FEHMotor left_motor(FEHMotor :: Motor0, 9.0);
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
        right_motor.SetPercent(percent);
        left_motor.SetPercent(-percent);
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
        right_motor.SetPercent(percent_right);
        left_motor.SetPercent(percent_left);
    }
    right_motor.Stop();
    left_motor.Stop();
}

// turn left function
void turnLeft(float counts, int percent_right, int percent_left){
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    while(right_encoder.Counts() < counts){
        right_motor.SetPercent(-percent_right);
        left_motor.SetPercent(-percent_left);
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
/*2 seconds = 1.5 inches*/
void goUp(float time)
{
    float start_time = TimeNow();
    while(TimeNow() - start_time < time)
    {
        vex_motor.SetPercent(25);
    }
    vex_motor.Stop();
}

// rack and pinion go down function
void goDown(float inches)
{
    // 1 SECOND = 0.95 INCHES
    // MAX INCHES IS 7.5
    float time = inches/0.95;
    float start_time = TimeNow();
    while(TimeNow() - start_time < time)
    {
        vex_motor.SetPercent(-25);
    }
        vex_motor.Stop();

}

/* Main function */
int main(void)
{
    // CHECKPOINT 5
    // initialize RCS
    // RCS.InitializeTouchMenu("D30D1Hj1u");

    // while loop to sleep until cds cell is on
    while(Cds_cell.Value() >= 1.0){
        Sleep(0.05);
    }

    // pre ramp adjust to position
    goBackward(1.0, 25);
    goStraight(3.0, 25);
    turnRight(right45 + 50, 25, 25);
    goStraight(4.0, 25);
    turnLeft(55, 25, 25);
    goStraight(9.0, 25);
    Sleep(0.5);

    // up the ramp
    goStraight(21.5, 35);

    // post-ramp
    turnLeft(left90, 25, 25);

    // drop the luggage
    goStraight(23.25, 35);

    // go back down
    goBackward(0.5, 25);
    turnLeft(left90, 25, 25);
    goStraight(10.0, 15);

}
