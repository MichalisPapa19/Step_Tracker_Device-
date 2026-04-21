import matplotlib.pyplot as plt
import numpy as np
import scipy.signal as signal
import math
import re


# Συνάρτηση για την εξαγωγή των τιμών από το αρχείο
def extract_values(file_path):
   
    data_XL_YL_ZL = {'XL': [], 'YL': [], 'ZL': []}
    
    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()
            if line.startswith('XL:'):
                data_XL_YL_ZL['XL'].append(float(line.split(':')[1]))
            elif line.startswith('YL:'):
                data_XL_YL_ZL['YL'].append(float(line.split(':')[1]))
            elif line.startswith('ZL:'):
                data_XL_YL_ZL['ZL'].append(float(line.split(':')[1]))
                
            match = re.search(r'Counter_Data:\s*(\d+)', line)
            if match:
             Count = int(match.group(1))
            
    return  data_XL_YL_ZL,Count

# Συνάρτηση για τον υπολογισμό του magnitude
def calculate_magnitude(x, y, z):
    return math.sqrt(x**2 + y**2 + z**2)
def calculate_magnitudexy(x, y):
    return math.sqrt(x**2 + y**2)


# Διαβάζουμε τα δεδομένα από το αρχείο example.txt
file_path = 'example2.txt'
data_XL_YL_ZL,Count = extract_values(file_path)
print(f"Data number is: {Count}")


mag_XL_YL_ZL = [
    calculate_magnitude(x, y, z) 
    for x, y, z in zip(data_XL_YL_ZL['XL'], data_XL_YL_ZL['YL'], data_XL_YL_ZL['ZL'])
]

mag_XL_YL = [
    calculate_magnitudexy(x, y) 
    for x, y in zip(data_XL_YL_ZL['XL'], data_XL_YL_ZL['YL'])
]

avgmag2 = sum(mag_XL_YL) / len(mag_XL_YL)
netmags2 = [(mag2 - avgmag2)**2/Count for mag2 in mag_XL_YL]
peaks2, _ = signal.find_peaks(netmags2, height=900, distance=2)

# Ο χρόνος (σε ms), αυξάνεται ανά 150ms για κάθε σετ μετρήσεων
time = [i * 70 for i in range(len(mag_XL_YL_ZL))]

def filter_close_peaks(peak_times, peak_values, min_distance=700):  
    filtered_peaks = []  # Αποθήκευση των φιλτραρισμένων κορυφών  
    i = 0  

    while i < len(peak_times):  
        current_peak = (peak_times[i], peak_values[i])  
        j = i + 1  

        # Έλεγχος αν υπάρχουν κοντινές κορυφές
        while j < len(peak_times) and (peak_times[j] - peak_times[i] < min_distance):  
            if peak_values[j] > current_peak[1]:  # Αν η νέα κορυφή είναι μεγαλύτερη, αντικαθιστούμε
                current_peak = (peak_times[j], peak_values[j])  
            j += 1  

        filtered_peaks.append(current_peak)  # Αποθήκευση της μεγαλύτερης κορυφής
        i = j  # Προχωράμε στην επόμενη απομακρυσμένη κορυφή  

    return filtered_peaks 

peakXY = filter_close_peaks(np.array(time)[peaks2], np.array(netmags2)[peaks2], min_distance=700)

number_of_Steps = len(peakXY)

# Εκτύπωση των κορυφών (χρόνος, τιμή netmags2)
print("Number Peaks(Time, Net Magnitude XY):")
for peak2 in peakXY:
    print([peak2])
 
 # Διαχωρισμός χρόνου και τιμής κορυφών
filtered_peak_times, filtered_peak_values = zip(*peakXY) 
    
# Δημιουργία διαγράμματος για XL, YL, ZL
plt.figure(figsize=(15, 6))
plt.plot(time, data_XL_YL_ZL['XL'], marker='o', label='XL', color='r')
plt.plot(time, data_XL_YL_ZL['YL'], marker='o', label='YL', color='g')
plt.plot(time, data_XL_YL_ZL['ZL'], marker='o', label='ZL', color='b')
plt.title('XL, YL, ZL σε σχέση με τον Χρόνο')
plt.xlabel('Χρόνος (ms)')
plt.ylabel('Τιμές')
plt.legend()
plt.grid(True)

# Δημιουργία διαγράμματος
plt.figure(figsize=(15, 6))
plt.plot(time, netmags2, label='NET Magnitude XY', color='b')

# Σχεδίαση των φιλτραρισμένων κορυφών
plt.scatter(filtered_peak_times, filtered_peak_values, color='r', marker='x', label='Filtered Peaks')
plt.title('Φιλτραρισμένες Κορυφές - Net Magnitude XY')
plt.xlabel('Χρόνος (ms)')
plt.ylabel('Net Magnitude XY')
plt.legend()
plt.grid(True)
plt.show()

# Εκτύπωση του αριθμού των βημάτων
print(f'Number of steps: {number_of_Steps}')