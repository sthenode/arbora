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
///   File: search.hpp
///
/// Author: $author$
///   Date: 4/26/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_STD_TREE_SEARCH_HPP
#define _XOS_BASE_STD_TREE_SEARCH_HPP

#include "xos/base/std/tree/branch.hpp"

namespace xos {
namespace std {
namespace tree {

///////////////////////////////////////////////////////////////////////
///  Class: findt
///////////////////////////////////////////////////////////////////////
template <class branch, class extends, class find>
class findt: public extends {
public:
    findt(find& _find, branch& b): find_(_find) { 
        this->search(&b); 
    }
    virtual branch* found(branch* b) {
        return find_.found(b);
    }
protected:
    find& find_;
};

///////////////////////////////////////////////////////////////////////
///  Class: searcht
///////////////////////////////////////////////////////////////////////
template <class branch>
class searcht {
public:
    searcht() {}
    virtual ~searcht() {}
    virtual void search(branch* b) {}
    virtual branch* found(branch* b) { return 0; }
};

///////////////////////////////////////////////////////////////////////
///  Class: breadth_first_searcht
///////////////////////////////////////////////////////////////////////
template <class branch, class branches, class extends = searcht<branch> >
class breadth_first_searcht: public brancht<branch, branches, extends> {
public:
    breadth_first_searcht() {}
    breadth_first_searcht(branch* v) { this->search(v); }
    virtual void search(branch* v) {
        if (v) {
            do {
                if (this->found(v)) { break; }
                for (auto b: v->branches()) {
                    this->queue_branch(b);
                }
            } while ((v = this->pop_branch()));
        }
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: depth_first_searcht
///////////////////////////////////////////////////////////////////////
template <class branch, class branches, class extends = searcht<branch> >
class depth_first_searcht: public brancht<branch, branches, extends> {
public:
    depth_first_searcht() {}
    depth_first_searcht(branch* v) { this->search(v); }
    virtual void search(branch* v) {
        if (v) {
            do {
                if (this->found(v)) { break; }
                for (auto b: v->branches()) {
                    this->push_branch(b);
                }
            } while ((v = this->pop_branch()));
        }
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: depend_first_searcht
///////////////////////////////////////////////////////////////////////
template <class branch, class branches>
class depend_first_searcht: public brancht<branch, branches, searcht<branch> > {
public:
    depend_first_searcht() {}
    depend_first_searcht(branch* v) { this->search(v); }
    virtual void search(branch* v) {
        if (v) {
            do {
                stack_.push_branch(v);
                for (auto b: v->branches()) {
                    this->push_branch(b);
                }
            } while ((v = this->pop_branch()));
            while ((v = stack_.pop_branch())) {
                if (this->found(v)) { break; }
            }
        }
    }
protected:
    branches stack_;
};

} /// namespace tree
} /// namespace std
} /// namespace xos

#endif /// _XOS_BASE_STD_TREE_SEARCH_HPP 
