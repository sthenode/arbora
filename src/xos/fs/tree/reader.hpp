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
///   File: reader.hpp
///
/// Author: $author$
///   Date: 5/17/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_TREE_READER_HPP
#define _XOS_FS_TREE_READER_HPP

#include "xos/base/std/tree/read.hpp"
#include "xos/fs/tree/reader_events.hpp"
#include "xos/fs/tree/branch.hpp"

namespace xos {
namespace fs {
namespace tree {

typedef reader_events readert_implements;
typedef std::tree::depth_first_readt
<branch, branches, leaf, node, 
 stream, reader_events, reader_events_extend> readert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: readert
///////////////////////////////////////////////////////////////////////
template 
<class TImplements = readert_implements, class TExtends = readert_extends>

class _EXPORT_CLASS readert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef readert derives;

    typedef reader_events events;

    readert(events* forward_to) {
        this->forward_reader_events_to(forward_to);
    }
    readert() {
    }

protected:
    virtual event_handled_status on_read_node(const fs::tree::node& node) {
        events* forwarded_to = this->reader_events_forwarded_to();
        if ((forwarded_to)) {
            event_handled_status status = event_unhandled;
            if ((status = forwarded_to->on_read_node(node))) {
                return status;
            }
        }
        return extends::on_read_node(node);
    }
};
typedef readert<> reader;

} /// namespace tree
} /// namespace fs
} /// namespace xos

#endif /// _XOS_FS_TREE_READER_HPP 
