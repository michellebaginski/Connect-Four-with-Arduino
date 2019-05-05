/* The responsibility of the LED Board is to display the positions of each player
 * The code uses an array of  strings to keep track of the positions of each player
 * This array is used to determine if there is a winner or if the column is full
 * It sends this information through serial monitor to the LCD code
 */
int datapin0 = 2;  // pins for row 1
int latchpin0 = 3;
int clockpin0 = 4;
int datapin1 = 5;   // pins for row 2
int latchpin1 = 6;
int clockpin1 = 7;
int datapin2 = 8;   // pins for row 3
int latchpin2 = 9;
int clockpin2 = 10;
int datapin3 = 11;  // pins for row 4
int latchpin3 = 12;
int clockpin3 = 13;

// hold the pattern of which LEDs are currently turned on or off
byte leds0 = 0;  
byte leds1 = 0;
byte leds2 = 0;
byte leds3 = 0;

const int arraySize = 16;

// board representation 
String statusArray[arraySize] = {"empty", "empty", "empty", "empty",
                                 "empty", "empty", "empty", "empty",
                                 "empty", "empty", "empty", "empty",
                                 "empty", "empty", "empty", "empty"};
String player, win;
int reading;
char readChar;
bool changeTurns;

void setup(){
  // set all the pins of 74HC595 as OUTPUT
  Serial.begin(9600);
  pinMode(latchpin0, OUTPUT);
  pinMode(datapin0, OUTPUT);
  pinMode(clockpin0, OUTPUT);
  pinMode(latchpin1, OUTPUT);
  pinMode(datapin1, OUTPUT);
  pinMode(clockpin1, OUTPUT);
  pinMode(latchpin2, OUTPUT);
  pinMode(datapin2, OUTPUT);
  pinMode(clockpin2, OUTPUT);
  pinMode(latchpin3, OUTPUT);
  pinMode(datapin3, OUTPUT);
  pinMode(clockpin3, OUTPUT);
  leds0 = B11111111;
  leds1 = B11111111;
  leds2 = B11111111;
  leds3 = B11111111;
  player = "R";
  changeTurns = false;
}

void loop()  {
  reading = Serial.read();
  reading = (reading - 48);
  
  if ((reading >= 0 && reading <= 3)) {
    Serial.println(reading);
    
  // send buzzer error
  if (checkColumn(reading)) {
    Serial.write("#");
    Serial.write("F");
  }
  
  setRowbits(leds0, leds1, leds2, leds3, reading, player, changeTurns);
  
  if (winner(player)) {
    if (player == "G") {
      Serial.write("#");
      Serial.write("GW");
   }
    else {
      Serial.write("#");
      Serial.write("RW");
    }
  }
  
  else if (player == "R" && changeTurns) {
     Serial.write("#");
     Serial.write("G");
     player = "G";
     changeTurns = false;
  }
 
  else if (player == "G" && changeTurns) {
    Serial.write("#");
    Serial.write("R");
    player = "R";
    changeTurns = false;
  }
 }
 
  else if (reading == 4) {
    Serial.write("#RS");
    leds0 = B11111111;
    leds1 = B11111111;
    leds2 = B11111111;
    leds3 = B11111111;
    player = "R";
    changeTurns = false;

    // reset the array to empty
    for (int i = 0; i < 16; i++)
      statusArray[i] = "empty";
  }

  // update registers to reflect change on the board
  updateShiftRegister(latchpin0, clockpin0, datapin0, leds0);
  updateShiftRegister(latchpin1, clockpin1, datapin1, leds1);
  updateShiftRegister(latchpin2, clockpin2, datapin2, leds2);
  updateShiftRegister(latchpin3, clockpin3, datapin3, leds3);
  
 if (player == "R" && changeTurns) {
    player = "G";
    changeTurns = false;
 }

  else if (player == "G" && changeTurns) {
    player = "R";
    changeTurns = false;
  }
  
  delay(500); 
}


bool checkColumn(int column) {
  int count = 0;
  int y = column;
  
  for (int i = 0; i < 4; i++) {
    if (statusArray[y] != "empty")
      count++;
      y+=4;
  }
  
  return (count == 4 ? true : false);
}


// light up an LED according to the column
void setRowbits(byte &row0, byte &row1, byte &row2, byte &row3, int column, String color, bool &change) {
  int index = column;
  int pos = column;
  byte row = row0;
  int RowtoChange = 0;
  int greenPos = 2 * index;
  int redPos = 2 * index+ 1;
  bool found = false;

  for (int i=0; i<4; i++) {
    if ((statusArray[pos] == "empty") && !(found)) {
      if (color == "G") {
        bitWrite(row, greenPos, 0);
        statusArray[pos] = "G";
      }
      
    else if (color == "R") {
      bitWrite(row, redPos, 0);
      statusArray[pos] = "R";
    }
  found = true;
    }
  pos=pos+4;
  
  if (RowtoChange == 0) {
    row0 = row;
    row = row1;
    RowtoChange = 1;
  }
  
  else if ( RowtoChange == 1) {
    row1 = row;
    row = row2;
    RowtoChange = 2;
  }

  else if (RowtoChange == 2) {
    row2 = row;
    row = row3;
    RowtoChange = 3;
  }
}
  row3 = row;
  change = found;
}

// looks for a winner
bool winner(String color) {
    
  int compareV, compareH, countH, countV;
    
  // horizontal/vertical comparison
  for (int i=0; i<4; i ++) {
    compareV = i; compareH = i;
    countH = 0; countV = 0;
      
    for (int j = 0; j < 4; j++) {
      if (statusArray[compareV] == color) countV++;
      if (statusArray[compareH] == color) 
        countH++;
        compareV = compareV + 4;
        compareH++;
        }
  
    if (countH == 4  || countV == 4) return true;
    }
    
    // diagonal comparison
    compareV = 0 ; compareH = 3; countH = 0; countV = 0;
    for (int i=0; i<4; i++) {
      if (statusArray[compareV] == color) countV++;
      if (statusArray[compareH] == color) countH++;
    
      compareV = compareV + 5;
      compareH = compareH + 3;
    }
    
    if (countH == 4 || countV == 4)
    return true;
    return false;
}

/* updateShiftRegister() - This function sets the latchPin to low, 
*  then calls the Arduino function 'shiftOut' to shift out contents 
*  of variable 'leds' in the shift register before putting the 'latchPin' 
*  high again
*/
void updateShiftRegister(int latchPin, int clockPin, int dataPin, byte data) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, data);
  digitalWrite(latchPin, HIGH);
}
