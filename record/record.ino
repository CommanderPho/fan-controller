#define MAX_SIGNAL_LEN 1500

void setup() {
  // Serial.begin(9600);
  Serial.begin(115200);
  pinMode(2, INPUT);
}

int recordSignal() {
    Serial.print(F("Ready to record: "));

    int val = 0;
    int lastval = 0;
    static unsigned long sig[MAX_SIGNAL_LEN+1];
    unsigned long lasttime;
    int siglength = 0;
    bool recdone = false;
    unsigned long aborttime = 5000000; // Abort after 5 seconds

    while (1) {
        unsigned long mnow = micros();
        val = digitalRead(2);
        if (val != lastval) {
            sig[siglength] = mnow;
            lasttime = mnow;
            siglength += 1;
            lastval = val;
        }
        if (mnow > aborttime) {
            return 2;
        }
        if ((siglength > 1) && ((mnow - lasttime) > 30000 || siglength == MAX_SIGNAL_LEN)) {
            if (siglength < 10) {
                // Too small, assume a failure
                return 1;
            }
            Serial.print(F("\nCapture Complete. Signal Length: "));
            delay(5);
            Serial.println(siglength);
            Serial.println(F("======= Start Signal Below Here =========="));
            for (int i=1; i<siglength; i++) {
                Serial.print(sig[i] - sig[i-1]);
                Serial.print(F(", "));
            }
            Serial.println("");
            Serial.println(F("======= End Signal Here =========="));
            return 0;
        }
    }
}

void loop() {
  Serial.println(F("\n\nStarting receive..."));
  int result = recordSignal();
  if (result == 0) {
    Serial.println(F("Receive completed successfully!"));
  } else {
    Serial.print(F("Receive errored, no signal was written, return code: "));
    Serial.println(result);
  }

  Serial.println("");
  Serial.println(F("Reset your Arduino to scan again..."));

  while(true) {}
}
