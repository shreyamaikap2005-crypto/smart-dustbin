#include <Servo.h>

// ================= PIN =================

const int IR_PIN       = 5;
const int METAL_PIN    = 6;
const int ROTATOR_PIN  = 7;
const int FLIP_PIN     = 8;
const int MOISTURE_PIN = A0;
const int BUZZER_PIN   = 12;


// ================= SERVOS =================

Servo rotatorServo;
Servo flipServo;


// ================= FLIP COVER =================

const int FLIP_CLOSED = 0;
const int FLIP_OPEN   = 60;


// ================= ROTATOR =================
//
// 3 compartments:
// 1 → 2 → 3 → 1 → 2 → 3 ...
//
// Ei value-ta tomader mechanical setup-er
// sathe adjust korte hobe.
//

const int ROTATOR_HOME = 0;
const int ROTATOR_STEP = 60;


// Current compartment number
int currentCompartment = 0;


// ================= MOISTURE =================
//
// Serial Monitor diye value check kore
// threshold adjust korbe.
//

const int WET_THRESHOLD = 500;


// ================= SENSOR LOGIC =================

// IR module-e object detect hole normally LOW
const int IR_DETECTED = LOW;

// Tomar metal sensor LOW output dile metal detected
// opposite hole HIGH kore debe.
const int METAL_DETECTED = LOW;


// ================= SETUP =================

void setup() {

  Serial.begin(9600);

  pinMode(IR_PIN, INPUT);
  pinMode(METAL_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  rotatorServo.attach(ROTATOR_PIN);
  flipServo.attach(FLIP_PIN);

  // Starting position
  rotatorServo.write(ROTATOR_HOME);

  // Flip cover initially closed
  flipServo.write(FLIP_CLOSED);

  delay(1000);

  Serial.println("================================");
  Serial.println("SMART DUSTBIN READY");
  Serial.println("================================");
}


// ================= MAIN LOOP =================

void loop() {

  // ------------------------------------------
  // 1. Check whether waste is present
  // ------------------------------------------

  if (digitalRead(IR_PIN) == IR_DETECTED) {

    Serial.println();
    Serial.println("WASTE DETECTED!");

    delay(500);


    // ------------------------------------------
    // 2. Read metal + moisture
    // ------------------------------------------

    int metalState = digitalRead(METAL_PIN);
    int moistureValue = analogRead(MOISTURE_PIN);

    Serial.print("Metal = ");
    Serial.println(metalState);

    Serial.print("Moisture = ");
    Serial.println(moistureValue);


    // ------------------------------------------
    // 3. CLASSIFY WASTE
    // ------------------------------------------

    if (metalState == METAL_DETECTED) {

      Serial.println("TYPE = METAL");

      // Normal metal → buzzer OFF
      digitalWrite(BUZZER_PIN, LOW);

    }

    else if (moistureValue < WET_THRESHOLD) {

      Serial.println("TYPE = WET");

      digitalWrite(BUZZER_PIN, LOW);

    }

    else {

      Serial.println("TYPE = DRY");

      digitalWrite(BUZZER_PIN, LOW);
    }


    // ------------------------------------------
    // 4. ROTATE TO NEXT COMPARTMENT
    // ------------------------------------------

    rotateToNextCompartment();


    // ------------------------------------------
    // 5. WAIT 2 SECONDS
    // ------------------------------------------

    Serial.println("Waiting 2 seconds...");

    delay(2000);


    // ------------------------------------------
    // 6. OPEN FLIP COVER
    // ------------------------------------------

    Serial.println("Flip cover opening...");

    flipServo.write(FLIP_OPEN);

    delay(1200);


    // ------------------------------------------
    // 7. WASTE FALLS
    // ------------------------------------------

    Serial.println("Waste dropping...");

    delay(1000);


    // ------------------------------------------
    // 8. CLOSE FLIP COVER
    // ------------------------------------------

    Serial.println("Flip cover closing...");

    flipServo.write(FLIP_CLOSED);

    delay(1200);


    Serial.println("Waste deposited successfully.");

    // Wait before detecting same object again
    delay(1500);
  }

  delay(50);
}


// =================================================
// ROTATE TO NEXT COMPARTMENT
// =================================================

void rotateToNextCompartment() {

  currentCompartment++;

  // After compartment 3 → go back to 1
  if (currentCompartment > 3) {
    currentCompartment = 1;
  }


  Serial.print("Moving to compartment: ");
  Serial.println(currentCompartment);


  // Calculate required servo angle
  int targetAngle =
      (currentCompartment - 1) * ROTATOR_STEP;


  // Safety limit for normal SG90
  if (targetAngle > 180) {
    targetAngle = 180;
  }


  rotatorServo.write(targetAngle);

  // Give servo time to reach position
  delay(1000);


  Serial.print("Rotator angle = ");
  Serial.println(targetAngle);
}