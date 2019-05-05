/* The responsibility of the buzzer is to sound when a column is full 
 * The LED flashes when a winner is found
 * The code reads serial input from the LED Board code and prompts the buzzer/LED when a certain string is read
 */ 
 
char readChar;
String player;
String reading="";
int index = 0;
int buzzer = 10;
int LED = 11;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  while (Serial.available()>0) {
  readChar = Serial.read();
  reading = reading + readChar;
}
Serial.print(reading);  
if (reading.indexOf('F') != -1) {
  tone(buzzer,1000); // send 1KHz sound signal
  delay(1000);
  noTone(buzzer);  
}

else if (reading.indexOf('W') != -1) {
 Serial.print(reading);
  int i = 1;
  while(i <= 5){
    digitalWrite(LED, HIGH);  
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
    i++;
  }
}

reading = ""; // reset for the next reading

}
