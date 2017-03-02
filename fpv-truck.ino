// EDAY ROBOT 
// MATT RUFFNER
// FEB 2017

// channel values
int ch1;
int ch2;

#define THROTTLE_IN 7 // elevator on rc reciever
#define STEERING_IN 8 // rudder on rc reciever

// for drive motor
#define DC1 9  // to h bridge, channel a1
#define DC2 10 // to h bridge, channel a2

// for steering motor
#define SC1 11 // to h bridge, channel b1
#define SC2 12 // to h bridge, channel b2

#define DIR_CENTER 0
#define DIR_LEFT   1
#define DIR_RIGHT  2

int ss = DIR_CENTER;

void setup() {

  // input pins
  pinMode(THROTTLE_IN, INPUT);
  pinMode(STEERING_IN, INPUT);

  pinMode(DC1, OUTPUT);
  pinMode(DC2, OUTPUT);
  pinMode(SC1, OUTPUT);
  pinMode(DC2, OUTPUT);
  
  Serial.begin(9600); // Pour a bowl of Serial
}

void loop() {
  
  ch1 = pulseIn(THROTTLE_IN, HIGH, 25000); // Read the pulse width of 
  ch2 = pulseIn(STEERING_IN, HIGH, 25000); // each channel

  ch1 = map(ch1, 1000,2000,-500,500);
  ch2 = map(ch2, 1000,2000,500,-500);

  Serial.print("ch1: "); Serial.println(ch1);
  Serial.print("ch2: "); Serial.println(ch2); Serial.println();

  if( ch1>20 ){
    forward(map(abs(ch1),20,500,0,255));
  } else if( ch1<-20 ){
    reverse(map(abs(ch1),20,500,0,255));
  } else {
    noDrive();
  }

  if( ch2<-20 ){
    left();
  } else if( ch2>20 ){
    right();
  } else {
    noSteer();
  }

  delay(50);

}

void forward(int sp) {
  Serial.println("forward");
  
  //digitalWrite(DC1, HIGH);
  analogWrite(DC1, sp);
  digitalWrite(DC2, LOW);
}

void reverse(int sp) {
  Serial.println("reverse");
  
  digitalWrite(DC1, LOW);
  analogWrite(DC2, sp);
}

void noDrive() {
  digitalWrite(DC1, LOW);
  digitalWrite(DC2, LOW);
}

void left() {
  //if( ss==DIR_LEFT ) return;

  Serial.println("left");
  
  digitalWrite(SC1, LOW);
  digitalWrite(SC2, HIGH);
  //delay(dur);
  ss = DIR_LEFT;

}

void right() {
  //if( ss==DIR_RIGHT ) return;

  Serial.println("right");
  
  digitalWrite(SC1, HIGH);
  digitalWrite(SC2, LOW);
  //delay(dur);
  ss = DIR_RIGHT;
}



void noSteer() {
  digitalWrite(SC1, LOW);
  digitalWrite(SC2, LOW);
}

