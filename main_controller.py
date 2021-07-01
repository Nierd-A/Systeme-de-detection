import time
import RPi.GPIO as GPIO

RX = 15 #reciever
TX = 14 #transmitter
PX = 20 #sensor

GPIO.setup(RX, GPIO.IN)
GPIO.setup(TX, GPIO.OUT)
GPIO.setup(PX, GPIO.IN)

#affichage lors de tests
print('Running. Press CTRL-C to exit.')

try:
	while True:
		#Sensor reading, 0 = detection
		if GPIO.input(PX) == 0:
			GPIO.output(TX, 0)
			time.sleep(0.1)
			GPIO.output(TX, 1)
		msgNano = nanoReading()
		if GPIO.input(RX):
			messageHandler("Sound detected")
			
		time.sleep(0.1) #wait for arduino to answer
		
except KeyboardInterrupt:
	print("KeyboardInterrupt has been caught.")
				
def printLog(msgLog):
	print(msgLog)
	
def messageHandler(msgNano):
	printLog(msgNano)