#!/bin/bash

#
# Carrick Detweiler 2022
#

# Run socat in a loop to do the network bridge from the host serial to /dev/tty_serial_bridge
BRIDGE_LOC="/dev/tty_serial_bridge"
while true; do
    echo 
    echo -n "Creating serial bridge to $BRIDGE_LOC ... "
    socat pty,link=$BRIDGE_LOC,rawer tcp:host.docker.internal:7777 > /dev/null 2>&1 &
    PID=$!
    sleep 1
    if [[ -d /proc/$PID ]]; then
        echo "success!"
        echo "Ctrl-C to kill the Docker session"
        echo
        wait $PID
    fi
    echo "serial connection failed."
    echo "Make sure tcp_serial_redirect.py is running on the host computer."
    echo "Will retry connection soon."
    sleep 5
done
