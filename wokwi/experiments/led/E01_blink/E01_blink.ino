const uint8_t LED_RED = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_RED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Commence the show");

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(millis());
  
  digitalWrite(LED_RED, HIGH);
  Serial.println("ON");
  delay(500);

  digitalWrite(LED_RED, LOW);
  Serial.println("OFF");
  delay(500);
  

}
