#include <LiquidCrystal.h>

// Configuração dos pinos do LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// LEDs e buzzer
int ledVerde = 8;
int ledAmarelo = 7;
int ledVermelho = 9;
int buzzer = 10;

void setup()
{
  // Inicia a comunicação serial
  Serial.begin(9600);

  // Inicializa o LCD
  lcd.begin(16, 2);

  // Define os pinos como saída
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  // Mensagem inicial do sistema
  lcd.print("Capsula IoT");
  lcd.setCursor(0, 1);
  lcd.print("Sistema Ativo");

  delay(2000);

  lcd.clear();
}

void loop()
{
  // Leitura dos sensores
  int temperatura = analogRead(A0);
  int luminosidade = analogRead(A1);
  int vibracao = analogRead(A2);

  // Variável que controla o nível de risco
  int risco = 0;

  // Verifica temperatura
  if (temperatura > 250)
  {
    risco = risco + 1;
  }

  // Verifica luminosidade
  if (luminosidade < 300)
  {
    risco = risco + 1;
  }

  // Verifica vibração
  if (vibracao > 600)
  {
    risco = risco + 1;
  }

  // Atualiza as informações no LCD
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperatura);

  lcd.print(" L:");
  lcd.print(luminosidade);

  lcd.setCursor(0, 1);
  lcd.print("V:");
  lcd.print(vibracao);

  // Situação normal
  if (risco == 0)
  {
    lcd.print(" OK");

    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);

    noTone(buzzer);
  }

  // Situação de atenção
  else if (risco == 1)
  {
    lcd.print(" ATENCAO");

    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);

    noTone(buzzer);
  }

  // Situação crítica
  else
  {
    lcd.print(" CRITICO");

    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);

    // Emite um alerta sonoro curto
    tone(buzzer, 100);
    delay(50);
    noTone(buzzer);
  }

  // Exibe os dados no Monitor Serial
  Serial.print("Temperatura: ");
  Serial.print(temperatura);

  Serial.print(" | Luz: ");
  Serial.print(luminosidade);

  Serial.print(" | Vibracao: ");
  Serial.print(vibracao);

  Serial.print(" | Nivel de risco: ");
  Serial.println(risco);

  delay(1000);
}