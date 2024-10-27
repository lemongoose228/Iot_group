import time
import paho.mqtt.client as mqtt_client
import random
import serial
from uuid import getnode as get_mac
import hashlib
import collections

broker = "broker.emqx.io"

port_photo = "COM4"

def get_id():
    h = hashlib.new('sha256')
    mac = get_mac() + random.randint(1, 10000)
    h.update(str(mac).encode())

    new_id = h.hexdigest()[:10]

    return new_id


def unique_id():
    h = hashlib.new('sha256')
    secret_key = 'skibidi'
    h.update(str(secret_key).encode())

    new_id = h.hexdigest()[:10]

    return new_id


pub_id = get_id()
unique_id = unique_id()

activate_stream_topic = f'lab/{unique_id}/photo/activate_stream'

response = {
    'command': 'p',
    'value': 1
}

delays = {
    'instant': 1,
    'average': 1,
    'stream': 0.5,
    'min&max': 5
}

timers = {
    'instant': time.time(),
    'average': time.time(),
    'stream': time.time(),
    'min&max': time.time()
}

deque = collections.deque()
deque_len = 20


maximum = 0
minimum = 1023


stream_work = False


def on_message(client, userdata, message):
    global stream_work

    if message.topic == activate_stream_topic:
        data = str(message.payload.decode("utf-8"))

        if data == 'on':
            stream_work = True
        elif data == 'off':
            stream_work = False


def instant(value_instant, client_instant):
    if time.time() - timers['instant'] > delays['instant']:
        timers['instant'] = time.time()
        client_instant.publish(f"lab/{unique_id}/photo/instant", value_instant)

        print('instant:', value_instant)
        print()


def average(value_average, client_average):
    global deque

    if time.time() - timers['average'] > delays['average']:
        timers['average'] = time.time()

        if len(deque) != deque_len:
            deque.append(value_average)
            return
        else:
            deque.popleft()
            deque.append(value_average)

        client_average.publish(f"lab/{unique_id}/photo/average", int(sum(deque) / len(deque)))
        print('average:', value_average)
        print()

def stream(value_stream, client_stream):
    if time.time() - timers['stream'] > delays['stream']:
        timers['stream'] = time.time()
        client_stream.publish(f"lab/{unique_id}/photo/stream", value_stream)

        print('stream:', value_stream)
        print()


def min_and_max(value_min_max, client_min_max):
    global minimum
    global maximum

    if time.time() - timers['min&max'] > delays['min&max']:
        timers['min&max'] = time.time()

        if value_min_max > maximum:
            maximum = value_min_max
        elif value_min_max < minimum:
            minimum = value_min_max

        client_min_max.publish(f"lab/{unique_id}/photo/min", minimum)
        client_min_max.publish(f"lab/{unique_id}/photo/max", maximum)
        print('min:', minimum)
        print('max:', maximum)
        print()


def send_command(cmd: str,
                 response_len: int,
                 connection: serial.Serial) -> int:
    str_resp: int = 0
    connection.write(cmd.encode())
    if response_len > 0:
        resp: bytes = connection.read(response_len)
        str_resp = int.from_bytes(resp, 'little')

    return str_resp



print(f"Listen me at id {unique_id}")

client = mqtt_client.Client(
    mqtt_client.CallbackAPIVersion.VERSION2,
    pub_id
)

print("Connecting to broker", broker)
client.connect(broker)
client.loop_start()
client.subscribe(activate_stream_topic)
print("Publishing")

while True:
    value = random.randint(1, 20)

    instant(value, client)
    average(value, client)
    if stream_work:
        stream(value, client)

    min_and_max(value, client)

    time.sleep(0.1)

client.disconnect()
client.loop_stop()
