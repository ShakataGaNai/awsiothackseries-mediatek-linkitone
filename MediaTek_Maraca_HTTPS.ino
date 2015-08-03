
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <Wire.h>
#include <LDateTime.h>
#include <ADXL345.h>

#include <MtkAWSImplementations.h>
#include <AWSFoundationalTypes.h>
#include "keys.h"
#include "HardwareFunctions.h"
#include "AWShelperFunctions.h"

// Bar Hack
//#include <Grove_LED_Bar.h>
//Grove_LED_Bar bar(8, 9, 0);  // Clock pin, Data pin, Orientation
#include <Suli.h>
#include <Wire.h>
#include "Seeed_LED_Bar_Arduino.h"

// Bar

// Servo Hack
#include <Servo.h>
Servo groveServo;
int waitSome = 0;
unsigned long shakeTime = 0;
unsigned long lastShakeTime = 0;
// Servo

// It is an Arduino hack to include libraries that are referenced in other libraries. 
// For example WiFi is used in AWS libraries but we still need to include in the main sketch file for it to be recognized.

AWS_Service_ID CurrentService;

void setup() {
  
        Serial.println("Begin Setup..");
        Serial.println(CurrentService);

	/* Begin serial communication. */
	Serial.begin(9600);
	digitalWrite(BUZZER_PIN, LOW);

        // Connect to WiFi (function loops until successful connection is made)
	Mtk_Wifi_Setup(ssid, pass);
        printWifiStatus();

	configureIO();
	accelerometerInit();
       
	SNSClient_Setup();
	DynamoBDClient_Setup();
	KinesisClient_Setup();

	CurrentService = SNS;
	indicateServiceThroughLED_blink_Buzzer(DYNAMO_DB);

	Serial.println("Setup complete! Looping main program");
	Serial.println("Initial mode: DynamoDB");      

        groveServo.attach(3); //the servo is attached to D3
        pinMode(0, INPUT);
        groveServo.write(90);
        
//        bar.begin();        
        SeeedLedBar bar(8, 9); 
}

unsigned long currentTime = 0;
unsigned long LastPostTime = 0;
enum {
	POSTING_PERIOD_MS = 50 //Was 500
};

int buttonVal = LOW;
int prevButtonVal = LOW;

double xyz[3];

void loop() {                


        shakeTime = millis();
	if ((shakeTime - lastShakeTime) > 750) {
		lastShakeTime = millis();
                groveServo.write( random(0, 180) );
        }
        
	readAcceleration(xyz);	
	if (isAccelerometerShaking(xyz)) {
                printAcceleration(xyz);
		// light the onboard LED
		//digitalWrite(MEDIATEK_LED_PIN, HIGH);
                if(xyz[2]>0){
                  bar.setLevel(xyz[2]*5);
                  Serial.println(xyz[2]*5);
                }else{
                  bar.setLevel((1+xyz[2])*5);
                  Serial.println((1+xyz[2])*5);
                }
                
		currentTime = millis();
		if ((currentTime - LastPostTime) > POSTING_PERIOD_MS) {
			currentTime = millis();
			switch (CurrentService) {
			case 0:
				Serial.println("Posting to Kinesis");
				putKinesis(xyz[0], xyz[1], xyz[2]);
				break;
			case 1:
				Serial.println("Posting to DynamoDB");
				putDynamoDb();
				break;
			case 2:
				Serial.println("Posting to SNS");
				putSns();
				break;
			default:
				Serial.println("Wrong selection");
				break;
			}
			LastPostTime = currentTime;
		}
	} else {
		//Serial.println("Not publishing...");
//		digitalWrite(MEDIATEK_LED_PIN, LOW);
                bar.setLevel(0);
	}

	// check if button has been pressed
	buttonVal = digitalRead(BUTTON_PIN);
	if (prevButtonVal == LOW && buttonVal == HIGH) {
		CurrentService = changeService(CurrentService);
	}
	prevButtonVal = buttonVal;
	delay(20);  //Was 200


}

































































