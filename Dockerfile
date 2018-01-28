FROM        ubuntu:16.04
MAINTAINER  gyong1211@gmail.com

RUN         apt-get -y update

# Build environment setting
RUN         apt-get install -y git unzip build-essential
RUN         apt-get install -y make gcc-avr avr-libc binutils-avr dfu-programmer
RUN         apt-get install -y binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib dfu-util

# Zsh & Vim
RUN         apt-get install -y zsh curl
RUN         curl -L http://install.ohmyz.sh | sh || true
RUN         chsh -s /usr/bin/zsh
RUN         apt-get install -y vim

RUN         apt-get autoremove
RUN         apt-get clean

WORKDIR     /root
RUN         git clone https://github.com/tmk/tmk_keyboard.git
WORKDIR     /root/tmk_keyboard
RUN         git pull

