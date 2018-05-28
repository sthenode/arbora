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
///   File: main.hpp
///
/// Author: $author$
///   Date: 4/26/2018
///////////////////////////////////////////////////////////////////////
#ifndef _XOS_APP_CONSOLE_ARBORA_MAIN_HPP
#define _XOS_APP_CONSOLE_ARBORA_MAIN_HPP

#include "xos/console/getopt/main.hpp"
#include "xos/console/output_stream.hpp"
#include "xos/io/crt/file.hpp"
#include "xos/os/fs/entry.hpp"
#include "xos/fs/tree/reader.hpp"
#include "xos/fs/tree/searcher.hpp"

namespace xos {
namespace app {
namespace console {
namespace arbora {

typedef fs::tree::reader_events maint_reader_events_implements;
typedef fs::tree::searcher_events maint_searcher_events_implements;
typedef xos::console::getopt::main::implements maint_implements;
typedef xos::console::getopt::main maint_extends;
///////////////////////////////////////////////////////////////////////
///  Class: maint
///////////////////////////////////////////////////////////////////////
template 
<class TReaderEventsImplements = maint_reader_events_implements, 
 class TSearcherEventsImplements = maint_searcher_events_implements, 
 class TImplements = maint_implements, class TExtends = maint_extends>
class _EXPORT_CLASS maint
: virtual public TReaderEventsImplements, virtual public TSearcherEventsImplements, 
  virtual public TImplements, public TExtends {
public:
    typedef TReaderEventsImplements reader_events;
    typedef TSearcherEventsImplements searcher_events;
    typedef TImplements implements;
    typedef TExtends extends;
    typedef maint derives;

    typedef typename extends::string_t string_t;
    typedef typename string_t::char_t char_t;
    
    maint(): on_found_node_(0) {
    }
    virtual ~maint() {
    }
private:
    maint(const maint &copy): on_found_node_(0) {
    }

protected:
    virtual int run(int argc, char_t** argv, char_t** env) {
        const char_t* arg = 0;
        int err = 0;

        if ((optind < argc) && (arg = argv[optind]) && (arg[0])) {
            os::os::fs::entry entry;

            if ((entry.exists(arg))) {
                fs::tree::searcher searcher(this);

                if ((entry.is_directory())) {
                    on_found_node_ = &derives::on_found_node_write;
                    searcher.search(root_, arg);
                } else {
                    io::crt::char_file file;

                    if ((file.open(arg))) {
                        fs::tree::reader reader(this);
                        ssize_t count = 0;
                        count = reader.read(root_, file);
                        file.close();
                        on_found_node_ = &derives::on_found_node_output;
                        searcher.search(root_);
                    }
                }
            }
        } else {
            err = this->usage(argc, argv, env);
        }
        return err;
    }

    event_handled_status (derives::*on_found_node_)(const fs::tree::node& node);
    virtual event_handled_status on_found_node(const fs::tree::node& node) {
        if ((this->on_found_node_)) {
            return (this->*on_found_node_)(node);
        }
        return event_handled_failed;
    }
    virtual event_handled_status on_found_node_output(const fs::tree::node& node) {
        const char_t *path = node.path(), *name = node.name(),
                     *slash = ((path) && (path[0]) && (path[0]!='/'))?("/"):("");
        this->outlln(path, slash, name, NULL);
        return event_handled_success;
    }
    virtual event_handled_status on_found_node_write(const fs::tree::node& node) {
        xos::console::output_stream ostream(*this);
        node.write(ostream);
        return event_handled_success;
    }

    virtual event_handled_status on_read_node(const fs::tree::node& node) {
        return event_unhandled;
    }

protected:
    fs::tree::branch root_;
};
typedef maint<> main;

} /// namespace arbora
} /// namespace console
} /// namespace app
} /// namespace xos

#endif /// _XOS_APP_CONSOLE_ARBORA_MAIN_HPP 
