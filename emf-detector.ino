// EMF Detector


#define NUMREADINGS 15
int senseLimit = 30;
int antennaPin = 1;
int val = 0; // reading from antennaPin

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4

#define BUZZER 6
#define BUZZER_FREQ_START 440

// variables for smoothing

int readings[NUMREADINGS];                // the readings from the analog input
int idx = 0;                            // the idx of the current reading
int total = 0;                            // the running total
int average = 0;                          // final average of the probe reading


void setup() {

  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);  // initiate serial connection for debugging/etc

  for (int i = 0; i < NUMREADINGS; i++)
    readings[i] = 0;                      // initialize all the readings to 0
}


void lightWhenAbove(int value, int led, int threshold) {
  if (value > threshold) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}

#define A_HZ 440
#define B_HZ 494
#define C_HZ 523
#define D_HZ 587
#define E_HZ 659
#define F_HZ 698
#define G_HZ 794

void playTone(int frequency) {
  tone(BUZZER, frequency, 500);
  Serial.print(", playTone: ");
  Serial.print(frequency);
}

void playToneAt(int value) {
  if (value > 300) {
    playTone(A_HZ);
  } else if (value > 400) {
    playTone(B_HZ);
  } else if (value > 500) {
    playTone(C_HZ);
  } else if (value > 600) {
    playTone(D_HZ);
  } else if (value > 700) {
    playTone(E_HZ);
  } else if (value > 800) {
    playTone(F_HZ);
  } else if (value > 900) {
    playTone(G_HZ);
  }
}

void loop() {

  val = analogRead(antennaPin);
  Serial.print("analog: ");
  Serial.print(val); 
  
  if (val >= 1) {                

    val = constrain(val, 1, senseLimit);
    val = map(val, 1, senseLimit, 0, 1000);

    Serial.print(", mapped: ");
    Serial.print(val); 

    total -= readings[idx];               
    readings[idx] = val;                  
    total += val;               
    idx++;                   

    if (idx >= NUMREADINGS)               
      idx = 0;                           

    average = total / NUMREADINGS;
    Serial.print(", avg: ");
    Serial.print(average); 

    lightWhenAbove(average, LED0, 300);
    lightWhenAbove(average, LED1, 400);
    lightWhenAbove(average, LED2, 500);
    lightWhenAbove(average, LED3, 600);
    lightWhenAbove(average, LED4, 700);
    
    playToneAt(average);
  }
  Serial.println();
  delay(1000);
}
