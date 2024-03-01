

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

// speed
#define straight_speed 35
#define turn_speed 25

// turns
#define left90 240.0
#define left45 115.0
#define right90 295.0
#define right45 147.5

//Encoder has 318 counts per revolution
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
void turnRight(float counts, int percent_right, int percent_left, DigitalEncoder re, DigitalEncoder le, FEHMotor rm, FEHMotor lm){
    re.ResetCounts();
    le.ResetCounts();
    while(re.Counts() < counts){
        rm.SetPercent(percent_right);
        lm.SetPercent(percent_left);
    }
    rm.Stop();
    lm.Stop();
}

// turn left function
void turnLeft(float counts, int percent_right, int percent_left, DigitalEncoder re, DigitalEncoder le, FEHMotor rm, FEHMotor lm){
    re.ResetCounts();
    le.ResetCounts();
    while(re.Counts() < counts){
        rm.SetPercent(-percent_right);
        lm.SetPercent(-percent_left);
    }
    rm.Stop();
    lm.Stop();
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

    // while loop to sleep until cds cell is on
    while(Cds_cell.Value() >= 1.0){
        Sleep(0.05);
    }

    // CHECKPOINT 1
    // right 45 turn 
    float right = right45+20;
    turnRight(right, 25, 25, right_encoder, left_encoder, left_motor, right_motor);

    // straight and left to fix turn
    goStraight(3.0, 25, right_encoder, left_encoder, left_motor, right_motor);
    turnLeft(40, turn_speed, turn_speed, right_encoder, left_encoder, left_motor, right_motor);

    // straight 35 inches up ramp
    // changed distance
    goStraight(29.5, 35, right_encoder, left_encoder, left_motor, right_motor);

    // after ramp
    // turn left 90 after ramp
    // note: back left wheel not turning 
    // turning left too much 
    turnLeft(left90, turn_speed, 20, right_encoder, left_encoder, left_motor, right_motor);

    // straight 11 inches
    goStraight(6.0, straight_speed, right_encoder, left_encoder, left_motor, right_motor);

    // right 90 turn
    turnRight(right90, turn_speed, turn_speed, right_encoder, left_encoder, left_motor, right_motor);

    // straight 11 inches
    goStraight(18.0, straight_speed, right_encoder, left_encoder, left_motor, right_motor);
    
}
