package com.example.lesaha.test4_remove;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

/**
 * Created by lesaha on 11.03.15.
 */
public class BootReceiver extends BroadcastReceiver
{


    public void onReceive(Context context, Intent intent)
    {

        // Your code to execute when Boot Completd
        Toast.makeText(context, "Booting Completed", Toast.LENGTH_LONG).show();
    }
}