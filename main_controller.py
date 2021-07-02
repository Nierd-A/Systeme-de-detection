import time
import RPi.GPIO as GPIO
from time import strftime

def printLog(msgLog):
	print(msgLog)
	
def messageHandler(msgNano):
	printLog(msgNano)

#MAIN
GPIO.setmode(GPIO.BCM)

RX = 15 #reciever
TX = 14 #transmitter
PX = 20 #sensor

GPIO.setup(RX, GPIO.IN)
GPIO.setup(TX, GPIO.OUT)
GPIO.setup(PX, GPIO.IN)

start = -1

GPIO.output(TX,1)

#affichage lors de tests
print('Running. Press CTRL-C to exit.')

try:
	while True:
		#Sensor reading, 0 = detection
		if GPIO.input(PX) == 0:
            start = time.time()
            print("Capteur de proximite detecte")
			GPIO.output(TX, 0)
			time.sleep(0.1)
			GPIO.output(TX, 1)
        else if ( GPIO.input(PX) == 1 & start != -1 ):
            end = time.time()
            fichier = open("log.txt", "a")
            fichier.write("\nPrésence détectée pendant une durée de " end - start " secondes, le " strftime(%Y-%m-%d, datetime.now())" à " strftime(%H:%M:%S, datetime.now())
            fichier.close()
        if GPIO.input(RX) == 0:
            messageHandler("Sound detected")
            start = time.time()
        else if ( GPIO.input(RX) == 1 & start != -1 ):
            end = time.time()
            fichier = open("log.txt", "a")
            fichier.write("\nBruit détecté pendant une durée de " end - start " secondes, le " strftime(%Y-%m-%d, datetime.now())" à " strftime(%H:%M:%S, datetime.now())
            fichier.close()
            time.sleep(0.1) #wait for arduino to answer
		
except KeyboardInterrupt:
	print("KeyboardInterrupt has been caught.")
	GPIO.cleanup()
