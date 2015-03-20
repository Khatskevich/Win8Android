package com.example.lesaha.clipchangedlistener;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by lesaha on 20.03.15.
 */
public class Utility {
    public static void showToastMessage(Context context, String message, int duration){
        Toast.makeText(context, message, duration).show();

    }
}
