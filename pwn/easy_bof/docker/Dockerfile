# docker build -t easy_bof .
# docker run -p 1024:1024 --rm -it easy_bof
FROM ubuntu:20.04

RUN apt-get update

RUN useradd -d /home/ctf/ -m -p ctf -s /bin/bash ctf
RUN echo "ctf:ctf" | chpasswd

WORKDIR /home/ctf

COPY ebof .
COPY flag .
COPY ynetd .

RUN chmod +x ynetd

RUN chown -R root:root /home/ctf

USER ctf
EXPOSE 1024
CMD ./ynetd -p 1024 ./ebof