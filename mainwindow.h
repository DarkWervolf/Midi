#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "midiplayer.h"

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
    void openFileDialog();
    void playFile();
    void moveSlider(int value);

private:
    Ui::MainWindow *ui;
    QMidiFile* midiFile;
    QMidiOut* midiOut;
    MidiPlayer* player;
    QString filename;
};

#endif // MAINWINDOW_H
