/* 4 push buttons represent the columns in the board, once one is pressed information is sent to  the LED Board code. The 5th pushbutton is the reset button for when a winner is found.  */
int btn1Val1, btn1Val2;
int btn2Val1, btn2Val2;
int btn3Val1, btn3Val2;
int btn4Val1, btn4Val2;
int resetBtnVal1, resetBtnVal2;
int btn1 = 2;
int btn2 = 4;
int btn3 = 6;
int btn4 = 8;
int resetBtn = 10;

void setup() {
// initialize input and output pins 
pinMode(btn1, INPUT);   
   pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT); 
pinMode(resetBtn, INPUT);
  Serial.begin(9600);
}

void loop() {
// read initial input
btn1Val1 = digitalRead(btn1); 
btn2Val1 = digitalRead(btn2);  
btn3Val1 = digitalRead(btn3);  
btn4Val1 = digitalRead(btn4);  
resetBtnVal1 = digitalRead(resetBtn);
delay(100);
btn1Val2 = digitalRead(btn1);  
btn2Val2 = digitalRead(btn2);  
btn3Val2 = digitalRead(btn3);  
btn4Val2 = digitalRead(btn4); 
resetBtnVal2 = digitalRead(resetBtn);

 if(btn1Val1 != btn1Val2)
    if(btn1Val1 == 1)
        Serial.write("0");

if(btn2Val1 != btn2Val2)
if(btn2Val1 == 1)
Serial.write("1");

 if(btn3Val1 != btn3Val2)
    if(btn3Val1 == 1)
      Serial.write("2");

 if(btn4Val1 != btn4Val2)
    if(btn4Val1 == 1)
Serial.write("3");

 if(resetBtnVal1 != resetBtnVal2)
    if(resetBtnVal1 == 1)
        Serial.write("4");
}
