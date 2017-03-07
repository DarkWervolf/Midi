#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QMidiFile.h>
#include <QMidiOut.h>
#include <QThread>
#include <QElapsedTimer>

class MidiPlayer : public QThread
{
    Q_OBJECT
public:
    MidiPlayer(QMidiFile* file, QMidiOut* out);
    void stop();
private:
    QMidiFile* midi_file;
    QMidiOut* midi_out;
protected:
    void run();
signals:
    void eventChanged(int);
};

#endif // MIDIPLAYER_H
