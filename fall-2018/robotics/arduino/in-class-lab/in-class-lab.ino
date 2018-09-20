int LED_pin = 6;
int button_pin = 12;

void setup() {
    Serial.begin(57600);
    Serial.println("Starting demo");
    pinMode(LED_pin, OUTPUT);
    pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
    delay(200);
    int pin_val = digitalRead(button_pin);

    Serial.print("Pin 12: ");
    Serial.println(pin_val);

    if(pin_val == 0) {
        digitalWrite(LED_pin, HIGH);
    } else {
        digitalWrite(LED_pin, LOW);
    }
}
