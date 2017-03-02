#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaPlayerControl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openButton, SIGNAL(clicked(bool)), this, SLOT(openFileDialog()));
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(playFile()));
    connect(ui->openButton1, SIGNAL(clicked(bool)), this, SLOT(openFileDialog1()));
    connect(ui->playButton1, SIGNAL(clicked(bool)), this, SLOT(playAudio()));
    connect(ui->stopButton, SIGNAL(clicked(bool)), this, SLOT(stopAudio()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileDialog()
{
    filename = QFileDialog::getOpenFileName(this, "Open Image", "", "MIDI Files (*.midi *.mid)");
    ui->filenameEdit->setText(filename);
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

void MainWindow::openFileDialog1()
{
    filename1 = QFileDialog::getOpenFileName(this, "Open Image", "", "Audio Files (*.mp3 *.waw)");
    ui->filenameEdit->setText(filename1);
}

void MainWindow::playAudio()
{
    if(!filename1.isEmpty()){
        player1 = new QMediaPlayer();
        playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl(filename1));
        playlist->setCurrentIndex(1);
        player1->setPlaylist(playlist);
        player1->play();
    }
}

void MainWindow::stopAudio()
{
    player1->stop();
}

void MainWindow::moveSlider(int value)
{
    ui->fileSlider->setValue(value);
}
