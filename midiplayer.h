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
    MidiPlayer(QMidiOut* out);
    ~MidiPlayer();
    void stop();
    void setMidiFile(QMidiFile* file);
private:
    enum states {STOPPED, PLAYING};
    QMidiFile* midi_file;
    QMidiOut* midi_out;
    int state;
protected:
    void run();
signals:
    void eventChanged(int);
};

#endif // MIDIPLAYER_H
