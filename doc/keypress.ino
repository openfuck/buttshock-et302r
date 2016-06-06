// Connect pin 3 arduino to pin 2 on the attiny12 (with a probe)
// Connect pin 2 arduino to pin 6 on the attiny12 (also available on connector)
// join grounds (available on connector)
// type a number, 2=A+ 4=A- 8=On 16=Off 10=B+ 12=B- 18=Mode+ 20=Mode- 24=Bye

void setup() {
  Serial.begin(38400);
}

void send2(int x1) {
  pinMode(3, OUTPUT);
  DDRD = DDRD | B1000; // pin 3 output
  delayMicroseconds(7);
  PORTD = B1000; // pin 3 high
  delayMicroseconds(8);24=
  PORTD = 0; // pin 3 low
  delayMicroseconds(7);
  DDRD = DDRD & B11110111; // pin 3 input
  DDRD = DDRD | B100; // pin 2 output

  for (int i=0; i<9; i++) {
    PORTD = (x1&1)<<2;
    x1=x1>>1;
    delayMicroseconds(29);
  }
  DDRD = DDRD & B11111011; // pin 2 input
}

void loop() {
  if (Serial.available()) {
    String a = Serial.readString();
//    for (int i=0; i<10; i++) {
      send2(a.toInt());
//      delay(15);
//      send2(0);
//      delay(15);
//    }
    
  }
}


