// To take digital inputs from the encoders A and B and to plot the output to a map of 5 (usually 5 is used since +5V is used)

#define ENCA 2 //Green in encoder
#define ENCB 3 //Yellow in encoder

void setuo(){
  Serial.begin(9600);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);

}

void loop(){
  int a = digitalRead(ENCA, INPUT);
  int b = digitalRead(ENCB, INPUT);
  Serial.print(a*5);
  Serial.print(" ");
  Serial.print(b*5);
  Serial.println();
  
}
