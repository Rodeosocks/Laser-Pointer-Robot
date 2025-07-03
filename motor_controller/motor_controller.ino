int enA = 15;
int in1 = 2;
int in2 = 0;

void setup() {
  Serial.begin(9600);

  // Set used pins as output
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
    
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void loop() {
  Serial.println("speed=50");
  analogWrite(enA, 50);
  
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  delay(5000);
  Serial.println("speed=100");
  analogWrite(enA, 100);
  delay(2000);
  Serial.println("speed=180");
  analogWrite(enA, 180);
  delay(2000);
  Serial.println("speed=255");
  analogWrite(enA, 255);
  delay(2000);
  Serial.println("speed=200");
  analogWrite(enA, 200);
  delay(2000);
  Serial.println("speed=75");
  analogWrite(enA, 75);
  delay(2000);
  Serial.println("Turned off");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  
  delay(5000);
}