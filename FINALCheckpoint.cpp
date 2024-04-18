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

void adjustGear();

//Encoder has 318 counts per revolution
//wheel radius and pi can be constants
void goStraight(float inches, int percent){
    float rightPower = percent;
    float leftPower = percent;
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    float num_revolutions = inches/(circ);
    while(right_encoder.Counts() < 318 * num_revolutions){
        right_motor.SetPercent(rightPower);
        left_motor.SetPercent(-leftPower);
        if(left_encoder.Counts() < right_encoder.Counts()){
            
            rightPower += 0.0001;
        }
        
        if(right_encoder.Counts() < left_encoder.Counts()){
           
            leftPower += 0.0001;
        }
    }
    right_motor.Stop();
    left_motor.Stop();
}

void goStraightTime(float time, int percent)
{
    float start_time = TimeNow();
    while(TimeNow() - start_time < time)
    {
        right_motor.SetPercent(percent);
        left_motor.SetPercent(-percent);
    }
    right_motor.Stop();
    left_motor.Stop();
}

void goBackTime(float time, int percent)
{
    float start_time = TimeNow();
    while(TimeNow() - start_time < time)
    {
        right_motor.SetPercent(-percent);
        left_motor.SetPercent(percent);
    }
    right_motor.Stop();
    left_motor.Stop();
}

