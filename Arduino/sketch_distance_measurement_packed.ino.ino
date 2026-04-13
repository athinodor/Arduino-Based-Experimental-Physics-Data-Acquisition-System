#include <EEPROM.h>
int decimalprec=2; //Ακρίβεια δεκαδικών ψηφίων στην εμφάνιση
int inputButtonPin=2; //Push Button input pin
int potPin = A0; // Potentiometer output connected to analog pin 0
int potVal = 0; // Variable to store the input from the potentiometer
int rythm=10; //The delay of sampling in miliseconds 
int startstop=0; //if startstop=0 
unsigned long currentTime;
//unsigned long stratTimeX=0;
//unsigned long timeX=0;

int echoPin = 12; // Echo Pin
int trigPin = 13; // Trigger Pin
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration; // Διάρκεια για να υπολογιστεί η απόσταση
float distance, prevDistance; // Απόσταση, Προηγούμενη Απόσταση για να υπολογιστεί η ταχύτητα
unsigned long startMillis; // Ο χρόνος έναρξης της συλλογής δεδομένων (που πατήθηκε το push button)
unsigned long elapsed; //Ο χρόνος (milliseconds) που πέρασε από την έναρξη συλλογής των τιμών (που πατήθηκε το push button)
unsigned long prevelapsed; //Η ποροηγούμενη τιμή του χρόνου (milliseconds) που πέρασε από την έναρξη συλλογής των τιμών (που πατήθηκε το push button) για να υπολογιστεί η ταχύτητα
float speed; //H ταχύτητα 
float prevspeed; //H προηγούμενη τιμή της ταχύτητας (m/sec) για τον υπολογισμό της επιτάχυνσης
float acceleration; // Επιτάχυνση 
unsigned long count; // Μετρητής των επαναλήψεων χρησιμοποιείται για να μην εκτυπωνονται οι πρωτες 3 μετρήσεις 


