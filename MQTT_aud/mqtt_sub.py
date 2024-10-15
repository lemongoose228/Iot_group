import time
import paho.mqtt.client as mqtt_client
from uuid import getnode as get_mac
import hashlib
import serial

port_led = "COM16"
connection_led = serial.Serial(port_led, timeout=1)

broker = "broker.emqx.io"
pub_id = "bc27bob771"

responses = {
    'd': 7,
    'u': 6,
    'p': 4
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


if not pub_id:
    raise RuntimeError("Publisher id is not defined")

h = hashlib.new('sha256')
mac = get_mac()
h.update(str(mac).encode())
sub_id = h.hexdigest()[10:20]

def on_message(client, userdata, message):
    data = str(message.payload.decode("utf-8"))
    photo_val = int(data)
    if photo_val and len(str(photo_val)) != 0:
        print("photo_val_resp", photo_val)
        print("photo_val", photo_val)
        if photo_val > 500:
            resp = send_command('u', responses['u'], connection_led)
        else:
            resp = send_command('d', responses['d'], connection_led)
        time.sleep(1)
    else:
        print("Получена пустая строка")

client = mqtt_client.Client(
    mqtt_client.CallbackAPIVersion.VERSION2,
    sub_id
)

client.on_message=on_message

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()
print("Subscribing")
client.subscribe(f"lab/46e01e253e/led/state")
time.sleep(1800)
client.disconnect()
client.loop_stop()
