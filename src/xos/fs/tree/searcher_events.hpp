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
///   File: searcher_events.hpp
///
/// Author: $author$
///   Date: 5/24/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_TREE_SEARCHER_EVENTS_HPP
#define _XOS_FS_TREE_SEARCHER_EVENTS_HPP

#include "xos/fs/tree/branch.hpp"
#include "xos/base/event.hpp"

namespace xos {
namespace fs {
namespace tree {

typedef implement_base searcher_eventst_implements;
///////////////////////////////////////////////////////////////////////
///  Class: searcher_eventst
///////////////////////////////////////////////////////////////////////
template <class TImplements = searcher_eventst_implements>
class _EXPORT_CLASS searcher_eventst: virtual public TImplements {
public:
    typedef TImplements implements;
    typedef searcher_eventst events_t;

    virtual event_handled_status on_found_branch(const branch& b) {
        events_t* forwarded_to = searcher_events_forwarded_to();
        if ((forwarded_to)) {
            event_handled_status status = event_unhandled;
            if ((status = forwarded_to->on_found_branch(b))) {
                return status;
            }
        }
        return on_found_node(b);
    }
    virtual event_handled_status on_found_leaf(const leaf& l) {
        events_t* forwarded_to = searcher_events_forwarded_to();
        if ((forwarded_to)) {
            event_handled_status status = event_unhandled;
            if ((status = forwarded_to->on_found_leaf(l))) {
                return status;
            }
        }
        return on_found_node(l);
    }
    virtual event_handled_status on_found_node(const node& n) {
        events_t* forwarded_to = searcher_events_forwarded_to();
        if ((forwarded_to)) {
            event_handled_status status = event_unhandled;
            if ((status = forwarded_to->on_found_node(n))) {
                return status;
            }
        }
        return event_unhandled;
    }

    virtual events_t* forward_searcher_events_to(events_t* to) {
        return 0;
    }
    virtual events_t* searcher_events_forwarded_to() const {
        return 0;
    }
};
typedef searcher_eventst<> searcher_events;

typedef searcher_events searcher_events_extendt_implements;
typedef base searcher_events_extendt_extends;
///////////////////////////////////////////////////////////////////////
///  Class: searcher_events_extendt
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = searcher_events_extendt_implements, 
 class TExtends = searcher_events_extendt_extends>

class _EXPORT_CLASS searcher_events_extendt
: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef typename implements::events_t events_t;

    searcher_events_extendt(events_t* events): events_(events) {
    }
    searcher_events_extendt
    (const searcher_events_extendt &copy): events_(0) {
    }
    searcher_events_extendt(): events_(0) {
    }
    virtual ~searcher_events_extendt() {
    }
    
    virtual events_t* forward_searcher_events_to(events_t* to) {
        events_t* forwarded_to = searcher_events_forwarded_to();
        events_ = to;
        return forwarded_to;
    }
    virtual events_t* searcher_events_forwarded_to() const {
        return events_;
    }

protected:
    events_t* events_;
};
typedef searcher_events_extendt<> searcher_events_extend;

} /// namespace tree
} /// namespace fs
} /// namespace xos

#endif /// _XOS_FS_TREE_SEARCHER_EVENTS_HPP 
