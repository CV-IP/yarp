// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
#ifndef _YARP2_NETWORK_
#define _YARP2_NETWORK_

#include <yarp/os/Contact.h>

//protects against some dangerous ACE macros
#ifdef main
#undef main
#endif

namespace yarp {
    namespace os {
        class Network;
    }
}

/**
 * \ingroup comm_class
 *
 * Utilities for manipulating the YARP network.
 */
class yarp::os::Network {
public:
    /**
     * Request that an output port connect to an input port.
     * @param src the name of an output port
     * @param dest the name of an input port
     * @param carrier the name of the protocol to use (tcp/udp/mcast)
     * @param quiet suppress messages displayed upon success/failure
     * @return true on success, false on failure
     */
    static bool connect(const char *src, const char *dest,
                        const char *carrier = 0 /*NULL*/,
                        bool quiet=true);

    /**
     * Request that an output port disconnect from an input port.
     * @param src the name of an output port
     * @param dest the name of an input port
     * @param quiet suppress messages displayed upon success/failure
     * @return true on success, false on failure
     */
    static bool disconnect(const char *src, const char *dest, 
                           bool quiet=true);

    /**
     * The standard main method for the YARP companion utility.
     * @param argc argument count
     * @param argv command line arguments
     * @return 0 on success, non-zero on failure
     */
    static int main(int argc, char *argv[]);


    /**
     * Initialization.  On some operating systems, there are certain
     * start-up tasks that need to be performed, and this method does
     * them.  It is a good idea to call this method near the start of
     * your program, and to call Network::fini towards the end.
     */
    static void init();


    /**
     * Deinitialization.  On some operating systems, there are certain
     * shut-down tasks that need to be performed, and this method does
     * them.  It is a good idea to call Netork::init near the start of
     * your program, and to call this method towards the end.
     */
    static void fini();


    /**
     * Find out information about a registered name.
     * This communicates with the name server to find out
     * what is known about how to contact the entity with the given name
     * (if one exists).
     * @param name the name to query
     * @return full contact information for the name.  If nothing is
     * known about the name, the returned contact is invalid
     * (Contact::isValid returns false)
     */
    static Contact queryName(const char *name);

    /**
     * Register a name with the name server.
     * The name server will allocate a way to contact that name.
     * It is up to you to make sure that this works.
     * @param name the name to register
     * @return the contact information now associated with that name
     * (in other words, what Contact::queryName would now return)
     */
    static Contact registerName(const char *name);

    /**
     * Register contact information with the name server.
     * The name server will fill in any extra information needed
     * to make the contact information complete..
     * @param contact the proposed contact information (may be incomplete)
     * @return the contact information now associated with a name
     * (in other words, what Contact::queryName would now return)
     */
    static Contact registerContact(const Contact& contact);

    /**
     * Removes the registration for a name from the name server.
     * @param name the name to unregister
     * @return the contact information now associated with that name
     * (in other words, what Contact::queryName would now return).
     * This will be the invalid contact (Contact::isValid is false).
     */
    static Contact unregisterName(const char *name);

    /**
     * Removes the registration for a contact from the name server.
     * @param contact the contact to unregister
     * @return the contact information now associated with its former name
     * (in other words, what Contact::queryName would now return).
     * This will be the invalid contact (Contact::isValid is false).
     */
    static Contact unregisterContact(const Contact& contact);


    /**
     * Chooses whether communication is process-local.
     * Call this with flag=true to avoid ever consulting an
     * external nameserver.
     * @param flag true if communication should be local to the calling process.
     * @return prior state of this flag.
     */
    static bool setLocalMode(bool flag);
};

#endif


