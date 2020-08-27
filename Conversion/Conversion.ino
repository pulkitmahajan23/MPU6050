#include<MPU6050.h>
#define accCoef 0.02
#define gyroCoef 0.98

MPU6050 mpu; //Creating an object for MPU

float ax,ay,az; //Variables for storing converted acceleration values
float anglex,angley,anglez;//Defining unsigned 16 bit integer variables to store raw gyroscope values read by the mpu

void setup() {
  Serial.begin(115200);
  mpu.initialize(); 
  
  Serial.println("Testing device connections..."); 
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed"); //Checking if the MPU is responding or not
}

void loop() {
  get_accel();
  get_angles();
  Serial.println("Acceleration values");
  Serial.print(ax);Serial.print("\t");
  Serial.print(ay);Serial.print("\t");
  Serial.print(az);Serial.print("\n");
  Serial.println("Gyro values");
  Serial.print(anglex);Serial.print("\t");
  Serial.print(angley);Serial.print("\t");
  Serial.print(anglez);Serial.print("\t");
  
}

void get_accel() // The default full scale range is ± 2g
{
  int16_t raw_ax,raw_ay,raw_az; //Defining unsigned 16 bit integer variables to store raw acceleration values read by the mpu
  mpu.getAcceleration(&raw_ax,&raw_ay,&raw_az); //Getting the raw values of acceleration from the mpu
  ax=raw_ax/16384.0;
  ay=raw_ay/16384.0;
  az=raw_az/16384.0;
}

void get_angles() // The default full scale range is ± 250
{
  get_accel();
  int16_t raw_gx,raw_gy,raw_gz;
  mpu.getRotation(&raw_gx, &raw_gy, &raw_gz);
  float angleAccX = 180*atan2(ay, sqrt(ax*ax+az*az))/ PI; // Effect due to angular acceleration
  float angleAccY = -180*atan2(ax, sqrt(ay*ay+az*az)) / PI;

  float gx = ((float)raw_gx) / 131.0;
  float gy = ((float)raw_gy) / 131.0;
  anglez = ((float)raw_gz) / 131.0;

  anglex = (gyroCoef * (anglex + gx )) + (accCoef * angleAccX);
  angley = (gyroCoef * (angley + gy )) + (accCoef * angleAccY);
}
