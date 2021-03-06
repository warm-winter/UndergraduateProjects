//
// Generated file, do not edit! Created by opp_msgc 4.1 from common/OverSimMessage.msg.
//

#ifndef _OVERSIMMESSAGE_M_H_
#define _OVERSIMMESSAGE_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0401
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>common/OverSimMessage.msg</tt> by opp_msgc.
 * <pre>
 * packet OverSimMessage
 * {
 *     @customize(true);
 * }
 * </pre>
 *
 * OverSimMessage_Base is only useful if it gets subclassed, and OverSimMessage is derived from it.
 * The minimum code to be written for OverSimMessage is the following:
 *
 * <pre>
 * class OverSimMessage : public OverSimMessage_Base
 * {
 *   public:
 *     OverSimMessage(const char *name=NULL, int kind=0) : OverSimMessage_Base(name,kind) {}
 *     OverSimMessage(const OverSimMessage& other) : OverSimMessage_Base(other.getName()) {operator=(other);}
 *     OverSimMessage& operator=(const OverSimMessage& other) {OverSimMessage_Base::operator=(other); return *this;}
 *     virtual OverSimMessage *dup() const {return new OverSimMessage(*this);}
 *     // ADD CODE HERE to redefine and implement pure virtual functions from OverSimMessage_Base
 * };
 * </pre>
 *
 * The following should go into a .cc (.cpp) file:
 *
 * <pre>
 * Register_Class(OverSimMessage);
 * </pre>
 */
class OverSimMessage_Base : public ::cPacket
{
  protected:

    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OverSimMessage_Base&);
    // make constructors protected to avoid instantiation
    OverSimMessage_Base(const char *name=NULL, int kind=0);
    OverSimMessage_Base(const OverSimMessage_Base& other);
    // make assignment operator protected to force the user override it
    OverSimMessage_Base& operator=(const OverSimMessage_Base& other);

  public:
    virtual ~OverSimMessage_Base();
    virtual OverSimMessage_Base *dup() const {throw cRuntimeError("You forgot to manually add a dup() function to class OverSimMessage");}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
};


#endif // _OVERSIMMESSAGE_M_H_
