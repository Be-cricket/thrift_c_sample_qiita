From centos

WORKDIR /root

RUN yum -y update

RUN yum -y groupinstall "Development Tools"

RUN yum install -y wget

#Update autoconf
RUN wget http://ftp.gnu.org/gnu/autoconf/autoconf-2.69.tar.gz

RUN tar xvf autoconf-2.69.tar.gz

WORKDIR /root/autoconf-2.69

RUN ./configure --prefix=/usr

RUN make

RUN make install

#Update automake
WORKDIR /root

RUN wget http://ftp.gnu.org/gnu/automake/automake-1.14.tar.gz

RUN tar xvf automake-1.14.tar.gz

WORKDIR /root/automake-1.14

RUN ./configure --prefix=/usr

RUN make

RUN make install

#Update bison
WORKDIR /root

RUN wget http://ftp.gnu.org/gnu/bison/bison-2.5.1.tar.gz
RUN tar xvf bison-2.5.1.tar.gz
WORKDIR /root/bison-2.5.1
RUN ./configure --prefix=/usr
RUN make
RUN make install

#Install glib
WORKDIR /root
RUN yum -y install glib2-devel

#Install Berkeley DB (Optional)
WORKDIR /root
RUN yum -y install libdb-devel


#Install other lib for development.
WORKDIR /root
RUN yum -y install libevent-devel zlib-devel openssl-devel

#Build and Install Thrift Compiler
WORKDIR /root
RUN git clone https://github.com/apache/thrift.git
WORKDIR /root/thrift
RUN ./bootstrap.sh
RUN ./configure --with-lua=no --with-python=yes --with-c_glib=yes 
RUN make
RUN make install

#Install pip
WORKDIR /root
RUN wget https://bootstrap.pypa.io/get-pip.py
RUN python get-pip.py
RUN python -m pip -V

#Install six
RUN pip install six

#Install sample source
WORKDIR /root
RUN git clone https://github.com/Be-cricket/thbdb.git

ENV LD_LIBRARY_PATH=/usr/local/lib
