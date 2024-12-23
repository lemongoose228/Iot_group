import time
import paho.mqtt.client as paho

broker = 'broker.emqx.io'
client = paho.Client("client-isu-003")

print("Connecting to broker ", broker)
client.connect(broker)
client.loop_start()
