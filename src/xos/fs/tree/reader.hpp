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

#include "xos/base/std/tree/search.hpp"
#include "xos/fs/tree/reader_events.hpp"
#include "xos/fs/tree/branch.hpp"

namespace xos {
namespace fs {
namespace tree {

typedef reader_events reader_implementt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: reader_implementt
///////////////////////////////////////////////////////////////////////
template <class TImplements = reader_implementt_implements>
class _EXPORT_CLASS reader_implementt: virtual public TImplements {
public:
    typedef TImplements implements;
};
typedef reader_implementt<> reader_implement;

typedef reader_implement readert_implements;
typedef reader_events_extend readert_extends;
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

    typedef reader_events events_t;

    readert(events_t* events): extends(events) {
        construct();
    }
    readert(const readert &copy): extends(copy) {
        construct();
    }
    readert() {
        construct();
    }
    virtual ~readert() {
        destruct();
    }

    virtual ssize_t read(branch& root, stream& from) {
        ssize_t count = 0;
        fs::tree::node node;

        root_ = &root;
        do {
            if ((0 < (count = node.read(from)))) {
                if (event_handled_success != (on_read_node(node))) {
                    break;
                }
            } else {
                if (0 > (count))
                    return -1;
            }
        } while (0 < (count));
        root_ = 0;
        return count;
    }
    
protected:
    virtual event_handled_status on_read_node(const fs::tree::node& node) {
        events_t* forwarded_to = this->reader_events_forwarded_to();
        if ((forwarded_to)) {
            event_handled_status status = event_unhandled;
            if ((status = forwarded_to->on_read_node(node))) {
                return status;
            }
        }
        if ((root_)) {
            branch& root = *root_;
            size_t depth = node.depth();

            if (0 < (depth)) {

                if ((parent_)) {
                    bool is_less_depth = false, is_greater_depth = false;
                    
                    if ((is_less_depth = (depth < (depth_ + 1)))) {
                        do {
                            if (!(parent_ = stack_.pop_branch())) {
                                LOG_ERROR("...failed on stack_.pop_branch()");
                                return event_handled_failed;
                            } else {
                                depth_ = parent_->depth();
                            }
                        } while (depth < (depth_ + 1));
                    } else {
                        if ((is_greater_depth = (depth > (depth_ + 1)))) {
                            fs::tree::branch* child = 0;

                            if (!(child = parent_->last_branch())) {
                                LOG_ERROR("...failed on parent_->last_branch()");
                                return event_handled_failed;
                            } else {
                                stack_.push_branch(parent_);
                                depth_ = child->depth();
                                parent_ = child;
                            }
                        }
                    }
                    if ((node.is_directory())) {
                        fs::tree::branch* branch = 0;

                        if (!(branch = root.clone(*parent_, node))) {
                            LOG_ERROR("...failed on tree_.clone(node)");
                            return event_handled_failed;
                        } else {
                            parent_->queue_branch(branch);
                        }
                   } else {
                        fs::tree::leaf* leaf = 0;

                        if (!(leaf = leaf_.clone(*parent_, node))) {
                            LOG_ERROR("...failed on leaf_.clone(node)");
                            return event_handled_failed;
                        } else {
                            parent_->queue_leaf(leaf);
                            if ((is_greater_depth)) {
                                if (!(parent_ = stack_.pop_branch())) {
                                    LOG_ERROR("...failed on stack_.pop_branch()");
                                    return event_handled_failed;
                                } else {
                                    depth_ = parent_->depth();
                                }
                            }
                        }
                   }
                } else {
                    LOG_ERROR("...failed on (parent_)");
                    return event_handled_failed;
                }
            } else {
                root = node;
                parent_ = &root;
                depth_ = 0;
            }
        } else {
            LOG_ERROR("...failed on (root_)");
            return event_handled_failed;
        }
        return event_handled_success;
    }

    virtual void construct() {
        root_ = (0);
        parent_ = (0);
        depth_ = (0);
    }
    virtual void destruct() {
        leaf_.clear();
        stack_.clear();
    }

protected:
    leaf leaf_;
    branches stack_;
    branch *root_, *parent_;
    size_t depth_;
};
typedef readert<> reader;

} /// namespace tree
} /// namespace fs
} /// namespace xos

#endif /// _XOS_FS_TREE_READER_HPP 
