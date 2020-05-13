#include "wrap_sys_ioctl.h"


//  For: SIOCGSTAMP
#include <sys/socket.h>

#include <sys/ioctl.h>
#include <cassert>
#include "impl_vposix/linux_call.h"

using namespace impl_vposix;
using namespace std::chrono;

//=======================================================================================
std::chrono::microseconds wrap_sys_ioctl::sioc_get_timestamp( int fd )
{
    struct timeval tv;
    auto res = linux_call::check( ::ioctl, fd, SIOCGSTAMP, &tv );
    assert( res == 0 );

    return seconds(tv.tv_sec) + microseconds(tv.tv_usec);
}
//=======================================================================================
