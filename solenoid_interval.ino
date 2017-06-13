/*
  first open relay and then waiting for sound signal.
  it will print the time interval before the relay open
  and receive a sound signal
*/

#define digi_sound 9
#define anal_sound 0 // for debug
#define LED 13
#define RELAY 7

int val = 0; // for debug
int digit = 0;
unsigned long startTime = 0;
unsigned long stopTime = 0;
bool flag = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(digi_sound, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digit = digitalRead(digi_sound);
  // val = analogRead(anal_sound);
  
  if (digit == 0 && flag) {    
    digitalWrite(LED, HIGH);
    Serial.print("open time of solenoid is: ");
    Serial.print(millis() - startTime);
    Serial.println("ms");
    startTime = 0;
    flag = false;
    delay(500);
    digitalWrite(RELAY, LOW);
  } else {
    digitalWrite(LED, LOW);
    
  }

}

/*
 * serial event to interrupt current loop
 */
void serialEvent() {
  while (Serial.available()){
    // get the new byte
    char firstChar = (char) Serial.read(); 
    // get the first char in buffer

    if (firstChar == 's') {
      digitalWrite(RELAY, HIGH); // start up relay
      delay(100);
      Serial.println("Relay start up! waiting for sound...");
      startTime = millis(); // record the start time
      flag = true; // flag is set to true in order to 
                  //go inside sound detect loop
    }
  }

}
