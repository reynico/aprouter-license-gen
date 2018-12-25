# APRouter v6.1 license generator
For Edimax 7209 access points running Aprouter v6.1 firmware
### Compile
* `gcc -o license license.c -lm -lcrypt`

### Use
* `./license <mac address>`
  * Example: `./license 001122334454`

### Docker container
Wrote a Docker container to simplify things when using a non unix environment
* `docker pull reynico/edimax-license-gen:latest`
* `docker run --rm -v ${PWD}:/usr/src/edimax -w /usr/src/edimax edimax-license-gen ./license 001122334454`

