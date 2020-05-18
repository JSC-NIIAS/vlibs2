#include "wrap_signal.h"
#include "impl_vposix/poll_context.h"
#include "impl_vposix/linux_call.h"

#include <signal.h>

using namespace impl_vposix;

//=======================================================================================
//  Устанавливает обработчик прерываний по Ctrl+C на остановку поллинга.
//=======================================================================================

//=======================================================================================
static void on_signal(int)
{
    poll_context::current()->stop();
}
//---------------------------------------------------------------------------------------
static int register_exit = []
{
    ::signal( SIGINT,  on_signal );
    ::signal( SIGKILL, on_signal );
    ::signal( SIGTERM, on_signal );

    //  Так не получится, возвращается pointer.
    //linux_call::check( ::signal, SIGINT,  &on_signal );
    //linux_call::check( ::signal, SIGKILL, &on_signal );
    //linux_call::check( ::signal, SIGTERM, &on_signal );

    return 0;
}();
//=======================================================================================

//=======================================================================================
void wrap_signal::kill( pid_t pid, int sig )
{
    linux_call::check( ::kill, pid, sig );
}
//=======================================================================================
bool wrap_signal::kill_no_err( pid_t pid, int sig )
{
    return linux_call::no_err( ::kill, pid, sig );
}
//=======================================================================================
//       If sig is 0, then no signal is sent, but existence and permission
//       checks are still performed; this can be used to check for the
//       existence of a process ID or process group ID that the caller is
//       permitted to signal.
bool wrap_signal::has_process( pid_t pid )
{
    return 0 == kill_no_err(pid, 0);
}
//=======================================================================================
