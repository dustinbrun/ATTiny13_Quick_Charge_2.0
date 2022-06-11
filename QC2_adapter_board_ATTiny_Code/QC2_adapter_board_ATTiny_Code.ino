/*
   ATTiny 13 Quick Charge 2.0 Powerbank Adapter Board
   Author: dustinbrun
           licensed under CC BY 4.0

   Version 03.2022
*/

const int J1 = 4;
const int Dp_2k2 = 0;
const int Dp_10k = 1;
const int Dn_10k = 2;
const int load = 3;

bool active_9V = 0;

void setup()
{
  delay(500);

  pinMode(load, OUTPUT);
  pinMode(J1, INPUT_PULLUP);

  blink_load(2, 100);

  // Quickcharge Init
  pinMode(Dn_10k, INPUT);
  pinMode(Dp_2k2, INPUT);
  pinMode(Dp_10k, OUTPUT);
  digitalWrite(Dp_10k, HIGH);
  delay(2000);
  pinMode(Dn_10k, OUTPUT);
  digitalWrite(Dn_10k, LOW);
  delay(500);
  // End of Quickcharge Init

  digitalWrite(load, HIGH);
  delay(500);
  
  if (digitalRead(J1) == LOW) //Jumper is set, Output 9V
  {
    // Quickcharge set 9V
    pinMode(Dp_2k2, OUTPUT);
    digitalWrite(Dp_2k2, HIGH);
    digitalWrite(Dn_10k, HIGH);
    // End of Quickcharge set 9V
    
    blink_load(2, 500);
    active_9V = true;
  }
  else  //Jumper is not set, Output 12V
  {
    // Quickcharge set 12V
    pinMode(Dp_2k2, OUTPUT);
    digitalWrite(Dp_2k2, LOW);
    digitalWrite(Dn_10k, HIGH);
    // End of Quickcharge set 12V
    
    blink_load(1, 500);
    active_9V = false;
  }
}

void loop() 
{
  delay(3000);

  if (active_9V)
  {
    blink_load(2, 1000);
  }
  else
  {
    blink_load(1, 1000);
  }

}


void blink_load(int x, int delaytime)
{
  for (int i = 0; i < x ; i++)
  {
    digitalWrite(load, HIGH);
    delay(delaytime);
    digitalWrite(load, LOW);
    delay(delaytime);
  }
}
