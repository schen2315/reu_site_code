/* GStreamer
 * Copyright (C) 2008 Wim Taymans <wim.taymans at gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

int
main (int argc, char *argv[])
{
  GMainLoop *loop;
  GstRTSPServer *server;
  GstRTSPMountPoints *mounts;
  GstRTSPMediaFactory *factory;

  gst_init (&argc, &argv);

  loop = g_main_loop_new (NULL, FALSE);

  /* create a server instance */
  server = gst_rtsp_server_new ();

  /* get the mount points for this server, every server has a default object
   * that be used to map uri mount points to media factories */
  mounts = gst_rtsp_server_get_mount_points (server);

  /* make a media factory for a test stream. The default media factory can use
   * gst-launch syntax to create pipelines. 
   * any launch line works as long as it contains elements named pay%d. Each
   * element with pay%d names will be a stream */
  factory = gst_rtsp_media_factory_new ();
  /*
  gst_rtsp_media_factory_set_launch (factory,
      "( videotestsrc is-live=1 ! x264enc ! rtph264pay name=pay0 pt=96 )");
  */
/*
  gst_rtsp_media_factory_set_launch (factory,
      "( v4l2src is-live=1 device=/dev/video1 ! video/x-raw,framerate=30/1,width=2560,height=720 ! omxvp8enc ! rtpvp8pay name=pay0 pt=96 )");
*/
/*
  gst_rtsp_media_factory_set_launch (factory,
      "( v4l2src is-live=1 device=/dev/video1 ! video/x-raw,framerate=30/1,width=2560,height=720 ! omxh264enc ! rtph264pay name=pay0 pt=96 )");
*/
/*
  gst_rtsp_media_factory_set_launch (factory,
      "( v4l2src is-live=1 device=/dev/video1 ! video/x-raw,framerate=30/1,width=1344,height=376 ! omxh264enc ! rtph264pay name=pay0 pt=96 )");

*/


//doesn't work
/*
  gst_rtsp_media_factory_set_launch (factory,
      "( v4l2src device=/dev/video1 ! video/x-raw,framerate=30/1,width=3840,height=1080 ! tee name=t ! queue ! nvvidconv ! 'video/x-raw(memory:NVMM), width=3840, height=1080, format=I420' !  omxh264enc bitrate=40000000 ! h264parse ! qtmux ! filesink location=stream_while_recording5.mp4 sync=false t. ! queue ! videoscale ! video/x-raw,width=1280,height=360 ! omxh264enc ! rtph264pay name=pay0 pt=96 -e -vvv )");
*/
/*
  gst_rtsp_media_factory_set_launch (factory,
      "( v4l2src device=/dev/video1 ! video/x-raw,framerate=30/1,width=3840,height=1080 ! tee name=t ! queue ! omxh264enc ! rtph264pay name=pay0 pt=96 t. ! queue ! videoscale ! video/x-raw,width=1280,height=360 ! omxh264enc ! rtph264pay name=pay1 pt=96 -e -vvv )");
*/
/*
  gst_rtsp_media_factory_set_launch (factory,
      "( v4l2src device=/dev/video1 ! video/x-raw,framerate=30/1,width=3840,height=1080 ! tee name=t ! queue ! omxh264enc ! rtph264pay name=pay0 pt=96 t. ! nvvidconv ! 'video/x-raw(memory:NVMM), width=3840, height=1080, format=I420' !  omxh264enc bitrate=40000000 ! h264parse ! qtmux ! filesink location=stream_while_recording6.mp4 sync=false -e -vvv )");
*/
/*
  gst_rtsp_media_factory_set_launch (factory,
      "( v4l2src device=/dev/video1 ! video/x-raw,framerate=30/1,width=3840,height=1080 ! omxh264enc ! rtph264pay name=pay0 pt=96  -e -vvv )");
*/
/*
//actually works
gst_rtsp_media_factory_set_launch (factory,
      "( v4l2src device=/dev/video1 ! video/x-raw,framerate=30/1,width=3840,height=1080 ! tee name=t ! queue ! xvimagesink t. ! queue ! videoscale ! video/x-raw,width=1280,height=360 ! omxh264enc ! rtph264pay name=pay0 pt=96 )");
*/

gst_rtsp_media_factory_set_launch (factory,
      "( v4l2src device=/dev/video0 ! tee name=t ! queue !  videorate ! jpegenc ! avimux  ! filesink location=video0_s3.mp4 t. ! queue  ! jpegenc ! rtpjpegpay name=pay0 pt=96 -vvv)");


/*
gst_rtsp_media_factory_set_launch (factory,
      "( v4l2src device=/dev/video1 ! video/x-raw,framerate=30/1,width=3840,height=1080 ! videoscale ! video/x-raw,width=1280,height=360 ! omxh264enc ! rtph24pay name=pay0 pt=96 )");
*/
  gst_rtsp_media_factory_set_shared (factory, TRUE);

  /* attach the test factory to the /test url */
  gst_rtsp_mount_points_add_factory (mounts, "/test", factory);

  /* don't need the ref to the mapper anymore */
  g_object_unref (mounts);

  /* attach the server to the default maincontext */
  gst_rtsp_server_attach (server, NULL);

  /* start serving */
  g_print ("stream ready at rtsp://127.0.0.1:8554/test\n");
  g_main_loop_run (loop);

  return 0;
}
