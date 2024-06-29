FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends wget unzip git make \
  srecord bc xz-utils gcc python3 curl python3-pip python3-dev build-essential python-is-python3 && \
\
  pip3 install -U platformio && \
  pio platform install espressif32 --with-package framework-arduinoespressif32 && \
\
  git clone https://github.com/thorsten-l/CameraControlBT-TDS3P.git && \
  ( cd /CameraControlBT-TDS3P; /usr/local/bin/platformio run ) && \
  rm -fr /CameraControlBT-TDS3P && \
  mkdir /work

WORKDIR /work
