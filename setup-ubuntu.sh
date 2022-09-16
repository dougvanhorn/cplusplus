#!/bin/bash

apt update
apt upgrade -y

apt install -y \
    build-essential \
    python3 \
    python3-dev \
    python3-pip \
    vim

