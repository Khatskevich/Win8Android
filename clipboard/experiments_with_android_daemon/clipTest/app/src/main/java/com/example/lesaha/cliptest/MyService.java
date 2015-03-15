package com.example.lesaha.cliptest;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.widget.Toast;


/**
 * Created by lesaha on 10.03.15.
 */

public class MyService extends Service{
    @Override
    public IBinder onBind(Intent arg0){
        return null;
    }
    @Override
    public int onStartCommand( Intent intent, int  flags, int startId){
        Toast.makeText(this, "Service Started", Toast.LENGTH_LONG).show();
        return START_STICKY;
    }
    @Override
    public void onDestroy(){
        super.onDestroy();
        Toast.makeText(this, "Service Stopped", Toast.LENGTH_LONG).show();
    }
}
