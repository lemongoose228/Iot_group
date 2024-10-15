import serial
import time

responses = {
    'd': 7, # led_off
    'u': 6, # led_on
    'p': 4 # 0-1023 zero fill to leftside
}

#port = "/dev/ttyACM0" #COM4 or similar for windows
#port = "COM12"
port_led = "COM14"
port_photo = "COM12"
#connection = serial.Serial(port, baudrate=9600)
#connection = serial.Serial(port, timeout=1)
connection_led = serial.Serial(port_led, timeout=1)
connection_photo = serial.Serial(port_photo, timeout=1)

def send_command(cmd: str,
                 response_len: int,
                 connection: serial.Serial) -> str:
    #str_resp = None
    str_resp: str = ""
    connection.write(cmd.encode())
    if response_len > 0:
        # connection.in_waiting <-> available
        resp: bytes = connection.read(response_len)
        str_resp = resp.decode()
    return str_resp

while True:
    photo_val_resp: str = send_command('p', responses['p'], connection_photo)
    if photo_val_resp:
        photo_val = int(photo_val_resp)
        print("photo_val_resp", photo_val_resp)
        print("photo_val", photo_val)
        if photo_val > 500:
            resp = send_command('u', responses['u'], connection_led)
        else:
            resp = send_command('d', responses['d'], connection_led)
        time.sleep(1)
    else:
        print("Получена пустая строка")
