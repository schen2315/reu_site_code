
## Installation Instructions
First make sure gstreamer is installed in your Linux Ubuntu distro. Then do:

`sudo apt-get install gstreamer1.0-plugins-base libgstreamer-plugins-base1.0-dev libgstreamer-plugins-base1.0-0 gstreamer1.0-libav gstreamer1.0-libav-dbg`
 
`apt-cache search gst | grep "good\|bad\|ugly"`

install both the regular and dbg plugins. Then do:

`apt-cache search gst | grep "rtsp"`

if you see libgstrtspserver-1.0-0 (NOT version 0.1) then go ahead and install
otherwise do:
go to here: https://gstreamer.freedesktop.org/src/gst-rtsp-server/
download gst-rtsp-server-1.2.3.tar.xz
extract, go to the directory and do:
`sudo ./configure && make && make install`

Now go back to reu_site_code directory and try:  
  
To view on a Linux x86 pc:
`gst-launch-1.0 -v v4l2src device=/dev/video0 ! xvimagesink`
Press ^C to end the stream  
  
record video
`gst-launch-1.0 -v v4l2src device=/dev/video0 num-buffers=500 ! videorate ! jpegenc ! avimux  ! filesink location=video0_s1.mp4`  
  
view the sample1
`gst-launch-1.0 -v playbin uri=file:/home/song/Code/reu_site_code/video0_s1.mp4`  
  
record while viewing video
`gst-launch-1.0 v4l2src device=/dev/video0 ! tee name=t ! queue ! jpegenc ! avimux  ! filesink location=video0_s2.mp4 t. ! queue ! xvimagesink`  
  
view sample2
`gst-launch-1.0 -v playbin uri=file:/home/song/Code/reu_site_code/video0_s2.mp4`  
  
test video0 over streaming + recording
`make video0`  
  
then in another terminal
`gst-launch-1.0 --gst-debug=3 rtspsrc location="rtsp://127.0.0.1:8554/test" latency=100 ! decodebin ! videorate ! autovideosink`  
  
now to play sample3
`gst-launch-1.0 -v playbin uri=file:/home/song/Code/reu_site_code/video0_s3.mp4`  
  
Now if you have the ZED camera plugged in:
`make`  
  
then in another terminal:
`gst-launch-1.0 --gst-debug=3 rtspsrc location="rtsp://127.0.0.1:8554/test" latency=100 ! decodebin ! videorate ! autovideosink`  
  
to get your local network address:
`ifconfig`

under wlan0 next to inet addr is your local network address.
Now replace 127.0.0.1 w/ this address for the new instruction:
`gst-launch-1.0 --gst-debug=3 rtspsrc location="rtsp://${LOCAL_NETWORK_ADDRESS}:8554/test" latency=100 ! decodebin ! videorate ! autovideosink`  
  
  
  
Check out the REU Site Umass Lowell Research Gists from here for details on how to build, run, and understand these projects.

