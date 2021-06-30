import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
RX = 15
TX = 14
PX = 20
GPIO.setup(RX, GPIO.IN)
GPIO.setup(TX, GPIO.OUT)

try:
    print("PIR Module Test")
    print(" (CTRL+C to exit)")
    time.sleep(2)
    print "Ready"
    GPIO.output(TX, 1)

    while True:
        if GPIO.input(RX):
            print("arduino detected")
        time.sleep(1)
except KeyboardInterrupt:
    print("Quitting")
    GPIO.cleanup()