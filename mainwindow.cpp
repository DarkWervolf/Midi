#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openButton, SIGNAL(clicked(bool)), this, SLOT(openFileDialog()));
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(playFile()));
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

void MainWindow::moveSlider(int value)
{
    ui->fileSlider->setValue(value);
}
