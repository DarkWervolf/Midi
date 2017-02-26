#include "midiplayer.h"

MidiPlayer::MidiPlayer(QMidiFile* file, QMidiOut* out)
{
    midi_file = file;
    midi_out = out;
}

void MidiPlayer::run()
{
    QElapsedTimer t;
    t.start();
    QList<QMidiEvent*> events = midi_file->events();
    int eventNumber = 0;
    for (QMidiEvent* e : events) {
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
}

