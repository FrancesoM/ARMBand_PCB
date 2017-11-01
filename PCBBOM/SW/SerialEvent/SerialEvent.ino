/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */

void touch()
{
  //Output connected to ground, touched.
  DDRB |= (1<<PB0);  //Pin as output
  PORTB &= ~(1<<PB0); //Set is to ground.
}

void detouch()
{
  //High impedence, non touched
  DDRB &= ~(1<<PB0); //Pin as input.
  PORTB &= ~(1<<PB0); //Disable pull up.
}

int state = 0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  detouch();
  DDRB |= (1<<PB1); //Pin as output

}

void loop() {

}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    if((char)Serial.read() == 't')
    {
      touch();
      PORTB |= (1<<PB1); //on
      delay(300);
      detouch();
      PORTB &= ~(1<<PB1); //off
    }
  }
}


