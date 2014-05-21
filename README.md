This is a fork from
http://sourceforge.net/p/octave/sockets/ci/default/tree/

Some changes are:

* The functions now throw a error with message describing the problem.
  The original function just returns -1 and you can't figure out
  what error occurred.

* New socket constants SOL_SOCKET, SO_DEBUG, SO_REUSEADDR
  and functions setsockopt and getsockopt to manipulate socket options
