import serial
import time
# Set up the serial connection (Adjust 'COM3' to your Arduino's COM port)
ser = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)  # Wait for the connection to establish
while True:
	if ser.in_waiting > 0:
		line = ser.readline().decode('utf-8').rstrip()
		# file.write(f"{time.strftime('%Y-%m-%d %H:%M:%S')} - {line}°C\n")
		print(line)