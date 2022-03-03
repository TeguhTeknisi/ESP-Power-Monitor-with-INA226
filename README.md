# ESP-Power-Monitor-with-INA226
<b>ESP8266 Power Monitor with INA226</b> adalah alat ukur voltase, arus, daya dan energi dengan tambahan modul DHT11 untuk ukur temperatur dan kelembaban.
Alat ini dibuat sesuai kebutuhan sistem plts di tempat ana, dan ana tidak men jamin bisa jalan di tempat lain.
Alat ini kurang cocok untuk mengukur ke beban Inverter yang banyak Noise nya.

📣 Harus pakai Server Blynk Lokal , tutorial ada disini https://github.com/TeguhTeknisi/blynk-server
Sekedar info, ana install server blynk ke laptop ubuntu linux, tapi bisa juga di install ke android yang di instali linux.
Tambahan, Kalau mau pakai Server Online, silahkan modif codenya.

✔️ Kode dan Skema ada 2 versi:
1. versi 1 sensor, supaya lebih murah bisa pakai Modul Sensor INA226 dengan R Shunt R002 dengan kemampuan ukur continue 20 Ampere max 35 Volt.
   --> versi ini hanya mengukur 1 sumber saja, dan bisa hemat sekitar 80rb karena tidak perlu beli Modul INA226 yang kedua + R Shunt FL4.
2. versi 2 sensor, ini untuk yang ingin mengukur 2 sumber, seperti yang ana pakai, untuk ukur sumber dari Output Scc dan Baterai ke Beban. 
   --> Kemampuan Ukur pada Modul Sensor INA226 yang kedua ana tambahkan RShunt FL4 50A 75mV, sehingga bisa ukur beban sampai 50A 35 Volt
   --> Dengan R Shunt FL4 50A bisa 1.400 Watt untuk sistem 28 Volt yang ana pakai.
   --> Bisa diganti ke R Shunt 100A, 150A, 200A, 250A tapi harus ganti code nya dan hati hati jika bekerja dengan Arus besar.

⛔ Code harus di edit pada:
1. Auth Token Blynk
2. Nama SSID Hotspot dan Password nya.

Untuk tingkat akurasinya sudah cukup bagus menurut ana, dengan membandingkan pengukuran arus dan voltase pakai multimeter Zoyi ZT102A
Karena keterbatasan kemampuan ana dalam coding dan elektronika mikrokontroller, pada alat ukur voltase dari INA226 nya tidak akurat, jadi ana ganti mengukur pakai ADC. 

Untuk Sensor INA226 beli di link yang ana kasih dibawah, Insya Allah terjamin.
Untuk part lain, hanya sebagai referensi harga, ana tidak menjamin kualitasnya.

⛔ HATI HATI, ada modul INA226 Palsu, ana pernah beli dan gak bisa didetek I2C nya pakai I2C Scanner, tapi pas di ganti alamat ke 0x50 bisa detek tapi hanya tampil pengukuran Voltase tapi gak bisa dipakai buat ukur voltase.
NodeMCU dan Wemos D1 juga mulai muncul dengan raqgam kualitas yang gak bisa dilihat dari harga, bisa murah atau mahal.
Biasanya buat upload code akan sering error karena kualitas Chip Flash nya yang kurang bagus, atau yang parah gak bisa di program karena Chip Flash nya rusak.

✔️Kemampuan membaca Voltase Max 35 volt, disarankan 30 Volt
✔️Kemampuan membaca Arus tergantung nilai R Shunt.
Untuk Kode nya ana seting untuk:
1. Sensor 1 Continue max 20A, peak 25A pakai INA226 dengan R Shunt SMD R002
2. Sensor 2 Continue max 50A, pakai INA226 dengan RShunt SMD R100 yang di sambung ke R Shunt Eksternal FL4 50A 75mV

☑️ Kit ESP8266 bisa pakai Wemos D1 Mini agar kecil ringkas, atau pakai NodeMCU bentuk agak besar, ana pakai NodeMCU

☑️ Modul LCD 1602 pakai IC I2C PCF8574  untuk IC versi lain, silahkan memakai atau mencari library yang cocok.

