/* the LCD has 3 resposibilities to display messages to the user:
 * whose turn it is
 * when a winner is found
 * when a column is full. 
 * the display gets updated according to what is received from the LED Board code.
 */
 
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char readChar;
String reading="";
String player;
int index;

void setup() {
   Serial.begin(9600);                                                                              
   lcd.begin(16, 2);
   lcd.setCursor(0,0);
   lcd.print("The player is: ");
   lcd.setCursor(0,1);
   lcd.print("  ");
   lcd.print(“RED!!");
}

void loop() {
  // read from serial monitor and store everything in a string 
  while(Serial.available() > 0) {
    readChar = Serial.read();
    reading = reading + readChar;
  }

  reading.trim(); 
  index = reading.indexOf('#'); 
  player = reading.substring(index+1);
  Serial.println(player);
  
  if (player == "R" || player == "RS") {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("The player is: ");
    lcd.setCursor(0,1);
    lcd.print("  ");
    lcd.print("RED!!");
  }
  
  else if (player ==  "G") {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("The player is: ");
    lcd.setCursor(0,1);
    lcd.print("  ");
    lcd.print("GREEN!!");
  }
  
  else if (player == "F")  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Column full!!");
    lcd.setCursor(0,1);
    lcd.print("Try again");
  }
  
  else if (player == "GW") {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GREEN WINS");
    lcd.setCursor(0,1);
    lcd.print("Press Reset");
  }
  
  else if (player == "RW") {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RED WINS");
    lcd.setCursor(0,1);
    lcd.print("Press Reset");
  }
  
  else if (player == "-9999"){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Wrong Input");
    lcd.setCursor(0,1);
    lcd.print("Try again");
  }
  
  reading = ""; //reset for the next read                                
  delay(1000)
}
