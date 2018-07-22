#!/usr/bin/python3
import sys
import signal
import serial
from datetime import datetime
import os
import sqlite3
import re

STATUS_DATABASE = "beerwise.sqlite3"

# "beer: 'ab.cd', chamber: 'de.fg', cooling: 'h'"
SERIAL_PARSE_RE = re.compile("beer: '(?P<beer>.*?)', chamber: '(?P<chamber>.*?)', cooling: '(?P<cooling>.)'")

if __name__ == '__main__':
    def exit_handler(signum, frame):
        ser.close()
        dbcon.close()
        print("exiting")
        sys.exit(0)

    def connect_database():
        dbexists = os.path.isfile(STATUS_DATABASE)
        dbcon = sqlite3.connect(STATUS_DATABASE)
        dbcur = dbcon.cursor()
        if not dbexists:
            dbcur.execute('''CREATE TABLE beerstatus (date datetime, beer real, chamber real, cooling boolean)''')
        return (dbcon, dbcur)

    print("connecting to serial")
    serial_port = sys.argv[1] if (len(sys.argv) > 1)  else os.environ["ARDUINOPORT"]
    ser = serial.Serial(serial_port, 57600)

    print("connecting to database")
    dbcon, dbcur = connect_database()

    # exit with ctrl+C or kill
    signal.signal(signal.SIGINT, exit_handler)
    signal.signal(signal.SIGTERM, exit_handler)

    while True:
        line = ser.readline().decode("utf-8").strip()
        print("{} {}".format(datetime.now().isoformat(), line))

        try:
            # dummy line for testing
            # line = "beer: '21.00', chamber: '22.00', cooling: '1'"
            parsed = SERIAL_PARSE_RE.match(line).groupdict()
            # save it into the database
            dbcur.execute('''INSERT INTO beerstatus VALUES (?, ?, ?, ?)''', (datetime.now().isoformat(), parsed['beer'], parsed['chamber'], parsed['cooling']))
            dbcon.commit()
        except Exception as e:
            print("data error: {}".format(e))


