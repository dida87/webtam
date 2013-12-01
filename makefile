rm -f pulse_play pulse_record
gcc  -o pulse_play pulse_play.c -lpulse -lpulse-simple
gcc  -o pulse_record pulse_record.c -lpulse -lpulse-simple
