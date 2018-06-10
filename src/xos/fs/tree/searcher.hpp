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

typedef std::tree::breadth_first_searcht
 <branch, branches, leaves> breadth_first_search;

typedef std::tree::depth_first_searcht
 <branch, branches, leaves> depth_first_search;

typedef std::tree::depend_first_searcht
 <branch, branches, leaves> depend_first_search;

typedef std::tree::bottom_first_searcht
 <branch, branches, leaves> bottom_first_search;

typedef searcher_events searchert_implements;
typedef searcher_events_extend searchert_extends;
///////////////////////////////////////////////////////////////////////
///  Class: searchert
///////////////////////////////////////////////////////////////////////
template 
<class TSearched = depth_first_search,
 class TImplements = searchert_implements, class TExtends = searchert_extends>

class _EXPORT_CLASS searchert: virtual public TImplements, public TExtends {
public:
    typedef TImplements implements;
    typedef TExtends extends;
    typedef searchert derives;
    typedef TSearched searched;

    searchert(searcher_events* events): extends(events) {
    }
    searchert(const searchert &copy) {
    }
    searchert() {
    }
    virtual ~searchert() {
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
        std::tree::findt<branch, searched, derives> search(*this, b);
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
};
typedef searchert<> searcher;
typedef searchert<breadth_first_search> breadth_first_searcher;
typedef searchert<depth_first_search> depth_first_searcher;
typedef searchert<depend_first_search> depend_first_searcher;
typedef searchert<bottom_first_search> bottom_first_searcher;

} /// namespace tree
} /// namespace fs
} /// namespace xos

#endif /// _XOS_FS_TREE_SEARCHER_HPP 
