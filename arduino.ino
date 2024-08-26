const int eyeSensorPin = 2;         // Eye-tracking sensor pin
const int relayPin = 3;             // Relay module control pin
const int eyeClosedDuration = 3000; // 3 seconds in milliseconds
const int eyeCLOSEDDURATION = 5000; // 5 seconds in milliseconds
const int led = 4;
const int buzzer = 5;
unsigned long eyeClosedStartTime = 0; // Timestamp when the eye was closed

bool msg_send = false; // boolean

void setup()
{
  pinMode(eyeSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(relayPin, LOW); // Turn on the relay module at the beginning
  Serial.begin(9600);          // begin the serial panel
}

void loop()
{
  int eyeState = digitalRead(eyeSensorPin);

  if (eyeState == HIGH)
  {
    if (eyeClosedStartTime == 0)
    {
      eyeClosedStartTime = millis();
    }

    if (millis() - eyeClosedStartTime >= eyeClosedDuration)
    {
      // digitalWrite(relayPin, HIGH);  // Stop the relay module if the eye is closed for 3 seconds
      digitalWrite(led, HIGH); // lit thd led
      digitalWrite(buzzer, HIGH);
    }
    if (millis() - eyeClosedStartTime >= eyeCLOSEDDURATION)
    {
      digitalWrite(relayPin, HIGH); // Stop the relay module if the eye is closed for 5 seconds
      // digitalWrite(led,HIGH);
      digitalWrite(buzzer, LOW);

      if (!msg_send)
      { // if msg_send is false then it will print 1
        Serial.println(1);
        msg_send = true; // msg_true will became true, so no infinite loops
      }
    }
  }
  else
  {
    eyeClosedStartTime = 0;      // Reset the timer
    digitalWrite(relayPin, LOW); // Turn on the relay module when the eye is open
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);

    msg_send = false;
  }
}
