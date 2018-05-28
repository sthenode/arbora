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
///   File: leaf.hpp
///
/// Author: $author$
///   Date: 5/15/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_STD_TREE_LEAF_HPP
#define _XOS_BASE_STD_TREE_LEAF_HPP

#include "xos/base/base.hpp"
#include <list>

namespace xos {
namespace std {
namespace tree {

///////////////////////////////////////////////////////////////////////
///  Class: leavest
///////////////////////////////////////////////////////////////////////
template <class tleaf, class extends = ::std::list<tleaf*> >
class leavest: public extends {
public:
    typedef tleaf leaf_t;

    leavest() {}
    virtual ~leavest() {}

    virtual tleaf* push_leaf(tleaf* first) {
        if (first) { this->push_front(first); }
        return first;
    }
    virtual tleaf* pop_leaf() {
        tleaf* first = 0;
        if (!(this->empty())) {
            first = this->front();
            this->pop_front();
        }
        return first;
    }
    virtual tleaf* queue_leaf(tleaf* last) {
        if (last) { this->push_back(last); }
        return last;
    }
    virtual tleaf* pull_leaf() {
        tleaf* last = 0;
        if (!(this->empty())) {
            last = this->back();
            this->pop_back();
        }
        return last;
    }

    virtual void delete_all() {
        for (auto l: *this) {
            if (l) {
                delete l;
                l = 0;
            }
        }
        this->clear();
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: leaft
///////////////////////////////////////////////////////////////////////
template <class tbranch, class extends>
class leaft: public extends {
public:
    typedef tbranch branch_t;

    leaft(): branch_(0) {}
    virtual ~leaft() {}

    virtual tbranch* set_branch(tbranch* to) {
        branch_ = to;
        return branch_;
    }
    virtual tbranch* branch() const {
        return (tbranch*)branch_;
    }

protected:
    tbranch* branch_;
};

} /// namespace tree
} /// namespace std
} /// namespace xos

#endif /// _XOS_BASE_STD_TREE_LEAF_HPP 
