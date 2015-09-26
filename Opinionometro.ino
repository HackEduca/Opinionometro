#include <EEPROM.h>         // For data persistence 
#include <EEPROMAnything.h> // To be able to write entire objects at one into the EEPROM

struct opiniao{
  int infeliz;
  int meio_infeliz;
  int meio_feliz;
  int feliz;
};

opiniao opinioes;
int infeliz = 0;
int meio_infeliz = 0;
int meio_feliz = 0;
int feliz = 0;



void escreveEEPROM() {
  opinioes.infeliz = infeliz;
  opinioes.meio_infeliz = meio_infeliz;
  opinioes.meio_feliz = meio_feliz;
  opinioes.feliz = feliz;
  EEPROM_writeAnything(0, opinioes);
}

void leEEPROM() {
  EEPROM_readAnything(0, opinioes);
  infeliz = opinioes.infeliz;
  meio_infeliz = opinioes.meio_infeliz;
  meio_feliz = opinioes.meio_feliz;
  feliz = opinioes.feliz;
}

void setup() {
 // SOMENTE EXECUTE ESTA CHAMADA UMA UNICA VEZ QUANDO INICIALIZAR 
 // O ARDUINO, DEPOIS COMENTE  E RECOMPILE
 //escreveEEPROM();
 ////////////////////////////////////////////////////////////////
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT); // INFELIZ
  pinMode(3, INPUT); // MEIO INFELIZ
  pinMode(4, INPUT); // MEIO FELIZ
  pinMode(5, INPUT); // FELIZ
  leEEPROM();
  Serial.println("Totais:");
  Serial.print("  Infeliz: ");
  Serial.println(opinioes.infeliz);
  Serial.print("  Meio-Infeliz: ");
  Serial.println(opinioes.meio_infeliz);
  Serial.print("  Meio-Feliz: ");
  Serial.println(opinioes.meio_feliz);
  Serial.print("  Feliz: ");
  Serial.println(opinioes.feliz);
  Serial.println("===============");
}

void escreveSerial(int botao) {
  Serial.print("Apertou botao: ");
  Serial.println(botao);
  Serial.println("Totais:");
  Serial.print("  Infeliz: ");
  Serial.println(opinioes.infeliz);
  Serial.print("  Meio-Infeliz: ");
  Serial.println(opinioes.meio_infeliz);
  Serial.print("  Meio-Feliz: ");
  Serial.println(opinioes.meio_feliz);
  Serial.print("  Feliz: ");
  Serial.println(opinioes.feliz);
  Serial.println("===============");
}

void loop() {
  // INFELIZ!!   
  if (digitalRead(2) == 1) {
    digitalWrite(13, HIGH);
    infeliz++;
    escreveEEPROM();
    escreveSerial(1);
    delay(100);
    digitalWrite(13, LOW); 
    delay(500);
  }
  if (digitalRead(3) == 1) {
    digitalWrite(13, HIGH);
    meio_infeliz++;
    escreveEEPROM();
    escreveSerial(2);
    delay(100);
    digitalWrite(13, LOW); 
    delay(500);
  }
  if (digitalRead(4) == 1) {
    digitalWrite(13, HIGH);
    meio_feliz++;
    escreveEEPROM();
    escreveSerial(3);
    delay(100);
    digitalWrite(13, LOW); 
    delay(500);
  }
  // FELIZ!!
  if (digitalRead(5) == 1) {
    digitalWrite(13, HIGH);
    feliz++;
    escreveEEPROM();
    escreveSerial(4);
    delay(100);
    digitalWrite(13, LOW); 
    delay(500);
  }
  
}
