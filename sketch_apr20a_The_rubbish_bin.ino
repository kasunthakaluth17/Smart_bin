#include <Servo.h>    // Include the Servo library to control servo motors

Servo myServo;    // Create a servo object named myServo

int trigPin = 7;    // Ultrasonic sensor trigger pin
int echoPin = 6;    // Ultrasonic sensor echo pin
long duration;    // Variable to store the time taken for the echo pulse
int distance;   // Variable to store the calculated distance
int buzzerPin = 8;    // Buzzer positive pin

void setup() {
  pinMode(trigPin, OUTPUT);   // Set trigger pin as output (to send ultrasonic pulse)
  pinMode(echoPin, INPUT);    // Set echo pin as input (to receive reflected pulse)
  pinMode(buzzerPin, OUTPUT);   // Set buzzer pin as output

  myServo.attach(9);    // Connect servo motor to pin 9
  myServo.write(0);   // Start with the bin lid closed

  Serial.begin(9600);   // Initialize serial communication for debugging
}

void loop() {   // Send a short pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);   // Ensure the trigger pin starts LOW to clear any previous signal
  delayMicroseconds(2);   // Wait 2 microseconds before sending the trigger pulse
  digitalWrite(trigPin, HIGH);    // Send a HIGH pulse for 10 microseconds to trigger the ultrasonic sensor
  delayMicroseconds(10);    // Keep the trigger pin HIGH for 10 microseconds so the ultrasonic sensor sends a proper pulse
  digitalWrite(trigPin, LOW);   // Set the trigger pin LOW again to end the pulse

  duration = pulseIn(echoPin, HIGH);    // Measure the time taken for the echo to return

  distance = duration * 0.034 / 2;    // Convert the duration into distance (in cm)

  Serial.println(distance);   // Print distance to Serial Monitor for debugging

  if (distance < 30) {    // If an object is detected within 30 cm, turn on green LED
    digitalWrite(2, HIGH);    // Green LED ON (object detected)
    delay(300);   // Pause for 0.3 seconds to make the LED blink visibly when an object is detected
    digitalWrite(2, LOW);  // Turn LED OFF after short delay
  }

  if (distance > 30) {    // If no object is detected (distance > 30 cm), turn on red LED
    digitalWrite(4, HIGH);    // Red LED ON (no object detected)
    delay(300);   // Wait 300 milliseconds so the red LED stays ON long enough to be noticeable
    digitalWrite(4, LOW);   // Turn LED OFF after short delay
    delay(300);   // Pause briefly before restarting the loop to avoid rapid blinking
  }

  if (distance < 30) {    // Activate buzzer and open lid when object is close
    digitalWrite(buzzerPin, HIGH);    // Buzzer ON
    myServo.write(90);    // Open bin lid
  }

  if (distance > 30) {    // Turn off buzzer and close lid when object is far
    digitalWrite(buzzerPin, LOW);   // Buzzer OFF
    delay(300);   // Wait briefly before closing lid
  }

  if (distance < 30) {    // Keep lid open briefly when rubbish detected
    myServo.write(90);    // Open lid
    delay(500);   // Wait 0.3 seconds
  } 
  else {
    myServo.write(0);   // Close lid
  }
}