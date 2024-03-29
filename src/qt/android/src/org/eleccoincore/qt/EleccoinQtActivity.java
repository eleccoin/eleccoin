package org.eleccoincore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class EleccoinQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File eleccoinDir = new File(getFilesDir().getAbsolutePath() + "/.eleccoin");
        if (!eleccoinDir.exists()) {
            eleccoinDir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}
