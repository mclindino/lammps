FROM ubuntu:20.04
LABEL maintainer="m203581@dac.unicamp.br"
LABEL version="1.0"

RUN apt-get update && \
    apt-get install -y build-essential wget git && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y openmpi-common openmpi-bin libopenmpi-dev cmake