void goBackward(float inches, int percent){
    float leftPower = percent;
    float rightPower = percent;
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    float num_revolutions = inches/(circ);
    while(right_encoder.Counts() < 318 * num_revolutions){
        right_motor.SetPercent(-rightPower);
        left_motor.SetPercent(leftPower);
        if(left_encoder.Counts() < right_encoder.Counts()){
           
                rightPower += 0.0001;
            
            
        } else if(right_encoder.Counts() < left_encoder.Counts()){
            
            leftPower += 0.0001;
                 
        }
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

// turn right when right wheel = 0
void turnPivotRight(float counts, int percent_right){
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    while(left_encoder.Counts() < counts){
        right_motor.SetPercent(percent_right);
        left_motor.SetPercent(0);
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

void turnPivotLeft(float counts, int percent_left){
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    while(right_encoder.Counts() < counts){
        right_motor.SetPercent(0);
        left_motor.SetPercent(-percent_left);
    }
    right_motor.Stop();
    left_motor.Stop();
}

// display cds value function
float DisplayCdSValue(AnalogInputPin Cds_cell){
    return Cds_cell.Value();
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
    // 1 second = 0.95 inches
    // max inches is 7.5
    float time = inches/0.95;
    float start_time = TimeNow();
    while(TimeNow() - start_time < time)
    {
        vex_motor.SetPercent(-25);
    }
    vex_motor.Stop();

}

char checkLightColor(AnalogInputPin Cds_cell)
{
    LCD.Write(Cds_cell.Value());
    if(Cds_cell.Value() >= 1.5)
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


    
    adjustGear();

    // FINAL CODE
    // initialize RCS
     LCD.WriteLine(Cds_cell.Value());
    Sleep(2.0);
    RCS.InitializeTouchMenu("D30D1Hj1u");

    LCD.WriteLine(Cds_cell.Value());
    Sleep(2.0);
    // while loop to sleep until cds cell is on
    while(Cds_cell.Value() >= 1.7){
        Sleep(0.05);
    }

    //Lowest value for blue light: 1.6
    //Lowest value for red light: 
    
    // go to baggage
    goBackTime(0.4, 20);
    goStraight(13.0, 20);
    turnRight(50, 25, 20);

    // run into baggage
    goStraightTime(1.5, 40);

    // go back and reposition
    if(RCS.CurrentCourse() == 'A'){
        goBackward(6, 20);
        turnLeft(left90 - 23, 25, 25);
    }else{
        goBackward(6.15, 20);
        turnLeft(left90 - 29, 25, 25);
    }
    goBackTime(4.0, 20);

    int i = 0;
    // go to the fuel lever
    //goStraight(18.0, 20);
    for(i = 0; i < 6; i++){
        goStraight(17.5/6, 20);
    }

    //Lift the fuel lever up
    goDown(1.35);
    goUp(0.55);
    goBackward(3.0, 20);
    goDown(1.7);
    Sleep(5.0);

    // set the fuel lever down
    goStraight(3.0, 20);
    goUp(1.65);
    goDown(0.5);
    goBackward(3.0, 20);

    //Align against the wall before the ramp
    if(RCS.CurrentRegionLetter() == 'A')
    {
        goBackward(4.7, 20);
    }
    else
    {
        goBackward(5.0, 20);
    }
    turnRight(25, 25, 25);
    goBackward(6.0, 20);
    goBackTime(2.0, 20);
    if(RCS.CurrentCourse() == 'D'){
        turnPivotRight(right90*2 + 44, 25);
    }else{
        turnPivotRight(right90*2 + 39, 25);
    }
    goStraight(5.0, 20);
    Sleep(0.5);

    // up the ramp
    goStraight(20.0, 35);

    //Align against the wall after the ramp
    turnLeft(left90, 25, 25);
    goBackTime(3.0, 25);
    
    //Go to the light
    if(RCS.CurrentCourse() == 'A'){
        goStraight(7.0, 25);
    }else{
        goStraight(7.5, 25);
    }
    if(RCS.CurrentRegionLetter() == 'A')
    {
        turnRight(right45 - 5, 25, 25);
    }
    else
    {
        turnRight(right45, 25, 25);
    }

    //goStraight(21.0,25);
    for(i = 0; i < 5; i++){
        goStraight(21.0/5, 25);
    }

    //Read the light and right the color to the screen
    char color = checkLightColor(Cds_cell);
    LCD.WriteLine(color);
    Sleep(1.0);

    //Press the correct ticket button
    float redAdd = 0;
    float rightTurn = 0;
    if(color == 'b')
    {
        goBackward(8.0, 25);
        if(RCS.CurrentRegionLetter() == 'B')
        {
            goBackward(8.0, 25);
        }
        else
        {
            goBackward(8.0, 25);
            rightTurn = 2;
        }
    }
    else
    {
        if(RCS.CurrentRegionLetter() == 'B')
        {
            goBackward(15.0, 25);
            rightTurn = 5;
        }
        else
        {
            goBackward(13.5, 25);
        }
        redAdd = 3.5;
    }
    turnRight(right45 + rightTurn, 25, 25);
    goStraight(2.5 + redAdd, 25);
    goStraightTime(1.5, 25);

    //Align against the wall
    goBackward(12.0,25);
    Sleep(0.5);
    if(RCS.CurrentRegionLetter() == 'B')
    {
        turnLeft(left90 - 15, 25, 25);
    }
    else
    {
        turnLeft(left90 - 10, 25, 25);
    }
    goBackward(10.0,25);
    goBackTime(2.5, 25);
    goDown(1.6);

    // positioning to passport stamp
    if(RCS.CurrentCourse() == 'A')
    {
        goStraight(10.79, 25);
        turnLeft(left90 - 4, 25, 25);
    }
    else if(RCS.CurrentCourse()== 'B')
    {
        goStraight(10.80, 25);
        turnLeft(left90 + 9, 25, 25);
    }
    else
    {
        goStraight(10.71, 25);
        turnLeft(left90 - 4, 25, 25);
    }
    for(int i=0; i<5; i++)
    {
        goBackward(10.7/5, 25);
    }
    Sleep(3.0);

    //completing the passport stamp
    goUp(5.75);
    goBackward(7.0, 25);
    goStraight(1.0, 25);
    goDown(1.45);

    // adjust position before go straight
    turnRight(20, 25, 25);

    // adjust position
    goStraight(17.0, 25);
    turnRight(right90 - 20, 25, 25);
    goBackward(10.0, 25);
    goBackTime(4.0, 25);
    goStraight(1.0, 25);
    turnPivotLeft(left90*2 - 40, 25);

    // go down the ramp
    goStraight(34.0, 15);

    // hit the button
    turnLeft(left45 - 10, 25, 25);
    goStraight(10.0, 25);

}

void adjustGear(){
    float x_pos, y_pos;
    float x_trash, y_trash;
    bool cancel = false;
    LCD.Clear();
    LCD.SetFontColor(WHITE);
    LCD.DrawHorizontalLine(119,0,319);
    LCD.WriteAt("Cancel",140,60);
    LCD.WriteAt("Continue",140,180);
    LCD.ClearBuffer();
    while(!LCD.Touch(&x_pos,&y_pos)){};
    while(LCD.Touch(&x_trash,&y_trash)){};
    if(y_pos < 119){
        cancel = true;
    }
    while(!cancel){
        LCD.Clear();
        LCD.ClearBuffer();
        LCD.SetFontColor(WHITE);
        LCD.DrawHorizontalLine(119,0,319);
        LCD.WriteAt("Small Value",140,60);
        LCD.WriteAt("Large Value",140,180);
        LCD.ClearBuffer();
        while(!LCD.Touch(&x_pos,&y_pos)){};
        while(LCD.Touch(&x_trash,&y_trash)){};

        if(y_pos < 119){
            LCD.Clear();
            LCD.SetFontColor(WHITE);
            LCD.DrawHorizontalLine(47,0,319);
            LCD.DrawHorizontalLine(94,0,319);
            LCD.DrawHorizontalLine(141,0,319);
            LCD.DrawHorizontalLine(188,0,319);
            LCD.WriteAt("0.1",140,25);
            LCD.WriteAt("0.2",140,60);
            LCD.WriteAt("0.3",140,120);
            LCD.WriteAt("0.4",140,160);
            LCD.WriteAt("0.5",140,210);
            LCD.ClearBuffer();
            while(!LCD.Touch(&x_pos,&y_pos)){};
            while(LCD.Touch(&x_trash,&y_trash)){};

            float x_p, y_p;
            float x_t, y_t;
            LCD.Clear();
            LCD.SetFontColor(WHITE);
            LCD.DrawHorizontalLine(119,0,319);
            LCD.WriteAt("Up",140,60);
            LCD.WriteAt("Down",140,180);
            LCD.ClearBuffer();
            while(!LCD.Touch(&x_p,&y_p)){};
            while(LCD.Touch(&x_t,&y_t)){};
            if(y_pos < 47){
                if(y_p < 119){
                    goUp(0.1);
                }else{
                    goDown(0.1);
                }
            }else if(y_pos < 94){
                if(y_p < 119){
                    goUp(0.2);
                }else{
                    goDown(0.2);
                }
            }else if(y_pos < 141){
                if(y_p < 119){
                    goUp(0.3);
                }else{
                    goDown(0.3);
                }
            }else if(y_pos < 188){
                if(y_p < 119){
                    goUp(0.4);
                }else{
                    goDown(0.4);
                }
            } else{
                if(y_p < 119){
                    goUp(0.5);
                }else{
                    goDown(0.5);
                }
            }

        }else if(y_pos > 119){
            LCD.Clear();
            LCD.SetFontColor(WHITE);
            LCD.DrawHorizontalLine(47,0,319);
            LCD.DrawHorizontalLine(94,0,319);
            LCD.DrawHorizontalLine(141,0,319);
            LCD.DrawHorizontalLine(188,0,319);
            LCD.WriteAt("1.0",140,25);
            LCD.WriteAt("2.0",140,60);
            LCD.WriteAt("3.0",140,120);
            LCD.WriteAt("4.0",140,160);
            LCD.WriteAt("5.0",140,210);
            LCD.ClearBuffer();
            while(!LCD.Touch(&x_pos,&y_pos)){};
            while(LCD.Touch(&x_trash,&y_trash)){};

            float x_p2, y_p2;
            float x_t2, y_t2;
            LCD.Clear();
            LCD.SetFontColor(WHITE);
            LCD.DrawHorizontalLine(119,0,319);
            LCD.WriteAt("Up",140,60);
            LCD.WriteAt("Down",140,180);
            LCD.ClearBuffer();
            while(!LCD.Touch(&x_p2,&y_p2)){};
            while(LCD.Touch(&x_t2,&y_t2)){};
            if(y_pos < 47){
                if(y_p2 < 119){
                    goUp(1.0);
                }else{
                    goDown(1.0);
                }
            }else if(y_pos < 94){
                if(y_p2 < 119){
                    goUp(2.0);
                }else{
                    goDown(2.0);
                }
            }else if(y_pos < 141){
                if(y_p2 < 119){
                    goUp(3.0);
                }else{
                    goDown(3.0);
                }
            }else if(y_pos < 188){
                if(y_p2 < 119){
                    goUp(4.0);
                }else{
                    goDown(4.0);
                }
            } else{
                if(y_p2 < 119){
                    goUp(5.0);
                }else{
                    goDown(5.0);
                }
            }

        }

        LCD.Clear();
        LCD.SetFontColor(WHITE);
        LCD.DrawHorizontalLine(119,0,319);
        LCD.WriteAt("Cancel",140,60);
        LCD.WriteAt("Continue",140,180);
         LCD.ClearBuffer();
        while(!LCD.Touch(&x_pos,&y_pos)){};
        while(LCD.Touch(&x_trash,&y_trash)){};
        if(y_pos < 119){
            cancel = true;
        }
    }
    
}
