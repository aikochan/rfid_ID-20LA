// based on the arduino bildr turorial <http://bildr.org/2011/02/rfid-arduino/>
// cleaned up code to use standard conventions and modified to work with Particle Photon

#include "application.h"

#define LED_PIN1				D3
#define LED_PIN2				D4
#define LED_PIN3				D5

#define TAG_LENGTH		 	12
#define START_CHAR			2
#define LF_CHAR					10
#define CR_CHAR					13
#define ETX_CHAR				3

#define LED_DELAY				250
#define	LOOP_DELAY			500

String tag_yellow = String("7C00563C8C9A");
String tag_red = String("7C005615F8C7");
String tag_green = String("7C0055FAF023");

void checkTag(String readTag) {
  if (readTag.length() == 0) return;
    
  if (readTag.equals(tag_yellow)) {
  	Serial.println("\rmatched yellow");
    //lightLED(LED_PIN1);
  } else if (readTag.equals(tag_red)) {
    Serial.println("\rmatched red");
    //lightLED(LED_PIN2);
  } else if (readTag.equals(tag_green)) {
    Serial.println("\rmatched green");
    //lightLED(LED_PIN3);
  } else {
  	Serial.print("I don't recognize this tag: "); 
    Serial.println(readTag);
  }
}

void lightLED(int pin) {
  digitalWrite(pin, HIGH);
  delay(LED_DELAY);
  digitalWrite(pin, LOW);
}

void clearTag(char *tag) {
  memset(tag, '0', TAG_LENGTH);
}

void setup() {
	Serial.begin(9600);
  Serial1.begin(9600);

//   pinMode(LED_PIN1, OUTPUT);
//   pinMode(LED_PIN2, OUTPUT);
//   pinMode(LED_PIN3, OUTPUT);
}

void loop() {

  char tagString[TAG_LENGTH];
  int index = 0;
  boolean reading = false;
  
  clearTag(tagString);

  while (Serial1.available()) {

    int readByte = Serial1.read();
    
    if (readByte == START_CHAR) reading = true;
    if (readByte == ETX_CHAR) reading = false;

    if (reading 
    		&& readByte != START_CHAR 
    		&& readByte != LF_CHAR 
    		&& readByte != CR_CHAR 
    		&& index < TAG_LENGTH) 
		{
      tagString[index] = readByte;
      index++;
    }
  }
  
  if (index != 0) {
		String cleanString = String(tagString);
		cleanString.trim();
		checkTag(cleanString);
  }
  delay(LOOP_DELAY);
}

