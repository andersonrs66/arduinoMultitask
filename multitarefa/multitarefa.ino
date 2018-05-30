// multitarefa sem sistema operacional
// Anderson Ferreira Rodriguez
// 29-05-2018
// V1


//prototipo das funcoes
void pisca();
void trataTecla();
void brilhoPWM();

// Nome das portas usadas
#define LEDPWM 3
#define LED2HZ 7
#define MAIS 13
#define MENOS 12


static unsigned long timerBrilhoPWM;
static unsigned long timerPisca;
static unsigned long timerTrataTecla;

int brilho = 0;
bool estadoLed1 = 0;


void setup() {
  pinMode(LEDPWM, OUTPUT);
  pinMode(LED2HZ, OUTPUT);
  pinMode(MAIS, INPUT_PULLUP); //INPUT_PULLUP porque não usei resistor de pullup
  pinMode(MENOS, INPUT_PULLUP);

  //inicializar os timers das funcoes
  timerPisca = millis();
  timerTrataTecla = millis();
  timerBrilhoPWM = millis();
}

void loop() {
  //necessário declara uma variável global para armazenar o timer!
  
  //sintaxe:
  //if((millis() - [timerGlobalDaFuncao]) > [disparo]) [funcao()];

  if((millis() - timerPisca) > 500) pisca();

  if((millis() - timerTrataTecla) > 100) trataTecla();
  
  if((millis() - timerBrilhoPWM) > 200) brilhoPWM();
}

void pisca(){
  digitalWrite(LED2HZ, estadoLed1);
  estadoLed1 = !estadoLed1;
  timerPisca = millis();
}

void trataTecla(){
  if(digitalRead(MAIS) && (brilho < 255)){
    brilho = brilho + 1;
  }
  if(digitalRead(MENOS) && (brilho > 0)){
    brilho = brilho - 1;
  }
  timerTrataTecla = millis();//resetar o timer no fim da função
}

void brilhoPWM(){
  analogWrite(LEDPWM, brilho);
  timerBrilhoPWM = millis();
}

