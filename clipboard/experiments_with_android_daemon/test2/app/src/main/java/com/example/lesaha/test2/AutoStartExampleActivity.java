package com.example.lesaha.test2;

/**
 * Created by lesaha on 10.03.15.
 */
import android.app.Activity;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.os.Bundle;
import android.os.SystemClock;
import android.widget.Toast;

public class AutoStartExampleActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        while ( 1>0 ) {
            Toast.makeText(this, "Service Started", Toast.LENGTH_LONG).show();
            ClipboardManager clipboard = (ClipboardManager)
                    getSystemService(Context.CLIPBOARD_SERVICE);
            ClipData clip = ClipData.newPlainText("simple text", "Hellofafasdfas, World1!");
            clipboard.setPrimaryClip(clip);
            SystemClock.sleep(1000);
        }
    }
}