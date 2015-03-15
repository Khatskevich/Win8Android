package com.example.lesaha.test5;

/**
 * Created by lesaha on 11.03.15.
 */
import android.app.IntentService;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;
import android.widget.Toast;

import static android.support.v4.content.WakefulBroadcastReceiver.startWakefulService;

public class BootReceiver extends BroadcastReceiver{
    @Override
    public void onReceive(Context context, Intent intent) {
        //Log.d("DAVID", "Hi, Boot reciver was catch!");
        //Intent i = new Intent(context, TestReceiversActivity.class);
        //i.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        //context.startActivity(i);
        Toast.makeText(context, "Go go go!!! =)",
                Toast.LENGTH_LONG).show();
        //context.startService( new Intent(context, Valera.class) );
        //startService(new Intent(this, Valera.class));
    }
}