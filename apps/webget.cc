#include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  // TCPsocket建立http连接
  auto sock = TCPSocket();
  sock.connect( Address( host, "http" ) );
  // 发送请求
  sock.write( "GET " + path + " HTTP/1.1\r\n" );
  sock.write( "Host: " + host + "\r\n" );
  sock.write( "Connection: close\r\n" );
  sock.write( "\r\n" );
  // 关闭写端
  sock.shutdown( SHUT_WR );
  // 循环读端直到eof
  while ( !sock.eof() ) {
    string buffer;
    sock.read( buffer );
    cout << buffer;
  }
  // 关闭sock
  sock.close();
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
