#include "midiplayer.h"

MidiPlayer::MidiPlayer(QMidiOut* out) : midi_file(0), midi_out(out), state(STOPPED)
{
}

MidiPlayer::~MidiPlayer()
{
    stop();
}

void MidiPlayer::run()
{
    if (!midi_file) {
        return;
    }
    QElapsedTimer t;
    t.start();
    QList<QMidiEvent*> events = midi_file->events();
    int eventNumber = 0;
    state = PLAYING;
    for (QMidiEvent* e : events) {
        if (state != PLAYING) {
            break;
        }
        if (e->type() != QMidiEvent::Meta) {
            qint64 event_time = midi_file->timeFromTick(e->tick()) * 1000;

            qint32 waitTime = event_time - t.elapsed();
            if (waitTime > 0) {
                msleep(waitTime);
            }
            if (e->type() == QMidiEvent::SysEx) {
                // TODO: sysex
            } else {
                qint32 message = e->message();
                midi_out->sendMsg(message);
                emit eventChanged(++eventNumber);
            }
        }
    }
    
    midi_out->disconnect();
    delete midi_file;
}

void MidiPlayer::stop()
{
    state = STOPPED;
}

void MidiPlayer::setMidiFile(QMidiFile* file)
{
    midi_file = file;
}

