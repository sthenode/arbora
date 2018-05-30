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
///   File: read.hpp
///
/// Author: $author$
///   Date: 5/29/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_STD_TREE_READ_HPP
#define _XOS_BASE_STD_TREE_READ_HPP

#include "xos/base/std/tree/search.hpp"
#include "xos/base/exception.hpp"
#include "xos/base/event.hpp"

namespace xos {
namespace std {
namespace tree {

///////////////////////////////////////////////////////////////////////
///  Class: depth_first_readt
///////////////////////////////////////////////////////////////////////
template 
<class branch, class branches, class leaf, class node, 
 class reader, class reader_events, class reader_events_extends>

class depth_first_readt: virtual public reader_events, public reader_events_extends {
public:
    typedef reader_events implements;
    typedef reader_events_extends extends;

    depth_first_readt(branch& root, reader& from) { 
        this->construct();
        if (0 > (this->read(root, from))) {
            const exception e(exception_failed);
            this->destruct(); 
            throw (e);
        }
    }
    depth_first_readt(const depth_first_readt &copy): extends(copy) {
        this->construct(); 
    }
    depth_first_readt() { 
        this->construct(); 
    }
    virtual ~depth_first_readt() { 
        this->destruct(); 
    }
    
    ssize_t read(branch& root, reader& from) {
        ssize_t count = 0, amount = 0;
        node read;

        for (root_ = &root; (amount = read.read(from)); count += amount) {
            if ((0 < (amount))) {
                if (event_handled_success != (this->on_read_node(read))) {
                    count = -1;
                    break;
                }
            } else {
                if (0 > (amount)) {
                    count = amount;
                    break;
                }
            }
        }
        root_ = 0;
        return count;
    }

protected:
    event_handled_status on_read_node(const node& read) {
        if ((root_)) {
            branch& root = *root_;
            size_t depth = read.depth();

            if (0 < (depth)) {

                if ((parent_)) {
                    bool is_less_depth = false, is_greater_depth = false;
                    
                    if ((is_less_depth = (depth < (depth_ + 1)))) {
                        do {
                            if (!(parent_ = stack_.pop_branch())) {
                                return event_handled_failed;
                            } else {
                                depth_ = parent_->depth();
                            }
                        } while (depth < (depth_ + 1));
                    } else {
                        if ((is_greater_depth = (depth > (depth_ + 1)))) {
                            branch* child = 0;

                            if (!(child = parent_->last_branch())) {
                                return event_handled_failed;
                            } else {
                                stack_.push_branch(parent_);
                                depth_ = child->depth();
                                parent_ = child;
                            }
                        }
                    }
                    if ((read.is_directory())) {
                        branch* clone = 0;

                        if (!(clone = root.clone(*parent_, read))) {
                            return event_handled_failed;
                        } else {
                            parent_->queue_branch(clone);
                        }
                   } else {
                        leaf* clone = 0;

                        if (!(clone = leaf_.clone(*parent_, read))) {
                            return event_handled_failed;
                        } else {
                            parent_->queue_leaf(clone);
                            if ((is_greater_depth)) {
                                if (!(parent_ = stack_.pop_branch())) {
                                    return event_handled_failed;
                                } else {
                                    depth_ = parent_->depth();
                                }
                            }
                        }
                   }
                } else {
                    return event_handled_failed;
                }
            } else {
                root = read;
                parent_ = &root;
                depth_ = 0;
            }
        } else {
            return event_handled_failed;
        }
        return event_handled_success;
    }

    void construct() {
        root_ = 0;
        parent_ = 0;
        depth_ = 0;
    }
    void destruct() {
        leaf_.clear(); 
        stack_.clear();
        root_ = 0;
        parent_ = 0;
        depth_ = 0;
    }

protected:
    leaf leaf_;
    branches stack_;
    branch *root_, *parent_;
    size_t depth_;
};

} /// namespace tree
} /// namespace std
} /// namespace xos

#endif /// _XOS_BASE_STD_TREE_READ_HPP 
