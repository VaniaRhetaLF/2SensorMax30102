/*
Dibuat oleh: Wenda Maulana Yusup
Divisi: RnD
Instansi: PT. Makerindo Prima Solusi
Source Code: Pembacaan 2 Sensor Heart Rate dan Oksimeter pada ESP32
*/

#include <Arduino.h>
#include <DFRobot_RTU.h>
#include <DFRobot_BloodOxygen_S.h>
#include <Wire.h>


#define SDA_2 33
#define SCL_2 32

int cekspo1, cekspo2, cekhr1, cekhr2;

DFRobot_BloodOxygen_S_I2C MAX30102_1(&Wire, 0x57);
DFRobot_BloodOxygen_S_I2C MAX30102_2(&Wire1, 0x57);



void setup()
{
  Serial.begin(115200);

  Wire.begin();
  Wire1.begin(SDA_2, SCL_2);
  MAX30102_1.begin();
  MAX30102_2.begin();
  Serial.println("");
  MAX30102_1.sensorStartCollect();
  MAX30102_2.sensorStartCollect();
}

void loop()
{

  cekspo1 = 0;
  cekspo2 = 0;
  cekhr1 = 0;
  cekhr2 = 0;
  int rataspo1;
  int rataspo2;
  int ratahr1;
  int ratahr2;
  int rataspofinal;
  int ratahrfinal;

  for (int i = 1; i < 4; i++)
  {
    MAX30102_1.getHeartbeatSPO2();
    MAX30102_2.getHeartbeatSPO2();
    int SPO2_1 = MAX30102_1._sHeartbeatSPO2.SPO2;
    if (SPO2_1 < 0)
    {
      SPO2_1 = 0;
    }

    int HR_1 = MAX30102_1._sHeartbeatSPO2.Heartbeat;
    if (HR_1 < 0)
    {
      HR_1 = 0;
    }

    // Sensor 2
    int SPO2_2 = MAX30102_2._sHeartbeatSPO2.SPO2;
    if (SPO2_2 < 0)
    {
      SPO2_2 = 0;
    }

    int HR_2 = MAX30102_2._sHeartbeatSPO2.Heartbeat;
    if (HR_2 < 0)
    {
      HR_2 = 0;
    }

    cekspo1 += SPO2_1;
    cekspo2 += SPO2_2;
    cekhr1 += HR_1;
    cekhr2 += HR_2;

    Serial.println("-------------------------------");
    Serial.print(String() + "Nilai SPO2_1 ke " + String(i) + " : ");
    Serial.print(SPO2_1);
    Serial.println(" %");
    Serial.print(String() + "Nilai SPO2_2 ke " + String(i) + " : ");
    Serial.print(SPO2_2);
    Serial.println(" %");
    Serial.print(String() + "Nilai HR_1 ke " + String(i) + "   : ");
    Serial.print(HR_1);
    Serial.println(" Bpm");
    Serial.print(String() + "Nilai HR_2 ke " + String(i) + "   : ");
    Serial.print(HR_2);
    Serial.println(" Bpm");
    Serial.println("-------------------------------");
    delay(5000);

    // Serial.print(String() + SPO2_1 + "," + SPO2_2 + "," + HR_1 + "," + HR_2 + ",");
    // delay(5000);
  }
    rataspo1 = cekspo1 / 3.0;
    rataspo2 = cekspo2 / 3.0;
    ratahr1 = cekhr1 / 3.0;
    ratahr2 = cekhr2 / 3.0;
    rataspofinal = (rataspo1 + rataspo2) / 2;
    ratahrfinal = (ratahr1 + ratahr2) / 2;

    /*Dibawah ini merupakan rata-rata pembacaan Dua Sensor dengan dua Parameter
    di masing-masing sensor yaitu Oksimeter dan Heart Rate, dengan rentang 3 x 15 detik*/

    Serial.print("Rata-rata SPO2_1      : ");
    Serial.print(rataspo1);
    Serial.println(" %");
    Serial.print("Rata-rata SPO2_2      : ");
    Serial.print(rataspo2);
    Serial.println(" %");
    Serial.print("Rata-rata HR_1        : ");
    Serial.print(ratahr1);
    Serial.println(" Bpm");
    Serial.print("Rata-rata HR_2        : ");
    Serial.print(ratahr2);
    Serial.println(" Bpm");

    // /* Dibawah ini merupakan rata - rata gabungan dari 2 buah rata-rata parameter dari dua sensor,
    // yang bisa dikatakan sebuah rata-rata final pembacaan dua sensor menjadi satu, yaitu Nilai rata-rata Oksimeter dan Heart Rate yang menjadi satu*/
    Serial.println("-------------------------------");
    Serial.print("Rata-rata FINAL SPO2  : ");
    Serial.print(rataspofinal);
    Serial.println(" %");
    Serial.print("Rata-rata FINAL HR    : ");
    Serial.print(ratahrfinal);
    Serial.println(" Bpm");
    Serial.println("-------------------------------");

    // Serial.println(String() + rataspo1 + "," + rataspo2 + "," + ratahr1 + "," + ratahr2 + "," + rataspofinal + "," + ratahrfinal);
  }