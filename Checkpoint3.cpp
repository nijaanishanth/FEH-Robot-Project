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
#define left90 200.0
#define left45 92.5
#define left45 95
#define right90 200.0
#define right45 100.0

// right and left motors are flipped
// declare motors & cds cell
FEHMotor right_motor(FEHMotor :: Motor0, 9.0);
FEHMotor left_motor(FEHMotor :: Motor2, 9.0);
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

    
    // CHECKPOINT 3
    //initialize the RCS
    // team key: D30D1Hj1u
    // while loop to sleep until cds cell is on
    while(Cds_cell.Value() >= 1.0){
        Sleep(0.05);
    }
    // RCS.InitializeTouchMenu("D30D1Hj1u");
    int lever_distance = 0;
    // Check which lever to flip and perform some action
    // int correctLever = RCS.GetCorrectLever();
    int correctLever = 1;
    int correctLever = 0;
    if(correctLever == 0)
    {
        lever_distance = 3.0;
    } 
    else if(correctLever == 1)
    {
        lever_distance = 6.8;
    }
    else if(correctLever == 2)
    {
        lever_distance = 10.4;
    }

    // start hook at the top of rack
    // go straight 11
    goStraight(14.25, 25);
    goStraight(14.850, 25);

    // turn left
    turnLeft(left45, 25, 25);
    // go straight till fuel levers
    goStraight(lever_distance, 25);
    // move hook down
    goDown(3.75);
    // backwards
    goBackward(lever_distance, 25);
    Sleep(5.0);

    // move down a little
    goDown(0.75);
    goDown(0.9);

    // forwards again
    goStraight(lever_distance, 25);

    // move hook back up
    goUp(1.75);
    goUp(1.3);

    // go backwards and reset
    goBackward(lever_distance, 25);
    goUp(3.5);
    goUp(4.075);

}
