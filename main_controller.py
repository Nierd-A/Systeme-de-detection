#Importation des librairies

import time
import math
import RPi.GPIO as GPIO
from time import strftime
import datetime
import subprocess

# Declaration des fonctions

def ecriture_log(detection,start,end):

    log = open("log.txt", "a")
    log.write("\n" + datetime.datetime.now().strftime("%d/%m/%Y %H:%M:%S ") + str(detection) + " pendant une duree de " + str(round(float(end - start),2)) + " secondes")
   # derniere_ligne = log.readlines()[-1]
    log.close()
  #  return derniere_ligne

def capteur_presence(GPIO_PX,start):
    #Sensor reading, 0 = detection
    if (GPIO_PX == 0 and start == -1):
        start = time.time()
       	print("Capteur de proximite detecte")
        GPIO.output(TX, 0)
    elif ( GPIO_PX == 1 and start != -1 ):
        GPIO.output(TX, 1)
        end = time.time()
        ecriture_log('Presence detectee',start,end)
	start = -1
    return start

def capteur_son(GPIO_RX,start):
    #Sensor reading, 1 = detection
    if (GPIO_RX == 1 and start == -1):
        start = time.time()
	print("son detecte")
    elif ( GPIO_RX == 0 and start != -1 ):
        end = time.time()
        ecriture_log('Bruit detecte',start,end)
	start = -1
    return start


#MAIN
print("Setup ...")
#lancement du setup d'enregistrement des log
subprocess.call(["bash","setup_auto_log.sh"])

GPIO.setmode(GPIO.BCM)

RX = 15 #reciever
TX = 14 #transmitter
PX = 20 #sensor

GPIO.setup(RX, GPIO.IN)
GPIO.setup(TX, GPIO.OUT)
GPIO.setup(PX, GPIO.IN)

start_px = start_rx = -1

GPIO.output(TX,1)

#affichage lors de tests
print('Running. Press CTRL-C to exit.')

try:
	while True:

		start_px = capteur_presence(GPIO.input(PX),start_px)
       		 
		start_rx = capteur_son(GPIO.input(RX),start_rx)
		
except KeyboardInterrupt:
	print("KeyboardInterrupt has been caught.")
	GPIO.cleanup()
        
        #enregistrement des eventuelles derniers logs
        subprocess.call(["bash","auto_log.sh"])
        #suppression de l'enregistrement automatique
        subprocess.call(["bash","setup_auto_log.sh","-r"]) 
 


