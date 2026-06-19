#include <DHT.h>


#define DHTPIN D2
#define DHTTYPE DHT22

#define LDR_PIN A0

#define LED_PIN D8
#define BUZZER_PIN D10


DHT dht(DHTPIN, DHTTYPE);



float tempLimit = 40.0;
int lightLimit = 500;



void setup() {

  Serial.begin(115200);

  dht.begin();

  delay(2000);


  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);


  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);


  Serial.println("SMART ENVIRONMENT MONITOR");
  Serial.println("--------------------------");

}



void loop() {


  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();


  int lightValue = analogRead(LDR_PIN);



  Serial.println();

  Serial.println("SMART ENVIRONMENT MONITOR");
  Serial.println("--------------------------");



  // If DHT fails, keep previous logic alive

  if(isnan(temperature) || isnan(humidity))
  {

    Serial.println("DHT22 Reading Failed");

    temperature = 0;
    humidity = 0;

  }



  Serial.println("Sensor Readings:");
  Serial.println();


  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");


  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");


  Serial.print("Light Level: ");
  Serial.println(lightValue);



  Serial.println();



  bool alert = false;



  if(temperature > tempLimit || lightValue < lightLimit)
  {
    alert = true;
  }



  if(alert)
  {

    Serial.println("STATUS: NOT SAFE");


    digitalWrite(LED_PIN,HIGH);


    // short beep
    tone(BUZZER_PIN,1000,300);


  }

  else
  {

    Serial.println("STATUS: SAFE");


    digitalWrite(LED_PIN,LOW);


    noTone(BUZZER_PIN);

  }



  Serial.println("--------------------------");



  delay(2000);

}
