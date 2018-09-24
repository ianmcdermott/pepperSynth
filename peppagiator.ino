#include <werkstatt.h>


#define redPin 9
#define greenPin 10
#define bluePin 11
int data = 0;
int backupData;

#define max_char 12
char message[max_char];    // stores you message
char r_char;               // reads each character
byte index = 0;            // defines the position into your array
int i;
int flag = 0;
char currentColor;
String redTempValue;     // Red RGB pin -> D11
String greenTempValue;   // Green RGB pin -> D10
String blueTempValue;     // Blue RGB pin -> D9             // reads each character
int indexer;
/**** Peppagiator ****/
String scaleName;
arpeggiator arpeggiator(6); //initiate and name the arpeggiator class (Output pin)
int seq = 2;
int seqLength = 0;
/*
  notes are assigned in intervals: tonic, minor2nd, major2nd, minor3rd,
  major3rd, fourth, tritone, fifth, minor6th, major6th, minor7th,
  major7th, octave.
*/
//r chooses values
int values[8];
static int scale[8];

//g chooses scale
//int scale[7];

/**** Peppagiator ****/

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(38400);
  scale[0] = tonic;
  scale[1] = major2nd;
  scale[2] =  minor3rd;
  scale[3] = fourth;
  scale[4] = fifth;
  scale[5] = major6th;
  scale[6] = minor7th;
  scale[7] = octave;
}
void loop() {
  //while is reading the message

  while (Serial.available() > 0) {

    flag = 0;
    //the message can have up to 12 characters
    if (index < (max_char - 1)) {
      r_char = Serial.read();      // Reads a character
      Serial.print(r_char);
      Serial.print(" ");
      message[index] = r_char;     // Stores the character in message array
      if (r_char == 'R') {
        currentColor = 'R';
        redTempValue = "";

      }
      else if (r_char == 'G') {
        currentColor = 'G';
        greenTempValue = "";
      }
      else if (r_char == 'B') {
        currentColor = 'B';
        blueTempValue = "";
      }
      if (currentColor == 'R' && r_char != 'R') {
        redTempValue += r_char;
      }
      else if (currentColor == 'G' && r_char != 'G') {
        greenTempValue += r_char;
      }
      else if (currentColor == 'B' && r_char != 'B') {
        blueTempValue += r_char;
      }
      index++;                     // Increment position
      message[index] = '\0';       // Delete the last position
    }
    delay(10);
    greenArp( 127);

    //    Serial.print("GTV: ");
    redArp(127);
  }
  delay(10);
  if (scaleName == "ionian") {
    scale[0] = tonic;
    scale[1] = major2nd;
    scale[2] =  minor3rd;
    scale[3] = fourth;
    scale[4] = fifth;
    scale[5] = major6th;
    scale[6] = minor7th;
    scale[7] = octave;
  }  else if (scaleName == "dorian") {
    scale[0] = tonic;
    scale[1] = minor2nd;
    scale[2] =  minor3rd;
    scale[3] = fourth;
    scale[4] = fifth;
    scale[5] = minor6th;
    scale[6] = minor7th;
    scale[7] = octave;
  }  else if (scaleName == "phrygian") {
    scale[0] = tonic;
    scale[1] = major2nd;
    scale[2] =  major3rd;
    scale[3] = tritone;
    scale[4] = fifth;
    scale[5] = major6th;
    scale[6] = major7th;
    scale[7] = octave;
  }  else if (scaleName == "lydian") {
    scale[0] = tonic;
    scale[1] = major2nd;
    scale[2] =  major3rd;
    scale[3] = fourth;
    scale[4] = fifth;
    scale[5] = major6th;
    scale[6] = minor7th;
    scale[7] = octave;
  }  else if (scaleName == "mixolydian") {
    scale[0] = tonic;
    scale[1] = major2nd;
    scale[2] =  minor3rd;
    scale[3] = fourth;
    scale[4] = fifth;
    scale[5] = minor6th;
    scale[6] = minor7th;
    scale[7] = octave;
  }  else if (scaleName == "aeolian") {
    scale[0] = tonic;
    scale[1] = minor2nd;
    scale[2] =  minor3rd;
    scale[3] = fourth;
    scale[4] = tritone;
    scale[5] = minor6th;
    scale[6] = minor7th;
    scale[7] = octave;
  }  else   {
    scale[0] = tonic;
    scale[1] = minor2nd;
    scale[2] =  minor3rd;
    scale[3] = fourth;
    scale[4] = tritone;
    scale[5] = minor6th;
    scale[6] = minor7th;
    scale[7] = octave;
  }
  Serial.println(scaleName);

  if (flag == 0) {
    analogWrite(redPin, 255 - redTempValue.toInt());
    analogWrite(greenPin, 255 - greenTempValue.toInt());
    analogWrite(bluePin,  255 - blueTempValue.toInt());

    flag = 1;
    for (i = 0; i < 12; i++) {
      message[i] = '\0';
    }
    //resets the index
    index = 0;
  }
  indexer = int( map((255 - blueTempValue.toInt()), 0, 255, 0, 7.9999));

  for (int i = 0; i < 8; i++) {
    //    Serial.print("Val: ");
    //    Serial.println(values[i]);
    //    Serial.print(i);
    //    Serial.print(" : ");

    //define a BPM and run the arpeggiator.play function
    arpeggiator.play(140, scale[i], e);

  }
  //  Serial.print( ");

}

void redArp(int r) {
  if (r >= 0 && r < 51) {
    for (int i = 0 ; i < sizeof(values); i++) {
      values[i] = w;
    }
  } else if (r >= 51 && r < 102) {
    for (int i = 0 ; i < sizeof(values); i++) {
      values[i] = h;
    }
  } else if (r >= 102 && r < 153) {
    for (int i = 0 ; i < sizeof(values); i++) {
      values[i] = q;
    }
  } else if (r >= 153 && r < 204) {
    for (int i = 0 ; i < sizeof(values); i++) {
      values[i] = e;
    }
  } else { //if (r >= 204 && r < 256) {
    for (int i = 0 ; i < sizeof(values); i++) {
      values[i] = sx;
    }
  }
  delay(10);
  Serial.print("done rd");

}

void greenArp(int g) {
  if (g >= 0 && g < 36) {
    scaleName = "ionian";
  } else if (g >= 36 && g < 72) {
    scaleName = "dorian";
  } else if (g >= 72 && g < 108) {
    scaleName = "phrygian";
  } else if (g >= 108 && g < 144) {
    scaleName == "lydian";
  } else if (g >= 144 && g < 180) {
    scaleName = "mixolydian";
  } else if (g >= 180 && g < 216) { //if (g >= 216 && g < 256) {
    scaleName == "aeolian";
  } else {
    scaleName =  "locrian";
  }
  Serial.print("done green");
  delay(10);
}
