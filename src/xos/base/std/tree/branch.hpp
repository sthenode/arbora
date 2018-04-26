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

#include "xos/base/base.hpp"

#include <list>

namespace xos {
namespace std {
namespace tree {

///////////////////////////////////////////////////////////////////////
///  Class: branchest
///////////////////////////////////////////////////////////////////////
template <class branch, class extends = ::std::list<branch*> >
class branchest: public extends {
public:
    branchest() {}
    virtual ~branchest() {}
    virtual branch* push_branch(branch* first) {
        if (first) { this->push_front(first); }
        return first;
    }
    virtual branch* pop_branch() {
        branch* first = 0;
        if (!(this->empty())) {
            first = this->front();
            this->pop_front();
        }
        return first;
    }
    virtual branch* queue_branch(branch* last) {
        if (last) { this->push_back(last); }
        return last;
    }
    virtual branch* pull_branch() {
        branch* last = 0;
        if (!(this->empty())) {
            last = this->back();
            this->pop_back();
        }
        return last;
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: brancht
///////////////////////////////////////////////////////////////////////
template <class branch, class tbranches, class extends>
class brancht: public extends {
public:
    brancht() {}
    virtual ~brancht() {}
    virtual branch* push_branch(branch* first) {
        return branches_.push_branch(first);
    }
    virtual branch* pop_branch() {
        return branches_.pop_branch();
    }
    virtual branch* queue_branch(branch* last) {
        return branches_.queue_branch(last);
    }
    virtual branch* pull_branch() {
        return branches_.pull_branch();
    }
    virtual tbranches& branches() const {
        return (tbranches&)branches_;
    }
protected:
    tbranches branches_;
};

} /// namespace tree
} /// namespace std
} /// namespace xos

#endif /// _XOS_BASE_STD_TREE_BRANCH_HPP 
