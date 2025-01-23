import paho.mqtt.client as mqtt
import time


BROKER =  "localhost"           #"broker.hivemq.com"  # Public HiveMQ broker
PORT = 1885                  # Default MQTT port
TOPIC = "temperature/1"      # Topic to publish to


client = mqtt.Client()


try:
    print("Connecting to broker...")
    client.connect(BROKER, PORT, 60)
    print("Connected to HiveMQ broker!")
except Exception as e:
    print(f"Connection failed: {e}")
    exit(1)



try:
    for i in range(100):  # Publish 10 test messages
        MESSAGE = "hello" + str(i)
        client.publish(TOPIC, MESSAGE)
        print(f"Message '{MESSAGE}' published to topic '{TOPIC}'")
        time.sleep(1)  
except Exception as e:
    print(f"Failed to publish message: {e}")


client.disconnect()
print("Disconnected from broker.")
