import serial
import time
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures

def collect_data(min_dist, max_dist):
    ser = serial.Serial(PORT, BAUD, timeout=1)
    time.sleep(2)

    distances = []
    ir_values = []

    print(f"Сбор данных в диапазоне от {min_dist} до {max_dist} см...")

    while len(distances) < SAMPLES_NEEDED:
        line = ser.readline().decode().strip()
        if "," not in line:
            continue
        try:
            dist, ir = map(float, line.split(','))
            if min_dist <= dist <= max_dist:
                distances.append(dist)
                ir_values.append(ir)
                print(f"{len(distances)} / {SAMPLES_NEEDED}: {dist:.1f} см -> {ir:.0f}")
        except:
            continue

    ser.close()
    return np.array(ir_values), np.array(distances)

