import serial
import time
responces = {
    'd': 7, 
    'u': 6,
    'p': 4 
} 
port_led = "COM5" 
port_photo = "COM5"

connection_led = serial.Serial(port_led, timeout=1)
connection_photo = serial.Serial(port_photo, timeout=1)

def send_command(
        cmd: str,
        response_len: int,
        connection: serial.Serial) -> str:
    str_resp = ""
    connection.write(cmd.encode())
    if response_len > 0:
        resp: bytes = connection.read(response_len)
        str_resp = resp.decode()
    return str_resp

while True:
    photo_val_resp: str = send_command('p', responces['p'], connection_photo)
    photo_val = int(photo_val_resp)
    if photo_val > 500:
        resp = send_command('u', responces['u'], connection_led)
    else:
        resp = send_command('d', responces['d'], connection_led)

