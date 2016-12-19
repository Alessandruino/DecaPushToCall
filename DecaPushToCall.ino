#include <SoftwareSerial.h>

//pin seriali per il modulo bluetooth hm10
SoftwareSerial mySerial(10, 11); // RX, TX

// pins per i LEDs e per il pulsante:
const int connectionLed = 5;
const int notificationLed = 13;
int buttonPin = 8;
int statePin = 2;

// variabili booleane di controllo
bool button1;
bool button0;
bool btconnected;

void setup() {
  // inizializza seriale:
  mySerial.begin(115200);
  // assegnazione pin di output e imput:
  pinMode(connectionLed, OUTPUT);
  pinMode(notificationLed, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(statePin, INPUT);

}

void loop() {

  if (digitalRead(statePin) == HIGH){
    btconnected = true;
    digitalWrite(connectionLed,HIGH);
    
  }
  else {
    btconnected = false;
    digitalWrite(connectionLed,LOW);
  }

  // se ci sono dati sul seriale leggili:
  while (mySerial.available() > 0) {

    // cerca il prossimo valore integer valido:
    int primo = mySerial.parseInt();
    // do it again:
    int secondo = mySerial.parseInt();
    // do it again:
    int terzo = mySerial.parseInt();
    
// fine del pacchetto

    if (mySerial.read() == '\n') {
      
      if (primo == 200 && digitalRead(buttonPin) == HIGH){
          mySerial.print("100");
      }

      else if (primo == 200 && digitalRead(buttonPin) == LOW){
          mySerial.print("0");
        
      }
    }
  }

  if((digitalRead(buttonPin) == HIGH) and !button1 and btconnected){
          mySerial.print("100");
          digitalWrite(notificationLed,HIGH);
          button1 = true;
          button0 = false;
          delay(300);
      }
  else if ((digitalRead(buttonPin) == LOW) and !button0 and btconnected){
        mySerial.print("0");
        digitalWrite(notificationLed,LOW);
        button1 = false;
        button0 = true;
        delay(300);
      }
}
