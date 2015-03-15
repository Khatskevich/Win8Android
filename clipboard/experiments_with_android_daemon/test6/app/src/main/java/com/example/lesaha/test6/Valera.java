package com.example.lesaha.test6;

import android.app.IntentService;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.widget.Toast;

/**
 * Created by lesaha on 12.03.15.
 */

public class Valera extends IntentService {
    private Handler handler = new Handler();
    public Valera() {
        super("Name for Service");
    }

    @Override
    protected void onHandleIntent(Intent workIntent) {

        // Gets data from the incoming Intent
        String dataString = workIntent.getDataString();
    int i = 0;
        while(1>0) {
            i++;
            ClipboardManager clipboard = (ClipboardManager) this.getApplicationContext().getSystemService(Context.CLIPBOARD_SERVICE);
            ClipData clip = ClipData.newPlainText("simple text", "Hello, World"+i);
            clipboard.setPrimaryClip(clip);
            //Toast.makeText(this , "this is my Toast message!!! =)",  Toast.LENGTH_LONG).show();
            handler.post(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(getApplicationContext(), "import finished", Toast.LENGTH_SHORT).show();
                }
            });

            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}