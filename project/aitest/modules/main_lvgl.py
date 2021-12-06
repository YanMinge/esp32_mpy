import lvgl as lv
import lcd, espidf, time, sensor, image
sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.HQVGA)
snapshot = sensor.snapshot()

espidf.test_esp32lvgl()
time.sleep(5)
lcd.set_backlight(1)

scr = lv.obj()
img = lv.img(scr)
img_data = snapshot.to_bytes()
img.align_to(lv.scr_act(), lv.ALIGN.CENTER, -160, -120)
img_dsc = lv.img_dsc_t({
    'header':{
        'always_zero': 0,
        'w':snapshot.width(),
        'h':snapshot.height(),
        'cf':lv.img.CF.TRUE_COLOR
    },
    'data_size': len(img_data),
    'data': img_data
})

lv.scr_load(scr)

print(len(img_data))
print("width")
print(snapshot.width())
print("height")
print(snapshot.height())

btn = lv.btn(scr)
btn.align_to(lv.scr_act(), lv.ALIGN.CENTER, 100, -50)
label = lv.label(btn)
label.set_text("Hello")
lv.scr_load(scr)
face_cascade = image.HaarCascade("frontalface", stages=25)

# FPS clock
clock = time.clock()

while True:
    clock.tick()
    # Capture snapshot
    start = time.ticks_us()
    snapshot = sensor.snapshot()
    print("s:%d" %(time.ticks_diff(time.ticks_us(), start)))

    # Find objects.
    # Note: Lower scale factor scales-down the image more and detects smaller objects.
    # Higher threshold results in a higher detection rate, with more false positives.
    start = time.ticks_us()
    objects = snapshot.find_features(face_cascade, threshold=0.75, scale_factor=1.25)
    print("f:%d" %(time.ticks_diff(time.ticks_us(), start)))

    # Draw objects
    for r in objects:
        print("!!")
        snapshot.draw_rectangle(r)

    # Print FPS.
    # Note: Actual FPS is higher, streaming the FB makes it slower.
    print(clock.fps())

    img_data = snapshot.to_bytes()
    w = snapshot.width()
    h = snapshot.height()
    # snapshot.draw_rectangle((0,0,100,100), fill=True, color=lcd.RED)
    #img_data = snapshot.to_bytes()
    img_dsc = lv.img_dsc_t({
        'header':{
            'always_zero': 0,
            'w': w,
            'h': h,
            'cf':lv.img.CF.TRUE_COLOR
        },
        'data_size': w*h*2,
        'data': img_data 
    })

    img.set_src(img_dsc)
    #img.set_drag(True)
