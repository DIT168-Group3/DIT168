## Simple web-based signal viewer

This example encapsulates a simple JavaScript-enabled web-based viewer for messages exchanged in an OD4Session.
To run this example run the script.sh file.

```
./script.sh
```

The Docker image is provided for amd64 platforms. To change to a different CID session, simply provide a different parameter in the script.sh file "--cid='YourChannel'"

```
docker run --rm -ti --net=host -p 8085:8085 webgui --cid=111
```

If the port 8085 is occupied by some program on your machine than change --port parameter at the last line of the Dockerfile.
```
ENTRYPOINT ["/opt/bin/websocketd", "--staticdir=/opt/signal-viewer", "--port=YOURPORT", "--binary=true", "/bin/cluon-OD4toStdout"]

```
To change the messages that this application can understand, simply modify the messages.odvd (or let it dynamically load from somewhere :-)

