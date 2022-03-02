# ESP-Power-Monitor-with-INA226
ESP8266 Power Monitor with INA226 adalah alat ukur voltase, arus, daya dan energi dengan tambahan modul dht11 untuk ukur temperatur dan kelembaban.
Alat ini dibuat sesuai kebutuhan sistem plts di tempat ana, dan ana tidak men jamin bisa jalan di tempat lain.
Untuk tingkat akurasinya sudah cukup bagus menurut ana, dengan membandingkan pengukuran arus dan voltase pakai multimeter Zoyi ZT102A
Karena keterbatasan kemampuan ana dalam coding dan elektronika mikrokontroller, pada alat ukur voltase dari INA226 nya tidak akurat, jadi ana ganti mengukur pakai ADC. 

Kemampuan membaca Voltase Max 35 volt, disarankan 30 Volt
Kemampuan membaca Arus tergantung nilai R Shunt.

Codenya ana ambil dari berbagai tempat, sumbernya ada dibawah ini:
1. https://forum.arduino.cc/t/solar-power-monitor-w-ina226-and-esp8266-v1/649695
2. https://community.blynk.cc/t/power-monitor-dc-current-and-voltage-sensor-ina219/10297 ( referensi code max voltase, arus dan daya )
3. https://www.engineersgarage.com/nodemcu-battery-voltage-monitor/ ( referensi alat ukur voltase pakai resistor divider )
4. https://how2electronics.com/iot-based-battery-status-monitoring-system-using-esp8266/ ( referensi alat ukur voltase pakai resistor divider )
5. https://openenergymonitor.org/forum-archive/node/198.html ( referensi kwh meter dan log harian )

Part list
1. Sensor 1 pakai INA226 20A 36v - https://shopee.co.id/product/43270505/8591547022?smtt=0.94966776-1646228655.9 ( 49rb )
2. Sensor 2 pakai INA226 1A 36v - https://www.tokopedia.com/lisuinstrument/ina226-bi-directional-monitor-module-voltage-current-power-alert ( 36rb )
3. LCD 1602 - https://www.tokopedia.com/ardushopid/lcd-blue-16x2-1602-i2c-serial-connection-free-kabel-jumper-arduino ( 38rb )
4. Wemos D1 Mini - https://www.tokopedia.com/hwthinker/wemos-d1-mini-nodemcu-lua-wifi-arduino-iot-based-on-esp8266 ( 36rb )
5. R Shunt 50A FL4 untuk Sensor 2 - https://www.tokopedia.com/avarelectric/fl-2-r-shunt-50a-dc-power-meter-current-50-a-fl-2 ( 40rb )
6. LM 7805 - https://www.tokopedia.com/search?st=product&q=LM7805 ( 1.400 )
7. Kapasitor Keramik 100nf 104 - https://www.tokopedia.com/isee/kapasitor-100nf-50v-104-multilayer-monolithic-ceramic-capasitor-0-1uf ( 300 x 3 = 900 )
8. Resistor 100K - https://www.tokopedia.com/isee/10-pcs-resistor-100k-100-kilo-ohm-1-4-watt-0-25-metal-film-1-toleran ( 10pcs - 1.000 )
9. Resistor 10K - https://www.tokopedia.com/isee/10-pcs-resistor-10k-10-kilo-ohm-1-4-watt-0-25-metal-film-1-toleran ( 10pcs - 1.000 )
10. Dioda 1A - https://www.tokopedia.com/isee/dioda-diode-in4001-in-4001 ( 200 )
11. pcb berlubang - https://www.tokopedia.com/isee/pcb-dot-matrix-ic-type-5x7-5-x-7-pcb-lubang-ic-5-7-cm ( 2.400 )
12. Sensor DHT11 - https://www.tokopedia.com/isee/dht-11-dht11-modul-sensor-kelembaban-suhu-humidity-temperature-arduino ( 17.500 )
Total 223.500

Resistor 100K bisa ganti 120K agar maks ukur jadi 43v tapi harus modif code nya dan ic LM7805 diganti modul step down 5v
karena ic LM7805 punya maks inut 35 volt saja.

Semoga membantu dan bermanfaat.
