#include <Servo.h>
#include <Adafruit_CircuitPlayground.h>
int drylevel = 510; //Set this value by callibrating the probe with the soil moisture where it is considered "dry"
Servo myservo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  CircuitPlayground.begin();
  myservo.attach(6);
  
}

void loop() {
  Serial.println(CircuitPlayground.readCap(9));
  float sum = 0;
  for(int i=0; i< 5; i++){
    sum = sum + CircuitPlayground.readCap(9);
    delay(200);
  }
  float average = sum / 5.0 ; //Averaging due to the dips in the readings
  
  
  if (average < drylevel){
    CircuitPlayground.setBrightness(175);
    Serial.println("Dry");
    for (int pixel=0; pixel<10; pixel++){
      CircuitPlayground.setPixelColor(pixel, 229, 57, 20);
    }
    myservo.write(90);
    delay(1000);
  }
  else if (average > drylevel){
    CircuitPlayground.setBrightness(100);
    Serial.println("Wet");
    for (int pixel=0; pixel<10; pixel++){
      CircuitPlayground.setPixelColor(pixel, 20, 198, 35);
    }
    myservo.write(180);
    delay(1000);
  }
  else {
    Serial.println("Unknown");
  }
}
