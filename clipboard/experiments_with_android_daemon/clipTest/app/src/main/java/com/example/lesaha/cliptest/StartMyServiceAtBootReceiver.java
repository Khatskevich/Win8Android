package com.example.lesaha.cliptest;

import android.content.BroadcastReceiver;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

import static java.security.AccessController.getContext;


/**
 * Created by lesaha on 10.03.15.
 */
public class StartMyServiceAtBootReceiver  extends BroadcastReceiver{


        @Override
        public void onReceive(Context context, Intent intent) {


            ClipboardManager clipboard = (ClipboardManager) context.getSystemService(Context.CLIPBOARD_SERVICE);
            ClipData clip = ClipData.newPlainText("simple text", "Hello, Woeeeeeeeeeerld1!");
            clipboard.setPrimaryClip(clip);

            if ("android.intent.action.BOOT_COMPLETED".equals(intent.getAction())) {
                Intent serviceIntent = new Intent("com.myapp.MySystemService");
                context.startService(serviceIntent);
            }
        }
}