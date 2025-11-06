// Include the library
#include <SimpleWebSerial.h>
#include <Servo.h>

// Create an instance of the library
SimpleWebSerial WebSerial;

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  // Initialize serial communication
  Serial.begin(57600);
  digitalWrite(LED_BUILTIN, LOW);
  
  // Define events to listen to and their callback
  WebSerial.on("event-to-arduino", eventCallback); 
  
  // Send named events to browser with a number, string, array or json object
  WebSerial.send("event-from-arduino", 123);

  // Set up stepper motor
  for(int i=22;i<30;i+=2)
  {
    pinMode(i,OUTPUT);
  }

  // Set up servo
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}


int stepsPerAngle(float degrees) {
  // a measure of how many times the motor shaft must turn for the output shaft to complete one revolution
  // each step is 360/64
  float reductionRatio = 1./64.;
  float steppingAngle = 5.625 * reductionRatio;

  // stepping angle = fixed angle it rotates with each discrete pulse it receives

  // return number of steps
  return (int) degrees / steppingAngle / 8.;
}

void eventCallback(JSONVar data) {
    // Do something, even sending events right back!
    Serial.println(data);
    WebSerial.send("event-from-arduino", data);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);
};

void callbackWithStringParameter(JSONVar some_string) {
  Serial.println(some_string);
}

void loop() {
  // Check for new serial data every loop
  WebSerial.check();
  //delay(5);

  /*int a;
  a=stepsPerAngle(180.0);
  while(a--)
  {
   for(int i=22;i<30;i+=2)
   {
    digitalWrite(i,1);
    delay(2); // 2 seems to be the lower limit
    digitalWrite(i,0);
   }
  }
  exit(0);*/

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
