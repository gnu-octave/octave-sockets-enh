// Copyright (C) John Swensen <jpswensen@comcast.net>
// Copyright (C) 2007 Tom Holroyd <tomh@kurage.nimh.nih.gov>
// Copyright (C) 2009 Paul Dreik <slask@pauldreik.se>
// Copyright (C) 2013 Carnë Draug <carandraug@octave.org>
// Copyright (C) 2014 Andreas Weber <andy.weber.aw@gmail.com>
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, see <http://www.gnu.org/licenses/>.

// Octave Includes
#include <octave/oct.h>
#include <octave/parse.h>
#include <octave/toplev.h>
#include <octave/cmd-hist.h>
#include <octave/symtab.h>
#include <octave/variables.h>
#include <octave/Array.h>

#include <octave/ops.h>
#include <octave/ov-base.h>
#include <octave/ov-typeinfo.h>
#include <octave/ov.h>
#include <octave/ov-scalar.h>
#include <octave/ov-struct.h>
#include <octave/ov-uint8.h>

#include <octave/defun-dld.h>

// System includes
#include <sys/types.h>
#ifndef __WIN32__
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#else
typedef unsigned int socklen_t;
#include <winsock2.h>
#endif
#include <errno.h>
#include <string.h>

/*
 * macro for defining all the socket constants as
 * octave functions.
 */
# define DEFUN_DLD_SOCKET_CONSTANT(name)\
  DEFUNX_DLD ( #name, F ## name, G ## name, args, nargout, \
               "socket constant")                          \
  {    return octave_value( name ); };


// PKG_ADD: autoload ("AF_UNIX", which ("socket"));
// PKG_DEL: try; autoload ("AF_UNIX", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(AF_UNIX );
#ifndef __WIN32__
// PKG_ADD: autoload ("AF_LOCAL", which ("socket"));
// PKG_DEL: try; autoload ("AF_LOCAL", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(AF_LOCAL );
#else
DEFUNX_DLD ("AF_LOCAL", FAF_LOCAL, GAF_LOCAL, args, nargout, "(not supported)")
{ error( "AF_LOCAL address family not supported on this platform" );
  return octave_value(); };
#endif
// PKG_ADD: autoload ("AF_INET", which ("socket"));
// PKG_DEL: try; autoload ("AF_INET", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(AF_INET );
// PKG_ADD: autoload ("AF_APPLETALK", which ("socket"));
// PKG_DEL: try; autoload ("AF_APPLETALK", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(AF_APPLETALK );
//DEFUN_DLD_SOCKET_CONSTANT(AF_INET6 );
//DEFUN_DLD_SOCKET_CONSTANT(AF_IPX );
//DEFUN_DLD_SOCKET_CONSTANT(AF_NETLINK );
//DEFUN_DLD_SOCKET_CONSTANT(AF_X25 );
//DEFUN_DLD_SOCKET_CONSTANT(AF_AX25 );
//DEFUN_DLD_SOCKET_CONSTANT(AF_ATMPVC );
//DEFUN_DLD_SOCKET_CONSTANT(AF_PACKET );

// PKG_ADD: autoload ("SOCK_STREAM", which ("socket"));
// PKG_DEL: try; autoload ("SOCK_STREAM", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOCK_STREAM );
// PKG_ADD: autoload ("SOCK_DGRAM", which ("socket"));
// PKG_DEL: try; autoload ("SOCK_DGRAM", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOCK_DGRAM );
// PKG_ADD: autoload ("SOCK_SEQPACKET", which ("socket"));
// PKG_DEL: try; autoload ("SOCK_SEQPACKET", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOCK_SEQPACKET );
// PKG_ADD: autoload ("SOCK_RAW", which ("socket"));
// PKG_DEL: try; autoload ("SOCK_RAW", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOCK_RAW );
// PKG_ADD: autoload ("SOCK_RDM", which ("socket"));
// PKG_DEL: try; autoload ("SOCK_RDM", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOCK_RDM );
//DEFUN_DLD_SOCKET_CONSTANT(SOCK_PACKET );

