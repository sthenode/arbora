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
#ifndef _XOS_FS_TREE_NODE_HPP
#define _XOS_FS_TREE_NODE_HPP

#include "xos/base/std/tree/node.hpp"
#include "xos/fs/directory/entry.hpp"
#include "xos/base/to_string.hpp"
#include "xos/io/stream.hpp"

namespace xos {
namespace fs {
namespace tree {

class node;
class leaf;
class branch;
typedef directory::entry entry;
typedef io::char_stream stream;
typedef std::tree::nodet<branch, leaf, node, stream, entry> node_extends;
///////////////////////////////////////////////////////////////////////
///  Class: node
///////////////////////////////////////////////////////////////////////
class node: public node_extends {
public:
    typedef node_extends extends;
    typedef node derives;

    typedef extends::string_t string_t;
    typedef string_t::char_t char_t;

    node(const string_t& path, const string_t& name, fs::entry_type type) {
        construct(path.chars(), name.chars(), type);
    }
    node(const string_t& path, fs::entry_type type) {
        construct(path.chars(), type);
    }
    node(const string_t& path, const fs::directory::entry& entry) {
        construct(path.chars(), entry);
    }
    node(const char* path, const char* name, fs::entry_type type) {
        construct(path, name, type);
    }
    node(const char* path, fs::entry_type type) {
        construct(path, type);
    }
    node(const char* path, const fs::directory::entry& entry) {
        construct(path, entry);
    }
    node(const fs::directory::entry& entry) {
        construct(entry);
    }
    node(const node& copy) {
        construct(copy);
    }
    node() {
        construct();
    }
    virtual ~node() {
        destruct();
    }

    virtual ssize_t write(stream& to) const {
        to.write(unsigned_to_string(this->depth()).chars());
        to.write(" ");
        if (0 < (this->depth())) {
            to.write(this->name());
            to.write(" ");
            to.write(unsigned_to_string(this->type()).chars());
        } else {
            to.write(this->path_name());
        }
        to.write("\n");
        return 0;
    }
    virtual ssize_t read(stream& from) {
        ssize_t count = 0, amount = 0;
        char_t c = 0;
        string_t s;
        this->clear();
        for (on_read_ = &derives::on_read_depth; 
             (0 < (amount = from.read(&c, 1))); count += amount) {
            if (0 < (amount = on_read(s, c, amount))) {
                count += amount;
                continue;
            } else {
                if (0 > (amount)) {
                    count = amount;
                }
            }
            break;
        }
        return count;
    }
    ssize_t (derives::*on_read_)(string_t& s, char_t& c, size_t size);
    virtual ssize_t on_read(string_t& s, char_t& c, size_t size) {
        if ((on_read_)) {
            return (this->*on_read_)(s, c, size);
        }
        return -1;
    }
    virtual ssize_t on_read_depth(string_t& s, char_t& c, size_t size) {
        switch ((char_t)c) {
        case ' ':
            if ((s.length())) {
                LOG_DEBUG("...depth = " << s << " on_read_ = &derives::on_read_name");
                on_read_ = &derives::on_read_name;
                set_depth(s.to_unsigned());
                s.clear();
            } else {
                LOG_ERROR("...unexpected char " << char_to_string(c) << "");
                return -1;
            }
            break;
        case '\n':
            return 0;
        default:
            if ((c < '0') || (c > '9')) {
                LOG_ERROR("...invalid char " << char_to_string(c) << "");
                return -1;
            } else {
                s.append(&c, 1);
            }
            break;
        }
        return size;
    }
    virtual ssize_t on_read_name(string_t& s, char_t& c, size_t size) {
        switch ((char_t)c) {
        case ' ':
            if ((s.length())) {
                LOG_DEBUG("...name = \"" << s << "\" on_read_ = &derives::on_read_type");
                on_read_ = &derives::on_read_type;
                set_name(s.chars());
                s.clear();
            } else {
                LOG_ERROR("...unexpected char " << char_to_string(c) << "");
                return -1;
            }
            break;
        case '\n':
            if ((s.length())) {
                LOG_DEBUG("...path name = \"" << s << "\"");
                set_path_name(s.chars());
                s.clear();
            } else {
                LOG_ERROR("...unexpected char " << char_to_string(c) << "");
                return -1;
            }
            return 0;
        default:
            s.append(&c, 1);
            break;
        }
        return size;
    }
    virtual ssize_t on_read_type(string_t& s, char_t& c, size_t size) {
        switch ((char_t)c) {
        case '\n':
            size = 0;
        case ' ':
            if ((s.length())) {
                LOG_DEBUG("...type = " << s << "");
                set_type(s.to_unsigned());
                s.clear();
            } else {
                LOG_ERROR("...unexpected char " << char_to_string(c) << "");
                return -1;
            }
            break;
        default:
            if ((c < '0') || (c > '9')) {
                LOG_ERROR("...invalid char " << char_to_string(c) << "");
                return -1;
            } else {
                s.append(&c, 1);
            }
            break;
        }
        return size;
    }

    using extends::set;
    virtual node& set(const char* path, const char* name, fs::entry_type type) {
        this->set_path_name(path, name);
        this->set_path(path);
        this->set_name(name);
        this->set_type(type);
        return *this;
    }
    virtual node& set(const char* path, fs::entry_type type) {
        this->set_path_name(path);
        this->set_type(type);
        return *this;
    }
    virtual node& set(const char* path, const fs::directory::entry& entry) {
        extends::set(entry);
        this->set_path_name(path);
        return *this;
    }
    virtual node& set(const node& copy) {
        extends::set(copy);
        this->set_depth(copy.depth());
        return *this;
    }
    virtual node& clear() {
        extends::clear();
        this->set_depth(0);
        return *this;
    }

protected:
    template <class derives>
    derives* clone(const node& parent, const node& node) const {
        derives* n = 0;
        if ((n = new derives(node))) {
            const char_t *path = 0, *name = 0;
            if ((path = parent.has_path_name()) && (name = node.has_name())) {
                n->set_path(path);
                n->set_path_name(path, name);
            }
        }
        return n;
    }

private:
    void construct(const char* path, const char* name, fs::entry_type type) {
        construct();
        this->set_path_name(path, name);
        this->set_path(path);
        this->set_name(name);
        this->set_type(type);
    }
    void construct(const char* path, fs::entry_type type) {
        construct();
        this->set_path_name(path);
        this->set_type(type);
    }
    void construct(const char* path, const fs::directory::entry& entry) {
        construct(entry);
        this->set_path_name(path);
    }
    void construct(const fs::directory::entry& entry) {
        construct();
        this->set(entry);
    }
    void construct(const node& copy) {
        construct();
        this->set(copy);
    }
    void construct() {
    }
    void destruct() {
    }
    
protected:
};
typedef std::tree::nodest<branch, leaf, node, stream> nodes;

} /// namespace tree
} /// namespace fs
} /// namespace xos

#endif /// _XOS_FS_TREE_NODE_HPP 
