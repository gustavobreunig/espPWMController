all:
	platformio run -t upload --upload-port COM4
	platformio serialports monitor -p COM4 -b 115200