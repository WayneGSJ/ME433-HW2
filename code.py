import time
import board
import pwmio
from adafruit_motor import servo

pwm = pwmio.PWMOut(board.GP15, duty_cycle=0, frequency=50)
my_servo = servo.Servo(pwm)

while True:
    for angle in range(0, 180, 1):
        my_servo.angle = angle
        time.sleep(0.02)

    for angle in range(180, 0, -1):
        my_servo.angle = angle
        time.sleep(0.02)