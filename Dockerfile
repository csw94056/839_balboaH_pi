# Dockerfile for running ROS with a VNC setup.
#
# Lots of this taken from various Docker files from places
#
# Carrick Detweiler, 2022

#Official images: https://hub.docker.com/_/ros/
FROM ros:melodic

ENV DEBIAN_FRONTEND=noninteractive

# Setup the environments
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8
ENV ROS_DISTRO=melodic
ENV HOME=/home/
ENV ROS_WS=/home/shared/catkin_ws/
WORKDIR ${HOME}

# Install the full desktop workspace
RUN apt-get update && apt-get install -y --no-install-recommends \
    ros-melodic-desktop-full \
  && rm -rf /var/lib/apt/lists/*


# Install some helpful utilities
RUN apt-get update && apt-get install -y --no-install-recommends \
    nano \
    vim \
    git \
    g++ \
    rsync \
    zip \
    make \
    cmake \
    curl \
    wget \
    libopencv-dev \
    python3-opencv \
    build-essential \
    lsb-release \
    gnupg2 \
    python3 \
    python3-pip \
    netbase \
    htop \
    nmap \
    less \
    emacs \
    screen \
    socat \
    dos2unix \
    ros-melodic-usb-cam \
    && rm -rf /var/lib/apt/lists/*


#Python serial libraries
RUN pip3 install setuptools
RUN pip3 install serial serial-tool

#Install python2 pip for ROS
RUN apt-get update && apt-get install -y --no-install-recommends \
    python-pip \
  && rm -rf /var/lib/apt/lists/*

#The 2.0 libs for ROS
RUN pip install setuptools
RUN pip install pyserial

#############################
#
# Setup VNC
#
# Some of the useful sites where this config was shamelessly copied from:
#  https://qxf2.com/blog/view-docker-container-display-using-vnc-viewer/
#  https://stackoverflow.com/questions/16296753/can-you-run-gui-applications-in-a-linux-docker-container
#  https://github.com/dbushell/docker-xfce-vnc/blob/main/Dockerfile
#  https://github.com/x11vnc/x11vnc-desktop.git
#############################

RUN apt-get update && apt-get install -y --no-install-recommends \
    x11vnc \
    xfce4 \
    dbus-x11 \
    tigervnc-common \
    tigervnc-standalone-server \
    tigervnc-xorg-extension \
    tigervnc-viewer \
    && rm -rf /var/lib/apt/lists/*
    

#RUN wget -qO- https://dl.bintray.com/tigervnc/stable/tigervnc-1.10.1.x86_64.tar.gz \
#  | tar xz --strip 1 -C /
  
#Set resolution and VNC password
ENV DISPLAY=:1 \
  VNC_DEPTH=24 \
  VNC_RESOLUTION=1280x720 \
  VNC_PASSWORD=password


RUN     mkdir ~/.vnc
# Setup a password
RUN     x11vnc -storepasswd 1234 ~/.vnc/passwd

EXPOSE 5901

#Other userful GUI stuff
RUN apt-get update && apt-get install -y --no-install-recommends \
    firefox \
    gnome-terminal \
    xterm \
    ros-melodic-tf2-geometry-msgs \
    ros-melodic-ackermann-msgs \
    ros-melodic-joy \
    ros-melodic-map-server \
    && rm -rf /var/lib/apt/lists/*


#############################################
# END VNC STUFF
#############################################

#Make screen and bash a bit nicer
COPY ./.screenrc /home/
COPY ./.bashrc /home/
COPY ./.namescreen_src /home/

#xfce configuration to a temporary location as it gets overwritten when starting tightvnc-start.sh (?)
COPY ./.config /home/config2

#Copy the serial bridge script over
COPY ./serial_bridge_script.sh /

#Create a symbolic link to the shared catkin_ws
RUN ln -s /home/shared/catkin_ws /home/catkin_ws

# Start the VNC server and run things
COPY ./tigervnc-start.sh /
RUN ["chmod", "+x", "/tigervnc-start.sh"]
ENTRYPOINT ["/tigervnc-start.sh"]
CMD ["bash"]


#############################
# BUILDING AND RUNNING:
# docker build -t ros .
# docker run --rm -v $PWD/shared:/home/shared -p 5901:5901 -it ros
#
# VNC: connect to localhost:5901 with password password
#  On OS X: "screen sharing"
#  On Windows:
#  On Linux: 
