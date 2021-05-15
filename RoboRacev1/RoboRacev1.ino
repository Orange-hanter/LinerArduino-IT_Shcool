#define PIN_SENSOR1  A0
#define PIN_SENSOR2  A1
const int dirF2 = 3;
const int dirB2 = 4;
const int dirB1 = 7;
const int dirF1 = 6;
const int pinPowR = 2;
const int pinPowL = 5;

void logging()
{
  // Контролируем датчик с периодичностью около 200мс
  if (digitalRead(PIN_SENSOR1)) { // Датчик не срабатывает
    Serial.println("LIGHT 1");
  }
  else { // Датчик срабатывает
    Serial.println("BLACK 1");
  }

  if (digitalRead(PIN_SENSOR2)) { // Датчик не срабатывает
    Serial.println("LIGHT 2");
  }
  else { // Датчик срабатывает
    Serial.println("BLACK 2");
  }
}


void setup() {
  // Инициализируем работу с серийным портом для вывода отладочной информации
  Serial.begin(9600);

  // Настраиваем на вход пин, к которому подключен датчик линии.
  // Здесь нет необходимости включать внутреннюю подтяжку пина к VCC, т.к.
  // модуль сам заботится о формировании логической "1" при отсутствии цели
  pinMode(PIN_SENSOR1, INPUT);
  pinMode(PIN_SENSOR2, INPUT);
  pinMode(dirB1, OUTPUT);
  pinMode(dirB2, OUTPUT);
  pinMode(dirF1, OUTPUT);
  pinMode(dirF2, OUTPUT);
  pinMode(pinPowR, OUTPUT); analogWrite(pinPowR, 70);
  pinMode(pinPowL, OUTPUT); analogWrite(pinPowL, 70);
}

void pause()
{
  analogWrite(pinPowR, 0);
  analogWrite(pinPowL, 0);
  delay(50);
}

void start()
{
   analogWrite(pinPowR, 100);
  analogWrite(pinPowL, 100);
  delay(50);
  analogWrite(pinPowR, 60);
  analogWrite(pinPowL, 60);
  delay(100);
  analogWrite(pinPowR, 70);
  analogWrite(pinPowL, 70);
 }

void loop() {
  if (!digitalRead(PIN_SENSOR1) )
  {
    pause();
    digitalWrite(dirB1, HIGH);
    start();
  }
  else
  {
    pause();
    digitalWrite(dirB1, LOW);
    start();
  }

  if (!digitalRead(PIN_SENSOR2))
  {
    pause();
    digitalWrite(dirB2, HIGH);
    start();
  }
  else
  {
    pause();
    digitalWrite(dirB2, LOW);
    start();
  }
}
