
all:	clean
	gcc test-readme.c -o test-readme.exe -Wall `pkg-config --cflags --libs gstreamer-1.0 gstreamer-rtsp-server-1.0`
	./test-readme.exe

video0:	clean	
	gcc test-video0.c -o test-video0.exe -Wall `pkg-config --cflags --libs gstreamer-1.0 gstreamer-rtsp-server-1.0`
	./test-video0.exe
clean:	
	rm  -f *.exe *~ *.mp4
