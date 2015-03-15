package com.example.lesaha.test2;

/**
 * Created by lesaha on 10.03.15.
 */
import android.content.BroadcastReceiver;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class AutoStart extends BroadcastReceiver
{

    public void onReceive(Context context, Intent intent)
    {
        System.out.println ( "Application Started" );
        // put your TimerTask calling class here
        //Toast.makeText(context, "Service starting", Toast.LENGTH_LONG).show();
        ClipboardManager clipboard = (ClipboardManager)
                context.getSystemService(Context.CLIPBOARD_SERVICE);
        ClipData clip = ClipData.newPlainText("simple text", "Hellofafasdfas, World1!");
        clipboard.setPrimaryClip(clip);

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