// PKG_ADD: autoload ("MSG_PEEK", which ("socket"));
// PKG_DEL: try; autoload ("MSG_PEEK", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(MSG_PEEK );
#ifdef MSG_DONTWAIT
// PKG_ADD: autoload ("MSG_DONTWAIT", which ("socket"));
// PKG_DEL: try; autoload ("MSG_DONTWAIT", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(MSG_DONTWAIT );
#endif
#ifdef MSG_WAITALL
// PKG_ADD: autoload ("MSG_WAITALL", which ("socket"));
// PKG_DEL: try; autoload ("MSG_WAITALL", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(MSG_WAITALL );
#endif

/*
 * see manpage for setsockopt
 * and pitfall 3 from https://www.ibm.com/developerworks/library/l-sockpit/
 * https://upload.wikimedia.org/wikipedia/commons/0/08/TCP_state_diagram.jpg
 */
// PKG_ADD: autoload ("SOL_SOCKET", which ("socket"));
// PKG_DEL: try; autoload ("SOL_SOCKET", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SOL_SOCKET );
// PKG_ADD: autoload ("SO_DEBUG", which ("socket"));
// PKG_DEL: try; autoload ("SO_DEBUG", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SO_DEBUG );
// PKG_ADD: autoload ("SO_REUSEADDR", which ("socket"));
// PKG_DEL: try; autoload ("SO_REUSEADDR", which ("socket"), "remove"); catch; end;
DEFUN_DLD_SOCKET_CONSTANT(SO_REUSEADDR );

//we need to keep track if sockets has been loaded, as it
//requires initialization on windows platforms.
#ifdef __WIN32__
static bool type_loaded = false;
#endif

// PKG_ADD: autoload ("socket", which ("socket"));
// PKG_DEL: try; autoload ("socket", which ("socket"), "remove"); catch; end;
// Function to create a socket
DEFUN_DLD(socket, args, , "\
-*- texinfo -*-\n\
@deftypefn  {Loadable Function} {} socket ()\n\
@deftypefnx {Loadable Function} {} socket (@var{domain})\n\
@deftypefnx {Loadable Function} {} socket (@var{domain}, @var{type})\n\
@deftypefnx {Loadable Function} {} socket (@var{domain}, @var{type}, @var{protocol})\n\
Creates a socket.\n\
\n\
@var{domain} is an integer, where the value AF_INET\n\
can be used to create an IPv4 socket.\n\
\n\
@var{type} is an integer describing the socket.  When using IP, specifying\n\
SOCK_STREAM gives a TCP socket.\n\
\n\
@var{protocol} is currently not used and should be 0 if specified.\n\
\n\
If no input arguments are given, default values AF_INET and\n\
SOCK_STREAM are used.\n\
\n\
See the local @command{socket} reference for more details.\n\
@end deftypefn")
{
  int domain    = AF_INET;
  int type      = SOCK_STREAM;
  int protocol  = 0;

#ifdef __WIN32__
  if (! type_loaded)
    {
      type_loaded = true;

      WORD wVersionRequested;
      WSADATA wsaData;
      int err;

      wVersionRequested = MAKEWORD (2, 2);
      err = WSAStartup (wVersionRequested, &wsaData);
      if (err != 0)
        {
          error ("socket: could not initialize winsock library");
          return octave_value();
        }
    }
#endif

  // Convert the arguments to their #define'd value
  const octave_idx_type nargin = args.length ();
  if (nargin > 0)
    {
      domain = args(0).int_value ();
      if (error_state)
        {
          error ("socket: DOMAIN must be a scalar integer");
          return octave_value ();
        }
    }

  if (nargin > 1)
    {
      type = args(1).int_value ();
      if (error_state)
        {
          error ("socket: TYPE must be a scalar integer");
          return octave_value ();
        }
    }

  if (nargin > 2)
    {
      protocol = args(2).int_value ();
      if (error_state)
        {
          error ("socket: PROTOCOL must be a scalar integer");
          return octave_value ();
        }
      else if (protocol != 0)
      {
        error ("socket: for now, PROTOCOL must always be 0 (zero)");
        return octave_value ();
      }
    }

  // Create the new socket
  const int sock_fd = ::socket (domain, type, protocol);
  if (sock_fd == -1)
      error ("socket failed with error %i (%s)", errno, strerror(errno));

  return octave_value(sock_fd);
}

