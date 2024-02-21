

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


FEHServo servo(FEHServo::Servo0); // declare servo arm

/* Main function to control menu system */
int main(void)
{
    // right motor is negative
    AnalogInputPin cds(FEHIO::P0_0);
    FEHMotor rightMotor(FEHMotor::Motor1, 9.0);
    FEHMotor leftMotor(FEHMotor::Motor0, 9.0);
    // front switches
    DigitalInputPin switch0(FEHIO::P2_0);
    DigitalInputPin switch1(FEHIO::P2_3);
    // back switches
    DigitalInputPin switch2(FEHIO::P2_1);
    DigitalInputPin switch3(FEHIO::P3_2);

    // going straight
    while(switch0.Value() + switch1.Value() != 0)
    {
        rightMotor.SetPercent(-25);
        leftMotor.SetPercent(25);
    }
    rightMotor.Stop();
    leftMotor.Stop();

    // turning right
    while(switch2.Value() + switch3.Value() != 0)
    {
        rightMotor.SetPercent(35);
        leftMotor.SetPercent(-10);
    }
    rightMotor.Stop();
    leftMotor.Stop();

    // straight
    while(switch0.Value() + switch1.Value() != 0)
    {
        rightMotor.SetPercent(-25);
        leftMotor.SetPercent(25);
    }
    rightMotor.Stop();
    leftMotor.Stop();


    // turn left
    while(switch3.Value())
    {
        rightMotor.SetPercent(-10);
        leftMotor.SetPercent(-25);
    }
    while(switch2.Value())
    {
        rightMotor.SetPercent(10);
        leftMotor.SetPercent(-25);
    }

    rightMotor.Stop();
    leftMotor.Stop();

    // going straight
    while(switch0.Value() + switch1.Value() != 0)
    {
        rightMotor.SetPercent(-25);
        leftMotor.SetPercent(25);
    }
    rightMotor.Stop();
    leftMotor.Stop();
        
}

