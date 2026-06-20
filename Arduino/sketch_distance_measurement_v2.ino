#include <EEPROM.h>
int decimalprec=2; //Ακρίβεια δεκαδικών ψηφίων στην εμφάνιση
int inputButtonPin=2; //Push Button input pin
int potPin = A0; // Potentiometer output connected to analog pin 0
int potVal = 0; // Variable to store the input from the potentiometer
int rythm=10; //The delay of sampling in miliseconds 
int startstop=0; //if startstop=0 
unsigned long currentTime;

int echoPin = 12; // Echo Pin
int trigPin = 13; // Trigger Pin
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration; // Διάρκεια για να υπολογιστεί η απόσταση
float distance, prevDistance; // Απόσταση, Προηγούμενη Απόσταση για να υπολογιστεί η ταχύτητα
unsigned long startMillis; // Ο χρόνος έναρξης της συλλογής δεδομένων (που πατήθηκε το push button)
unsigned long elapsed; //Ο χρόνος (milliseconds) που πέρασε από την έναρξη συλλογής των τιμών (που πατήθηκε το push button)
unsigned long prevelapsed; //Η προηγούμενη τιμή του χρόνου (milliseconds) για να υπολογιστεί η ταχύτητα
float speed; //H ταχύτητα 
float prevspeed; //H προηγούμενη τιμή της ταχύτητας (cm/sec) για τον υπολογισμό της επιτάχυνσης
float acceleration; // Επιτάχυνση 
unsigned long count; // Μετρητής των επαναλήψεων

// ====== ΝΕΟ: Εξομάλυνση (moving average) ======
// Αντί να υπολογίζουμε v και a από 2 διαδοχικές, "ακατέργαστες" μετρήσεις απόστασης
// (πολύ ευαίσθητο στον θόρυβο του HC-SR04, βλ. εξήγηση παρακάτω), κρατάμε ένα μικρό
// "παράθυρο" πρόσφατων μετρήσεων απόστασης και δουλεύουμε πάνω στον μέσο όρο τους.
const int WINDOW = 5;              // μέγεθος παραθύρου εξομάλυνσης (δοκιμάστε 3-7)
float distBuffer[WINDOW];          // κυκλικός buffer με τις τελευταίες WINDOW μετρήσεις
int bufIndex = 0;                  // επόμενη θέση εγγραφής στο buffer
int bufCount = 0;                  // πόσες έγκυρες τιμές υπάρχουν ακόμα στο buffer (<= WINDOW)

float smoothDistance(float newDist) {
  // Προσθήκη της νέας μέτρησης στο κυκλικό buffer
  distBuffer[bufIndex] = newDist;
  bufIndex = (bufIndex + 1) % WINDOW;
  if (bufCount < WINDOW) bufCount++;

  // Μέσος όρος των έγκυρων τιμών του buffer
  float sum = 0;
  for (int i = 0; i < bufCount; i++) sum += distBuffer[i];
  return sum / bufCount;
}
// ================================================

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
      count=0; //Αρχικοποίηση του μετρητή των επαναλήψεων (κάθε φορά που πατάω το κουπί αρχικοποιείται)

      prevDistance=0; //Αρχικοποίηση της προηγούμενης τιμής της απόστασης 
      prevelapsed=0; //Αρχικοποίηση της προηγούμενης τιμής του χρόνου
      prevspeed=0; // Αρχικοποίηση της προηγούμενης τιμής της ταχύτητας
      bufIndex=0;      // ΝΕΟ: καθαρισμός buffer εξομάλυνσης σε κάθε νέα εκκίνηση μέτρησης
      bufCount=0;      // ΝΕΟ
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

    float rawDistance = duration/58.2; //Ακατέργαστη απόσταση (cm) από τον αισθητήρα. Ή (0.034cm/μs ταχύτητα ήχου στους 20C) distance=0.034*duration/2;

    if (rawDistance >= maximumRange || rawDistance <= minimumRange){
      Serial.println("Εκτός ορίων");
      delay(100);
    }
    else {

      // ΝΕΟ: φιλτράρισμα ακραίων τιμών (spike rejection) πριν την εξομάλυνση.
      // Αν η νέα μέτρηση διαφέρει υπερβολικά από την προηγούμενη (π.χ. >15cm
      // σε ένα μόνο βήμα δειγματοληψίας), πιθανότατα είναι σφάλμα ανάκλασης
      // του υπερήχου και όχι πραγματική μετατόπιση του αμαξιδίου — την αγνοούμε.
      const float MAX_JUMP_CM = 15.0;
      if (bufCount > 0 && abs(rawDistance - prevDistance) > MAX_JUMP_CM) {
        // αγνοούμε αυτό το δείγμα, δεν ενημερώνουμε prevDistance/prevelapsed
        delay(rythm);
        return;
      }

      distance = smoothDistance(rawDistance); // ΝΕΟ: χρησιμοποιούμε την εξομαλυμένη τιμή

      elapsed = (millis() - startMillis);  //ο χρόνος που πέρασε σε σχέση με τον χρόνο έναρξης

      // Υπολογισμός και εκτύπωση της ταχύτητας
      float ds=distance-prevDistance; //διαφορά απόστασης σε centimeters
      float dt=elapsed-prevelapsed; // διαφορά χρόνου σε milliseconds
      speed=(float)(ds/dt)*1000.0; // Υπολογισμός της ταχύτητας Πολλάπλασιάζω με το 1000 για να γίνει η μετατροπή σε cm/sec
      float dv=speed-prevspeed; //διαφορά ταχύτητας (cm/sec)
      acceleration=(float)(dv/dt)*1000.0; //Υπολογισμός της επιτάχυνσης cm/sec^2

      if (count >3) { //Εάν περάσουμε τις 3 πρώτες μετρήσεις τότε να εκτυπώνει για να υπολογίζεται η επιτάχυνση σωστά
        Serial.print(elapsed/1000.0,decimalprec); //εκτύπωση του χρόνου σε sec decimalprec=ακρίβεια δεκαδικών ψηφίων

        // Εκτύπωση της απόστασης
        Serial.print(", ");
        Serial.print(distance,decimalprec);

        // Εκτύπωση της ταχύτητας
        Serial.print(", ");
        Serial.print(speed,decimalprec);

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
    //Καθυστέρηση πριν την επόµενη ανάγνωση
    delay(rythm);
  }
  else //Εάν το push button δεν είναι πατημένο τότε ρύθμισε τον ρυθμό δειγματοληψίας
  {
    startstop=0;
    potVal = analogRead(potPin);   // Διάβασε την τιμή που δίνει το ποτενσιόμετρο στο input pin
    int step = map(potVal, 0, 1023, 1, 5);    // Μετατροπή σε 1 - 5
    rythm = step * 20;                      // Πολλαπλάσια του 5 (5 - 50)

    startMillis = millis();
  }
    
}
