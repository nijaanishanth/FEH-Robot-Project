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
#define left45 120.0
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

// checks color of the light
char checkLightColor(AnalogInputPin Cds_cell)
{
    if(Cds_cell.Value() >= 1.4)
    {
        return 'b';
    }
    else
    {
        return 'r';
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

    // declare color
    char color;
    
    // while loop to sleep until cds cell is on
    while(Cds_cell.Value() >= 1.65){
        Sleep(0.05);
    }
    
    goStraight(2.5, 25, right_encoder, left_encoder, left_motor, right_motor);
    turnLeft(150, turn_speed, turn_speed, right_encoder, left_encoder, left_motor, right_motor);

    // CHECKPOINT 2
    // right 45 turn 
    /*
    float right = right45+60;
    turnRight(right, 25, 25, right_encoder, left_encoder, left_motor, right_motor);

    // straight and left to fix turn
    goStraight(4.5, 25, right_encoder, left_encoder, left_motor, right_motor);
    turnLeft(80, turn_speed, turn_speed, right_encoder, left_encoder, left_motor, right_motor);
    */

    // straight 31 inches up ramp
    // changed distance
    //goStraight(8.0, 35, right_encoder, left_encoder, left_motor, right_motor);
    goStraight(28.5, 30, right_encoder, left_encoder, left_motor, right_motor);
    
    

    // after ramp
    // turn left 90 after ramp
    // note: back left wheel not turning 
    // turning left too much 
    turnLeft(110, turn_speed, 20, right_encoder, left_encoder, left_motor, right_motor);

    // straight 16 inches to read light
    goStraight(24.0, 35, right_encoder, left_encoder, left_motor, right_motor);
    
    // read light color and store length
    // no light ~2
    // red light ~0.71
    // blue light ~1.5
    float lightLength = 0;
    float lightTurn = 0;
    while(Cds_cell.Value() > 1.65){
        Sleep(0.05);
    }
    color = checkLightColor(Cds_cell);
    if(color == 'r')
    {
        LCD.Write("Red");
        Sleep(1000);
        lightLength = 14.5;
        lightTurn = 120;
        
    }
    else if(color == 'b')
    {
        LCD.Write("Blue");
        Sleep(1000);
        lightLength = 8.0;
        lightTurn = 100;

    }
    
    // go backwards after reading light
    goBackward(lightLength, 35, right_encoder, left_encoder, left_motor, right_motor);

    // right based on color
    turnRight(lightTurn, turn_speed, 20, right_encoder, left_encoder, left_motor, right_motor);

    // straight
    goStraight(12, 35, right_encoder, left_encoder, left_motor, right_motor);

}
