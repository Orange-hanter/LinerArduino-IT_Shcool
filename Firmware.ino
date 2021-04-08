
// Include Libraries
#include "Arduino.h"
#include "DCMDriverL298.h"


// Pin Definitions
const int DCMOTORDRIVERL298_PIN_INT1 = 2;
const int DCMOTORDRIVERL298_PIN_ENB = 6;
const int DCMOTORDRIVERL298_PIN_INT2 = 3;
const int DCMOTORDRIVERL298_PIN_ENA = 5;
const int DCMOTORDRIVERL298_PIN_INT3 = 4;
const int DCMOTORDRIVERL298_PIN_INT4 = 7;
const int IRLINEFOLLOW_1_PIN_OUT = 8;
const int IRLINEFOLLOW_2_PIN_OUT = 9;


// Global variables and defines
const int timeout = 10000;       // timeout of 10 sec
char menuOption = 0;
long time0;

char menu();

// object initialization
DCMDriverL298 dcMotorDriverL298(DCMOTORDRIVERL298_PIN_ENA,
                                DCMOTORDRIVERL298_PIN_INT1,
                                DCMOTORDRIVERL298_PIN_INT2,
                                DCMOTORDRIVERL298_PIN_ENB,
                                DCMOTORDRIVERL298_PIN_INT3,
                                DCMOTORDRIVERL298_PIN_INT4);




// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(115200);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    pinMode(IRLINEFOLLOW_1_PIN_OUT, INPUT);
    pinMode(IRLINEFOLLOW_2_PIN_OUT, INPUT);
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // L298N Motor Driver with Dual Micro DC Motors (Geared) - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298.setMotorA(200,1);
    dcMotorDriverL298.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298.stopMotors();
    delay(2000);

    }
    else if(menuOption == '2') {
    // IR Line Track Follower Sensor #1 - Test Code
    //Read IR Line Follower Sensor. irLineFollow_1Var will be '0' if a black line was detected
    bool irLineFollow_1Var = digitalRead(IRLINEFOLLOW_1_PIN_OUT);
    Serial.print(F("LineFollow: ")); Serial.println(irLineFollow_1Var);

    }
    else if(menuOption == '3') {
    // IR Line Track Follower Sensor #2 - Test Code
    //Read IR Line Follower Sensor. irLineFollow_2Var will be '0' if a black line was detected
    bool irLineFollow_2Var = digitalRead(IRLINEFOLLOW_2_PIN_OUT);
    Serial.print(F("LineFollow: ")); Serial.println(irLineFollow_2Var);

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) L298N Motor Driver with Dual Micro DC Motors (Geared)"));
    Serial.println(F("(2) IR Line Track Follower Sensor #1"));
    Serial.println(F("(3) IR Line Track Follower Sensor #2"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing L298N Motor Driver with Dual Micro DC Motors (Geared)"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing IR Line Track Follower Sensor #1"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing IR Line Track Follower Sensor #2"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

