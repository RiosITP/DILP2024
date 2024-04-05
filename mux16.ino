//mux pins IOT:
// if using 4051 you will only have A B C

const int a = 14;
const int b = 15;
const int c = 16;
const int d = 17;
const int enable = 18;
const int inputSignal = 19;


int muxRead[12]; // my code has 12 sensors so im storing 12 values in this array

void setup() {
  Serial.begin(9600);

// set Multiplexer (mux) pins to output
  for (int i = 14; i < 19; i++) {
    pinMode(i, OUTPUT);
  }

// Mux Common pin is an input. this tells the arduino the sensor readings
  pinMode(19, INPUT);
  digitalWrite(enable, LOW);
}

void loop() {

// read all the sensors using the custom readMux function
  for (int i = 0; i < 12; i++) {
    muxRead[i] = readMux(i);
   // Serial.print(muxRead[i]);
   // Serial.print(" ");
  }
  //Serial.println(" ");
}


//  Function to read the multiplexer
int readMux(int channel) {

// if using 4051 you will only have A B C
  int controlPin[] = { a, b, c, d };

// if using 4051 you will use muxChannel[8][4]
// Also confirm the truth table matches the 4051 datasheet and remove channel 8-15
  int muxChannel[16][4] = {
    { 0, 0, 0, 0 },  //channel 0
    { 1, 0, 0, 0 },  //channel 1
    { 0, 1, 0, 0 },  //channel 2
    { 1, 1, 0, 0 },  //channel 3
    { 0, 0, 1, 0 },  //channel 4
    { 1, 0, 1, 0 },  //channel 5
    { 0, 1, 1, 0 },  //channel 6
    { 1, 1, 1, 0 },  //channel 7
    { 0, 0, 0, 1 },  //channel 8
    { 1, 0, 0, 1 },  //channel 9
    { 0, 1, 0, 1 },  //channel 10
    { 1, 1, 0, 1 },  //channel 11
    { 0, 0, 1, 1 },  //channel 12
    { 1, 0, 1, 1 },  //channel 13
    { 0, 1, 1, 1 },  //channel 14
    { 1, 1, 1, 1 }   //channel 15
  };

  //loop through the 4 sig// for at 4051 change this  to loop  through 3 signals
  for (int i = 0; i < 4; i++) {
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
 
  digitalWrite(enable, LOW);
 
 // AFTER setting the above pins read the value at the SIG pin
  int val = analogRead(inputSignal);

  //return the value
  return val;
}
