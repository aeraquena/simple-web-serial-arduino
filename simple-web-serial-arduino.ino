// 22, 24, 26, 28
void setup()
{
  Serial.begin(9600);
  for(int i=22;i<30;i+=2)
  {
    pinMode(i,OUTPUT);
  }
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

void loop()
{
  int a;
  a=stepsPerAngle(180.0);
  while(a--)
  {
   for(int i=22;i<30;i+=2)
   {
    digitalWrite(i,1);
    delay(2); // 2 seems to be the lower limit
    digitalWrite(i,0);
   }
    Serial.println(a);
  }
  exit(0);
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
