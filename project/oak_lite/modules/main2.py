import time, event

@event.start
def start():
    print("system app start")
    time.sleep(0.1)

@event.button_pressed
def is_button_pressed():
    print("is_button_pressed")
    time.sleep(0.1)