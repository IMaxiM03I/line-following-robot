// motor pins
#define PWM_R 9
#define PWM_L 10

// edge IR
#define IR_ELEFT_D 8    // 1
#define IR_ERIGHT_D 2   // 7

// center IR
#define IR_LEFT_D 7     // 2
#define IR_CLEFT_D 6    // 3
#define IR_CENTER_D 5   // 4
#define IR_CRIGHT_D 4   // 5
#define IR_RIGHT_D 3    // 6

// vehicle dynamics
const int MAX_SPEED = 60;
bool driving;

void setSpeed(int l_speed, int r_speed) {
  analogWrite(PWM_L, l_speed);
  analogWrite(PWM_R, r_speed);
}

bool seeWhite(int sensor_pin) { return digitalRead(sensor_pin); }

void setup() {
    pinMode(PWM_R, OUTPUT);
    pinMode(PWM_L, OUTPUT);
    setSpeed(MAX_SPEED, MAX_SPEED);
    driving = 0;

    Serial.begin(9600);
}

void loop() {

  // we no longer see the straight/finish, turn on
  if (!seeWhite(IR_ELEFT_D) && !driving) {
    driving = 1;
  }
  
  // we see the start/finish again, stop the car
  if (seeWhite(IR_ELEFT_D) && driving) {
    driving = 0;
    setSpeed(0, 0);
  }

  // if right edge sees white, slow down
  if (seeWhite(IR_ERIGHT_D)) {
    // setSpeed(MAX_SPEED / 2, MAX_SPEED / 2);
    Serial.println("edge right");
  }

  // skip all below if not driving
  if (!driving) return;

  // if we see only black, stop the car, ur getting robbed
  if (!(seeWhite(IR_RIGHT_D) || seeWhite(IR_CRIGHT_D) || seeWhite(IR_CENTER_D) || seeWhite(IR_CLEFT_D) || seeWhite(IR_LEFT_D))) {
    setSpeed(0, 0);
    return;
  }

  // intersection
  if (seeWhite(IR_RIGHT_D) && seeWhite(IR_LEFT_D)) {
    setSpeed(MAX_SPEED, MAX_SPEED);
    return;
  }
  
  // if right sensor detects white -> move right
  if (seeWhite(IR_RIGHT_D)) {
    setSpeed(MAX_SPEED, 0);
    Serial.println("right");
    return;
  }
  // if left sensor detects white -> move left
  if (seeWhite(IR_LEFT_D)) {
    setSpeed(0, MAX_SPEED);
    Serial.println("left");
    return;
  }

  // if either center sensor detects white -> go straight
  if (seeWhite(IR_CENTER_D) || seeWhite(IR_CRIGHT_D) || seeWhite(IR_CLEFT_D)) {
    setSpeed(MAX_SPEED, MAX_SPEED);
    Serial.println("straight");
    return;
  }
}