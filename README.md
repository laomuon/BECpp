# BECpp
Bureau d'étude de Cpp

Pour ce BE, on a été fourni une carte ESP8266, un écran Grove-LCD RGB Backlight, un détecteur de distance Ultrasonic Ranger, un détecteur de température, un buzzer et un bouton

Pour compiler, mettez lib.h, lib.cpp et testCpp.ino dans un dossier et nommez-le testCpp. Maintenant on peut compiler facilement le programme grâce à l'IDE de Arduino

Pin à connecter sur Grove:
- LCD: I2C (faites attention, le LCD a besoin une tension de 5V donc, au lieu de connecter directement à 3V3 on doit le brancher à Vin de Grove)
- Bouton: D5
- Ultrasonic: D7
- Température: A0
- Buzzer: D6

Sur l'écran vous verrez la température et la distance qui sont détectées par les détecteurs et il se rafraichit chaque 500ms pour affficher des nouvelles données
Au début l'écran est en rouge et ça veut dire que le buzzer est activé. Donc si la distance est trop petite (on a défini 10cm par défaut et on peut le changer), le buzzer sera déclenché
On peut désactiver le buzzer en pressant le bouton. L'écran deviendra vert et on pourra même toucher le détecteur de distance et le buzzer ne bippera pas
