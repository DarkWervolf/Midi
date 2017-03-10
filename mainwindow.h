#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "midiplayer.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaPlayerControl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void playAudio();
    void stopMidi();
    void stopAudio();
    void pauseAudio();
    void openMidiFileDialog();
    void openAudioFileDialog();
    void playMidi();
    void moveMidiSlider(int value);
    void moveAudioSlider(qint64 value);

private:
    Ui::MainWindow *ui;
    QMidiFile* midiFile;
    QMidiOut* midiOut;
    MidiPlayer* midiPlayer;
    QMediaPlayer* audioPlayer;
    QMediaPlaylist* playlist;
    QString audioFilename;
    QString midiFilename;
    int check;
    bool paused;
    qint64 sizeSong;
    qint64 pos;
};

#endif // MAINWINDOW_H
