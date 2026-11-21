import random

TRUE_DIST = 100

random.seed(42)

noise_mean = 0
std_deviation = 3

num_readings = 50
estimate = 0

for k in range(1, num_readings + 1):
    noise = random.gauss(noise_mean, std_deviation)
    measurement = TRUE_DIST + noise
    gain_K = 1/k
    estimate = estimate + gain_K * (measurement - estimate)
    print("Measurement: ", measurement, "Gain K: ", gain_K, "Estimate for reading k = ", k, " : ", estimate)

print("Final Estimate: ", estimate)
print("Final Error", estimate - TRUE_DIST)
