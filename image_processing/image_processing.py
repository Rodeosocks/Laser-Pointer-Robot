import cv2
import numpy as np
import requests
import helper_functions as f

# URL of the ESP32-CAM capture endpoint
esp32_cam_url = 'http://192.168.86.35/capture' # <-- REPLACE with your ESP32-CAM's IP address

# # --- COLOR TRACKING SETUP ---
# # Define the lower and upper bounds of the color you want to track in RBG.
# # R = Red (0-255), B = Blue (0-255), G = Green (0-255)
# lower = np.array([230, 230, 180])
# upper = np.array([255, 255, 255])

# # Convert bounds to HSV
# # H = Hue (0-179), S = Saturation (0-255), V = Value/Brightness (0-255)
# lower = f.RGB2HSV(lower)
# upper = f.RGB2HSV(upper)
# # -----------------------------

def nothing(x):
    # Dummy function for trackbar creation
    pass

# Create a window for the controls
cv2.namedWindow("Controls")
cv2.resizeWindow("Controls", 500, 300)

# Create trackbars for H, S, V lower and upper bounds
cv2.createTrackbar("H-Min", "Controls", 0, 179, nothing)
cv2.createTrackbar("S-Min", "Controls", 0, 255, nothing)
cv2.createTrackbar("V-Min", "Controls", 0, 255, nothing)
cv2.createTrackbar("H-Max", "Controls", 179, 179, nothing)
cv2.createTrackbar("S-Max", "Controls", 255, 255, nothing)
cv2.createTrackbar("V-Max", "Controls", 255, 255, nothing)

# --- Set initial trackbar positions (optional, using previous green example) ---
cv2.setTrackbarPos("H-Min", "Controls", 35)
cv2.setTrackbarPos("S-Min", "Controls", 80)
cv2.setTrackbarPos("V-Min", "Controls", 80)
cv2.setTrackbarPos("H-Max", "Controls", 85)
cv2.setTrackbarPos("S-Max", "Controls", 255)
cv2.setTrackbarPos("V-Max", "Controls", 255)
# --------------------------------------------------------------------------

# Create windows to display the video feed and the mask
cv2.namedWindow('ESP32-CAM Feed', cv2.WINDOW_NORMAL)
cv2.namedWindow('Mask', cv2.WINDOW_NORMAL)

while True:
    try:
        # Send an HTTP GET request to the ESP32-CAM
        response = requests.get(esp32_cam_url, timeout=5)

        if response.status_code == 200:
            # Convert the image data to a NumPy array
            img_array = np.array(bytearray(response.content), dtype=np.uint8)
            frame = cv2.imdecode(img_array, -1)

            # --- COLOR TRACKING LOGIC ---

            # 1. Convert the frame to the HSV color space
            hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

            # 2. Get current positions of all trackbars
            h_min = cv2.getTrackbarPos("H-Min", "Controls")
            s_min = cv2.getTrackbarPos("S-Min", "Controls")
            v_min = cv2.getTrackbarPos("V-Min", "Controls")
            h_max = cv2.getTrackbarPos("H-Max", "Controls")
            s_max = cv2.getTrackbarPos("S-Max", "Controls")
            v_max = cv2.getTrackbarPos("V-Max", "Controls")

            # 3. Create the lower and upper HSV bounds from trackbar values
            lower_bound = np.array([h_min, s_min, v_min])
            upper_bound = np.array([h_max, s_max, v_max])

            # 4. Create a mask for the specified color range
            mask = cv2.inRange(hsv_frame, lower_bound, upper_bound)
            
            # Optional: Apply morphological operations to reduce noise
            mask = cv2.erode(mask, None, iterations=2)
            mask = cv2.dilate(mask, None, iterations=2)

            # 5. Find contours (outlines) of the colored objects in the mask
            contours, _ = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

            # Only proceed if at least one contour was found
            if len(contours) > 0:
                # 6. Find the largest contour by area
                largest_contour = max(contours, key=cv2.contourArea)
                
                # 7. Get the minimum enclosing circle's position and radius
                ((x, y), radius) = cv2.minEnclosingCircle(largest_contour)

                # Only draw the circle if the radius meets a minimum size
                if radius > 10:
                    # Draw the circle on the original frame
                    cv2.circle(frame, (int(x), int(y)), int(radius), (0, 255, 255), 2)
                    # Draw a center point
                    cv2.circle(frame, (int(x), int(y)), 5, (0, 0, 255), -1)
            
            # --- END OF COLOR TRACKING LOGIC ---

            # Display the resulting frame and the mask
            cv2.imshow('ESP32-CAM Feed', frame)
            cv2.imshow('Mask', mask)

        else:
            print(f"Failed to get frame: HTTP {response.status_code}")
            cv2.waitKey(1000)

    except requests.exceptions.RequestException as e:
        print(f"Request failed: {e}")
        cv2.waitKey(1000)

    # Change the key to quit from 'q' to the Escape key (ASCII 27)
    key = cv2.waitKey(1) & 0xFF
    if key == 27:
        break

# Clean up
cv2.destroyAllWindows()