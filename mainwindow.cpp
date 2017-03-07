#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaPlayerControl>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), check(0), pauseCheck(0), pos(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openButton, SIGNAL(clicked(bool)), this, SLOT(openFileDialog()));
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(playFile()));
    connect(ui->openButton1, SIGNAL(clicked(bool)), this, SLOT(openFileDialog1()));
    connect(ui->playButton1, SIGNAL(clicked(bool)), this, SLOT(playAudio(pos)));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(stopAudio()));
    connect(ui->pauseButton, SIGNAL(clicked(bool)), this, SLOT(pauseAudio()));
    connect(ui->stopMidiButton, SIGNAL(clicked(bool)), this, SLOT(stopMidi()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileDialog()
{
    filename = QFileDialog::getOpenFileName(this, "Open Image", "", "MIDI Files (*.midi *.mid)");
    ui->filenameEdit->setText(filename);
    if(check == 1){
        player1->stop();
        //player->stop();
    }
}

void MainWindow::playFile()
{
    if (!filename.isEmpty()) {
        midiFile = new QMidiFile;
        midiFile->load(filename);
        ui->fileSlider->setMaximum(midiFile->events().size());
        ui->fileSlider->setValue(0);

        QMidiOut* midi_out = new QMidiOut();
        midi_out->connect(QMidiOut::devices().firstKey());

        player = new MidiPlayer(midiFile, midi_out);
        connect(player, SIGNAL(eventChanged(int)), this, SLOT(moveSlider(int)));
        player->start();
   }
}

void MainWindow::stopMidi()
{
    if(!player->isRunning()){
        abort();
    }
    else{
        player->stop();
        ui->fileSlider->setValue(0);
    }
}

void MainWindow::openFileDialog1()
{
    filename1 = QFileDialog::getOpenFileName(this, "Open Image", "", "Audio Files (*.mp3 *.waw)");
    ui->filenameEdit->setText(filename1);
    player1 = new QMediaPlayer();
    playlist = new QMediaPlaylist();
    if(check == 1){
        player1->stop();
        //player->stop();
    }
}

void MainWindow::playAudio(qint64 position)
{
    if(check == 1){
        player1->stop();
        player->stop();
        check = 0;
    }
    if(!filename1.isEmpty()){
        playlist->addMedia(QUrl(filename1));
        playlist->setCurrentIndex(1);
        player1->setPlaylist(playlist);
        connect(player1, SIGNAL(positionChanged(qint64)), this, SLOT(moveSlider1(qint64)));
        check = 1;
        player1->setPosition(position);
        qDebug() << player1->position();
        player1->play();
    }
}

void MainWindow::stopAudio()
{
    if(player1){
        player1->stop();
    }
}

void MainWindow::pauseAudio()
{
    if(pauseCheck == 1){
         playAudio(sizeSong);
    }
    if(pauseCheck == 0){
        pauseCheck = 1;
        sizeSong = player1->position();
        qDebug() << player1->position();
        player1->pause();
        check = 0;
    }
}

void MainWindow::moveSlider(int value)
{
    ui->fileSlider->setValue(value);
}

void MainWindow::moveSlider1(qint64 value)
{
    ui->fileSlider->setMaximum(player1->duration());
    ui->fileSlider->setValue(value);
}
