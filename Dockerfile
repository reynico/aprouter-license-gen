FROM gcc:4.9
COPY . /usr/src/edimax
WORKDIR /usr/src/edimax
RUN gcc -o license license.c -lm -lcrypt
#CMD ["./license","001122334454"]
