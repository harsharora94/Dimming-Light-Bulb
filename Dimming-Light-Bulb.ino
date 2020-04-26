// ---------------------------------------------------------------------------------
//  Name        		:	Dimming-Light-Bulb.ino
//  Author      		:	Harsh Arora
//  Description     	:	This arduino code is responsible for dimming light bulb. 
//----------------------------------------------------------------------------------

#define fullOn 100
#define fullOff 0
#define FQ_50 1

int AC_Pin = 3;
int dimming = fullOff;
boolean freq = FQ_50;
String inString = "";
int x;
volatile boolean zero_cross = false;

void setup()
{
  pinMode(AC_Pin, OUTPUT);
  attachInterrupt(0, zero_cross_int, RISING);
  Serial.begin(9600);
}

void zero_cross_int()
{
  zero_cross = true;
}
void loop()
{
  if (zero_cross) {
    zero_cross = false;
    if (dimming >= 0 && dimming <= 100) {
      int dimtime = 90 * dimming;
      delayMicroseconds(dimtime);
      digitalWrite(AC_Pin, HIGH);
      delayMicroseconds(100);
      digitalWrite(AC_Pin, LOW);
    }
  }
 //  delay(20);
  if (Serial.available() > 0) {
    serial_int();
  }
}

void serial_int()
{
  while (Serial.available() > 0)
  {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char
      // and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      dimming = inString.toInt();
      Serial.println(dimming);
      Serial.print("String: ");
      Serial.println(inString);
      // clear the string for new input:
      inString = "";
    }
  }
}