/*
 * helper function to convert an octave value to an integer,
 * returning -1 if it failed.
 */
int get_socket(const octave_value& arg)
{
  const int fd = arg.int_value();
  if (error_state)
    {
      return -1;
    }
  return fd;
}


/*
 * closes the given socket file descriptor
 */
inline void close_octavesocket(const int sock_fd) {
#ifndef __WIN32__
  ::close (sock_fd);
#else
  ::closesocket (sock_fd);
#endif
}

// PKG_ADD: autoload ("connect", which ("socket"));
// PKG_DEL: try; autoload ("connect", which ("socket"), "remove"); catch; end;
// function to create an outgoing connection
DEFUN_DLD(connect, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} connect (@var{s}, @var{serverinfo})\n\
Connect socket.\n\
\n\
Connects the socket @var{s} following the information\n\
in the struct @var{serverinfo} which must contain the\n\
following fields:\n\
\n\
@table @code\n\
@item addr\n\
a string with the host name to connect to\n\
\n\
@item port\n\
the port number to connect to (an integer)\n\
@end table\n\
\n\
On successful connect, the returned status is zero.\n\
\n\
See the @command{connect} man pages for further details.\n\
@end deftypefn")
{

  if (args.length () != 2)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (error_state)
    {
      error ("connect: S must be a valid socket");
      return octave_value ();
    }

  // Extract information about the server to connect to.
  const octave_scalar_map struct_serverInfo = args(1).scalar_map_value ();
  if (error_state)
    {
      error ("connect: SERVERINFO must be a struct");
      return octave_value ();
    }

  const std::string addr = struct_serverInfo.getfield ("addr").string_value ();
  const int port    = struct_serverInfo.getfield ("port").int_value ();
  if (error_state)
    {
      error ("connect: SERVERINFO must have a string and integer in fields \"addr\" and \"port\"");
      return octave_value ();
    }
  else if (addr.empty ())
    {
      error ("connect: SERVERINFO addr is an empty string");
      return octave_value ();
    }

  // Fill in the server info struct
  struct sockaddr_in serverInfo;
  serverInfo.sin_family = AF_INET;

  struct hostent* hostInfo = gethostbyname (addr.c_str ());
  if (! hostInfo)
    {
      error ("connect: error in gethostbyname()");
      return octave_value ();
    }
  serverInfo.sin_addr.s_addr = *((long*)hostInfo->h_addr_list[0]);
  serverInfo.sin_port = htons(port);

  const int retval = connect (s, (struct sockaddr*)&serverInfo,
                              sizeof (struct sockaddr));
  if (retval == -1)
      error ("connect failed with error %i (%s)", errno, strerror(errno));

  return octave_value (retval);
}

// PKG_ADD: autoload ("disconnect", which ("socket"));
// PKG_DEL: try ; autoload ("disconnect", which ("socket"), "remove") ; catch ; end;
// function to disconnect asocket
DEFUN_DLD(disconnect, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} disconnect (@var{s})\n\
Disconnect socket.\n\
\n\
Disconnects the socket @var{s}.  If successful, @code{disconnect} returns 0,\n\
otherwise, it returns -1.\n\
\n\
Since we can't call fclose on the file descriptor directly, use this\n\
function to disconnect the socket.\n\
\n\
@end deftypefn")
{
  if (args.length () != 1)
    {
      print_usage ();
      return octave_value ();
    }

  int retval = -1;
  const int s = get_socket (args(0));
  if (! error_state)
    {
      close_octavesocket(s);
      retval = 0;
    }
  return octave_value (retval);
}

