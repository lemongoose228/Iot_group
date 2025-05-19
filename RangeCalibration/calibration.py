import serial
import time
import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.preprocessing import PolynomialFeatures

PORT = 'COM4'
BAUD = 9600
MIN_DIST = 10
MAX_DIST = 30
POLY_DEGREE = 3
SAMPLES_NEEDED = 50

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

def fit_model(ir_values, distances, degree):
    poly = PolynomialFeatures(degree)
    X_poly = poly.fit_transform(ir_values.reshape(-1, 1))
    model = LinearRegression().fit(X_poly, distances)
    return model, poly

def show_plot(ir_values, distances, model, poly):
    ir_sorted = np.sort(ir_values)
    X_plot = poly.transform(ir_sorted.reshape(-1, 1))
    y_plot = model.predict(X_plot)

    plt.scatter(ir_values, distances, color='red', label='Измерения')
    plt.plot(ir_sorted, y_plot, color='blue', label=f'Полином степени {POLY_DEGREE}')
    plt.xlabel('IR-сигнал')
    plt.ylabel('Расстояние (см)')
    plt.title('Калибровка инфракрасного датчика')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()

def convert(ir_value, model, poly):
    transformed = poly.transform([[ir_value]])
    return model.predict(transformed)[0]

if __name__ == "__main__":
    ir_vals, dist_vals = collect_data(MIN_DIST, MAX_DIST)
    model, poly = fit_model(ir_vals, dist_vals, POLY_DEGREE)
    show_plot(ir_vals, dist_vals, model, poly)

    example = 500
    result = convert(example, model, poly)
    print(f"IR={example} => Расстояние ≈ {result:.2f} см")
