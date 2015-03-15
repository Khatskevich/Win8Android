package com.example.lesaha.daemontest;


import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class AutoStart extends BroadcastReceiver
{

    public void onReceive(Context context, Intent intent)
    {
        System.out.println ( "Application Started" );
        // put your TimerTask calling class here

        try
        {
            Intent myIntent = new Intent ( context, AutoStartExampleActivity.class );
            myIntent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(myIntent);
        }
        catch ( Exception e )
        {
            System.out.println ( " Error while Starting Activity " + e.toString() );
        }
    }
}