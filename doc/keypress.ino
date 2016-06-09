// Connect pin 3 arduino to pin 2 on the attiny12 (with a probe)
// Connect pin 2 arduino to pin 6 on the attiny12 (also available on connector)
// Connect pin 4 arduino to pin on the attiny12 (clock, also on connector)
// join grounds (available on connector)
// we won't use interrupts since they don't work well on my due board
// type a number, 2=A+ 4=A- 8=On 16=Off 10=B+ 12=B- 18=Mode+ 20=Mode- 24=Bye

void setup() {
  Serial.begin(38400);
  DDRD = 0;  // all inputs
}

void send2(int x1) {
  DDRD = DDRD | B1000; // pin 3 output
  delayMicroseconds(7);
  PORTD = B1000; // pin 3 high
  delayMicroseconds(8);
  PORTD = 0; // pin 3 low
  delayMicroseconds(7);
  PORTD = B100; // pin 2 high
  DDRD = DDRD & B11100111; // pin 3,4 input
  DDRD = DDRD | B100; // pin 2 output

  while((PIND&B10000) != 0) {}; // wait for clock L

  for (int i=0; i<8; i++) {
    PORTD = (x1&1)<<2;
    x1=x1>>1;
    while((PIND&B10000) == 0) {};     
    if (i<7) while((PIND&B10000) != 0) {}; // wait for clock L->H
  }
  DDRD = DDRD & B11111011; // pin 2 input
}

byte pinintstate = 0;

void loop() {
  byte x = PIND&B1000; // pin3
  
  if (x != pinintstate) {
    pinintstate = x;
    if (x == 0) { // gone low!      
      byte z = 0;      
      delayMicroseconds(5);
      for (byte i=0; i<8; i++) { 
        while((PIND&B10000) != 0) {};        
        while((PIND&B10000) == 0) {}; // wait for clock L->H
        z=z<<1;
        if (PIND&B100) {
           z=z+1;
        }
      }
    String s = "00000000"+String(z,BIN);
    Serial.println(s.substring(s.length()-8));
    }
  }
  if (Serial.available()) {
    String a = Serial.readString();
//    for (int i=0; i<16; i++) {
      send2(a.toInt());
//     delay(103);
//     send2(0);
//     delay(15);
//   }
    
  }
}


