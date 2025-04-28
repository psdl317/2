// Arduino program to simulate traffic lights using 3 LEDs

const int redPin = 12;
const int yellowPin = 11;
const int greenPin = 10;

void setup() { 
  // Set the LED pins as OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() { 
  // Red light ON
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  delay(5000); // Red light for 5 seconds

  // Yellow light ON (prepare to go green)
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, LOW);
  delay(2000); // Yellow light for 2 seconds

  // Green light ON
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, HIGH);
  delay(5000); // Green light for 5 seconds
}
