FROM        ubuntu:noble
MAINTAINER  Mu Lei (mulei@gnu.org)
ENV         LANG C.UTF-8

ARG CACHE_UPDATE=1
RUN     apt-get update 

ARG CACHE_APT=1
RUN     apt install --no-install-recommends -y binutils-arm-none-eabi gcc-arm-none-eabi guile-3.0 sudo \
        && apt install --no-install-recommends -y libnewlib-arm-none-eabi libnewlib-dev libstdc++-arm-none-eabi-newlib gdb-multiarch \
        && apt install --no-install-recommends -y cmake python3 python3-virtualenv git build-essential figlet boxes lolcat \
        && rm -rf /var/lib/apt/lists/* \

ARG CACHE_ZEPHYR=1
SHELL   ["/bin/bash", "-c"]
RUN     virtualenv .env \
	&& ls .env \
        && source .env/bin/activate \
	&& pip3 install west dtc ninja \
       && west init /zephyr \
       && cd /zephyr/zephyr \
       && git checkout v2.7.99 \
       && west update \
       && west zephyr-export \
       && pip3 install -r /zephyr/zephyr/scripts/requirements.txt 

ARG CACHE_MISC=1
RUN    useradd -s /bin/bash -m animula \
       && echo "figlet -f mini Animula | boxes -d parchment | /usr/games/lolcat -a -s 200" >> /home/animula/.bashrc \
       && echo "echo 'Zephyr RTOS workspace' | /usr/games/lolcat -a -s 200" >> /home/animula/.bashrc \
       && echo "export ZEPHYR_BASE=/zephyr/zephyr" >> /home/animula/.bashrc \
       && echo "export GNUARMEMB_TOOLCHAIN_PATH=/usr" >> /home/animula/.bashrc \
       && echo "export ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb" >> /home/animula/.bashrc \
       && echo "alias ls='ls --color'" >> /home/animula/.bashrc \
       && git clone https://github.com/hardenedlinux/animula-zephyr-bsp.git \
       && ln -s /animula-zephyr-bsp/arm/* /zephyr/zephyr/boards/arm/ \
       && chown animula:animula /zephyr/* -R

