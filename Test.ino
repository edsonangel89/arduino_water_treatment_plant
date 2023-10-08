const int mainDoorPin = 3;
const int receptionWindowPin = 4;
const int checkoutWindowPin = 5;

const int mainPowerPin = 10;

const int greenLedPin = 15;
const int redLedPin = 16;

bool mainDoorState;
bool receptionWindowState;
bool checkoutWindowState;

void setup() {
  Serial.begin(9600);
  pinMode(mainDoorPin, INPUT);
  pinMode(receptionWindowPin, INPUT);
  pinMode(checkoutWindowPin, INPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(mainPowerPin, OUTPUT);
  digitalWrite(mainPowerPin, LOW);
}

void loop() {
  getSensors();
  if (mainDoorState || receptionWindowState || checkoutWindowState == LOW) {
      digitalWrite(mainPowerPin, LOW);
      digitalWrite(redLedPin, HIGH);
      errorMsgs();
    }
    else {
      digitalWrite(mainPowerPin, HIGH);
      digitalWrite(greenLedPin, HIGH);
      successMsgs();
    }
  delay(2000);
}

void errorMsgs() {
  Serial.println("");
  Serial.print("Main door: ");Serial.println(mainDoorState);
  Serial.print("Reception window: ");Serial.println(receptionWindowState);
  Serial.print("Checkout window: ");Serial.println(checkoutWindowState);
  Serial.println("Check doors and windows");
  Serial.println("");
}

void successMsgs() {
  Serial.println("System enabled");
}

void getSensors() {
  int x = 1;
  while (mainDoorState || receptionWindowState || checkoutWindowState == 1) {
    mainDoorState = digitalRead(mainDoorPin);
    receptionWindowState = digitalRead(receptionWindowPin);
    checkoutWindowState = digitalRead(checkoutWindowPin);
    x = 0;
  }
}
