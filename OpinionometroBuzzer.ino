/*--------------------------------------------------------
OPINIONOMETER
Box that uses a four-value Likert scale 
to register opinions about something:
- highly unhappy
- medium unhappy
- medium happy
- highly happy

(c) Aldo von Wangenheim, Fernando Pacheco 2015
  --------------------------------------------------------*/

#include <EEPROM.h>         // For data persistence 
#include <EEPROMAnything.h> // To be able to write entire objects at one into the EEPROM

#define maxOpinioes 4      // Likert scale size
                           // Should be an even number
#define buzzPin     12     // Pin to connect the buzzer
                           // Code here uses active buzzer
#define ledPin      13     // Pin with feedback LED
                           // Using onboard LED only for development tests

int opinioes[maxOpinioes];
// infeliz = opinioes[0];
// meio_infeliz = opinioes[1];
// meio_feliz = opinioes[2];
// feliz = opinioes[3];

String nomesOpinioes[] = { "infeliz", "meio infeliz", "meio feliz", "feliz"};

String inputString;

void inicializaOpinioes() {
  for (int i=0; i<maxOpinioes; i++) {
    opinioes[i] = 0;
  } //end for
}

void escreveEEPROM() {
  EEPROM_writeAnything(0, opinioes);
}

void leEEPROM() {
  EEPROM_readAnything(0, opinioes);
}

void setup() {
  // SOMENTE EXECUTE ESTA CHAMADA UMA UNICA VEZ QUANDO INICIALIZAR 
  // O ARDUINO, DEPOIS COMENTE  E RECOMPILE
  //escreveEEPROM();
  ////////////////////////////////////////////////////////////////
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  for (int i=0; i<maxOpinioes; i++) {
    pinMode((i + 2), INPUT);
  } //end for
  leEEPROM();
  escreveValores();
  Serial.println("Parar zerar o contador envie codigo '12345'");
  Serial.println("===============");
}

void escreveValores() {
  Serial.println("Totais:");
  for (int i=0; i<maxOpinioes; i++) {
    Serial.print(nomesOpinioes[i] + ": ");
    Serial.println(opinioes[i]);
  } //end for
  Serial.println("===============");
}

void escreveSerial(int botao) {
  Serial.print("Apertou botao: ");
  Serial.println(botao);
  escreveValores();
}

void processaBotoes() {
  for (int i=0; i<maxOpinioes; i++) {
    processaBotao(i);
  } //end for
} //end processaBotoes 

void processaBotao(int i) {
  if (digitalRead(i+2) == 1) {
    digitalWrite(ledPin, HIGH);
    opinioes[i]++;
    escreveEEPROM();
    escreveSerial(i);
    buzz();
    while (digitalRead(i+2) == 1) {
      delay(50); 
    } //end while
    digitalWrite(ledPin, LOW); 
    delay(500);
  } // endif  
} //end processaBotao

void buzz() {
  digitalWrite(buzzPin, HIGH);
  delay(100);
  digitalWrite(buzzPin, LOW);
} //end buzz

void processaEntrada() {
  if (Serial.available()) {
    inputString = Serial.readString();
    if ((inputString.substring(0, 5)).equals("12345")) {
      Serial.println("Zerando valores!!");
      inicializaOpinioes();
      escreveEEPROM();
    } //endif input=12345
  } // endif serial not empty
} // end processaEntrada

void loop() {
  processaBotoes();
  processaEntrada();
}