// PKG_ADD: autoload ("gethostbyname", which ("socket"));
// PKG_DEL: try; autoload ("gethostbyname", which ("socket"), "remove"); ; catch; end;
// function to get a host number from a host name
DEFUN_DLD(gethostbyname, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} gethostbyname (@var{hostname})\n\
Return IP address for host name.\n\
\n\
For example:\n\
\n\
@example\n\
@group\n\
gethostbyname (\"localhost\")\n\
  @result{} 127.0.0.1\n\
@end group\n\
@end example\n\
\n\
See the @command{gethostbyname} man pages for details.\n\
\n\
@end deftypefn")
{
  const int nargin = args.length ();

  if (nargin != 1)
    {
      print_usage ();
      return octave_value ();
    }

  const std::string addr = args(0).string_value ();
  if (error_state)
    {
      error ("gethostbyname: HOSTNAME must be a string");
      return octave_value ();
    }

  string_vector host_list;
  struct hostent* hostInfo = gethostbyname (addr.c_str ());
  if (hostInfo)
    {
      for (int i = 0 ; i < hostInfo->h_length/4; i++)
        {
          std::string temp_addr = inet_ntoa (*(struct in_addr*)hostInfo->h_addr_list[i]);
          host_list.append (temp_addr);
        }
    }
  return octave_value (host_list);
}

