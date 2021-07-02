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
        	elif ( GPIO.input(PX) == 1 & start != -1 ):
            		end = time.time()
            		fichier = open("log.txt", "a")
            		fichier.write("\nPresence detectee pendant une duree de " + ( end - start) + " secondes, le " + strftime(%Y-%m-%d, datetime.now()) + " a " + strftime(%H:%M:%S, datetime.now())
			start =	-1
        	if GPIO.input(RX) == 0:
            		messageHandler("Sound detected")
            		start = time.time()
        	elif ( GPIO.input(RX) == 1 & start != -1 ):
            		end = time.time()
            		fichier = open("log.txt", "a")
            		fichier.write("\nBruit detecte pendant une duree de " + (end - start) + " secondes, le " + strftime(%Y-%m-%d, datetime.now()) + " à " + strftime(%H:%M:%S, datetime.now())
			start = -1
            		time.sleep(0.1) #wait for arduino to answer
    fichier.close()
		
except KeyboardInterrupt:
	print("KeyboardInterrupt has been caught.")
	GPIO.cleanup()
    
fichier.close()
