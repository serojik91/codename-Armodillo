// pin definition for motoro 1 (left)
int mot1_en = 13;
int mot1_a = 11;
int mot1_b = 10;


// pin definition for motoro 2 (right)
int mot2_en = 12;
int mot2_a = 9;
int mot2_b = 8;

// pin definitions for left/right motor
int motLR_1 = 7;
int motLR_2 = 6;

void motor_control( int mot_power, int mot_dir );  // moving motors 
void LR_mot(int dir); // steering wheel motor - 1 for left, 0 for right

byte val;

void setup() {

  Serial.begin(115200);//Change the baud rate value depending on the default baud rate of your bluetooth module, for Bluesmirf-115200 and for JY-MCU-9600
  //left.attach(9, 800, 2200); //left servo on digital pin 9 of arduino
  //right.attach(10, 800, 2200); //right servo on digital pin 10 of arduino

  // pin direction definition for motor 1	
  pinMode(mot1_en, OUTPUT);
  pinMode(mot1_a, OUTPUT);
  pinMode(mot1_b, OUTPUT);



  // pin direction definition for motor 2
  pinMode(mot2_en, OUTPUT);
  pinMode(mot2_a, OUTPUT);
  pinMode(mot2_b, OUTPUT);

  // pin definitions for left/right motor 
  pinMode(motLR_1, OUTPUT);
  pinMode(motLR_2, OUTPUT);

  //if (Serial.available()) 
  Serial.println("Connected to bluetooth device");
}


void loop() {


  int a=0;
  if(Serial.available())
  {
    val=Serial.read();
    Serial.print(int(val));

    if(int(val) == 70)//Move front
    {
      for (;;) {
      motor_control( HIGH, 1);  // motors ON, dir backward
      Serial.println("  move forward");
      Serial.flush();
      break;
      }
    }

    if(int(val) == 66)//Move back
    {
      for (;;) {
      motor_control( HIGH, 2);  // motors ON, dir backward
      Serial.println("  move back");
      Serial.flush();
       break;
      }
    }

    if(int(val) == 83 ) //Stop
    {
      for(;;) {
      motor_control( LOW, 0);
      Serial.println("  stop");
      Serial.flush();
      break;
      }
    }

    if(int(val)==76)//left
    {
      for (;;) {
      LR_mot(3);  // turn left
      LR_mot(1);  // turn back left middle
      Serial.println("  move left");
      Serial.flush();
      break;
      }
    }

    if(int(val)==82)//right
    {
      for ( ;;) {
      LR_mot(2);  // turn right
      LR_mot(4);  // turn back right middle
      Serial.println("  movel right");
      Serial.flush();
      break;
      }
    }
  
  Serial.flush();

  }


 // Serial.flush();
  //motor_control( HIGH, 1);  // motors ON, dir backward
   
 /*  LR_mot(2);  // turn right
   delay(2000);
   LR_mot(4);  // turn back right middle
   delay(2000);
   LR_mot(3);  // turn left
   delay(2000);
   LR_mot(1);  // turn back left middle
   delay(2000);*/


}


void motor_control(  int mot_power, int mot_dir ) {

  if ( mot_power != 0 ) {
    if ( mot_dir == 1 ) { // for forward use 1

        // for mot 1
      digitalWrite(mot1_en, mot_power ); 
      digitalWrite(mot1_a, HIGH);
      digitalWrite(mot1_b, LOW);
      //delay(100);                                                                                                                                                                                                                                                                                                                                                                          
      //// for mot 2
      digitalWrite(mot2_en, mot_power ); 
      digitalWrite(mot2_a, HIGH);
      digitalWrite(mot2_b, LOW);

    }
    else if ( mot_dir == 2 ) { // for backward use 0 

      // for mot 1
      digitalWrite(mot1_en, mot_power ); 
      digitalWrite(mot1_a, LOW);
      digitalWrite(mot1_b, HIGH);
      //delay(100);
      // for mot 2
      digitalWrite(mot2_en, mot_power ); 
      digitalWrite(mot2_a, LOW);
      digitalWrite(mot2_b, HIGH);
    }
  }
  else if ( mot_power == 0 ) {

    // for mot 1
    digitalWrite(LOW, mot_power ); 
    digitalWrite(mot1_a, LOW);
    digitalWrite(mot1_b, LOW);

    // for mot 2
    digitalWrite(LOW, mot_power ); 
    digitalWrite(mot2_a, LOW);
    digitalWrite(mot2_b, LOW);

  }

}

void LR_mot( int dir) {

  int prev_dir = 0;
  int actual_dir = dir;

  if ( prev_dir == 3 ) // if turned left
  {
    actual_dir = 1;  // turn left middle

  }
  else if ( prev_dir == 2 ) { // truned right

    actual_dir = 4;  // turn right middle
  } 
  else if ( prev_dir == 0 ) {
    digitalWrite( motLR_1, LOW);
    digitalWrite( motLR_2, LOW);
  }

  if ( actual_dir == 1 ) { // turn left middle
    digitalWrite( motLR_1, LOW);
    digitalWrite( motLR_2, HIGH);
    delay(600);
    digitalWrite( motLR_1, LOW);
    digitalWrite( motLR_2, LOW);
    prev_dir = 0;
  }
  else if ( actual_dir == 2 ){  // turn right
    digitalWrite( motLR_1, LOW);
    digitalWrite( motLR_2, HIGH);
    delay(700);
    digitalWrite( motLR_1, LOW);
    digitalWrite( motLR_2, LOW);

  }
  else if ( actual_dir == 3 ) { // turn left

    digitalWrite( motLR_1, HIGH);
    digitalWrite( motLR_2, LOW);
    delay(700);
    digitalWrite( motLR_1, LOW);
    digitalWrite( motLR_2, LOW);

  }
  else if  ( actual_dir == 4 ) { // turn right middle

    digitalWrite( motLR_1, HIGH);
    digitalWrite( motLR_2, LOW);
    delay(400);
    digitalWrite( motLR_1, LOW);
    digitalWrite( motLR_2, LOW);
    prev_dir = 0;

  }
  prev_dir = actual_dir;
}







