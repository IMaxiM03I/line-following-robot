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
const int MAX_SPEED = 512;

bool seeWhite(int sensor_pin) { return digitalRead(sensor_pin); }

void setup() {
    pinMode(PWM_R, OUTPUT);
    pinMode(PWM_L, OUTPUT);
}

void loop() {
    // if right sensor detects white -> move right
    if (seeWhite(IR_RIGHT_D) || seeWhite(IR_CRIGHT_D)) {
        analogWrite(PWM_R, 0);
        analogWrite(PWM_L, MAX_SPEED);
    }
    // if left sensor detects white -> move left
    if (seeWhite(IR_LEFT_D) || seeWhite(IR_CRIGHT_D)) {
        analogWrite(PWM_R, MAX_SPEED);
        analogWrite(PWM_L, 0);
    }
    // if neither detects white -> move both
    if (seeWhite(IR_CENTER_D)) {
        analogWrite(PWM_R, MAX_SPEED);
        analogWrite(PWM_L, MAX_SPEED);
    }
    // if both detect white -> we'll figure this out later
}