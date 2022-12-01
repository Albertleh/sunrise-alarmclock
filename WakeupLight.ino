#include <Time.h>
#include <TimeLib.h> 

#define LEDPIN 3 // pwm out
#define MAX_BRIGHTNESS 150.0 // 0-255 

#define SHINE_MAX_BRIGHTNESS_SECONDS 120 // shine at max brightness after sunrise
#define SUNRISE_LENGTH_MINUTES 30 // how long the sunrise buildup should take

#define BEGIN_SUNRISE_HOUR 6
#define BEGIN_SUNRISE_MINUTE 20
#define BEGIN_SUNRISE_SECOND 0

void setup()
{
  Serial.begin(9600);
  setTime(21,48,0,1,12,22); // set initial time 
  pinMode(LEDPIN, OUTPUT);
  analogWrite(LEDPIN, 0);
}

void loop()
{
  digitalClockDisplay();
  checkWakeUp();
  delay(1000);  
}

void checkWakeUp(){
  if ((hour() == BEGIN_SUNRISE_HOUR) && (minute() == BEGIN_SUNRISE_MINUTE) && (second() == BEGIN_SUNRISE_SECOND)){
    int FadeSpeed = floor((SUNRISE_LENGTH_MINUTES * 60) / MAX_BRIGHTNESS * 1000.0);
    Serial.println("starting wakeup!\n");
    int brightness = 0;
    for (int i=0; i <= floor(MAX_BRIGHTNESS); i += 1){
      analogWrite(LEDPIN, i);
      delay(FadeSpeed);
      if (brightness != floor((i/MAX_BRIGHTNESS) * 100)){
        brightness = floor((i/MAX_BRIGHTNESS) * 100);
        Serial.print("Brightness: ");
        Serial.print(brightness);
        Serial.println("%");
      }
    }
    delay((SHINE_MAX_BRIGHTNESS_SECONDS * 1000));
    analogWrite(LEDPIN, 0);
  }
}

void digitalClockDisplay() // Clock on Serial Monitor
{
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year());
  Serial.println();  
}
void printDigits(int digits) 
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);  
}
