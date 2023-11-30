/*
  Trabalho de Sistemas Embarcados - Engenharia da Computação - ESAMC


  Professor Pericles A. Carvalho


  Integrantes:

  - Beatriz
  - Eloy
  - Guilherme
  - Jonas
  - Micheli
  - Pamela
  - Patricia

*/

#include <Wire.h> 
#include "LiquidCrystal_I2C.h";       // Biblioteca para display
#include "HX711.h";                   // Biblioteca HX711

#define DOUT  A0                      // HX711 DATA OUT = pino A0 do Arduino 
#define CLK  A1                       // HX711 SCK IN = pino A1 do Arduino 

HX711 balanca;                        // define instancia balança HX711

float fator_calibracao = 42130;       // fator de calibração aferido na Calibraçao 

// Variável da LCD
LiquidCrystal_I2C lcd(0x27,16,2); 

// Variáveis dos botões
const int botao_esquerda = 2;
const int botao_baixo = 3;
const int botao_cima = 4;
const int botao_direita = 5;

bool esquerda;
bool baixo;
bool cima;
bool direita;

long tempoApertoBotao_e;
long tempoApertoBotao_d;

// Opções do menu
String Menu[] = { "Gramagem <>", "Dosagem <>", "Tara >", "Iniciar > ", "Sair >" };

// Variáveis do menu
int posicao = 0;
int gramagem = 50;  // pre-set de peso
int dosagem = 50;
int tara = 0;

// Variável do motor
int motor = 9;
 
// Variável do sensor de presença
int presenca = 8;

// Variáveis do processo
int processo_iniciado = 0;
int dosagem_atual = 0;
 
void setup() {
  Serial.begin (9600);

  // Configurando os pinos dos botões como entrada
  pinMode(botao_esquerda, INPUT_PULLUP);
  pinMode(botao_baixo, INPUT_PULLUP);
  pinMode(botao_cima, INPUT_PULLUP);
  pinMode(botao_direita, INPUT_PULLUP);

  // Inicializa a balança
  balanca.begin(DOUT, CLK);
  balanca.set_scale(fator_calibracao);               // ajusta fator de calibração
  balanca.tare();                                    // zera a Balança
  
  // Configurando o motor
  pinMode (motor, OUTPUT);
  digitalWrite (motor, LOW);
  
  // Configurando o sensor de presença
  pinMode (presenca, INPUT);

  // Inicializa o display
  lcd.init();
  lcd.setBacklight ( HIGH ) ;
  lcd.begin (16, 2);
  lcd.print ("Seja Bem Vindo!");
  
  // Construindo menu
  Tara();
  Movimenta_Menu ();
} 
 
