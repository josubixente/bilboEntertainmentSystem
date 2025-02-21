import socket
import cv2
import mediapipe as mp

# Configurar socket UDP
UDP_IP = "127.0.0.1"  # Localhost
UDP_PORT = 5005
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Inicializar MediaPipe Hands
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(min_detection_confidence=0.7, min_tracking_confidence=0.5)

cap = cv2.VideoCapture(0)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        continue

    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = hands.process(rgb_frame)

    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            # Obtener coordenadas del dedo índice (índice 8 en MediaPipe)
            index_finger = hand_landmarks.landmark[8]
            x, y = int(index_finger.x * frame.shape[1]), int(index_finger.y * frame.shape[0])

            # Enviar datos a C
            message = f"{x},{y}".encode()
            sock.sendto(message, (UDP_IP, UDP_PORT))

    cv2.imshow("Hand Tracking", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
