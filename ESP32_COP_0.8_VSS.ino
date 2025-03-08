// Define hardware pins globally
const uint8_t C1 = 4;
const uint8_t C2 = 0;
const uint8_t C3 = 2;
const uint8_t C4 = 15;
const uint8_t SIN = 23;
const uint8_t CYP = 35;
const uint8_t TDC = 34;

// Global variable for cylinder state
const uint8_t Op = LOW; //Open gate state, depending on the transistors used in Q1,Q2,Q3,Q4 Default is PNP
const uint8_t Cl = HIGH; //Closed gate state, depending on the transistors used in Q1,Q2,Q3,Q4 Default is PNP
volatile int CYL = 0; // Use volatile for shared variables in ISRs

// Function prototypes (declare before setup)
void ChngCyl();
void SYNC();

void setup() {
  // Initialize pins as outputs
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(SIN, OUTPUT);

  // Attach interrupts (no parentheses needed here)
  attachInterrupt(digitalPinToInterrupt(TDC), ChngCyl, RISING);  // Pass function pointer, no arguments
  attachInterrupt(digitalPinToInterrupt(CYP), SYNC, RISING);  // Pass function pointer, no arguments
}

void loop() {
  // Main loop can be empty or contain other tasks
}

// Function to change cylinder state
void ChngCyl() {
  switch (CYL) {
    case 1:
      digitalWrite(C1, Op);
      digitalWrite(C2, Cl);
      digitalWrite(C3, Cl);
      digitalWrite(C4, Cl);
      CYL = 3;
      break;
    case 2:
      digitalWrite(C1, Cl);
      digitalWrite(C2, Op);
      digitalWrite(C3, Cl);
      digitalWrite(C4, Cl);
      CYL = 1;
      break;
    case 3:
      digitalWrite(C1, Cl);
      digitalWrite(C2, Cl);
      digitalWrite(C3, Op);
      digitalWrite(C4, Cl);
      CYL = 4;
      break;
    case 4:
      digitalWrite(C1, Cl);
      digitalWrite(C2, Cl);
      digitalWrite(C3, Cl);
      digitalWrite(C4, Op);
      CYL = 2;
      break;
  }
}

// Function to synchronize and trigger cylinder change
void SYNC() {
  if(CYL!=1){
  CYL = 1;
  ChngCyl();  // Call ChngCyl without passing CYL, as it's a global variable
  digitalWrite(SIN, HIGH);};
}
