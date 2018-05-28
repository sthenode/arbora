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
///   File: branch.hpp
///
/// Author: $author$
///   Date: 4/26/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_STD_TREE_BRANCH_HPP
#define _XOS_BASE_STD_TREE_BRANCH_HPP

#include "xos/base/std/tree/leaf.hpp"

namespace xos {
namespace std {
namespace tree {

///////////////////////////////////////////////////////////////////////
///  Class: reverse_ranget
///////////////////////////////////////////////////////////////////////
template <class trange>
class reverse_ranget {
public:
    reverse_ranget(trange& range): range_(range) {}
    typename trange::reverse_iterator begin() const {
        return range_.rbegin();
    }
    typename trange::reverse_iterator end() const {
        return range_.rend();
    }
protected:
    trange& range_;
};

///////////////////////////////////////////////////////////////////////
///  Class: branchest
///////////////////////////////////////////////////////////////////////
template <class tbranch, class extends = ::std::list<tbranch*> >
class branchest: public extends {
public:
    typedef tbranch branch_t;
    typedef reverse_ranget<branchest> reverse_range;

    branchest() {}
    virtual ~branchest() {}

    virtual tbranch* push_branch(tbranch* first) {
        if (first) { this->push_front(first); }
        return first;
    }
    virtual tbranch* pop_branch() {
        tbranch* first = 0;
        if (!(this->empty())) {
            first = this->front();
            this->pop_front();
        }
        return first;
    }
    virtual tbranch* first_branch() const {
        tbranch* first = 0;
        if (!(this->empty())) {
            first = this->front();
        }
        return first;
    }
    virtual tbranch* last_branch() const {
        tbranch* last = 0;
        if (!(this->empty())) {
            last = this->back();
        }
        return last;
    }
    virtual tbranch* queue_branch(tbranch* last) {
        if (last) { this->push_back(last); }
        return last;
    }
    virtual tbranch* pull_branch() {
        tbranch* last = 0;
        if (!(this->empty())) {
            last = this->back();
            this->pop_back();
        }
        return last;
    }

    virtual void delete_all() {
        for (auto b: *this) {
            if (b) {
                delete b;
                b = 0;
            }
        }
        this->clear();
    }

    static reverse_range reverse_iterate(branchest& branches) {
        return reverse_range(branches);
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: brancht
///////////////////////////////////////////////////////////////////////
template <class tbranch, class tbranches, class tleaves, class extends>
class brancht: public extends {
public:
    typedef typename tleaves::leaf_t tleaf;
    typedef tbranch branch_t;
    typedef tleaves leaves_t;
    typedef typename leaves_t::leaf_t leaf_t;

    brancht(): branch_(0) {}
    virtual ~brancht() {}

    virtual tbranch* push_branch(tbranch* first) {
        return branches_.push_branch(first);
    }
    virtual tbranch* pop_branch() {
        return branches_.pop_branch();
    }
    virtual tbranch* queue_branch(tbranch* last) {
        return branches_.queue_branch(last);
    }
    virtual tbranch* pull_branch() {
        return branches_.pull_branch();
    }
    virtual tbranch* first_branch() const {
        return branches_.first_branch();
    }
    virtual tbranch* last_branch() const {
        return branches_.last_branch();
    }
    virtual tbranch* set_branch(tbranch* to) {
        branch_ = to;
        return branch_;
    }
    virtual tbranch* branch() const {
        return (tbranch*)branch_;
    }
    virtual tbranches& branches() const {
        return (tbranches&)branches_;
    }

    virtual tleaf* push_leaf(tleaf* first) {
        return leaves_.push_leaf(first);
    }
    virtual tleaf* pop_leaf() {
        return leaves_.pop_leaf();
    }
    virtual tleaf* queue_leaf(tleaf* last) {
        return leaves_.queue_leaf(last);
    }
    virtual tleaf* pull_leaf() {
        return leaves_.pull_leaf();
    }
    virtual tleaves& leaves() const {
        return (tleaves&)leaves_;
    }

protected:
    tbranch* branch_;
    tbranches branches_;
    tleaves leaves_;
};

} /// namespace tree
} /// namespace std
} /// namespace xos

#endif /// _XOS_BASE_STD_TREE_BRANCH_HPP 