void loop() {
  esquerda = !digitalRead(botao_esquerda);
  baixo = !digitalRead(botao_baixo);
  cima = !digitalRead(botao_cima);
  direita = !digitalRead(botao_direita);
  delay (1000);  

  Serial.begin (9600);
  
  // Se botão baixo for pressionado
  if (baixo) {
    if (posicao == 4) {
      posicao = 0;
    } else {
      posicao = posicao + 1;
    }

    Movimenta_Menu ();
  } else {

    // Se botão cima for pressionado
    if (cima) {
      if (posicao == 0) {
        posicao = 4;
      } else {
        posicao = posicao - 1;
      }
      Movimenta_Menu ();
    }
  }

  // Se o botão esquerdo for pressionado
  if (esquerda && posicao < 2) {
    tempoApertoBotao_e = millis ();

    while (esquerda) {
      if (millis () - tempoApertoBotao_e >= 5000) {
        switch (posicao) {
          case 0:
          if (gramagem >= 9) {
            gramagem = gramagem - 10;
          } else {
            dosagem --;
          }
          break;

          case 1:
          if (dosagem >= 9) {
            dosagem = dosagem - 10;
          } else {
            dosagem --;
          }
          break;
        }
        Movimenta_Menu ();

      } else {
        switch (posicao) {
          case 0:
            if (gramagem != 0) {
              gramagem--;
            }

            break;

          case 1:
            if (dosagem != 0) {
              dosagem--;
            }
            
            break;
        }
        Movimenta_Menu ();
      }
    }
  } else {
    // Se o botao direito for pressionado e estiver em uma posicao de medidas
    if (direita && posicao < 2) {
      tempoApertoBotao_d = millis ();

      while (direita) {
        if (millis () - tempoApertoBotao_d >= 5000) {
          switch (posicao) {
            case 0:
            gramagem = gramagem + 10;
            break;

            case 1:
            dosagem = dosagem + 10;
            break;
          }

          Movimenta_Menu ();
        } else {
          switch (posicao) {
            case 0:
            gramagem++;
            break;

            case 1:
            dosagem++;
            break;
          }

          Movimenta_Menu ();
        }
      }
    }
  }

  // Se o botao direito for pressionado e estiver em uma posicao de INICAR ou SAIR
  if (direita && posicao > 1) {
    switch (posicao) {
      case 2:
      Tara();
      break;

      case 3:
      Inicia_Processo ();
      break;

      case 4:
      //Desativar interruptor se tiver
      break;
    }
  }
  
  // Varredura da balancaa vem aqui!!
  int pesomedido = 0;   //pesomedido = digital/analogicRead(balanca);
  /* Checo se o processo foi iniciado */ 
  if (processo_iniciado == 1) {
    // Se sim, checo o se o peso atual e igual ao peso meta  
    if (pesomedido = (gramagem - tara)) {
      // Se sim, parar o motor e dar xau
      Encerra_Processo ();
    } else {
      // Se nao, checar se esta proximo da quantia
      if (pesomedido >= ((gramagem - tara) * 85 / 100)) {
        // Se sim, diminuir a velocidade do motor
        analogWrite (motor, 10);
      }
      // Se nao, deixar o motor rodar normalmente
    }
  }
}

 // Função que constroi menu
void Movimenta_Menu() {
  lcd.begin (16, 2);
  lcd.print (Menu[posicao]);
  
  switch (posicao) {
    // Menu Gramagem
    case 0: 
    lcd.setCursor (0, 1);
    lcd.print (gramagem);
    
    lcd.setCursor (3, 1);
    
    lcd.print ("G");
    break;

    // Menu Dosagem
    case 1:
    lcd.setCursor (0, 1);
    lcd.print (dosagem);
    lcd.setCursor (3, 1);
    lcd.print ("UN");
    break;

    // Menu Tara
    case 2:
    lcd.setCursor (0, 1);
    lcd.print(balanca.get_units(), 3);              // imprime peso na balança com 3 casas decimais 
    lcd.print (" g");
    delay(1000);
    break;
  }
}
 
// Função que liga o motor
void Inicia_Processo() {
  if (!digitalRead (presenca)) {
    lcd.begin (16, 2);
    lcd.print ("Iniciado!!");
    
    digitalWrite(motor, HIGH);
    processo_iniciado = 1;
  } else {
    lcd.begin (16, 2);
    lcd.print ("   Coloque o   ");
    
    lcd.setCursor (0, 1);
    lcd.print (" Reservatorio!");
    
    // Ativa buzzer
    delay (2000);
    Movimenta_Menu ();
  }
}
 
// Função que desliga o motor
void Encerra_Processo() {
  dosagem_atual++;

  if (dosagem = dosagem_atual) {
    lcd.begin (16, 2);
    lcd.print ("Processo");
    
    lcd.setCursor (0, 1);
    lcd.print ("Finalizado!");
    
    delay (2000);
    digitalWrite(motor, LOW);
    
    processo_iniciado = 0;

    //Desativar interruptor se tiver
  } else {
    lcd.begin (16, 2);
    lcd.print ("Prepare para");
    
    lcd.setCursor (0, 1);
    lcd.print ("proxima dose!");
    
    delay (5000);
    Inicia_Processo ();
  }
}

// Função que tira a tara
void Tara() {
  balanca.tare();
  delay(1000);

  Movimenta_Menu();
}