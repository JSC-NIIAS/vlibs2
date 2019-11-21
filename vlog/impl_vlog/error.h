#ifndef IMPL_VLOG_ERROR_H
#define IMPL_VLOG_ERROR_H

#include <sstream>
#include <cassert>

#include "impl_vcat/vcat_iface.h"
#include "impl_vlog/position_fix.h"

//=======================================================================================
namespace impl_vlog
{
    //===================================================================================
    class error final : public std::exception,
                        public impl_vcat::vcat_iface<error>
    {
    public:
        error( position_fix && pos );

        error( const error& other );

        const char* what() const noexcept override;

        //-------------------------------------------------------------------------------
    private:
        position_fix _pos;

        //  Работает так: когда объект создан, но не скопирован, то stream накапливает
        //  данные. Когда вызывается копирование, то сообщение "снимается" со stream-а
        //  и "запечатывается" (сохраняется в sealed_msg)
        bool _sealed = false;
        std::string _sealed_msg {};
        std::ostringstream _stream;

        //-------------------------------------------------------------------------------
        friend class impl_vcat::vcat_iface<error>;
        template<typename T>
        void do_cat( T && data )
        {
            assert( !_sealed );
            if ( _sealed ) return;
            _stream << std::forward<T>(data);
        }
        //-------------------------------------------------------------------------------
    };
    //===================================================================================
} // impl_vlog namespace
//=======================================================================================

#define verror impl_vlog::error( V_POSITION_FIX )

//=======================================================================================


#endif // IMPL_VLOG_ERROR_H