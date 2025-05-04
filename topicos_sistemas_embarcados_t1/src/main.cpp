#include LiquidCrystal.h

//-----------------------------DEFINIÇÃO DE ENTRADAS E SAIDAS------------------------//

// ENTRADAS DOS BOTOES(ANALOGICAS)
#define botao_select A0 // cinza
#define botao_cancela A1 // marrom
#define botao_sobe A2 // rosa
#define botao_desce A3 // roxo

// SAIDAS DOS LEDS(DIGITAIS)
const int led_azul = 9;
const int led_amarelo = 8;
const int led_verde = 7;
const int led_laranja = 6;

//---------------------------VARIAVEIS DE CADA LED------------------------------//

//VARIAVEIS LED AZUL
int v_led_azul = 500;
bool azul_piscando = false, estado_led_azul = false;
unsigned long ultima_troca_azul = 0;

//VARIAVIES LED AMARELO
int v_led_amarelo = 500;
bool amarelo_piscando = false, estado_led_amarelo = false;
unsigned long ultima_troca_amarelo = 0;

//VARIAVEIS LED VERDE
int v_led_verde = 500;
bool verde_piscando = false, estado_led_verde = false;
unsigned long ultima_troca_verde = 0;

//VARIAVEIS LED LARANJA
int v_led_laranja = 500;
bool laranja_piscando = false, estado_led_laranja = false;
unsigned long ultima_troca_laranja = 0;

//---------------------------OUTRAS VARIAVEIS----------------------//

int menu = 1;
bool select_submenu = false, select_submenu_velocidade = false;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte sorrisinho[8] = {
  B00000,
  B00010,
  B11001,
  B00001,
  B11001,
  B00010,
  B00000,
};

//----------------------------INÍCIO DO CÓDIGO------------------------//

void setup(){
  Serial.begin(9600);
  delay(100);
  
  lcd.begin(16,2);//APAGAR DEPOIS DO TESTE
  delay(100);
  /*
  //SETA O DISPLAY E IMPRIME MENSAGEM INICIAL
  lcd.begin(16,2);
  lcd.print("Trabalho de TSE1");
  lcd.createChar(0,sorrisinho);
  lcd.setCursor(0,1);
  lcd.print("aproveitem ");
  lcd.setCursor(11,1);
  lcd.write(byte(0));
  delay(5000);
  delay(100);
  */
  
  // BOTOES COMO INPUT
  pinMode(botao_sobe, INPUT_PULLUP);
  pinMode(botao_desce, INPUT_PULLUP);
  pinMode(botao_select, INPUT_PULLUP);
  pinMode(botao_cancela, INPUT_PULLUP);
  
  //LEDS COMO OUTPUT
  pinMode(led_azul, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_laranja, OUTPUT);
  
  //ATUALIZA O MENU
  atualiza_menu();
}

void loop(){
  if(!digitalRead(botao_sobe)){
    menu--;
    if(menu>5) menu = 5;
    atualiza_menu();
    delay(200);
    while(!digitalRead(botao_sobe));
  }
  
  if(!digitalRead(botao_desce)){
    menu++;
    atualiza_menu();
    delay(200);
    while(!digitalRead(botao_desce));
  }
  
  if(!digitalRead(botao_select)){
    if(select_submenu && !select_submenu_velocidade) select_submenu_velocidade = true;
    if(!select_submenu) select_submenu = true;
    menu*=10;
    atualiza_menu();
    delay(200);
    while(!digitalRead(botao_select));
  }

  if(!digitalRead(botao_cancela)){
    if(select_submenu && select_submenu_velocidade) select_submenu_velocidade = false;
    else select_submenu_velocidade = false;
    atualiza_menu();
    delay(200);
    while(!digitalRead(botao_cancela));
  }
  
  //-----PISCA OS LEDS--------//
  if (azul_piscando) {
    unsigned long agora = millis();
      if (agora - ultima_troca_azul >= v_led_azul) {
        ultima_troca_azul = agora;
        estado_led_azul = !estado_led_azul;
        digitalWrite(led_azul, estado_led_azul);
      }
  }
  
  if (amarelo_piscando) {
    unsigned long agora = millis();
      if (agora - ultima_troca_amarelo >= v_led_amarelo) {
        ultima_troca_amarelo = agora;
        estado_led_amarelo = !estado_led_amarelo;
        digitalWrite(led_amarelo, estado_led_amarelo);
      }
  }
  
  if (verde_piscando) {
    unsigned long agora = millis();
      if (agora - ultima_troca_verde >= v_led_verde) {
        ultima_troca_verde = agora;
        estado_led_verde = !estado_led_verde;
        digitalWrite(led_verde, estado_led_verde);
      }
  }
  
  if (laranja_piscando) {
    unsigned long agora = millis();
      if (agora - ultima_troca_laranja >= v_led_laranja) {
        ultima_troca_laranja = agora;
        estado_led_laranja = !estado_led_laranja;
        digitalWrite(led_laranja, estado_led_laranja);
      }
  }
}

  


