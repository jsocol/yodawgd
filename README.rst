========
FillItIn
========

A super-simple autocompletion service wrapped around yodawg_.


Building
========

To build FillItIn::

    git clone --recursive https://github.com/jsocol/fillitin.git
    cd fillitin
    make


Usage
=====

Right now it's very simple::

    ./fillitin <port>

I've been prefering port ``3434`` for no particular reason::

    ./fillitin 3434


Protocol
========

My goal for the line protocol is to be extremely simple, like Redis_,
memcached_ or IRC_. So far there are two methods. Eventually there might be
four.

``ADD <string>``:
    Add a string to the autocomplete list.
``COMPLETE <string>``:
    Get a list of possible completions for the given string.


ToDo
====

* Work out the details of the line protocol and responses.
* Make it actually, you know, work.
* Make the whole daemon thing more robust.
* Figure out a better name.


A little ways down the road
---------------------------

* Some kind of replica/slave/HA solution.


.. _yodawg: https://github.com/jsocol/yodawg
.. _Redis: http://redis.io/topics/protocol
.. _memcached: https://github.com/memcached/memcached/blob/master/doc/protocol.txt
.. _IRC: http://tools.ietf.org/html/rfc1459
