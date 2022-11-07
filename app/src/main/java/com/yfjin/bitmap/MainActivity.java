package com.yfjin.bitmap;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;

import com.yfjin.bitmap.databinding.ActivityMainBinding;

import androidx.appcompat.app.AppCompatActivity;


public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("bitmapJni");
    }

    private ActivityMainBinding binding;

    public static void jump(Context c) {
        c.startActivity(new Intent(c,MainActivity.class));
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        binding.fab.setOnClickListener(v -> load());
        binding.change.setOnClickListener(v -> action());
    }


    Bitmap mBitmap;

    private void load() {
        mBitmap = BitmapFactory.decodeFile("sdcard/223.png");
//        mBitmap=Bitmap.createBitmap(9,9,Bitmap.Config.ARGB_8888);
//        create();
        binding.preview.setImageBitmap(mBitmap);
    }

    private void action() {
        if (mBitmap != null) {
            changeBitmap(mBitmap);
        }
    }

    private void create() {
        Log.d("123123","is:"+mBitmap.isMutable());
        for (int i = 0; i < mBitmap.getHeight(); i++) {
            for (int j = 0; j <mBitmap.getWidth(); j++) {
//                int color=mBitmap.getPixel(i,j);
                if (i<=3){
                    mBitmap.setPixel(j,i, Color.RED);
                }else if(i<7){
                    mBitmap.setPixel(j,i, Color.GREEN);
                }else{
                    mBitmap.setPixel(j,i, Color.BLUE);
                }
            }
        }
//        binding.preview.setImageBitmap(mBitmap);
    }


    private native void changeBitmap(Bitmap b);

}