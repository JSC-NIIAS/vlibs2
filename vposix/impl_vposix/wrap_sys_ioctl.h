#ifndef IMPL_VPOSIX_WRAP_SYS_IOCTL_H
#define IMPL_VPOSIX_WRAP_SYS_IOCTL_H

//=======================================================================================
/*
 *  Есть большое желание собрать зоопрк вызовов ioctl в одном месте.
 *
 *  http://man7.org/linux/man-pages/man4/tty_ioctl.4.html
 *  https://unix.superglobalmegacorp.com/Net2/newsrc/sys/ioctl.h.html
 *  https://www.opennet.ru/cgi-bin/opennet/man.cgi?topic=ioctl_list&category=2
 *
 * [1] https://linux.die.net/man/7/socket
 *  SIOCGSTAMP
 *  Return a struct timeval with the receive timestamp of the last packet passed to the
 *  user. This is useful for accurate round trip time measurements. See setitimer(2)
 *  for a description of struct timeval. This ioctl should only be used if the socket
 *  option SO_TIMESTAMP is not set on the socket. Otherwise, it returns the timestamp
 *  of the last packet that was received while SO_TIMESTAMP was not set, or it fails
 *  if no such packet has been received, (i.e., ioctl(2) returns -1 with errno set
 *  to ENOENT).
*/
//=======================================================================================

#include <chrono>

//=======================================================================================
namespace impl_vposix
{
    //===================================================================================
    struct wrap_sys_ioctl
    {
        //-------------------------------------------------------------------------------
        // [1] -- SIOCGSTAMP
        static std::chrono::microseconds sioc_get_timestamp( int fd );
    };
    //===================================================================================
} // namespace impl_vposix
//=======================================================================================



#endif // IMPL_VPOSIX_WRAP_SYS_IOCTL_H
