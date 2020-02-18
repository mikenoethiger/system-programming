FROM ubuntu:latest

RUN apt-get update && apt-get install --yes gcc make libcap-dev libacl1-dev libncurses5-dev

CMD ["bash"]