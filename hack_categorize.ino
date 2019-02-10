// HackHer Code
// Assume right foot

#include <Shoe.h>

// Create list of shoes
Shoe ma("Brooks Adrenaline GTS 18", "motion", 120, 10.1);
//Shoe mb("Saucony Omni 15", "motion", 130, 10.8);
//Shoe mc("ASICS GEL Foundation 12", "motion", 120, 12.2);
//Shoe md("ASICS GEL Fortitude 7", "motion", 120, 12.2);
Shoe me("New Balance 1260 v6", "motion", 150, 11.5);
//Shoe mf("Mizuno Wave Inspire 13", "motion", 120, 11.0);
//Shoe mg("Hoka One One Gaviota", "motion", 150, 10.9);
Shoe na("Mizuno Wave Rider 21", "Neutral", 120, 10.10);
//Shoe nb("Saucony Freedom ISO 2", "Neutral", 160, 9.10);
//Shoe nc("New Balance 880v8", "Neutral", 125, 10.8);
Shoe nd("Mizuno Wave Creation 18", "Neutral", 160, 12.4);
//Shoe ne("ASICS GEL Nimbus 20", "Neutral", 160, 10.8);
//Shoe nf("Salomon Speedcross 4 CS", "Neutral", 130, 10.5);
//Shoe ng("Brooks Ghost 11", "Neutral", 120, 10.9);
//Shoe nh("Nike Air Zoom Vomero", "Neutral", 140, 10.7);
//Shoe ni("Brooks Glycerin 16", "Neutral", 150, 10.6);
//Shoe nj("Nike Air Zoom Elite 8", "Neutral", 115, 9.5);
Shoe sa("Asics Gel Kayano 24", "Stability", 160, 11.3);
//Shoe sb("Mizuno Wave Inspire 13", "Stability", 120, 11.0);
Shoe sc("Mizuno Wave Rider 20", "Stability", 120, 9.6);
//Shoe sd("Asics Gel-Kayano 19", "Stability", 150, 11.3);
//Shoe se("Saucony Guide 10", "Stability", 120, 10.0);
//Shoe sf("Brooks Adrenaline GTS 17", "Stability", 120, 10.7);
//Shoe sg("Nike LunarGlide 9", "Stability", 120, 9.3);
//Shoe sh("North Face Ultra 109 GTX", "Stability", 120, 15.5);
//Shoe si("Brooks Ravenna 9", "Stability", 110, 9.3);
//Shoe sj("Adidas Supernova M", "Stability", 130, 10.8);
Shoe shoelist[] = {na, nd, ma, me, sa, sc};

// fsr's 
int leftfsrPin = A1;
int rightfsrPin = A0;
double leftfsrReading;
double rightfsrReading;

// Percents
int leftpercent = 0;
int rightpercent = 0;

// Pronation: over = turning in; under = turning out
String pronation = " ";
// Other preferences
int maxprice = 0;
double light = 200.0;

void setup() {
  // put your setup code here, to run once:
  // Begin serial
  Serial.begin(9600);
  while(! Serial);
  Serial.println("Type '1' when you would like to get a new recommendation");
  //Serial.println(ma.fxn);
  //Serial.println(ma.model);
  //Serial.println(String("hello world"));
}

void loop() {
  // put your main code here, to run repeatedly:

  if(Serial.available()) {
    char ch = Serial.read();
    if(ch=='1'){
      // Get preference info
      Serial.println("What is your price range? Type 'a' for $125 and under, 'b' for $150 and under, and 'c' for $200 and under");
      delay(10000);
      char chb = Serial.read();
      if(chb=='a'){
        maxprice = 125;
      } else if(chb=='b'){
        maxprice = 150;
      } else if(chb=='c'){
        maxprice = 200;
      }
      //Serial.println(maxprice);
      Serial.println("Do you mind some extra weight on your shoes? If yes, type 'L'");
      delay(10000);
      char chc = Serial.read();
      if(chc=='L'){
        light = 10.85;
      }
      //Serial.println(light);
      // Read sensors
      leftfsrReading = analogRead(leftfsrPin);
      rightfsrReading = analogRead(rightfsrPin);

      //Serial.println(leftfsrReading);
      //Serial.println(rightfsrReading);

      // Convert values to percents of weight
      leftpercent = (leftfsrReading/(leftfsrReading + rightfsrReading))*100;
      rightpercent = (rightfsrReading/(leftfsrReading + rightfsrReading))*100;

      // Detect pronation
      if(leftpercent + rightpercent == 0){
        pronation = "none";
        Serial.println("No pressure detected");
      } else if(leftpercent > 85){
        pronation = "Stability";
        Serial.println("You are over-pronating. Try  a pair of stability shoes. Here are some recommendations:");
      } else if(rightpercent > 70) {
        pronation = "motion";
        Serial.println("You are under-pronating.  Try a pair of motion control shoes. Here are some recommendations:");
      } else {
        pronation = "Neutral";
        Serial.println(pronation);
        Serial.println("You are pronating a normal amount.  Try a pair of neutral shoes. Here are some recommendations:");
      }
    
      // User feedback
      for(int i=0; i<6; i++) {
        //Serial.println(shoelist[i].fxn);
        if(pronation.equals(shoelist[i].fxn)){
          if(shoelist[i].price <= maxprice) {
            if(shoelist[i].weight < light) {
              Serial.println(shoelist[i].model);
            }
          }
        }
      }
      
        }
      }
  delay(2500);
  maxprice = 0;
  light = 200.0;
}
