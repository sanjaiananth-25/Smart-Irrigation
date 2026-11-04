/************************************************************
        SMART IRRIGATION SYSTEM - SKETCH 2
      Servo + Soil Sensor + Relay Test
************************************************************/

#include <ESP32Servo.h>

#define SOIL_PIN   33
#define RELAY_PIN   4
#define SERVO_PIN  18

Servo servo;

// Moisture Targets
int targetMoisture[2] = {70, 80};

// Servo Angles
int servoAngle[2] = {0, 180};

//--------------------------------------------------

// Read soil moisture
int getMoisture()
{
  int raw = analogRead(SOIL_PIN);

  // Calibration
  // Dry = 4000
  // Wet = 2500

  int moisture = map(raw, 4000, 2500, 0, 100);
  moisture = constrain(moisture, 0, 100);

  Serial.print("Raw : ");
  Serial.print(raw);
  Serial.print("   Moisture : ");
  Serial.print(moisture);
  Serial.println("%");

  return moisture;
}

//--------------------------------------------------

void pumpON()
{
  digitalWrite(RELAY_PIN, LOW);      // Active LOW relay
  Serial.println("Pump ON");
}

void pumpOFF()
{
  digitalWrite(RELAY_PIN, HIGH);
  Serial.println("Pump OFF");
}

//--------------------------------------------------

void waterPot(int pot)
{
  Serial.println("--------------------------------");

  Serial.print("Moving Servo to Pot ");
  Serial.println(pot + 1);

  servo.write(servoAngle[pot]);

  delay(2000);

  int moisture = getMoisture();

  if (moisture < targetMoisture[pot])
  {
    pumpON();

    while (true)
    {
      moisture = getMoisture();

      if (moisture >= targetMoisture[pot])
      {
        break;
      }

      delay(500);
    }

    pumpOFF();
  }
  else
  {
    Serial.println("Soil Already Wet");
  }

  Serial.print("Pot ");
  Serial.print(pot + 1);
  Serial.println(" Completed");

  delay(2000);
}
//======================================================
// SERVO FUNCTIONS
//======================================================

void moveToPot(int pot)
{
  servo.write(servoAngle[pot]);
  delay(1500);

  Serial.print("Servo moved to Pot ");
  Serial.println(pot + 1);
}

//======================================================
// SOIL MOISTURE
//======================================================

int getMoisture()
{
  rawValue = analogRead(SOIL_PIN);

  // Calibration
  // Dry = 4000
  // Wet = 2500

  moisture = map(rawValue, 4000, 2500, 0, 100);
  moisture = constrain(moisture, 0, 100);

  Serial.print("Raw Value : ");
  Serial.print(rawValue);

  Serial.print("   Moisture : ");
  Serial.print(moisture);

  Serial.println("%");

  return moisture;
}

//======================================================
// PUMP FUNCTIONS
//======================================================

void pumpON()
{
  digitalWrite(RELAY_PIN, LOW);      // Active LOW Relay

  pumpStatus = true;

  Serial.println("Pump ON");
}

void pumpOFF()
{
  digitalWrite(RELAY_PIN, HIGH);

  pumpStatus = false;

  Serial.println("Pump OFF");
}

//======================================================
// WATER ONE POT
//======================================================

void waterPot(int pot)
{
  moveToPot(pot);

  int value = getMoisture();

  Serial.print("Target Moisture : ");
  Serial.println(targetMoisture[pot]);

  if(value < targetMoisture[pot])
  {
      pumpON();

      while(getMoisture() < targetMoisture[pot])
      {
          delay(500);
      }

      pumpOFF();
  }
  else
  {
      Serial.println("Soil already wet");
  }

  Serial.println("---------------------------");
}
//--------------------------------------------------

void setup()
{
  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH);

  servo.attach(SERVO_PIN);

  servo.write(0);

  Serial.println("SMART IRRIGATION TEST");
}

//--------------------------------------------------

void loop()
{
    waterPot(0);

    delay(3000);

    waterPot(1);

    delay(5000);
}
