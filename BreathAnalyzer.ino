/* MQ-4 Methane Sensor module with Arduino */
/* Interfacing with Arduino */

const int AO_Pin=0; // Connect AO of MQ4 with Analog channel 0 pin (A0) of Arduino
const int DO_Pin=7; // Connect DO of MQ4 with Digital pin 8 (D8) of Arduino

const int A1_Pin=1;
const int D1_Pin=8;

const int Led_Pin=13; // Connect an LED with D13 pin of Arduino
const int Btn_Pin=2;

int threshold0; // A variable to store digital output of MQ4
int threshold1;
int A0_Out; // stores analog output of MQ4 sensor
int A1_Out;
int D12_Inp;

// Tweeker Constant Parameters
const int Delta_Tolerance = 1; //One Point (Don't Change Plot);

void setup() {
Serial.begin(115200);  // Initialize serial communictation with a baud rate of 115200
pinMode(DO_Pin, INPUT); // Configure D8 pin as a digital input pin
pinMode(D1_Pin, INPUT);
pinMode(Btn_Pin, INPUT_PULLUP);
pinMode(Led_Pin, OUTPUT); //Configure D3 pin as a digital output pin
//Serial.println("Methane,Hydrogen");
}

int A0_Last_Out = 0;
int A1_Last_Out = 0;
void loop()
{
  D12_Inp = digitalRead(Btn_Pin);
  if(D12_Inp==0) {
    A0_Out= analogRead(AO_Pin); // Take Analog output measurement sample from AO pin of MQ4 sensor
    A1_Out = analogRead(A1_Pin);

    threshold0 = digitalRead(DO_Pin); //Read digital output of MQ4 sensor
    threshold1 = digitalRead(D1_Pin);
    
    if(A0_Out != A0_Last_Out || A1_Out != A1_Last_Out) 
    {
      Serial.print("Methane:");
      Serial.print(A0_Out);//prints the methane value
      Serial.print(',');
      Serial.print("Hydrogen:");
      Serial.println(A1_Out);//prints the methane value
    } 
    A0_Last_Out = A0_Out;
    A1_Last_Out = A1_Out;
    
    //Serial.print(" threshold_value: ");
    //Serial.print(threshold0);//prints the threshold_value reached as either LOW or HIGH (above or underneath)
  }
  delay(100);
  if (threshold0== HIGH) {
    digitalWrite(Led_Pin, HIGH);//if threshold_value has been reached, LED turns on as status indicator
  }
  else {
    digitalWrite(Led_Pin, LOW);//if threshold not reached, LED remains off
  }
}