void atualiza_menu(){
  switch (menu) {
//---------------------MENU PRINCIPAL------------------------//
	case 0:
		menu = 1;
		break;
	case 1:
		lcd.clear();
		lcd.print(">Led azul");
		lcd.setCursor(0, 1);
		lcd.print(" Led amarelo");
		break;
	case 2:
		lcd.clear();
		lcd.print(" Led azul");
		lcd.setCursor(0, 1);
		lcd.print(">Led amarelo");
		break;
	case 3:
		lcd.clear();
		lcd.print(">Led verde");
		lcd.setCursor(0, 1);
		lcd.print(" Led laranja");
		break;
	case 4:
		lcd.clear();
		lcd.print(" Led verde");
		lcd.setCursor(0, 1);
		lcd.print(">Led laranja");
		break;
	case 5:
		menu = 4;
		break;
    
//--------------------SUBMENU LED AZUL------------------------//
    case 9:
    	menu = 10;
    	break;
    case 10:
  		lcd.clear();
  		lcd.print(">ON azul");
  		lcd.setCursor(0,1);
  		lcd.print(" OFF azul");
  		break;
  	case 11:
  		lcd.clear();
  		lcd.print(" ON azul");
  		lcd.setCursor(0,1);
  		lcd.print(">OFF azul");
  		break;
  	case 12:
  		lcd.clear();
  		lcd.print(">SET velocidade");
        lcd.setCursor(0,1);
  		lcd.print("esc: voltar");
  		break;
  	case 13:
  		menu = 12;
  		break;
                  
//--------------------SUBMENU LED AMARELO---------------------//
    case 19:
    	menu = 20;
    	break;
    case 20:
  		lcd.clear();
  		lcd.print(">ON amarelo");
  		lcd.setCursor(0,1);
  		lcd.print(" OFF amarelo");
  		break;
  	case 21:
  		lcd.clear();
  		lcd.print(" ON amarelo");
  		lcd.setCursor(0,1);
  		lcd.print(">OFF amarelo");
  		break;
  	case 22:
  		lcd.clear();
  		lcd.print(">SET velocidade");
        lcd.setCursor(0,1);
  		lcd.print("esc: voltar");
  		break;
  	case 23:
  		menu = 22;
  		break;
                  
//--------------------SUBMENU LED VERDE-----------------------//
    case 29:
    	menu = 30;
    	break;
    case 30:
  		lcd.clear();
  		lcd.print(">ON verde");
  		lcd.setCursor(0,1);
  		lcd.print(" OFF verde");
  		break;
  	case 31:
  		lcd.clear();
  		lcd.print(" ON verde");
  		lcd.setCursor(0,1);
  		lcd.print(">OFF verde");
  		break;
  	case 32:
  		lcd.clear();
  		lcd.print(">SET velocidade");
        lcd.setCursor(0,1);
  		lcd.print("esc: voltar");
  		break;
  	case 33:
  		menu = 32;
  		break;
    
//--------------------SUBMENU LED LARANJA---------------------//
    case 39:
    	menu = 40;
    	break;
    case 40:
  		lcd.clear();
  		lcd.print(">ON laranja");
  		lcd.setCursor(0,1);
  		lcd.print(" OFF laranja");
  		break;
  	case 41:
  		lcd.clear();
  		lcd.print(" ON laranja");
  		lcd.setCursor(0,1);
  		lcd.print(">OFF laranja");
  		break;
  	case 42:
  		lcd.clear();
  		lcd.print(">SET velocidade");
        lcd.setCursor(0,1);
  		lcd.print("esc: voltar");
  		break;
  	case 43:
  		menu = 42;
  		break;
	}
}

void pisca_leds(){
  int n_menu = (int)floor(menu/10);
  switch(n_menu){
    case 1:
      digitalWrite(led_azul, high);
      
    
  }
}
void mostra_velocidade(){
  lcd.clear();
  lcd.print("V");
  if(menu/10 == 1) lcd.print("azul");
  else if(menu/10 == 2) lcd.print("amarelo");
  else if(menu/10 == 3) lcd.print("verde");
  else if(menu/10 == 4) lcd.print("laranja");

  lcd.setCursor(0,1);
  int v = 0;
  if(menu/10 == 1) v = v_led_azul;
  else if(menu/10 == 2) v = v_led_amarelo;
  else if(menu/10 == 3) v = v_led_verde;
  else if(menu/10 == 4) v = v_led_laranja;

  lcd.print(String(v) + " ms   ");
}
