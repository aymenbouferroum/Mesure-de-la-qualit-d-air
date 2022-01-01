_version_ = "1.0"
"""
Import packages
"""
import sys
import time
import Adafruit_DHT  # Library for DHT22 sensor
import board  # Libraries for ..
import busio  # IAQCore

"""
Verify if Python 3 is installed else exit code and return an error
"""
if sys.version_info < (3, 0):
    sys.stdout.write("Sorry, requires Python 3.x, not Python 2.x\n")
    sys.exit(1)

if __name__ == "_main_":
    print("Stop with CTRL+C ...")

    """
    Getting Temperature + Humidity mesures from the DHT22 sensor
    """
    DELAY_SECONDS = 1  # Measurement interval
    DHT_SENSOR = Adafruit_DHT.DHT22  # Define DHT sensor type
    DHT_PIN = 8  # Define the GPIO pin to which DHT22 is connected

    """
    Getting CO2 + TVOC mesures from the IAQ-Core sensor
    """
    # Create i2c class
    i2c = busio.I2C(board.SCL, board.SDA)  # you must specify the clock line "SCL" and data line pins "SDA"

    while not i2c.try_lock():  # This loop will continually call the try_lock function until it returns true that the I2C bus was locked
        pass

    address = int(0x5A)  # Define I2C base address for IAQ-Core
    result = bytearray(9)  # Define a bytearray with a size = 9 to store data

    """
    This function reads into result from the device selected by address (at least 1 byte must be read)
    """

    def measure():
        i2c.readfrom_into(address, result)
        return [int(x) for x in result]  # return an array of integers


    while True:
        try:
            f = open("results.txt", "w")  # Define a file where to write measurements
            # Read humidity and temperature values from DHT22 sensor
            humidity, temp = Adafruit_DHT.read_retry(DHT_SENSOR, DHT_PIN)
            data = measure()  # Read measurements from IAQ-Core sensor
            data = data[0:9]
            co2 = (data[0] << 8) + data[1]  # Use the first 2 bytes to compute CO2 measures
            status = data[2]  # Get the sensor status from the third byte
            tvoc = (data[7] << 8) + data[8]  # Use the last 2 bytes to compute TVOC measures

            """
            Check the status of IAQ-Core core sensor 
            """
            if status == 0:  # if status = 0 ==> the sensor is ok and the data is valid
                print(round(temp, 2), round(humidity, 2), co2, tvoc, file=f)
            elif status == 1:  # if status = 1 ==> the sensor is busy
                print("BUSY", file=f)
            else:  # else ==> error
                print("ERROR", file=f)

            # Display in console real time measurements
            print(
                "Temp: {0:0.1f} °C    Humidity: {1:0.1f} %    CO2: {2:0.1f} %   Tvoc: {3:0.1f} %".format(temp, humidity,
                                                                                                         co2, tvoc))
        except RuntimeError as error:
            print(error.args[0])
            time.sleep(2.0)  # In case of error retry after 2.0 seconds
            continue
        time.sleep(DELAY_SECONDS)