import time, sensor, image
sensor.reset()
#sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA)

face_cascade = image.HaarCascade("frontalface", stages=25)

# FPS clock
clock = time.clock()

while True:
    clock.tick()
    # Capture snapshot
    start = time.ticks_us()
    snapshot = sensor.snapshot()
    #print("s:%d" %(time.ticks_diff(time.ticks_us(), start)))

    start = time.ticks_us()
    objects = snapshot.find_features(face_cascade, threshold=0.75, scale_factor=1.25)
    #print("f:%d" %(time.ticks_diff(time.ticks_us(), start)))

    # Draw objects
    for r in objects:
        snapshot.draw_rectangle(r)

    print(clock.fps())
