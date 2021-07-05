import time
import math
import RPi.GPIO as GPIO
from time import strftime
import datetime

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
                        if start == -1:
           		     start = time.time()
            		print("Capteur de proximite detecte")
			GPIO.output(TX, 0)
			time.sleep(0.1)
			GPIO.output(TX, 1)
        	elif ( GPIO.input(PX) == 1 and start != -1 ):
            		end = time.time()
            		fichier = open("log.txt", "a")
            		fichier.write("\n" + datetime.datetime.now().strftime("%d/%m/%Y %H:%M:%S ") + "Presence detectee pendant une duree de " + str(round(float(end - start),2)) + " secondes")

                        fichier.close()
			start =	-1
        	if GPIO.input(RX) == 1:
            		messageHandler("Sound detected")
                        if start == -1:
              		    start = time.time()
        	elif ( GPIO.input(RX) == 0 and start != -1 ):
            		end = time.time()
            		fichier = open("log.txt", "a")
            		fichier.write("\n" + datetime.datetime.now().strftime("%d/%m/%Y %H:%M:%S ") + "Presence detectee pendant une duree de " + str(round(float(end - start),2)) + " secondes")
			start = -1
                        fichier.close()
		
except KeyboardInterrupt:
	print("KeyboardInterrupt has been caught.")
	GPIO.cleanup()
    
