var getifaddrs = require( "./getifaddrs" )
  , sys = require( "sys" )

sys.puts(sys.inspect(getifaddrs.interfaces()));
