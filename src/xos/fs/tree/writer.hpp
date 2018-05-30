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
///   File: writer.hpp
///
/// Author: $author$
///   Date: 5/30/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_TREE_WRITER_HPP
#define _XOS_FS_TREE_WRITER_HPP

#include "xos/base/std/tree/write.hpp"
#include "xos/fs/tree/searcher_events.hpp"
#include "xos/fs/tree/branch.hpp"

namespace xos {
namespace fs {
namespace tree {

typedef searcher_events writert_implements;
typedef std::tree::depth_first_writet
<branch, branches, leaf, leaves, node, 
 stream, searcher_events, searcher_events_extend> writert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: writert
///////////////////////////////////////////////////////////////////////
template <class TImplements = writert_implements, class TExtends = writert_extends>

class _EXPORT_CLASS writert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;

    typedef searcher_events events;

    writert(branch& root, stream& to): extends(root, to) {
    }
    writert(stream& to, events* forward_to): extends(to) {
        this->forward_searcher_events_to(forward_to);
    }
    writert(stream& to): extends(to) {
    }

protected:
    virtual event_handled_status on_found_node(const fs::tree::node& node) {
        events* forwarded_to = this->searcher_events_forwarded_to();
        if ((forwarded_to)) {
            event_handled_status status = event_unhandled;
            if ((status = forwarded_to->on_found_node(node))) {
                return status;
            }
        }
        return extends::on_found_node(node);
    }
};
typedef writert<> writer;

} /// namespace tree
} /// namespace fs
} /// namespace xos

#endif /// _XOS_FS_TREE_WRITER_HPP 
