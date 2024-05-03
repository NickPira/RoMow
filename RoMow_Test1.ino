// Motor control pins : L298N H bridge
const int in2Pin = 0; // Left motor Direction backwards THIS ONE
const int in4Pin = 1; // Right motor Direction backwards THIS ONE

// IR pins
const int IR_1 = 2; //front
const int IR_2 = 3; //mid left
const int IR_3 = 4; //mid right
const int IR_down = 5; //spin blade
const int blade_spin = 6;
const int enc_left = 7;
const int enc_right = 8;
const int launch_btn = 7; // maybe


//extraneous shit
const float pi = 3.1415926538;
const int wheel_dia = 10; //cm
const int encoder_holes = 15;
const float wheel_circum = pi * wheel_dia;
const float dist_per_hole_tick = wheel_circum / encoder_holes;
const float total_enc_dist_needed = 200;
const int enc_total_turn = 200;

enum Motor {LEFT, RIGHT};
int loop_enc_count = 0;

//the bot will always need to turn left at the start, so make its previous turn right
int last_turn = 1; //1 = right  0 = left 




////////////////////// INITILIZATION //////////////////////
void pin_mode_init(){
    pinMode(in2Pin, OUTPUT);
    pinMode(in4Pin, OUTPUT);

    pinMode(IR_1, INPUT);
    pinMode(IR_2, INPUT);
    pinMode(IR_3, INPUT);
    pinMode(IR_down, INPUT);
    pinMode(launch_btn, INPUT);

    pinMode(enc_left, INPUT);
    pinMode(enc_right, INPUT);
}


void blade_init(){
  pinMode(blade_spin, OUTPUT);
  digitalWrite(blade_spin, LOW);
}


void Pi_init(){
  /*
  int Pi_height = ;
  //int Pi_width = ;

  Pi_height -> Encoder/wheel rotation distance per 1 rev converstions
  Pi_width -> #of u_tunrs conversion
  */
}



////////////////////// excess voids //////////////////////
void blade_start(){
  digitalWrite(blade_spin, HIGH);
}

void blade_stop(){
  digitalWrite(blade_spin, LOW);
}

void blade_ON_OFF(int FACING_DOWN_IR){
  if(FACING_DOWN_IR == LOW){
    blade_stop(); // STOP THE SPIN
  } else {
      blade_start(); //if light on = spin
  }
}



// Set motor speed: 255 full ahead, −255 full reverse , 0 stop
void go(enum Motor m, int speed) {
  //digitalWrite (m == LEFT ? in1Pin : in3Pin , speed > 0 ? HIGH : LOW ); //forward
  digitalWrite (m == LEFT ? in2Pin : in4Pin , speed <= 0 ? HIGH : LOW ); //reverse
  //analogWrite(m == LEFT ? enAPin : enBPin, speed < 0 ? -speed : speed ); 
}



void testMotors () {
  static int speed[8] = { 128, 255, 128, 0 ,-128, -255, -128, 0};

  // left motor forward then back
  go(RIGHT, 0);
  for (unsigned char i = 0 ; i < 8 ; i++){
    go(LEFT, speed[i]);
    delay(200);
  }

// right motor forward then back
  for (unsigned char i = 0 ; i < 8 ; i++){
    go(RIGHT, speed[i]);
    delay(50);
  }
}





////////////////////// turning //////////////////////
void OA_turn_left(){
  //turn to the left
  //rotate right wheel more than left wheel
  go(LEFT, 0);
  go(RIGHT, 255);
//PID shit i guess fuckin hell
/*
if the front and middle right sensor, pick up something, call this funciton,
repeat until BOTH do not have a LOW sensing,
Take into account the middle right far right sensor and move forwards,
if both have a low keep rotating, if mid right does not have a low, move forwards
if far right does not have a lot, then rotate back how ever many times it moved, or atan2 it in arduino code

*/
}


void OA_turn_right(){
  //turn to the right
  //rotate left wheel more than right wheel
  go(RIGHT, 0);
  go(LEFT, 255);
//PID shit i guess fuckin hell
/*
if the front and middle left sensor, pick up something, call this funciton,
repeat until BOTH do not have a LOW sensing,
Take into account the middle left far left sensor and move forwards,
if both have a low keep rotating, if mid left does not have a low, move forwards
if far left does not have a lot, then rotate back how ever many times it moved, or atan2 it in arduino code

*/
}


void UTURN_LEFT(){
  //fully uturn this bitch to the left
  int count = 0;
  while(count != enc_total_turn){
    if(digitalRead(enc_right) == HIGH){
      count = count + 1;
    }
    go(LEFT, 0);
    go(RIGHT, 255);
  }
}


void UTURN_RIGHT(){
  //fully uturn this bitch to the right
  int count = 0;
  while(count != enc_total_turn){
    if(digitalRead(enc_left) == HIGH){
      count = count + 1;
    }
    go(LEFT, 255);
    go(RIGHT, 0);
  }
}





////////////////////////////////// SETUP AND LOOP ///////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  pin_mode_init();
  blade_init();
  Pi_init();

  //testMotors();
  go(LEFT, 0);
  go(RIGHT, 0);

  while(launch_btn != HIGH);
  digitalWrite(blade_spin, HIGH);
}




void loop() {
  //start moving
  go(LEFT, 255);
  go(RIGHT, 255);
  
  //take in sensors
  int sens_1 = digitalRead(IR_1);
  int sens_2 = digitalRead(IR_2);
  int sens_3 = digitalRead(IR_3);
  int sens_DOWN = digitalRead(IR_down);

  //check if blade spin yes or no
  blade_ON_OFF(sens_DOWN);

  // OA Turn Right
  if(sens_1 == HIGH && sens_2 == HIGH){
    int TR = 1;
    while(TR != 0){
      OA_turn_right();
      if(sens_1 == LOW && sens_2 == LOW){
        TR = 0;
      }
    }
  }


  //OA Turn Left
  if(sens_1 == HIGH && sens_3 == HIGH){
    int TL = 1;
    while(TL != 0){
      OA_turn_left();
      if(sens_1 == LOW && sens_3 == LOW){
        TL = 0;
      }
    }
  }


  //go straight until total encoder count
  if((digitalRead(enc_left) == HIGH) && (digitalRead(enc_right) == HIGH)){
    loop_enc_count = loop_enc_count + 1;
  }


  //uturn right
  if((loop_enc_count == total_enc_dist_needed) && last_turn == 0){
    UTURN_RIGHT();
    //reset enoder counts
    loop_enc_count = 0;
    last_turn = 1;
  }

  //uturn left
  if((loop_enc_count == total_enc_dist_needed) && last_turn == 1){
    UTURN_LEFT();
    //reset enoder counts
    loop_enc_count = 0;
    last_turn = 0;
  }

  // Check the next direction in 50 ms
  delay(50);
}
