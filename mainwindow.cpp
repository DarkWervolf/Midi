#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaPlayerControl>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), midiPlayer(0), check(0), paused(false), pos(0)
{
    ui->setupUi(this);
    connect(ui->openMidiButton, SIGNAL(clicked(bool)), this, SLOT(openMidiFileDialog()));
    connect(ui->playMidiButton, SIGNAL(clicked(bool)), this, SLOT(playMidi()));
    connect(ui->openAudioButton, SIGNAL(clicked(bool)), this, SLOT(openAudioFileDialog()));
    connect(ui->playAudioButton, SIGNAL(clicked(bool)), this, SLOT(playAudio()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(stopAudio()));
    connect(ui->pauseAudioButton, SIGNAL(clicked(bool)), this, SLOT(pauseAudio()));
    connect(ui->stopMidiButton, SIGNAL(clicked(bool)), this, SLOT(stopMidi()));
    audioPlayer = new QMediaPlayer;
    connect(audioPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(moveAudioSlider(qint64)));

    QMidiOut* midi_out = new QMidiOut();
    midi_out->connect(QMidiOut::devices().firstKey());
    midiPlayer = new MidiPlayer(midi_out);
    connect(midiPlayer, SIGNAL(eventChanged(int)), this, SLOT(moveMidiSlider(int)));
}

MainWindow::~MainWindow()
{
    delete midiPlayer;
    delete audioPlayer;
    delete ui;
}

void MainWindow::openMidiFileDialog()
{
    midiFilename = QFileDialog::getOpenFileName(this, "Open Image", "", "MIDI Files (*.midi *.mid)");
    ui->filenameEdit->setText(midiFilename);
}

void MainWindow::playMidi()
{
    stopAudio();
    stopMidi();
    if (!midiFilename.isEmpty()) {
        midiFile = new QMidiFile;
        midiFile->load(midiFilename);
        ui->fileSlider->setMaximum(midiFile->events().size());
        ui->fileSlider->setValue(0);
        midiPlayer->setMidiFile(midiFile);
        midiPlayer->start();
   }
}

void MainWindow::stopMidi()
{
    midiPlayer->stop();
    ui->fileSlider->setValue(0);
}

void MainWindow::openAudioFileDialog()
{
    audioFilename = QFileDialog::getOpenFileName(this, "Open Image", "", "Audio Files (*.mp3 *.wav)");
    ui->filenameEdit->setText(audioFilename);
}

void MainWindow::playAudio()
{
    stopAudio();
    stopMidi();
    if(!audioFilename.isEmpty()){
        audioPlayer->setMedia(QUrl::fromLocalFile(audioFilename));
        audioPlayer->play();
    }
}

void MainWindow::stopAudio()
{
    audioPlayer->stop();
}

void MainWindow::pauseAudio()
{
    if (audioPlayer->state() == QMediaPlayer::PlayingState){
        audioPlayer->pause();
    }
    else if (audioPlayer->state() == QMediaPlayer::PausedState){
        audioPlayer->play();
    }
}

void MainWindow::moveMidiSlider(int value)
{
    ui->fileSlider->setValue(value);
}

void MainWindow::moveAudioSlider(qint64 value)
{
    ui->fileSlider->setMaximum(audioPlayer->duration());
    ui->fileSlider->setValue(value);
}
