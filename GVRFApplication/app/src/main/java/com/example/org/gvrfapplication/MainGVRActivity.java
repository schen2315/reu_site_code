package com.example.org.gvrfapplication;

import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.os.Bundle;

import org.gearvrf.GVRActivity;
import org.gearvrf.GVRAndroidResource;
import org.gearvrf.GVRContext;
import org.gearvrf.GVRExternalTexture;
import org.gearvrf.GVRMain;
import org.gearvrf.GVRMesh;
import org.gearvrf.GVRRenderPass;
import org.gearvrf.GVRScene;
import org.gearvrf.GVRSceneObject;
import org.gearvrf.GVRTexture;
import org.gearvrf.scene_objects.GVRVideoSceneObject;
import org.gearvrf.scene_objects.GVRVideoSceneObjectPlayer;
import org.gearvrf.utility.Log;

import java.io.IOException;

public class MainGVRActivity extends GVRActivity {

    private static final String TAG = "GVRFApplication";
    private GVRScene mScene = null;
    GVRSceneObject screen = null;
    private GVRVideoSceneObjectPlayer<MediaPlayer> player;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setMain(new Main(), "gvr.xml");
    }

    private final class Main extends GVRMain {
        @Override
        public void onInit(GVRContext gvrContext) throws Throwable {
            mScene = gvrContext.getMainScene();
            //each param takes on values from 0 - 1 (not 0 - 255)
            mScene.getMainCameraRig().getLeftCamera().setBackgroundColor(0.0f, 0.0f, 0.0f, 1.0f);   //rgba -> black
            mScene.getMainCameraRig().getRightCamera().setBackgroundColor(0.0f, 0.0f, 0.0f, 1.0f);  //rgba -> black
            /*
                GVRTexture texture = gvrContext.getAssetLoader().loadTexture(new GVRAndroidResource(gvrContext, R.drawable.headtrackingpointer));
                GVRSceneObject quad = new GVRSceneObject(gvrContext, 1, 1, texture);
                quad.getTransform().setPosition(0, 0, -3);
                // keeps the object centered in front of the camera
                mScene.getMainCameraRig().addChildObject(quad);
            */
            //player
            player = makeMediaPlayer(gvrContext, "tx2_zed_sample20.mp4");
            // screen
            GVRMesh screenMesh = gvrContext.getAssetLoader().loadMesh(new GVRAndroidResource(
                    gvrContext, "multiplex/screen.obj"));
            GVRExternalTexture screenTexture = new GVRExternalTexture(gvrContext);
            screen = new GVRVideoSceneObject(gvrContext, screenMesh, player,
                    screenTexture, GVRVideoSceneObject.GVRVideoType.HORIZONTAL_STEREO);
            screen.getRenderData().setCullFace(GVRRenderPass.GVRCullFaceEnum.None);
            //center the screen in front of the camera
            mScene.getMainCameraRig().addChildObject(screen);
        }

        @Override
        public SplashMode getSplashMode() {
            return SplashMode.NONE;
        }

        @Override
        public void onStep() {
        }

        private GVRVideoSceneObjectPlayer<MediaPlayer> makeMediaPlayer(GVRContext context, String file) {
            final MediaPlayer mediaPlayer = new MediaPlayer();
            //final AssetFileDescriptor afd;

            try {
                //afd = context.getContext().getAssets().openFd(file);
                //android.util.Log.d(TAG, "Assets was found.");
                //mediaPlayer.setDataSource(afd.getFileDescriptor(), afd.getStartOffset(), afd.getLength());
                mediaPlayer.setDataSource("rtsp://10.0.0.36:8554/test");
                android.util.Log.d(TAG, "DataSource was set.");
                //afd.close();
                mediaPlayer.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                    @Override
                    public void onPrepared(MediaPlayer mp) {
                        Log.d(TAG, "onPrepared");
                        mediaPlayer.start();
                    }
                });
                mediaPlayer.prepareAsync();
                android.util.Log.d(TAG, "video prepared");
            } catch (IOException e) {
                e.printStackTrace();
                android.util.Log.e(TAG, "Assets were not loaded. Stopping application!", e);
                return null;
            }

            mediaPlayer.setLooping(true);
            android.util.Log.d(TAG, "starting player.");

            return GVRVideoSceneObject.makePlayerInstance(mediaPlayer);
        }
    }
}
