import numpy as np

def RGB2HSV(RGB):
    RGB_norm = RGB / 255
    C_max = max(RGB_norm)
    C_min = min(RGB_norm)
    delta = C_max - C_min

    if delta == 0:
        H = 0
    elif C_max == RGB_norm[0]:
        H = 60 * (((RGB_norm[1] - RGB_norm[2]) / delta) + 6)
    elif C_max == RGB_norm[1]:
        H = 60 * (((RGB_norm[2] - RGB_norm[0]) / delta) + 2)
    elif C_max == RGB_norm[2]:
        H = 60 * (((RGB_norm[0] - RGB_norm[1]) / delta) + 4)
    
    if C_max == 0:
        S = 0
    else:
        S = delta / C_max
    S *= 255

    V = C_max
    V *= 255

    return np.array([H, S, V])