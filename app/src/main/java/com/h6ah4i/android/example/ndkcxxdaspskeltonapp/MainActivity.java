package com.h6ah4i.android.example.ndkcxxdaspskeltonapp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.h6ah4i.android.example.ndklibrary.MyNdkLibrary;
import com.h6ah4i.android.example.ndklibrary.cxxdasp.FFTReal;

public class MainActivity extends AppCompatActivity {

    private TextView textView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.buttonFft).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                doFft();
            }
        });

        this.textView = (TextView) findViewById(R.id.text);

        MyNdkLibrary.loadModule();
    }

    private void doFft() {
        FFTReal fft = null;
        long startTime = 0, endTime = 0;
        try {
            fft = new FFTReal();
            fft.setup(1024);

            float[] input = new float[fft.inputBufferSize()];

            for (int i = 0; i < input.length; i++) {
                input[i] = (float) Math.sin((Math.PI * 2 / 32) * i);
            }
            float[] output = new float[fft.outputBufferSize()];

            startTime = System.nanoTime();
            fft.doFft(input, output);
            endTime = System.nanoTime();
        } finally {
            if (fft != null) {
                fft.release();
            }
        }

        this.textView.setText("TIME: " + ((endTime - startTime) / 1000) + " us");
    }
}
