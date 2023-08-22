#include <LiquidCrystal.h>
int janela = 3;
int botaoModo = 4, botaoLigaDesliga = 5;
int leituraLDR = 0;
int leituraBotaoModo = 0, leituraBotaoLigaDesliga = 0;
int x=1;
int aberta = 0;


LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

// ----- MODO -----
// par = manual
// impar = automatico

void setup() {
  pinMode(botaoModo,INPUT);
  pinMode(botaoLigaDesliga,INPUT);
  pinMode(A0, INPUT);
  pinMode(janela, OUTPUT);
  digitalWrite(janela,LOW);
  Serial.begin(9600);
  lcd.begin(16,2);
}

void loop() {
  //le o modo de operacao da janela
leituraBotaoModo = digitalRead(botaoModo);
  if(leituraBotaoModo == HIGH){
    x++;
    delay(500);
  }

  if(x>1){  //INICIOU O SISTEMA
    lcd.clear();
     if(x % 2 == 0){ //MANUAL

      //LCD 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("MODO: MANUAL");
      if(aberta == 1){
          lcd.setCursor(0, 1);
          lcd.print("Janela Aberta ");
      }
      else{
          lcd.setCursor(0, 1);
          lcd.print("Janela Fechada");
      }

      leituraBotaoLigaDesliga = digitalRead(botaoLigaDesliga);
      delay(500);
      if(leituraBotaoLigaDesliga == HIGH){  //verifca o botao liga desliga
          digitalWrite(janela,HIGH);
          delay(4000);
          digitalWrite(janela,LOW);
          if(aberta == 0){  //abriu a janela
              aberta = 1;
              lcd.setCursor(0, 1);
              lcd.print("Janela Aberta ");
          }
          else{ //fechou a janela
              aberta = 0;
              lcd.setCursor(0, 1);
              lcd.print("Janela Fechada");
          }
      }
    }
    else{   //AUTOMATICO

    //LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MODO: AUTOMATICO");
      if(aberta == 1){
          lcd.setCursor(0, 1);
          lcd.print("Janela Aberta ");
      }
      else{
          lcd.setCursor(0, 1);
          lcd.print("Janela Fechada");
      }

    leituraLDR = analogRead(A0);
    Serial.println(leituraLDR);
    delay(500);
    //NOITE 
    if(leituraLDR <= 800){
        if(aberta == 1){    //ta de noite e a janela ta aberta
        digitalWrite(janela,HIGH);
        delay(4000);
        digitalWrite(janela,LOW);
        aberta = 0;
        lcd.setCursor(0, 1);
        lcd.print("Janela Fechada");
        }
        while(1){
            leituraLDR = analogRead(A0);
          //gambiarra
          	leituraBotaoModo = digitalRead(botaoModo);
          	if(leituraBotaoModo = HIGH){
            break;   
          	}
            if(leituraLDR >= 800){ //se mudar a iluminacao faz alguma coisa, caso contrario fica só lendo
                break;
            }
    }
    }
    //DIA
    else{
        if(aberta == 0){    //ta de dia e a janela ta fechada
        digitalWrite(janela,HIGH);
        delay(4000);
        digitalWrite(janela,LOW);
        aberta = 1;
        lcd.setCursor(0, 1);
        lcd.print("Janela Aberta ");
        }
        while(1){
            leituraLDR = analogRead(A0);
          //gambiarra
          	leituraBotaoModo = digitalRead(botaoModo);
          	if(leituraBotaoModo = HIGH){
            break;   
          	}
            if(leituraLDR <= 800 ){ //se mudar a iluminacao faz alguma coisa, caso contrario fica só lendo  
              break;
            }
        }
    }
  }
  }
  else{
      lcd.setCursor(0, 0);
      lcd.print("JANELA ESPERTA");
  }
}