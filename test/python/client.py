#! /usr/bin/env python
# -*- coding: utf-8 -*-

import glob
import sys
sys.path.append('gen-py')

from sample import Basic
from sample import ttypes

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

if __name__ == '__main__':
    try:
        transport = TSocket.TSocket('localhost', 9090)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocol(transport)
        #client = Calculator.Client(protocol)
        client = Basic.Client(protocol)

        transport.open()

        print "Call ping() = %s " % (client.ping(),)

        print "Call hello() = %s " % (client.hello("Hey guys!"),)

        transport.close()

    except Thrift.TException, tx:
        print "%s" % (tx.message)
