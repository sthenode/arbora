///////////////////////////////////////////////////////////////////////
/// Copyright (c) 1988-2018 $organization$
///
/// This software is provided by the author and contributors ``as is'' 
/// and any express or implied warranties, including, but not limited to, 
/// the implied warranties of merchantability and fitness for a particular 
/// purpose are disclaimed. In no event shall the author or contributors 
/// be liable for any direct, indirect, incidental, special, exemplary, 
/// or consequential damages (including, but not limited to, procurement 
/// of substitute goods or services; loss of use, data, or profits; or 
/// business interruption) however caused and on any theory of liability, 
/// whether in contract, strict liability, or tort (including negligence 
/// or otherwise) arising in any way out of the use of this software, 
/// even if advised of the possibility of such damage.
///
///   File: reader_events.hpp
///
/// Author: $author$
///   Date: 5/17/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_TREE_READER_EVENTS_HPP
#define _XOS_FS_TREE_READER_EVENTS_HPP

#include "xos/fs/tree/branch.hpp"
#include "xos/base/event.hpp"

namespace xos {
namespace fs {
namespace tree {

typedef implement_base reader_eventst_implements;
///////////////////////////////////////////////////////////////////////
///  Class: reader_eventst
///////////////////////////////////////////////////////////////////////
template <class TImplements = reader_eventst_implements>
class _EXPORT_CLASS reader_eventst: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef reader_eventst events_t;

    virtual event_handled_status on_read_node(const node& node) {
        events_t* forwarded_to = reader_events_forwarded_to();
        if ((forwarded_to)) {
            event_handled_status status = event_unhandled;
            if ((status = forwarded_to->on_read_node(node))) {
                return status;
            }
        }
        return event_unhandled;
    }

    virtual events_t* forward_reader_events_to(events_t* to) {
        return 0;
    }
    virtual events_t* reader_events_forwarded_to() const {
        return 0;
    }
};
typedef reader_eventst<> reader_events;

typedef reader_events reader_events_extendt_implements;
typedef base reader_events_extendt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: reader_events_extendt
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = reader_events_extendt_implements, 
 class TExtends = reader_events_extendt_extends>

class _EXPORT_CLASS reader_events_extendt
: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef typename implements::events_t events_t;

    reader_events_extendt(events_t* events): events_(events) {
    }
    reader_events_extendt
    (const reader_events_extendt &copy): events_(0) {
    }
    reader_events_extendt(): events_(0) {
    }
    virtual ~reader_events_extendt() {
    }
    
    virtual events_t* forward_reader_events_to(events_t* to) {
        events_t* forwarded_to = reader_events_forwarded_to();
        events_ = to;
        return forwarded_to;
    }
    virtual events_t* reader_events_forwarded_to() const {
        return events_;
    }

protected:
    events_t* events_;
};
typedef reader_events_extendt<> reader_events_extend;

} /// namespace tree
} /// namespace fs
} /// namespace xos

#endif /// _XOS_FS_TREE_READER_EVENTS_HPP 
