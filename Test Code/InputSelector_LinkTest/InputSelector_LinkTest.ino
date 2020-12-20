//PINS
#define PIN_LINK_SW 4
#define PIN_LINK_RELAY 2

//Global Vars
byte LinkSwState = 0;

byte relayState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_LINK_SW, INPUT);
  pinMode(PIN_LINK_RELAY, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateLink();
  //delay(1000);
}

void updateLink()
{
  LinkSwState = digitalRead(PIN_LINK_SW);
  Serial.println(LinkSwState);
  if (LinkSwState != relayState)
  {
    if (LinkSwState == HIGH)
    {
      digitalWrite(PIN_LINK_RELAY, HIGH);
      relayState = HIGH;
    }else
    {
      digitalWrite(PIN_LINK_RELAY, LOW);
      relayState = LOW;
    }
    Serial.print("  updated relay ");
  }  
  
}
