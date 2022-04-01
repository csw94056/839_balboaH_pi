/**
 * Very basic serial latency testing program.
 *
 * Carrick Detweiler, 2022
 **/
void setup() {
  Serial.begin(115200);
}

int sendVal = 0;
void loop() {
  unsigned long sendTime = millis();
  Serial.write(sendVal);
  //Serial.print("Sending int "); Serial.println((int)sendVal);
  char c;
  while(1){
    if(Serial.available() > 0){
      c = Serial.read();
      unsigned long receivedTime = millis();
      if(c != sendVal){
        Serial.print("got "); Serial.print((int) c);
        Serial.print(" exp "); Serial.println(sendVal);
        //Serial.println("sync");
      }else{
        Serial.print("Round trip: ");
        Serial.print(receivedTime - sendTime);
        Serial.println("ms");
        delay(100);
        break;
      }
    }
    if((millis() - sendTime) > 800){
      Serial.print("Timeout, sendVal ");
      Serial.println(sendVal);
      break;
    }
  }
  sendVal++;
  //Don't use printable characters so reset
  if(sendVal > 5) sendVal = 0;

}
