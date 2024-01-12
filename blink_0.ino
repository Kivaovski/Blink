unsigned long nextMillis = 0; // Variável para armazenar o tempo da última mudança de estado
unsigned int estadoLED = 1; // Estado atual do LED (0 = apagado, 1 = aceso)
unsigned int manterEstado = 0; // Flag para indicar se o estado deve ser mantido
unsigned int contador = 0; // Contador de ciclos
int estado = 0;

int pinos[] = {16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17};
int b_blink[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int b_estado[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 25; i++) {
    pinMode(pinos[i], OUTPUT);
    digitalWrite(pinos[i], LOW);
  }
  nextMillis = millis() + 250;
}
void loop() {




  //controla estado do botao
  if (millis() >= nextMillis) {
    for (int i = 0; i < 2; i++) {
      // Lê o estado do botão
      pinMode(pinos[i], INPUT_PULLUP);
      if (b_estado[i]==0) {   //le botao e faz accoes
        b_estado[i] = !digitalRead(pinos[i]);
        if (b_estado[i])
          if (b_blink[i] == 0)
            b_blink[i] = 300;
          else if (b_blink[i] < 280 )
            b_blink[i] = 0;
      }
      else
        b_estado[i] = !digitalRead(pinos[i]);

      //controla botao
      Serial.println(b_blink[i]);
      if (b_blink[i] && estado<5) {
        pinMode(pinos[i], OUTPUT);
        digitalWrite(pinos[i], 0);
      }
      if ( b_blink[i] > 0)
        b_blink[i]--;
      else {
        pinMode(pinos[i], OUTPUT);
        digitalWrite(pinos[i], 0);
      }
    }
    estado = (estado + 1) % 10;
    nextMillis += 50;
  }
}
