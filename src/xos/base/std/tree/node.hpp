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
///   File: node.hpp
///
/// Author: $author$
///   Date: 5/18/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_BASE_STD_TREE_NODE_HPP
#define _XOS_BASE_STD_TREE_NODE_HPP

#include "xos/base/base.hpp"
#include <list>

namespace xos {
namespace std {
namespace tree {

///////////////////////////////////////////////////////////////////////
///  Class: nodest
///////////////////////////////////////////////////////////////////////
template 
<class tbranch, class tleaf, class tnode, 
 class tstream, class extends = ::std::list<tnode*> >

class nodest: public extends {
public:
    typedef tbranch branch_t;
    typedef tleaf leaf_t;
    typedef tnode node_t;

    nodest() {}
    virtual ~nodest() {}

    virtual tnode* push_node(tnode* first) {
        if (first) { this->push_front(first); }
        return first;
    }
    virtual tnode* pop_node() {
        tnode* first = 0;
        if (!(this->empty())) {
            first = this->front();
            this->pop_front();
        }
        return first;
    }
    virtual tnode* queue_node(tnode* last) {
        if (last) { this->push_back(last); }
        return last;
    }
    virtual tnode* pull_node() {
        tnode* last = 0;
        if (!(this->empty())) {
            last = this->back();
            this->pop_back();
        }
        return last;
    }

    virtual void delete_all() {
        for (auto n: *this) {
            if (n) {
                delete n;
                n = 0;
            }
        }
        this->clear();
    }

    virtual ssize_t write(tstream& to) const {
        ssize_t count = 0, amount = 0;
        for (auto n: *this) {
            if (n) {
                if (0 < (amount = n->write(to))) {
                    count += amount;
                } else {
                    if (0 > (amount)) {
                        return amount;
                    }
                }
            }
        }
        return count;
    }
    virtual ssize_t read(tnode& n, tstream& from) {
        ssize_t count = 0, amount = 0;
        tbranch* b = 0;
        tleaf* l = 0;
        delete_all();
        do {
            if (0 < (amount = n.read(from))) {
                if ((b = ((tbranch*)n))) {
                    if ((b = b->clone())) {
                        queue_node(b);
                    } else {
                        count = amount = -1;
                    }
                } else {
                    if ((l = ((tleaf*)n))) {
                        if ((l = l->clone())) {
                            queue_node(l);
                        } else {
                            count = amount = -1;
                        }
                    } else {
                        count = amount = -1;
                    }
                }
            }
        } while (0 < (amount));
        if (0 > (count)) {
            delete_all();
        }
        return count;
    }
};

///////////////////////////////////////////////////////////////////////
///  Class: nodet
///////////////////////////////////////////////////////////////////////
template <class tbranch, class tleaf, class tnode, class tstream, class extends>
class nodet: public extends {
public:
    typedef tbranch branch_t;
    typedef tleaf leaf_t;

    nodet(): depth_(0) {}
    virtual ~nodet() {}

    virtual ssize_t write(tstream& to) const {
        return 0;
    }
    virtual ssize_t read(tstream& from) {
        return 0;
    }
    virtual operator tbranch* () const {
        return 0;
    }
    virtual operator tleaf* () const {
        return 0;
    }

    virtual size_t set_depth(size_t to) {
        depth_ = to;
        return depth_;
    }
    virtual size_t depth() const {
        return depth_;
    }

protected:
    size_t depth_;
};

} /// namespace tree
} /// namespace std
} /// namespace xos

#endif /// _XOS_BASE_STD_TREE_NODE_HPP 
