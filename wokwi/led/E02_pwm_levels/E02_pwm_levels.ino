const uint8_t LED_RED = 6;
const uint8_t BRIGHTNESS_LEVELS[] = {0, 10, 50, 128, 200, 255};
const uint8_t NUM_LEVELS = sizeof(BRIGHTNESS_LEVELS)/sizeof(BRIGHTNESS_LEVELS[0]);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_RED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Commence the show");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for(uint8_t i = 0; i < len; i++){
    analogWrite(LED_RED, BRIGHTNESS_LEVELS[i]);
    Serial.println(BRIGHTNESS_LEVELS[i]);
    delay(1000);
  }  

}
