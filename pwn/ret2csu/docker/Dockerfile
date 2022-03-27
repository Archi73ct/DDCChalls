# docker build -t easy_bof .
# docker run -p 1024:1024 --rm -it easy_bof
FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y gcc
RUN useradd -d /home/ctf/ -m -p ctf -s /bin/bash ctf
RUN echo "ctf:ctf" | chpasswd

WORKDIR /home/ctf

RUN chown -R root:root /home/ctf

COPY r2c .
COPY flag .
COPY ynetd .
COPY r2c.c .
RUN chmod +x ynetd

RUN gcc r2c.c -o r2c -fno-stack-protector

USER ctf
EXPOSE 1024
CMD ./ynetd -p 1024 ./r2c