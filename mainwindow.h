#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "midiplayer.h"
#include "mp3.h"
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
    void playAudio(qint64 position);
    void stopMidi();
    void stopAudio();
    void pauseAudio();
    void openFileDialog();
    void openFileDialog1();
    void playFile();
    void moveSlider(int value);
    void moveSlider1(qint64 value);

private:
    Ui::MainWindow *ui;
    QMidiFile* midiFile;
    QMidiOut* midiOut;
    MidiPlayer* player;
    QMediaPlayer* player1;
    QMediaPlaylist* playlist;
    QString filename1;
    QString filename;
    int check;
    int pauseCheck;
    qint64 sizeSong;
    qint64 pos;
};

#endif // MAINWINDOW_H
