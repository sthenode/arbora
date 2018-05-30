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
///   File: write.hpp
///
/// Author: $author$
///   Date: 5/29/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_STD_TREE_WRITE_HPP
#define _XOS_BASE_STD_TREE_WRITE_HPP

#include "xos/base/std/tree/search.hpp"
#include "xos/base/exception.hpp"
#include "xos/base/event.hpp"

namespace xos {
namespace std {
namespace tree {

///////////////////////////////////////////////////////////////////////
///  Class: depth_first_writet
///////////////////////////////////////////////////////////////////////
template 
<class branch, class branches, class leaf, class leaves, class node, 
 class writer, class searcher_events, class searcher_events_extends>

class depth_first_writet: virtual public searcher_events, public searcher_events_extends {
public:
    typedef searcher_events implements;
    typedef searcher_events_extends extends;
    typedef depth_first_writet derives;
    
    depth_first_writet(branch& root, writer& to): to_(to) {
        if (0 > (this->write(root, to))) {
            const exception e(exception_failed);
            throw (e);
        }
    }
    depth_first_writet(const depth_first_writet &copy): to_(copy.to_) {
    }
    depth_first_writet(writer& to): to_(to) {
    }
    virtual ~depth_first_writet() {
    }

    size_t write(branch& root) {
        ssize_t count = 0;
        std::tree::findt
        <branch, std::tree::depth_first_searcht
         <branch, branches, leaves>, derives> search(*this, root);
        return count;
    }
    
    virtual branch* found(branch* b) {
        if ((b)) {
            if (event_handled_success != (this->on_found_branch(*b))) {
                return b;
            }
        }
        for (auto l: b->leaves()) {
            if ((found(l))) {
                return b;
            }
        }
        return 0;
    }
    virtual leaf* found(leaf* l) {
        if ((l)) {
            if (event_handled_success != (this->on_found_leaf(*l))) {
                return l;
            }
        }
        return 0;
    }

protected:
    event_handled_status on_found_node(const node& found) {
        if (0 <= (found.write(to_))) {
            return event_handled_success;
        }
        return event_handled_failed;
    }

protected:
    writer& to_;
};

} /// namespace tree
} /// namespace std
} /// namespace xos

#endif /// _XOS_BASE_STD_TREE_WRITE_HPP 
