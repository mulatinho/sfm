FROM debian:bookworm-slim
WORKDIR /usr/src/sfm

RUN apt-get update -y \
  && apt-get install -y build-essential libxml2-dev libgtk2.0-dev libglib2.0-dev libsmbclient-dev ncurses-dev

COPY . .

RUN ./autogen.sh && ./configure && make