// PKG_ADD: autoload ("send", which ("socket"));
// PKG_DEL: try; autoload ("send", which ("socket"), "remove"); catch; end;
// function to send data over a socket
DEFUN_DLD(send, args, , "\
-*- texinfo -*-\n\
@deftypefn  {Loadable Function} {} send (@var{s}, @var{data})\n\
@deftypefnx {Loadable Function} {} send (@var{s}, @var{data}, @var{flags})\n\
Send data on specified socket.\n\
\n\
Sends data on socket @var{s}.  @var{data} should be an uint8 array or\n\
a string.\n\
\n\
See the @command{send} man pages for further details.\n\
\n\
@end deftypefn")
{
  const octave_idx_type nargin = args.length ();

  if (nargin < 2 || nargin > 3)
  {
    print_usage ();
    return octave_value ();
  }

  int flags = 0;
  if (nargin > 2)
    {
      flags = args(2).int_value ();
      if (error_state)
        {
          error ("send: FLAGS must be a scalar integer");
          return octave_value ();
        }
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (error_state)
    {
      error ("send: s must be a valid socket");
      return octave_value ();
    }

  int retval = -1;
  // Extract the data from the octave variable and send it
  const octave_base_value& data = args(1).get_rep ();
  if (data.is_string ())
    {
      std::string buf = data.string_value ();
      retval = ::send (s, buf.c_str (), buf.length (), flags);
    }
  else if (data.byte_size () == size_t (data.numel ()))
    {
      const NDArray d1 = data.array_value ();
      const octave_idx_type length = d1.numel ();
      const double* d1fvec = d1.data ();

      OCTAVE_LOCAL_BUFFER (unsigned char, buf, length);
      for (int i = 0 ; i < length; i++)
        buf[i] = (unsigned char)d1fvec[i];

      //hmm, flags are set to 0, unlike the call above!
      retval = ::send (s, (const char*)buf, data.byte_size (), 0);
    }
  else
    {
      error( "connect: invalid DATA to send.  Please format it prior to sending" );
      return octave_value ();
    }

  return octave_value (retval);
}

// PKG_ADD: autoload ("recv", which ("socket"));
// PKG_DEL: try; autoload ("recv", which ("socket"), "remove"); catch; end;
// function to receive data over a socket
DEFUN_DLD(recv, args, , "\
-*- texinfo -*-\n\
@deftypefn  {Loadable Function} {[@var{data}, @var{count}] =} recv (@var{s}, @var{len})\n\
@deftypefnx {Loadable Function} {[@var{data}, @var{count}] =} recv (@var{s}, @var{len}, @var{flags})\n\
Read data from specified socket.\n\
\n\
Requests reading @var{len} bytes from the socket @var{s}.\n\
The optional integer @var{flags} parameter can be used to modify the\n\
behaviour of @code{recv}.\n\
\n\
The read data is returned in the uint8 array @var{data}.  The number of\n\
bytes read is returned in @var{count}.\n\
\n\
You can get non-blocking operation by using the flag @code{MSG_DONTWAIT}\n\
which makes the @code{recv()} call return immediately.  If there is no\n\
data, -1 is returned in count.\n\
\n\
See the @command{recv} man pages for further details.\n\
\n\
@end deftypefn")
{
  const octave_idx_type nargin = args.length ();
  int retval = 0;
  int flags = 0;

  if (nargin < 2 || nargin > 3)
    {
      print_usage ();
      return octave_value ();
    }

  if (nargin > 2)
    {
      flags = args(2).int_value ();
      if (error_state)
        {
          error ("recv: FLAGS must be a scalar integer");
          return octave_value ();
        }
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (error_state)
    {
      error ("recv: S must be a valid socket");
      return octave_value ();
    }

  const long len = args(1).int_value ();
  if (error_state || len < 0)
    {
      error ("recv: LEN must be a non-negative integer");
      return octave_value(-1);
    }

  OCTAVE_LOCAL_BUFFER (unsigned char, buf, len);
#ifndef __WIN32__
  retval = ::recv( s, buf, len, flags );
#else
  retval = ::recv( s, ( char* )buf, len, flags );
#endif

  if (retval == -1)
    warning ("recv error %i (%s)", errno, strerror(errno));

  octave_value_list return_list;
  uint8NDArray data;

  //always return the status in the second output parameter
  return_list(1) = retval;
  if (retval <= 0)
    // We get -1 if an error occurs, or if there is no data and the
    // socket is non-blocking. We should return in both cases.
    // We get 0 if the peer has shut down.
    return_list(0) = data;
  else
    {
      //Normal behaviour. Copy the buffer to the output variable. For
      //backward compatibility, a row vector is returned.
      data.resize (dim_vector (1, retval));
      octave_uint8* data_fvec = data.fortran_vec ();
      for (int i = 0 ; i < retval ; i++)
        data_fvec[i] = buf[i];

      return_list(0) = data;
    }
  return return_list;
}

// PKG_ADD: autoload ("bind", which ("socket"));
// PKG_DEL: try; autoload ("bind", which ("socket"), "remove"); catch; end;
// function to bind a socket
DEFUN_DLD(bind, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} bind (@var{s}, @var{portnumber})\n\
Bind specific socket to port number.\n\
\n\
See the @command{bind} man pages for further details.\n\
\n\
@end deftypefn")
{
  if (args.length () != 2)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (error_state)
    {
      error ("bind: S must be a valid socket");
      return octave_value ();
    }

  const long port = args(1).int_value ();
  if (error_state)
    {
      error ("bind: PORT must be a scalar integer");
      return octave_value ();
    }

  struct sockaddr_in serverInfo;
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_port = htons (port);
  serverInfo.sin_addr.s_addr = INADDR_ANY;

  int retval = ::bind (s, (struct sockaddr *)&serverInfo, sizeof (serverInfo));
  if (retval == -1)
      error ("bind failed with error %i (%s)", errno, strerror(errno));

  return octave_value (retval);
}

// PKG_ADD: autoload ("listen", which ("socket"));
// PKG_DEL: try; autoload ("listen", which ("socket"), "remove"); catch; end;
// function to listen on a socket
DEFUN_DLD(listen, args, , "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} listen (@var{s}, @var{backlog})\n\
Listen on socket for connections.\n\
\n\
Listens on socket @var{s} for connections.  @var{backlog} specifies\n\
how large the queue of incoming connections is allowed to\n\
grow.\n\
\n\
On success, zero is returned.\n\
\n\
See the @command{listen} man pages for further details.\n\
\n\
@end deftypefn")
{
  if (args.length() != 2)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (error_state)
    {
      error ("listen: S must be a valid socket");
      return octave_value ();
    }

  const int backlog = args(1).int_value ();
  if (error_state)
    {
      error ("listen: BACKLOG must be an integer scalar");
      return octave_value ();
    }

  const int retval = ::listen (s, backlog);
  if (retval == -1)
      error ("listen failed with error %i (%s)", errno, strerror(errno));

  return octave_value (retval);
}

// PKG_ADD: autoload ("accept", which ("socket"));
// PKG_DEL: try; autoload ("accept", which ("socket"), "remove"); catch; end;
// function to accept on a listening socket
DEFUN_DLD(accept,args,nargout, "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{client}, @var{info}] =} accept (@var{s})\n\
Accept incoming connection on specified socket.\n\
\n\
Accepts an incoming connection on the socket @var{s}.\n\
The newly created socket is returned in @var{client}, and\n\
associated information in a struct info.\n\
\n\
See the @command{accept} man pages for further details.\n\
\n\
@end deftypefn")
{
  struct sockaddr_in clientInfo;
  socklen_t clientLen = sizeof (struct sockaddr_in);

  if (args.length () != 1)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (error_state)
    {
      error ("accept: S must be a valid socket");
      return octave_value ();
    }

#ifndef __WIN32__
  int fd = ::accept( s, (struct sockaddr *)&clientInfo, &clientLen );
#else
  int fd = ::accept( s, (struct sockaddr *)&clientInfo, ( int* )&clientLen );
#endif
  if (fd == -1)
    {
      error ("accept failed with error %i (%s)", errno, strerror(errno));
      return octave_value ();
    }

#if 0
  // create the octave_socket object and set the fd
  octave_socket* retobj = new octave_socket(fd);
#endif
  // place the client information into a structure
  octave_scalar_map client_info_map;
  client_info_map.assign ("sin_family", octave_value (clientInfo.sin_family));
  client_info_map.assign ("sin_port", octave_value (clientInfo.sin_port));
  client_info_map.assign ("sin_addr", octave_value (inet_ntoa(clientInfo.sin_addr)));

  // returns the accepted socket and a clientinfo structure
  octave_value_list return_list;
  return_list(0) = octave_value (fd);
  return_list(1) = client_info_map;

  return return_list;
}

// PKG_ADD: autoload ("setsockopt", which ("socket"));
// PKG_DEL: try; autoload ("setsockopt", which ("socket"), "remove"); catch; end;
// function to set options for the specified socket
DEFUN_DLD(setsockopt,args,nargout, "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} setsockopt (@var{s}, @var{level}, @var{opt}, @var{value})\n\
Set options for specified socket.\n\
\n\
Manipulates options for the socket @var{s}.\n\
Options may exist at multiple protocol levels; they are always present\n\
at the uppermost socket level. Currently only SOL_SOCKET is supported for\n\
@var{level}. Supported values for @var{opt} are:\n\
@table @code\n\
@item SO_DEBUG\n\
Turns on recording of debugging information. This option enables or disables\n\
debugging in the underlying protocol modules.\n\
\n\
@item SO_REUSEADDR\n\
Specifies that the rules used in validating addresses supplied to bind()\n\
should allow reuse of local addresses, if this is supported by the protocol.\n\
@end table\n\
@end deftypefn")
{
  if (args.length () != 4)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (error_state)
    {
      error ("setsockopt: S must be a valid socket");
      return octave_value ();
    }

  int level = args(1).int_value();
  int opt = args(2).int_value();
  int value = args(3).int_value();
  if (error_state)
    {
      error ("setsockopt: LEVEL, OPT and VALUE must be integer values");
      return octave_value ();
    }

  int ret = setsockopt( s, level, opt, &value, sizeof(value) );
  if (ret == -1)
    error ("setsockopt failed with error %i (%s)", errno, strerror(errno));

  return octave_value ();
}

// PKG_ADD: autoload ("getsockopt", which ("socket"));
// PKG_DEL: try; autoload ("getsockopt", which ("socket"), "remove"); catch; end;
// function to get options for the specified socket
DEFUN_DLD(getsockopt,args,nargout, "\
-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{value} =} getsockopt (@var{s}, @var{level}, @var{opt})\n\
Get option for specified socket. See also TODO getsockopt\n\
@end deftypefn")
{
  if (args.length () != 3)
    {
      print_usage ();
      return octave_value ();
    }

  // Determine the socket on which to operate
  const int s = get_socket (args(0));
  if (error_state)
    error ("getsockopt: S must be a valid socket");

  int level = args(1).int_value();
  int opt = args(2).int_value();
  if (error_state)
    error ("getsockopt: LEVEL and OPT must be integer values");

  int value;
  socklen_t len;
  int ret = getsockopt(s, level, opt, &value, &len);
  if (ret == -1)
    error ("setsockopt failed with error %i (%s)", errno, strerror(errno));
  if (len != 4)
    error ("getsockopt: currently only int arguments are available for optval");

  return octave_value (value);
}

/*
%!test
%! ## Server socket
%! server = socket (AF_INET, SOCK_STREAM, 0);
%! assert (server >= 0);
%!
%! rc = bind (server, 9001);
%! assert (rc, 0);
%!
%! rc = listen (server, 1);
%! assert (rc, 0);
%!
%! ## Client socket
%! client = socket (AF_INET, SOCK_STREAM, 0);
%! assert (client >= 0);
%!
%! ## Create the connection and accept the connection
%! server_info = struct ("addr", "127.0.0.1", "port", 9001);
%! rc = connect (client, server_info);
%! assert (rc, 0);
%!
%! server_data = accept (server);
%! assert (server_data >= 0);
%!
%! ## Send and receive data
%!
%! ## Send as string from client
%! msg = "Hello socket-land!";
%! rc = send (client, msg);
%! assert (rc,length (msg));
%!
%! ## Receive at server
%! [msg_s, len_s] = recv (server_data, 100);
%! assert (msg_s != -1);
%! assert (len_s, length (msg));
%!
%! ## Send back out from server
%! rc = send (server_data, msg_s);
%! assert (rc, length (msg_s));
%!
%! ## Receive at client
%! [msg_c, len_c] = recv (client, 100);
%! assert (msg_c != -1);
%! assert (len_c, length (msg));
%!
%! ## Compare original string with recv string
%! assert (msg, num2str (msg_c, "%c"));
%!
%! assert (disconnect (client), 0);
%! assert (disconnect (server_data), 0);
%! assert (disconnect (server), 0);
*/

/*
%!test
%! ## Just try to trigger the TIME_WAIT problem on bind
%! ## Without setsockopt SO_REUSEADDR you get an bind error EADDRINUSE
%! ## if called test twice because the TCP socket is in TIME_WAIT state
%! ## for two up to four minutes. You can apply the SO_REUSEADDR socket
%! ## option to the socket, such that the port can be reused immediately.
%!
%! server = socket (AF_INET, SOCK_STREAM, 0);
%! setsockopt (server, SOL_SOCKET, SO_REUSEADDR, 1);
%! assert (getsockopt (server, SOL_SOCKET, SO_REUSEADDR), 1);
%! 
%! bind (server, 9001);
%! listen (server, 1);
%! 
%! client = socket (AF_INET, SOCK_STREAM, 0);
%! server_info = struct ("addr", "127.0.0.1", "port", 9001);
%! connect (client, server_info);
%! 
%! server_data = accept (server);
%! 
%! disconnect (server_data);
%! disconnect (server);
%! 
%! clear all
%! 
%! server2 = socket (AF_INET, SOCK_STREAM, 0);
%! setsockopt (server2, SOL_SOCKET, SO_REUSEADDR, 1);
%! assert (getsockopt (server2, SOL_SOCKET, SO_REUSEADDR), 1);
%! bind (server2, 9001);
%! 
%! disconnect (server2);
*/

