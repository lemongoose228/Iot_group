import time
import paho.mqtt.client as mqtt_client
import random
from uuid import getnode as ger_mac
import hashlib

import serial

port_photo = "COM5"

connection_photo = serial.Serial(port_photo, timeout=1)

responses = {
    'd': 7, # led_off
    'u': 6, # led_on
    'p': 4 # 0-1023 zero fill to leftside
}

def send_command(cmd: str,
                 response_len: int,
                 connection: serial.Serial) -> str:
    #str_resp = None
    str_resp: str = ""
    connection.write(cmd.encode())
    if response_len > 0:
        resp: bytes = connection.read(response_len)
        str_resp = resp.decode()
    return str_resp



broker='broker.emqx.io'

h = hashlib.new('sha256')
mac = ger_mac()
h.update(str(mac).encode())
pub_id = h.hexdigest()[:10]
print(f"Listen me at is {pub_id}")

client = mqtt_client.Client(
    mqtt_client.CallbackAPIVersion.VERSION2,
    pub_id
)

print("Connecting to broker", broker)
print(client.connect(broker))
client.loop_start()
print("Publishing")

for i in range(100):
    photo_val_resp: str = send_command('p', responses['p'], connection_photo)
    state = photo_val_resp
    print(f"Publishing {state}")
    client.publish(f"lab/{pub_id}/led/state", state)
    time.sleep(2)

client.disconnect()
client.loop_stop()
