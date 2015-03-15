package com.example.lesaha.test5;

import android.app.IntentService;
import android.app.Service;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

import static java.lang.Thread.*;

/**
 * Created by lesaha on 12.03.15.
 */
public class Valera extends IntentService {


    public Valera() {
        super("Name for Service");
    }

    @Override
    protected void onHandleIntent(Intent workIntent) {
        // Gets data from the incoming Intent
        String dataString = workIntent.getDataString();

        while(1>0) {
            ClipboardManager clipboard = (ClipboardManager) this.getApplicationContext().getSystemService(Context.CLIPBOARD_SERVICE);
            ClipData clip = ClipData.newPlainText("simple text", "Hello, Woeeeeeeeeeerld1!");
            clipboard.setPrimaryClip(clip);
            Toast.makeText(getApplicationContext(), "this is my Toast message!!! =)",
                    Toast.LENGTH_LONG).show();
            try {
                Thread.sleep(5000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}