void setup() {
  // put your setup code here, to run once:
  pinMode(inputButtonPin,INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  startMillis = millis(); // Αρχικοποίηση που μετρά την 1η τιμή του χρόνου από την έναρξη του προγράμματος
  
  
}
void loop() {
 // put your main code here, to run repeatedly:

if (digitalRead(inputButtonPin) == HIGH) { //if the button is pushed
    if (startstop==0) {
      //timeX=timeX+currentTime-stratTimeX;

      count=0; //Αρχικοποίηση του μετρητή των επαναλήψεων (κάθε φορά που πατάω το κουπί αρχικοποιείται)

      prevDistance=0; //Αρχικοποίηση της προηγούμενης τιμής της απόστασης 
      prevelapsed=0; //Αρχικοποίηση της προηγούμενης τιμής του χρόνου
      prevspeed=0; // Αρχικοποίηση της προηγούμενης τιμής της ταχύτητας
    }
    startstop=1;
   
    count=count+1; //Αύξηση του μετρητή για την αγνόηση των πρώτων μετρήσεων
  
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    currentTime = millis(); // Αποθήκευση του χρόνου που πέρασε από την εκκίνηση
    //Serial.print("Χρόνος: ");
    //Serial.print(currentTime);
    //Serial.println(" ms");
    //Serial.println(duration);
    
    distance = duration/58.2; //Υπολογισµός απόστασης (σε cm) βασιζόµενοι στην ταχύτητα του ήχου. Ή (0.034cm/μs ταχύτητα ήχου στους 20C) distance=0.034*duration/2; 

    if (distance >= maximumRange || distance <= minimumRange){
      Serial.println("Εκτός ορίων");
      delay(100);
    }
    else {
    // unsigned long elapsed = millis() - startMillis;
    // Serial.print("Χρόνος από την εκκίνηση: ");
    // Serial.print(elapsed / 1000);
    // Serial.println(" δευτερόλεπτα");
    
    //Serial.print(currentTime);

    // Εκτύπωση του χρόνου
     //Serial.print(timeX);
      elapsed = (millis() - startMillis);  //ο χρόνος που πέρασε σε σχέση με τον χρόνο έναρξης
      

      
      // Υπολογισμός και εκτύπωση της ταχύτητας
      float ds=distance-prevDistance; //διαφορά απόστασης σε centimeters (εάν θέλω μετρήσεις σε μέτρα εδώ να δοκιμάσω να το διαιρέσω με το 100) 
      float dt=elapsed-prevelapsed; // διαφορά χρόνου σε milliseconds (εάν θέλω μέτρηση σε sec να δοκιμάσω να το διαιρέσω με το 1000 και να σβήσω τις διαιρέσεις με το 1000 παρακάτω )
                                    // μια άλλη σκέψη είναι να μην διαιρέσω εδώ την απόσταση και τον χρόνο και να πολλαπλασιάσω την ταχύτητα με το 10 αντί με το 1000 για να μετράω 
                                    // ταχύτητα σε m/s επιτάχυνση σε m/sec^2
      speed=(float)(ds/dt)*1000.0; // Υπολογισμός της ταχύτητας Πολλάπλασιάζω με το 1000 για να γίνει η μετατροπή σε cm/sec
      //speed=(float)(distance/elapsed)*1000.0; // ΣΟΣ ΝΕΟΣ Υπολογισμός της ταχύτητας Πολλάπλασιάζω με το 1000 για να γίνει η μετατροπή σε cm/sec
      float dv=speed-prevspeed; //διαφορά ταχύτητας (cm/sec)
      acceleration=(float)(dv/dt)*1000.0; //Υπολογισμός της επιτάχυνσης cm/sec^2

      if (count >3) { //Εάν περάσουμε τις 3 πρώτες μετρήσεις τότε να εκτυπώνει για να υπλογίζεται η επιτάχυνση σωστά
        Serial.print(elapsed/1000.0,decimalprec); //εκτύπωση του χρόνου σε sec decimalprec=ακρίβεια δεκαδικών ψηφίων

      // Εκτύπωση της απόστασης
        Serial.print(", ");
        Serial.print(distance,decimalprec);
        
        //Serial.print(",Dist ");
        //Serial.print(distance);

        //Serial.print(",pervDist ");
        //Serial.print(prevDistance);
        
        //Serial.print(",elapsed ");
      // Serial.print(elapsed);

        //Serial.print(",prevelapsed ");
        //Serial.print(prevelapsed);

        //Serial.print(",DS ");
        //Serial.print(ds);

        //Serial.print(",Dt ");
        //.print(dt);

      // Εκτύπωση της ταχύτητας
        Serial.print(", ");
        Serial.print(speed,decimalprec);

        //Serial.print(" prevV, ");
        //Serial.print(prevspeed);

        //Serial.print(" dV, ");
        //Serial.print(dv);

        //Serial.print(" dt, ");
        //Serial.print(dt);

      // Εκτύπωση της επιτάχυνσης
        Serial.print(", ");
        Serial.println(acceleration,decimalprec);

        if (count>10) { //Εαν ξεπεράσουμε το 10 το ξαναβαζουμε στο 10 για να μην προκαλέσουμε stack overflow για την μεταβλητη count
          count=10;
        }

      }
      delay(rythm);
      

      prevDistance=distance; //Ανανέωση της τιμής της προηγούμενης τιμής της απόστασης 
      prevelapsed=elapsed; //Ανανέωση της τιμής της προηγούμενης τιμής του χρόνου
      prevspeed=speed;  //Ανανέωση της τιμής της προηγούμενης τιμής της ταχύτητας



    };
    //Καθυστέρηση 50ms πριν την επόµενη ανάγνωση
    delay(rythm);
  }
  else //Εάν το push button δεν είναι πατημένο τότε ρύθμισε τον ρυθμό δειγματοληψίας
  {

    startstop=0;
    potVal = analogRead(potPin);   // Διάβασε την τιμή που δίνει το ποτενσιόμετρο στο input pin
    int step = map(potVal, 0, 1023, 1, 5);    // Μετατροπή σε 1 - 5
    rythm = step * 20;                      // Πολλαπλάσια του 5 (5 - 50)
    //Serial.println(rythm);
    //stratTimeX=currentTime;

    startMillis = millis();
  }
}


