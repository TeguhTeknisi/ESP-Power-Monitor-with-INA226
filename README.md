# ESP-Power-Monitor-with-INA226
ESP8266 Power Monitor with INA226 adalah alat ukur voltase, arus, daya dan energi dengan tambahan modul dht11 untuk ukur temperatur dan kelembaban.
Alat ini dibuat sesuai kebutuhan sistem plts di tempat ana, dan ana tidak men jamin bisa jalan di tempat lain.
Untuk tingkat akurasinya sudah cukup bagus menurut ana, dengan membandingkan pengukuran arus dan voltase pakai multimeter Zoyi ZT102A
Karena keterbatasan kemampuan ana dalam coding dan elektronika mikrokontroller, pada alat ukur voltase dari INA226 nya tidak akurat, jadi ana ganti mengukur pakai ADC. 

Codenya ana ambil dari berbagai tempat, sumbernya ada dibawah ini:
1. https://forum.arduino.cc/t/solar-power-monitor-w-ina226-and-esp8266-v1/649695
2. https://community.blynk.cc/t/power-monitor-dc-current-and-voltage-sensor-ina219/10297 ( referensi code max voltase, arus dan daya )
3. https://www.engineersgarage.com/nodemcu-battery-voltage-monitor/ ( referensi alat ukur voltase pakai resistor divider )
4. https://how2electronics.com/iot-based-battery-status-monitoring-system-using-esp8266/ ( referensi alat ukur voltase pakai resistor divider )
5. https://openenergymonitor.org/forum-archive/node/198.html ( referensi kwh meter dan log harian )



Semoga membantu dan bermanfaat.
