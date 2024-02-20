void setup() {
  // Bella Lardin
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(9, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(digitalRead(9)){
    digitalWrite(5, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(500);            // wait for a second
    digitalWrite(5, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(6, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(500);            // wait for a second
    digitalWrite(6, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(7, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(500);            // wait for a second
    digitalWrite(7, LOW);   // turn the LED off by making the voltage LOW
  }
}
