#include<MPU6050.h>

MPU6050 mpu; //Creating an object for MPU

int16_t ax,ay,az; //Defining unsigned 16 bit integer variables to store raw acceleration values read by the mpu
int16_t gx,gy,gz;//Defining unsigned 16 bit integer variables to store raw gyroscope values read by the mpu

void setup() {
  Serial.begin(115200);
  mpu.initialize(); 
  
  Serial.println("Testing device connections..."); 
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed"); //Checking if the MPU is responding or not
}

void loop() {
  mpu.getAcceleration(&ax,&ay,&az); //Getting the raw values of acceleration from the mpu
  
}

float convert_accel(int16_t x) // The default full scale range is ± 2g
{
  return x/16384.0; 
}
