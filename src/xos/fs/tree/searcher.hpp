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
///   File: searcher.hpp
///
/// Author: $author$
///   Date: 5/24/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_FS_TREE_SEARCHER_HPP
#define _XOS_FS_TREE_SEARCHER_HPP

#include "xos/base/std/tree/search.hpp"
#include "xos/fs/tree/searcher_events.hpp"
#include "xos/fs/tree/branch.hpp"

namespace xos {
namespace fs {
namespace tree {

typedef searcher_events searcher_implementt_implements;
///////////////////////////////////////////////////////////////////////
///  Class: searcher_implementt
///////////////////////////////////////////////////////////////////////
template <class TImplements = searcher_implementt_implements>
class _EXPORT_CLASS searcher_implementt: virtual public TImplements {
public:
    typedef TImplements implements;
};
typedef searcher_implementt<> searcher_implement;

typedef searcher_implement searchert_implements;
typedef searcher_events_extend searchert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: searchert
///////////////////////////////////////////////////////////////////////
template <class TImplements = searchert_implements, class TExtends = searchert_extends>
class _EXPORT_CLASS searchert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef searchert derives;

    searchert(searcher_events* events): extends(events), search_(0) {
    }
    searchert(const searchert &copy): search_(0) {
    }
    searchert(): search_(0) {
    }
    virtual ~searchert() {
    }

    virtual ssize_t depth_first_search(branch& b, const char_t* path) {
        ssize_t count = 0;
        search_ = &derives::depth_first_search;
        count = search(b, path);
        search_ = 0;
        return count;
    }
    virtual ssize_t breadth_first_search(branch& b, const char_t* path) {
        ssize_t count = 0;
        search_ = &derives::breadth_first_search;
        count = search(b, path);
        search_ = 0;
        return count;
    }
    virtual ssize_t search(branch& b, const char_t* path) {
        ssize_t count = 0;
        if ((path) && (path[0])) {
            count = search(b = (path));
        }
        return count;
    }

    virtual ssize_t search(branch& b) {
        ssize_t count = 0;
        if ((search_)) {
            count = (this->*search_)(b);
        } else {
            count = depth_first_search(b);
        }
        return count;
    }
    virtual ssize_t depth_first_search(branch& b) {
        ssize_t count = 0;
        std::tree::findt
        <branch, std::tree::depth_first_searcht
         <branch, branches, leaves>, derives> search(*this, b);
        return count;
    }
    virtual ssize_t breadth_first_search(branch& b) {
        ssize_t count = 0;
        std::tree::findt
        <branch, std::tree::breadth_first_searcht
         <branch, branches, leaves>, derives> search(*this, b);
        return count;
    }

    virtual branch* found(branch* b) {
        if ((b)) {
            this->on_found_branch(*b);
        }
        for (auto l: b->leaves()) {
            found(l);
        }
        return 0;
    }
    virtual leaf* found(leaf* l) {
        if ((l)) {
            this->on_found_leaf(*l);
        }
        return 0;
    }

protected:
    ssize_t (derives::*search_)(branch& b);
};
typedef searchert<> searcher;

} /// namespace tree
} /// namespace fs
} /// namespace xos

#endif /// _XOS_FS_TREE_SEARCHER_HPP 