☑️ Komponen Kapasitor 100nF fungsinya untuk filter, usahakan pakai Kapasitor Keramik, bisa Keramik biasa atau multilayer.

☑️ Komponen Dioda bisa pakai IN4001 sampai IN4007, untuk pengaman jika salah polaritas agar tidak rusak.

☑️ Modul DHT11 ana pakai untuk mengukur temperature dan kelembaban di dalam box plts, bisa dipakai atau gak dipakai.

✔️ Untuk Codenya ana ambil dari berbagai tempat, sumbernya ada dibawah ini:
1. https://forum.arduino.cc/t/solar-power-monitor-w-ina226-and-esp8266-v1/649695
2. https://community.blynk.cc/t/power-monitor-dc-current-and-voltage-sensor-ina219/10297 ( referensi code max voltase, arus dan daya )
3. https://www.engineersgarage.com/nodemcu-battery-voltage-monitor/ ( referensi alat ukur voltase pakai resistor divider )
4. https://how2electronics.com/iot-based-battery-status-monitoring-system-using-esp8266/ ( referensi alat ukur voltase pakai resistor divider )
5. https://openenergymonitor.org/forum-archive/node/198.html ( referensi kwh meter dan log harian )

✔️ Part list
1. Sensor 1 pakai INA226 20A 36v - https://shopee.co.id/product/43270505/8591547022?smtt=0.94966776-1646228655.9 ( 49rb )
2. Sensor 2 pakai INA226 1A 36v - https://www.tokopedia.com/lisuinstrument/ina226-bi-directional-monitor-module-voltage-current-power-alert ( 36rb )
3. LCD 1602 - https://www.tokopedia.com/ardushopid/lcd-blue-16x2-1602-i2c-serial-connection-free-kabel-jumper-arduino ( 38rb )
4. Wemos D1 Mini - https://www.tokopedia.com/hwthinker/wemos-d1-mini-nodemcu-lua-wifi-arduino-iot-based-on-esp8266 ( 36rb )
   NodeMCU - https://www.tokopedia.com/best-ay/nodemcu-lua-wifi-v3-wifi-iof-esp8266-esp12-ch340g-board ( Rp. 34.500 )
5. R Shunt 50A FL4 untuk Sensor 2 - https://www.tokopedia.com/avarelectric/fl-2-r-shunt-50a-dc-power-meter-current-50-a-fl-2 ( 40rb )
6. LM 7805 - https://www.tokopedia.com/search?st=product&q=LM7805 ( 1.400 )
7. Kapasitor Keramik 100nf 104 - https://www.tokopedia.com/lisuinstrument/0-1uf-100nf-50v-104-multilayer-monolithic-ceramic-capacitor ( 300 x 3 = 900 )
8. Resistor 100K - https://www.tokopedia.com/isee/10-pcs-resistor-100k-100-kilo-ohm-1-4-watt-0-25-metal-film-1-toleran ( 10pcs - 1.000 )
9. Resistor 10K - https://www.tokopedia.com/isee/10-pcs-resistor-10k-10-kilo-ohm-1-4-watt-0-25-metal-film-1-toleran ( 10pcs - 1.000 )
10. Dioda 1A - https://www.tokopedia.com/lisuinstrument/in4001-1n4001-4001-general-purpose-plastic-rectifier-do-41 ( 200 )
11. pcb berlubang - https://www.tokopedia.com/isee/pcb-dot-matrix-ic-type-5x7-5-x-7-pcb-lubang-ic-5-7-cm ( 2.400 )
12. Sensor DHT11 - https://www.tokopedia.com/best-ay/modul-dht11-sensor-kelembaban-suhu-humidity-temperature-digital ( 14.950 )

☑️ Estimasi Total Biaya:
🟠 Untuk 1 Sensor Rp. 139.000 sampai Rp. 147.500
🔴 Untuk 2 Sensor Rp. 215.000 sampai Rp. 223.500

🔴🟠 Resistor 100K bisa ganti 120K agar maks ukur jadi 43v tapi harus modif code nya dan ic LM7805 diganti modul step down 5v
karena ic LM7805 punya maks inut 35 volt saja.

Semoga membantu dan bermanfaat.
