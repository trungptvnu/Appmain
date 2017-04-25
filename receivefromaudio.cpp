/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "receivefromaudio.h"
#include <QFileDialog>
#include <QBuffer>
#include <QtCore/QDebug>
#include "thread.h"
#include "sendtoaudio.h"
#include "QTimer"
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QSound>



ReceiveFromAudio::ReceiveFromAudio()
{

}

ReceiveFromAudio::~ReceiveFromAudio()
{

}


void ReceiveFromAudio::readSharedMemory(QString server)
{
    sharedMemory.setKey(server);
    if (!sharedMemory.attach())
    {
        return ;
    }

    QBuffer buffer;
    QDataStream in(&buffer);
    QString string;

    sharedMemory.lock();
    buffer.setData((char*)sharedMemory.constData(), sharedMemory.size());
    buffer.open(QBuffer::ReadOnly);
    in >>string;
    sharedMemory.unlock();

     if (string=="play")
     {   
         emit musicIsPlayed("played");
         qDebug()<<string;
         qDebug()<< "Music is playing now";  
     }
     else if (string=="stop")
     {
         emit musicIsStopped ("stopped");
         qDebug()<<string;
         qDebug()<< "Music is stopping";
     }
     else if (string =="next")
     {
         emit musicIsNexted ("nexted");
         qDebug()<<string;
         qDebug()<< "Music is nextting";
     }
     else if  (string == "add")
     {
         emit musicAddPlaylist ("added");
         qDebug()<<string;
         qDebug()<< "add play list from device";
     }
     else if (string == "pause")
     {
         emit musicIsPaused ("paused");
         qDebug()<<string;
          qDebug()<< "Pause music";
     }
     else if (string =="climate")
     {
         emit runClimate ("runclimate");
         qDebug()<<string;
     }
     buffer.close();
}
void ReceiveFromAudio::run()
{
   while (true)
    {       
        this -> readSharedMemory("server1");
    //    sleep(2);
        this -> readSharedMemory("server2");
   //     sleep(2);
        this -> readSharedMemory("server3");
   //     sleep(2);
        this -> readSharedMemory("server4");
    //     sleep(2);
         this -> readSharedMemory("server5");
    //     sleep(2);
          this -> readSharedMemory("server6");
        sleep(1);
    }
}

