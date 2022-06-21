/*
 *  This file is part of the  Linux Kernel Driver Package for EXTOLL R2.
 *
 *  Copyright (C) 2012 EXTOLL GmbH
 *
 *  Written by Tobias Groschup (2012), Sarah Neuwirth (2016)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _EXTOLL_KAPI_H_
#define _EXTOLL_KAPI_H_

#include "arch_define.h"

/*!
 * \file extoll_kapi.h
 * \brief Header file for the Linux Kernel API of Extoll R2
 * \author Tobias Groschup
 */

/*!
 \mainpage Linux Kernal API for EXTOLL R2
 
 \section INTRO Introduction
 
 This kernel module enables other kernel modules to use the EXTOLL network with a few simple function calls.
 All operations on the EXTOLL device, like send a message via VELO, receive a message, perform a put with RMA, perform a get with RMA, lock a lock, receive a message from RMA etc. are possible with without the need to handle the EXTOLL device by hand.


 Example of usage (Open the RMA device, send a message, receive a notification, close the device):
 \code
  RMA2_Handle *rhandle;
  RMA2_Notification *noti;
  kapi_rma2_open(&rhandle);
  
  kapi_rma2_put_bt(rhandle, remote_nodeid, remote_vpid, (void *)buffer, (void *)buffer_recv, 1, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT, RMA2_CONN_DEFAULT);

  kapi_rma2_noti_fetch(rhandle, noti);
  kapi_rma2_noti_dump(noti); 
  
  kapi_rma2_close(&rhandle);
 \endcode


 Currently implemented: VELO, Post RMA commands, read RMA Notifications.
  \todo api cleanup
  \todo benchmarks
 */
#include "extolldrv.h"
#include "velo2drv.h"
#include "rma2drv.h"
#include "extoll_bq.h"

#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/completion.h>

/*!
 * \defgroup EXTOLL Definitions used by both VELO and RMA
 * @{
 */
/*!
 * \brief Type for an EXTOLL VPID. 
 * 
 * As a VPID is 8 bits long in both the RMA and the VELO descriptors, we use a type for the VPIDs.
 */
typedef uint8_t vpid_t;

/*!
 * \brief Type for an EXTOLL node ID.
 * 
 * As a node ID is 16 bits long in both the RMA and the VELO descriptors, we use a type for the node IDs.
 */
typedef uint16_t nodeid_t;

typedef  enum {
  KAPI_WCB_OK,
  KAPI_WCB_RETRY_NEEDED,
  KAPI_WCB_NOTFULL,
  KAPI_WCB_FULL    
} kapi_wcb_send_state_t;

typedef  enum {
  KAPI_REPLAY_OK,
  KAPI_REPLAY_START,
  KAPI_REPLAY_IDLE,
  KAPI_REPLAY_EMPTY,
  KAPI_REPLAY_REPLAY,
  KAPI_REPLAY_NOTEMPTY  
} kapi_wcb_replay_state_t;


typedef  enum {
  KAPI_WCB_VELO,
  KAPI_WCB_RMA
} kapi_wcb_type_t;

struct kapi_wcb_info;

typedef void (*kapi_replay_callback_t)(struct kapi_wcb_info* info);

typedef struct kapi_wcb_info {
  kapi_wcb_type_t function;
  vpid_t vpid;
  void* parent; //pointer to associated handle (either velo or rma handle)
  uint64_t wcb_state;
  
  uint64_t* packet_buffer; //! buffer to save packets to be sent
  uint32_t committed_count;
  uint32_t packet_wp;
  uint64_t retried_packet_count;
    
  uint64_t retry;
  uint64_t retry_count;
  uint64_t assembly;
  uint64_t streamout;
  
  kapi_wcb_send_state_t state;
  kapi_wcb_replay_state_t replay_state;
  
  struct tasklet_struct tasklet;
  kapi_replay_callback_t callback;
  unsigned long tasklet_timeout_us;
  int disable_tasklet;
  
} kapi_wcb_info_t;



/*@}*/
/* **************************************************************************************
 * VELO datastructures
 * ************************************************************************************/
/*! \defgroup VDATA Datastructures for the VELO part of the Kernel API.
 * @{
 */ 
/*!
 * \brief This structure holds all informations for a opened VELO device. It is necessary to perform operations with VELO.
 
 Do not modify the content of this struct. Always use the given methods (e.g. \a kapi_velo2_open or \a kapi_velo2_close) initialise or to read values.
 
 */
typedef struct VELO2_Handle{
  velo_port_t *port; //! Pointer to underlying structure of the velo-driver. useful for identification.
  nodeid_t nodeid; //! Node ID of this node.
  vpid_t vpid; //! VPID of process (or module) which holds this VELO port.
  volatile uint64_t *header; //! Pointer to the first message in buffer queue.
  volatile uint64_t *msg; //! Pointer to the next message to be read.
  bq_descriptor_t *descs; //! Pointer to the bq-descriptors.
  uint64_t current_desc; //! Number of the current descriptor.
  unsigned int slots_read; //! Number of buffer queue slots read in one descriptor.
  
  //fields for wcbuf retry handling
  kapi_wcb_info_t wcb;
}VELO2_Handle;

/*!
 * \brief Software representation of the Header/Status word of a Velo message in memory
 */
#pragma pack(1)
typedef struct {
	unsigned int source_node : 16;
	unsigned int source_vpid : 10;
	unsigned int : 6; 
	unsigned int mtt : 2;
	unsigned int : 2;
	unsigned int eom : 1;
	unsigned int err : 1;
	unsigned int : 2;
	unsigned int tag : 8;
	unsigned int length : 12;
	unsigned int : 4;
} VELO2_Status;

#pragma pack()

/* !
 * \brief this enumeration contains the various error codes a function of the kernel apis VELO part can return.
 * They also contain all possibilities to return standard linux kernel error codes.
 * /
typedef enum {
  VELO_NO_NEW_MESSAGE,
  VELO_UNKNOWN_ERROR = -1,
  VELO_NO_ERROR = 0,
} velo_return_t;
*/
/*! @} */

/* *************************************************************************************
 * RMA Datastructures
 * ************************************************************************************/
/*! \defgroup RDATA Datastructures for the RMA  part of the Kernel API.
 * @{
 */ 

/*!
 * \brief Software representation of a RMA2 Descriptor.
 */
typedef struct {
  uint64_t value[3]; //!< the encoded value of the three words of the descriptor as it is passed to hardware
  uint64_t reserved0; //!< reserved field
  uint64_t reserved1; //!< reserved field
  uint64_t reserved2; //!< reserved field
  uint64_t reserved3; //!< reserved field
} RMA2_Descriptor;

/*!
 * \brief Software representation of the RMA Notifications
 */

#pragma pack(1)
typedef struct {
  union {
    uint64_t value; //! First part of the notification.
  } word0;
   union {
    uint64_t value; //! Second part of the notification.
  } word1;
 /*               NEEDS SOME SERIOUS THINKING
  union {
    uint64_t local_address; //!< NLA or physical address involved on this node, used for put/get commmands
    uint64_t immediate_value; //!< immediate value (for notification put operations)
    struct {
      uint16_t lock_id_low; //!<  bit 0-15 of the lock id
      uint8_t  lock_id_high; //!< bit 16-23 of the lock id
      uint8_t  lock_result; //!< A requester notification from a lock operation contains a 0, otherwise it contains a 1 if successfull, 0 otherwise
      uint32_t lock_value; //!< lock value after the operation was performed (successfully or no
     } lock; //! < used for lock operation, encodes lock id, result and val
  } operand;
  union {
    struct {
      uint16_t   payload_length_low; //!< bit 0-15 of the payload size
      uint8_t    payload_length_high; //!< bit 16-23 of the payload size
    } length; //! < used for put/get operation, codes the payload length
    struct {
      uint16_t   target; //!< 0 if the target of the lock was the Completer, 1 if the target was the responder
      uint8_t    reserved; //!< reserved
    } target; //! < used for lock operation, contains the target unit
      struct {
        uint16_t   immediate_value_high; //!< additional 9 bit of payload of the notification put are encoded in this field
        uint8_t    reserved; //!< reserved
      } immediate_high; //! < used for immediate put operations, contains additional payload
  } info;
   uint8_t    remote_vpid;  //!< 8 bit VPID field
   uint16_t   command_field; //!< 3 bit notification, 4 bit command, 6 bit mode and 3 bit error fields
   uint16_t   remote_nodeid; //!< the remote node that was involved in this command
   */
} RMA2_Notification;
#pragma pack()

/*!
 * \brief This structure holds all informations for a opened RMA device. It is necessary to perform operations with RMA.
 
 Do not modify the content of this struct. Always use the given methods (e.g. \a kapi_rma2_open or \a kapi_rma2_close) initialise or to read values.
 
 */

typedef struct RMA2_Handle {
  rma_port_t *port; //! Pointer to underlying structure of the RMA driver.
  nodeid_t nodeid; //! Node ID of this node.
  vpid_t vpid; //! VPID of the process owning this RMA2_Handle.
  uint32_t mtu; //! RMA MTU size
  uint64_t **requester; //! Pointer to the requester-page for this port and VPID.
  RMA2_Descriptor *descriptors; //! One descriptor for each RMA command pre-allocated.
  volatile uint64_t *header; //!Pointer to the status word of the next message.
  volatile uint64_t *msg; //! Pointer to the next message.
  bq_descriptor_t *descs; //! Pointer to the bq-descriptors.
  //uint64_t current_msg;
  uint64_t current_desc; //! number of the current descriptor
  unsigned int slots_read; //! number of slots read in one descriptor

  kapi_wcb_info_t wcb;
  struct page* rra_page;

} RMA2_Handle;

/*!
\brief Enumeration to specify the notifications a command can cause.

In EXTOLL RMA2, a command can cause three types of notifications:
\li requester notifications
\li completer notifications
\li responder notifications
Using a RMA2_notification_spec it is possible to request that a command
causes a certain notification or not. 
A command may only cause notifications at units it actually passes through:
\li all put-like commands may cause requester and completer notifications
\li all get-like comands (including locks) may cause all notifications
There exists a number of predefined constants for the most often used 
combinations. If a combinations that has no predefined encoding is wanted,
the different specs may be ored together.
The RMA2_notification_spec modifies a (basic) command in a number of ways
and as such increases the flexibility of the RMA2 command system
considerably.
Note: If the ERA command modifier for a command is set, a single software transaction may spawn many commands, one for each generated fragment.
*/
typedef enum {
  RMA2_REQUESTER_NOTIFICATION  = 1, //!< A requester notification should be issued for this command
  RMA2_RESPONDER_NOTIFICATION  = 2, //!< A responder notification should be issued for this command
  RMA2_COMPLETER_NOTIFICATION  = 4, //!< A completer notification should be issued for this command
  RMA2_REQCOMPL_NOTIFICATION   = 5, //!< Both a requester and a completer notification should be issued for this command
  RMA2_RESPCOMPL_NOTIFICATION  = 6, //!< Both a responder and a completer notification should be issued for this command
  RMA2_ALL_NOTIFICATIONS       = 7, //!< All possible notification should be issued for this command
  RMA2_NO_NOTIFICATION         = 0  //!< No notification should be issued for this command
} RMA2_Notification_Spec;

  /*!
   *    \brief Enumeration to specify different options to the connect call
   * 
   * Interrupts are disabled by default.
   * Not implemented: intterupts and transmission classes. Every commad posted with interrupt has TC 0.
   */
typedef enum {
  RMA2_CONN_DEFAULT = 0, //!default: everything disabled, TC 0
  RMA2_CONN_TC0     = 0, //! Trasnsmission Class 0
  RMA2_CONN_TC1     = 1, //! Trasnsmission Class 1
  RMA2_CONN_TC2     = 2, //! Trasnsmission Class 2
  RMA2_CONN_TC3     = 3, //! Trasnsmission Class 3
  RMA2_CONN_RRA     = 4, //! Remote Registerfile Acces
  RMA2_CONN_IRQ     = 8, //! Interrupt enabled
  RMA2_CONN_TE     = 16, //! Interrupt enabled
} RMA2_Connection_Options;

/*!
\brief Encoding of the RMA2 Command Modifiers

This is the encoding of all of the commands modifiers of the RMA2 unit. Several of these modifiers may be or'ed together.
RMA2 Command modifier are actually 4bit values, as they are passed to the requester.
*/
typedef enum {
  RMA2_CMD_DEFAULT=0, //!< default modifier, i.e. normal transfer without any special features turned on
  RMA2_CMD_MC = 1, //!< this command should be send as a multicast. Destination node id will be interpreted as a multicast group. Multicast must be enabled for this VPID.
  RMA2_CMD_NTR =2, //!< notification replicate modifier. Software requests larger than the MTU will be split. If this bit is set, each fragment generates a notification. Usefull when running on adaptive routing channels
  RMA2_CMD_ERA =4, //!< Excellerate Read Access. RMA2 will not read from main memory but from Excellerate Unit. Advanced usage. Must be enabled for this VPID.
  RMA2_CMD_EWA =8  //!< Excellerate Write Access. RMA2 will not write to main memory but to Excellerate Unit. Advanced usage. Must be enabled for this VPID.
}  RMA2_Command_Modifier;

 /*!
    \brief Encoding of the RMA2 Notification Modifiers

    This is the encoding of all of the modifiers within a RMA2 notification. Several of this modifiers may be or'ed together.
    RMA2 Notification modifiers are actually 6bit values.
  */
typedef enum {
  RMA2_NOTI_RRA  = 1, //!< command addressed remote registers and not memory
  RMA2_NOTI_IRQ  = 2, //!< command (i.e. notification) caused an interrupt
  RMA2_NOTI_TE   = 4,  //!< command operated on translated addresses or physical addresses
  RMA2_NOTI_EWA  = 8,  //!< Excellerate Write Access. RMA2 will not write to main memory but to Excellerate Unit. Advanced usage. Must be enabled for this VPID.
  RMA2_NOTI_NTR  = 16, //!< notification replicate modifier. Software requests larger than the MTU will be split. If this bit is set, each fragment generates a notification. Usefull when running on adaptive routing channels    
  RMA2_NOTI_ERA  = 32 //!< Excellerate Read Access. RMA2 will not read from main memory but from Excellerate Unit. Advanced usage. Must be enabled for this VPID.
}  RMA2_Notification_Modifier;

  /*!
   * \brief Encoding of the RMA2 commands
   * 
   * This is the encoding of all of the commands of the RMA2 unit. In addition, 
   * wildcard encodings for the matching functions are given.
   * RMA2 Commands are actually 4bit values.
   */
  typedef enum {
  RMA2_BT_GET          = 0, //!< Byte get command
  RMA2_QW_GET          = 1, //!< Quadword get command
  RMA2_BT_PUT          = 2, //!< Byte put command
  RMA2_QW_PUT          = 3, //!< Quadword put command
  RMA2_LOCK            = 4, //!< Lock command
  RMA2_NOTIFICATION_PUT= 5, //!< Notification Put command (one quadword plus one byte class)
  RMA2_IMMEDIATE_PUT   = 6, //!< Immediate Put command (one byte to one quadword)    
  RMA2_GET_BT_RSP      = 10, //!< Byte get commandresponse command (generated by HW as response to an RMA2_GET_BT)
  RMA2_GET_QW_RSP      = 11, //!< Quadword get commandresponse command (generated by HW as response to an RMA2_GET_QW)

  RMA2_LOCK_REQ        = 12,    //!< Lock command (FCAA), request command
  RMA2_LOCK_RSP        = 13,    //!< Lock command (FCAA), response command (generated by HW as response to an RMA2_LOCK_REQ)  
}RMA2_Command;

  
/* @} */
/* **************************************************************************************
 * VELO open and close methods
 * ************************************************************************************/
/*! \defgroup VOPENCLOSE Functions to open and close a VELO device.
 * @{
 */ 

/*!
 \brief Initialises the VELO handle/port. Also takes care of memory allocation.
 @param handle Pointer to the handle pointer. A module should declare a pointer to a \a VELO2_Handle struct. This method initialises the datastructure and sets the pointer to the \a VELO2_Handle accordingly.
 @param vpid Request a specific VPID. If the VPID is in use return error. If the parameter is given with -1, acquire any free vpid
 @return Linux error codes. Exspecially if the memory allocation was successful.
 */
int kapi_velo2_open(VELO2_Handle **handle, int vpid);

/*!
 \brief  Closes the VELO handle. Also frees all memory.
 @param handle Pointer to the handle pointer to be closed. Handle pointer will be NULL afterwards.
 @return Linux error codes.
 */
int kapi_velo2_close(VELO2_Handle **handle);

/* 
 * \brief Get the node ID of a VELO handle.
 *
 * @param handle The handle.
 * @return The node ID.
 */
nodeid_t kapi_velo2_get_nodeid(VELO2_Handle *handle);

/* 
 * \brief Get the VPID of a VELO handle.
 *
 * @param handle The handle.
 * @return The VPID.
 */
vpid_t kapi_velo2_get_vpid(VELO2_Handle *handle);
/*! @} */
/* **************************************************************************************
 * RMA  open and close methods
 * ************************************************************************************/
/*! \defgroup RVOPENCLOSE Functions to open and close a RMA device/connection.
 * @{
 */ 

/*!
 \brief Initialises the RMA handle/port. Also takes care of memory allocation.
 @param handle Pointer to the handle pointer. A module should declare a pointer to a \a RMA2_Handle struct. This method initialises the datastructure and sets the pointer to the \a RMA2_Handle accordingly.
 @param vpid Request a specific VPID. If the VPID is in use return error. If the parameter is given with -1, acquire any free vpid
 @return Linux error codes. Exspecially if the memory allocation was successful.
 */
int kapi_rma2_open(RMA2_Handle **handle, int vpid);

/*!
 \brief  Closes the RMA handle. Also frees all memory.
 @param handle Pointer to the handle pointer to be closed. handle pointer will be NULL afterwards.
 @return Linux error codes.
 */
int kapi_rma2_close(RMA2_Handle **handle);

/*! 
 * \brief Get the node ID of a RMA Handle.
 *
 * @param handle The handle.
 * @return The node ID.
 */
nodeid_t kapi_rma2_get_nodeid(RMA2_Handle *handle);

/*!
 * \brief Get the VPID of a RMA Handle.
 *
 * @param handle The handle.
 * @return The VPID.
 */
vpid_t kapi_rma2_get_vpid(RMA2_Handle *handle);

/*!
 * \brief Get the RMA MTU size
 *
 * @return The MTU size
 */
uint32_t kapi_rma2_get_mtu(RMA2_Handle *hanlde);

/*! @} */
/* *******************************************************************************************
 * Velo: Send and Receive Methods 
 * *****************************************************************************************/
/*! \defgroup VSENDRECEIVE Functions to send and receive via the VELO device.
 * @{
 */
/*!
 \brief Send a message with the VELO device.
 @param handle Handle of the used VELO device.
 @param destination_nodeid Nodeid of the receiving process' node. If the mc bit is set (multicast bit) indicates the multicast group to be used.
 @param destination_vpid VPID of the receiving process.
 @param buffer Pointer to the data to be send.
 @param buffer_length Length of the buffer to be send.
 @param tag User-defined tag of the data to be send.
 @param mtt User-definde message type tag.
 @param mc Indicates if this message should be a multicast (0 meas no multicast)
 @param interrupt Indicates, if interrupts should be used, Not tested yet.
 @return Linux error codes.
 */
int kapi_velo2_send(VELO2_Handle *handle, nodeid_t destination_nodeid, vpid_t destination_vpid, void *buffer, uint16_t buffer_length, uint8_t tag, int mtt, int mc, int interrupt);

/*!
 \brief Send a message with a given header.
 @param handle Handle of the used VELO device.
 @param destination_nodeid Nodeid of the receiving process' node. If the mc bit is set (multicast bit) indicates the multicast group to be used.
 @param destination_vpid VPID of the receiving process.
 @param buffer Pointer to the data to be send.
 @param buffer_length Length of the buffer to be send, in bytes.
 @param header the header
 @param haeder_length the length of the header, in quadwords
 @param tag User-defined tag of the data to be send.
 @param mtt User-definde message type tag.
 @param mc Indicates if this message should be a multicast (0 meas no multicast)
 @param interrupt Indicates, if interrupts should be used, Not tested yet.
 @return Linux error codes.
 */
int kapi_velo2_send_header(VELO2_Handle *handle, nodeid_t destination_nodeid, vpid_t destination_vpid, void *buffer, uint16_t buffer_length, uint64_t *header, unsigned int header_length, uint8_t tag, int mtt, int mc, int interrupt);

/*!
 \brief Wait for a message to be ready to be received, blocking.
 Note that this function may block forever, so it is not recommended to use it!
 
 Use kapi_velo2_recv_complete() to complete receiving of the message.
 The invoking function has to provide valid pointers for all parameters!
 
 @param handle Handle of the VELO device to be used.
 @param srcid  Pointer to a variable where the originating nodeid,vpid as sourceid will be stored
 @param len Pointer to a variable where the length of the message to be received will be stored
 @param mtt Pointer to a variable where the MTT of the message will be stored
 @param tag Pointer to a variable where the 8 bit tag of the message will be stored
 */
void kapi_velo2_wait(VELO2_Handle *handle,uint32_t* srcid, uint32_t* len, uint8_t* mtt, uint8_t* tag);
/*!
 \brief Check for a message to be ready to be received, non-blocking.
 
 If this function returns 0 a new message is ready be received. Use kapi_velo2_recv_complete() for that.
 The invoking function has to provide valid pointers for all parameters!
 
 @param handle Handle of the VELO device to be used.
 @param srcid  Pointer to a variable where the originating nodeid,vpid as sourceid will be stored
 @param len Pointer to a variable where the length of the message to be received will be stored
 @param mtt Pointer to a variable where the MTT of the message will be stored
 @param tag Pointer to a variable where the 8 bit tag of the message will be stored
 @return 0 if message available, -1 if no message is available currently
 */
int kapi_velo2_check(VELO2_Handle *handle,uint32_t* srcid, uint32_t* len, uint8_t* mtt, uint8_t* tag);

/*!
 \brief Check for a message to be ready to be received, non-blocking.
 
 This function completes receiving of a message. MAY only be called after a successfull call to kapi_velo2_wait() or kapi_velo2_check()!
 
 The invoking function has to provide valid pointers for all parameters!
 The buffer must be large enough to hold the message (should be known from calling kapi_velo2_wait() or kapi2_velo_check()
 
 @param handle Handle of the VELO device to be used.
 @param buffer Pointer to the memory where the received message should be stored.
 @return returns the number of receives that have been completed by sw, which are not yet committed to hw using kapi_velo2_recv_commit()
 */
int kapi_velo2_recv_complete(VELO2_Handle *handle, void *buffer);

/*!
 \brief Check for a message to be ready to be received, non-blocking.
 
 This function completes receiving of a message, minus the header bytes. MAY only be called after a successfull call to kapi_velo2_wait() or kapi_velo2_check()!
 
 The invoking function has to provide valid pointers for all parameters!
 The buffer must be large enough to hold the message (should be known from calling kapi_velo2_wait() or kapi2_velo_check()
 
 @param handle Handle of the VELO device to be used.
 @param buffer Pointer to the memory where the received message should be stored.
 @param hlen how many quadwords is the header consisting of
 @return returns 0 on success, else -1
 */
int kapi_velo2_recv_header(VELO2_Handle *handle, void *buffer, unsigned int hlen);

/*!
 \brief Check for a message to be ready to be received, non-blocking.
 
 This function completes receiving of a message, minus the header bytes. MAY only be called after a successfull call to kapi_velo2_wait() or kapi_velo2_check()!
 
 The invoking function has to provide valid pointers for all parameters!
 The buffer must be large enough to hold the message (should be known from calling kapi_velo2_wait() or kapi2_velo_check()
 
 @param handle Handle of the VELO device to be used.
 @param buffer Pointer to the memory where the received message should be stored.
 @param skip how many header quadwords need to skipped at the beginning of the buffer
 @return returns the number of receives that have been completed by sw, which are not yet committed to hw using kapi_velo2_recv_commit()
 */
int kapi_velo2_recv_payload(VELO2_Handle *handle, void *buffer, unsigned int skip);

/*!
 \brief Commit the current receive status back to hw
 
 After one or more messages have been received, commit the receive status back to hw. Failure to commit will eventually lead to a full receive buffer.
 It is ok though, to call this function only after a few messages have been received. Set the update_irq parameter to re-enable interrupts for this VPID.
 
 @param handle Handle of the VELO device to be used.
 @param update_irq flag, if the VELO irq mechanism should be update, so new interrupts will be generated for newly incoming interrupt requesting messages
 */
void kapi_velo2_recv_commit(VELO2_Handle *handle, int update_irq);

/*!
 \brief Receive a message via velo, blocking. NOT RECOMMENDED
 This function is blocking and not recommended to be used. Internally it calls kapi_velo2_wait(), kapi_velo2_recv_complete() and kapi_velo2_recv_commit().
 
 The module invoking this method has to check that the buffer is large enough for the expected message. So this means the buffer needs to be able to hold at least 120 bytes,
 since the size of the message is not known at the time of invocation.
  
 @param handle Handle of the VELO device to be used.
 @param buffer Pointer to the memory where the received message should be stored.
 @param srcid  Pointer to a variable where the originating nodeid,vpid as sourceid will be stored
 @param len Pointer to a variable where the length of the message to be received will be stored
 @param mtt Pointer to a variable where the MTT of the message will be stored
 @param tag Pointer to a variable where the 8 bit tag of the message will be stored
 @param update_irq flag, if the VELO irq mechanism should be update, so new interrupts will be generated for newly incoming interrupt requesting messages
 @return Linux error codes.
 */
int kapi_velo2_receive(VELO2_Handle *handle, void *buffer, uint32_t* srcid, uint32_t* len, uint8_t* mtt, uint8_t* tag, int update_irq);

/*!
 \brief Receive a message non blocking. The functions return code indicates if a messages has arrived and has been read. In case of no new message, the buffer is left untouched.

Internally it calls kapi_velo2_check(), kapi_velo2_recv_complete() and kapi_velo2_recv_commit().

 The module invoking this method has to check that the buffer is large enough for the expected message. So this means the buffer needs to be able to hold at least 120 bytes,
 since the size of the message is not known at the time of invocation.
  
 @param handle Handle of the VELO device to be used.
 @param buffer Pointer to the memory where the received message should be stored.
 @param srcid  Pointer to a variable where the originating nodeid,vpid as sourceid will be stored
 @param len Pointer to a variable where the length of the message to be received will be stored
 @param mtt Pointer to a variable where the MTT of the message will be stored
 @param tag Pointer to a variable where the 8 bit tag of the message will be stored
 @param update_irq flag, if the VELO irq mechanism should be update, so new interrupts will be generated for newly incoming interrupt requesting messages
 @return -1 of no message was available or if there was an error, otherwise the number of receives that have been completed by sw, which are not yet committed to hw using kapi_velo2_recv_commit()
 */
int kapi_velo2_receive_nb(VELO2_Handle *handle, void *buffer, uint32_t* srcid,  uint32_t* len, uint8_t* mtt, uint8_t* tag, int update_irq);

/*! @} */
/* **************************************************************************************
 * Issue a RMA command
 * ************************************************************************************/
/*! \defgroup RMAPOST Functions to post commands to the RMA device.
 * @{
 */
/*!
 * \brief Post a get byte command to the hardware.
 *
 * @param handle Handle for the RMA desvice to be used..
 * @param nodeid Node ID of the node where the data should be fetched.
 * @param vpid VPID of the target process on the remote node..
 * @param source_addr pointer to the data which should be fetched to the remote node..
 * @param dest_addr physical address on the remote node, where the data should be fetched..
 * @param count Number of consecutive bytes to be fetched. Minimum 1, max 2^23 (see RMA spec).
 * @param noti Which notifications should be issued..
 * @param  modifier Modifier of the command.
 * @param option Additional connection options, traffic class, interrupt etc.
 * @return Standard Linux Error Codes, 0 on success.
 */
int kapi_rma2_get_bt(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, void *source_addr, void *dest_addr, uint32_t count, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option);

/*!
 * \brief Post a get quadword command to the hardware.
 *
 * @param handle Handle for the RMA desvice to be used.
 * @param nodeid Node ID of the node where the data should be fetched.
 * @param vpid VPID of the target process on the remote node.
 * @param source_addr pointer to the data which should be fetched to the remote node.
 * @param dest_addr physical address on the remote node, where the data should be fetched.
 * @param count Number of consecutive quadwords to be fetched. Minimum 1, max 2^23 (see RMA spec).
 * @param noti Which notifications should be issued.
 * @param modifier Modifier of the command.
 * @param option Additional connection options, traffic class, interrupt etc.
 * @return Standard Linux Error Codes, 0 on success.
 */
int kapi_rma2_get_qw(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, void *source_addr, void *dest_addr, uint32_t count, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option);


/*!
 * \brief Post a put byte command to the hardware.
 *
 * @param handle Handle for the RMA desvice to be used.
 * @param nodeid Node ID of the node where the data should be put.
 * @param vpid VPID of the target process on the remote node.
 * @param source_addr pointer to the data which should be put to the remote node.
 * @param dest_addr physical address on the remote node, where the data should be put.
 * @param count Number of consecutive bytes to be put. Minimum 1, max 2^23 (see RMA spec).
 * @param noti Which notifications should be issued.
 * @param modifier Modifier of the command.
 * @param option Additional connection options, traffic class, interrupt etc.
 * @return Standard Linux Error Codes, 0 on success.
 */
int kapi_rma2_put_bt(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, void *source_addr, void *dest_addr, uint32_t count, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option);

/*!
 * \brief Post a put quadword command to the hardware.
 *
 * @param handle Handle for the RMA desvice to be used.
 * @param nodeid Node ID of the node where the data should be put.
 * @param vpid VPID of the target process on the remote node.
 * @param source_addr pointer to the data which should be put to the remote node.
 * @param dest_addr physical address on the remote node, where the data should be put.
 * @param count Number of consecutive quadwords to be put. Minimum 1, max 2^23 (see RMA spec).
 * @param noti Which notifications should be issued.
 * @param modifier Modifier of the command.
 * @param option Additional connection options, traffic class, interrupt etc.
 * @return Standard Linux Error Codes, 0 on success.
 */
int kapi_rma2_put_qw(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, void *source_addr, void *dest_addr, uint32_t count, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option);


/*!
 *  \brief Post a lock request
 * 
 * @param handle Handle for the RMA desvice to be used.
 * @param nodeid Target node ID.
 * @param vpid Target VPID.
 * @param target 0 to target completer, 1 to target responder unit.
 * @param lock_number  Lock identifier.
 * @param cmp_value Compare value for the FCAA operation.
 * @param add_value Add operand for the FCAA operation.
 * @param noti Which notifications should be issued.
 * @param modifier Modifier of the command.
 * @param option Additional connection options, traffic class, interrupt etc.
 * @return Standard Linux Error Codes, 0 on success.
 */
int kapi_rma2_post_lock(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, uint32_t  target,  uint32_t lock_number, int32_t cmp_value, int32_t add_value, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option);

/*!
 * \brief Post a immediate put command to the hardware.
 *
 * @param handle Handle for the RMA desvice to be used.
 * @param nodeid Node ID of the node where the data should be put.
 * @param vpid VPID of the target process on the remote node.
 * @param value Value to be put.
 * @param class Class of the notification put.
 * @param noti Which notifications should be issued.
 * @param modifier Modifier of the command.
 * @param option Additional connection options, traffic class, interrupt etc.
 * @return Standard Linux Error Codes, 0 on success.
 */
int kapi_rma2_put_notification(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, uint64_t value, uint16_t class, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option);

/*!
 * \brief Post a immediate put command to the hardware.
 *
 * @param handle Handle for the RMA desvice to be used.
 * @param nodeid Node ID of the node where the data should be put.
 * @param vpid VPID of the target process on the remote node.
 * @param value Value to be put.
 * @param dest_addr physical address on the remote node, where the data should be put.
 * @param count Number of consecutive quadwords to be put. Minimum 1, max 2^23 (see RMA spec).
 * @param noti Which notifications should be issued.
 * @param modifier Modifier of the command.
 * @param option Additional connection options, traffic class, interrupt etc.
 * @ * @return Standard Linux Error Codes, 0 on success.
 */
int kapi_rma2_put_immediate(RMA2_Handle *handle, nodeid_t nodeid, vpid_t vpid, uint64_t value, void *dest_addr, uint32_t count, RMA2_Notification_Spec noti, RMA2_Command_Modifier modifier, RMA2_Connection_Options option);

/*!
 * @}
 * \defgroup RMANOTI RMA Notification handling.
 * @{
 */

/*!
 * \brief Fetches the next notification from the buffer. Blocking
 * 
 * @param handle Handle for the RMA desvice to be used.
 * @param noti The fetched notification is copied to this location. Enough memory to hold a notification must be allocated.
 * @return Standard Linux error codes.
 */
int kapi_rma2_noti_fetch(RMA2_Handle *handle, RMA2_Notification **noti);

/* \brief Free the notification after use.
 */ 
int kapi_rma2_noti_free(RMA2_Handle *handle, int update_irq);

/*!
 * \brief Commit notifications which are marked as read to the hardware.
 *
 * @param update_irq: 1 if irqs should be enabled, 0 if not
 */
int kapi_rma2_noti_commit(RMA2_Handle *handle, int update_irq);

/*!
 * \brief Mark a notification as read.
 */
int kapi_rma2_noti_mark_read(RMA2_Handle *handle);

/*!
 * \brief Dumps the content of a notification to the kernel log file.
 * 
 * @param noti The notification to be dumped.
 */
void kapi_rma2_noti_dump(RMA2_Notification *noti);

/*!
 * \brief Check for a new Notification
 *
 * @return 0 if no new message is available, 1 if a unread notification is there.
 */
int kapi_rma2_noti_peek(RMA2_Handle *handle);

/*!
 * \brief Fetches a new notification, but only if a unread notification is in the buffer.
 * 
 * If a new notification is available, ths method behaves like \a kapi_rma2_noti_fetch. If no new notification is in the buffer, the function returns immediatly.
 * 
 * @param handle Handle for the RMA desvice to be used..
 * @param noti Pointer to the memory, where a new notification should be copied. If no new notification can be read, the memory is left untouched.
 * 
 * @return Standard Linux error codes. 0 if a new notification was read, 1 if no new notification is available.
 */
int kapi_rma2_noti_fetch_nb(RMA2_Handle *handle, RMA2_Notification **noti);

/*!
 * \brief Get the command of a notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The command of the notification.
 */
RMA2_Command kapi_rma2_noti_get_cmd(RMA2_Notification* noti);

/*!
 * \brief Get the type of a notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The type of the notification.
 */
RMA2_Notification_Spec kapi_rma2_noti_get_notification_type(RMA2_Notification* noti);

/*!
 * \brief Get the modifcation value of a notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The modification value of the notification.
 */
RMA2_Notification_Modifier kapi_rma2_noti_get_mode(RMA2_Notification *noti);

/*!
 * \brief Get the error value of a notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The error value of the notification.
 */
uint8_t kapi_rma2_noti_get_error(RMA2_Notification* noti);

/*!
 * \brief Get the node ID of the remote node from a notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The remote nodeid.
 */
nodeid_t kapi_rma2_noti_get_remote_nodeid(RMA2_Notification* noti);

/*!
 * \brief Get the VPID of the sending process from a notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The VPID of the sending process.
 */
vpid_t kapi_rma2_noti_get_remote_vpid(RMA2_Notification* noti);

/*!
 * \brief Get the size from a notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The size the command was issued with.
 */
uint32_t kapi_rma2_noti_get_size(RMA2_Notification* noti);

/*!
 * \brief Get the local address where the data was wirtten from a notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The local address.
 */
uint64_t kapi_rma2_noti_get_local_address(RMA2_Notification* noti);

/*!uint32_t* len, uint8_t* mtt, uint8_t* tag,
 * \brief Get the payload from a notification-put notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The payload.
 */
uint64_t kapi_rma2_noti_get_notiput_payload(RMA2_Notification* noti);

/*!
 * \brief Get the class from a notification-put notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The class of the notification.
 */
uint8_t kapi_rma2_noti_get_notiput_class(RMA2_Notification* noti);

/*!
 * \brief Get the lock value from  a lock notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The lock value.
 */
uint32_t kapi_rma2_noti_get_lock_value(RMA2_Notification* noti);

/*!
 * \brief Get the lock number from  a lock notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The lock number.
 */
uint32_t kapi_rma2_noti_get_lock_number(RMA2_Notification* noti);

/*!
 * \brief Get lock result from a lock notification.
 *
 * @param noti The notification from which the information should be read.
 * @return The lock result.
 */
uint8_t kapi_rma2_noti_get_lock_result(RMA2_Notification* noti);

/*!@}*/
/* *************************************************************************
 * Remote RF access
 * ************************************************************************/
/*! \defgroup RRA Functions to access remote RF entries
 * @{
 */
/*!
 * \brief Remote RF write
 *
 * @param dest_nodeid Node ID of the remote Extoll device
 * @dest_rra_address Physical address of the RF entry
 * @value 64bit value that should be written to dest_rra_address
 * @timeout timeout in usec for the noti to arrive
 * @return Standard Linux error codes, 0 on success
 */
int kapi_rra_write(RMA2_Handle *rhandle, uint16_t dest_nodeid, uint64_t dest_rra_address, uint64_t value,uint64_t timeout);

/*!
 * \brief Remote RF read
 *
 * @param dest_nodeid Node ID of remote Extoll device
 * @dest_rra_addr Physical address of the RF entry
 * @timeout timeout in usec for the noti to arrive
 * @return Value of remote RF entry
 */
uint64_t kapi_rra_read(RMA2_Handle *rhandle,  uint16_t dest_nodeid, uint64_t dest_rra_addr,uint64_t* value, uint64_t timeout);
/*!@}*/

/* *************************************************************************
 * Handle scatter/gather list mapping via ATU2
 * ************************************************************************/
/*!
* \brief Map a scatter/gather list to an NLA.
*
* @param vpid: The VPID the page list should be mapped for
* @param sg: The array of scatter/gather entries
* @param count: The number of scatter/gather entries
* @param nla: the NLA
* @return Linux error codes
*/
int kapi_atu2_map_sg(int vpid, struct scatterlist *sg, unsigned long count, unsigned long *nla);

/*!
* \brief Map a page list to an NLA.
*
* @param vpid: The VPID the page list should be mapped for
* @param pagelist: Pointer to the first struct page* of the page vector
* @param count: The number of scatter/gather entries
* @param stride: Number of bytes to be added to reach the next struct page in the vector
* @param nla: the NLA
* @return Linux error codes
*/
int kapi_atu2_map_pagelist(int vpid, struct page **pagelist, unsigned long count, unsigned int stride, unsigned long *nla);

/*!
* \brief Unmap a scatter/gather list.
*
* @param vpid: VPID
* @param count: Number of mapped pages
* @param nla: NLA that should be unregistered
* @return Linux error codes
*/
int kapi_atu2_unmap_sg(int vpid, unsigned long count, unsigned long nla);

/* *************************************************************************
 * Handle external IRQs. Needed for network-attached accelerators.
 * ************************************************************************/
void kapi_irq_register(irq_handler_t handler_fn);
void kapi_irq_register_with_arguments(irq_handler_t handler_fn, int irq, void *nvl);
void kapi_irq_unregister(void);

/* *************************************************************************
 * WCB Handling 
 * ************************************************************************/
/*!
* \brief Register a callback function called when a wcb fix was succesfull
*/
void kapi_velo2_wcb_register_callback(VELO2_Handle *handle,kapi_replay_callback_t f);

/*
* \brief Check wheter WCB is in good state
*
* Should be called after one or a series of velo send have been performed.
* Returns 0 on sucess. If return value != 0 kapi_velo2_wcb_fix() should be called,
* to fix the situation.
*/
int kapi_velo2_wcb_check(VELO2_Handle* handle,int us_timeout);
/*
* \brief Check whether WCB is not full
*
* Can be used to check whether the WCB is not full currently.
* If so, additional velo sends can be performed before needing
* to call kapi_velo2_wcb_check() potentially followed by kapi_velo2_wcb_fix().
* 
* When starting, 256 VELO packets can be sent without a call needed to 
* kapi_velo2_wcb_check() - although you may want to check earlier,
* since latency can increase in case of a retry otherwise.
*/
int kapi_velo2_wcb_notfull(VELO2_Handle* handle);
/*
* \brief Fix a retry situation or network congestion
*
* This function should be called, if kapi_velo2_wcb_check() returns non zero.
* It will try to fix the situation, once this is done, the callback function
* registered with kapi_velo2_wcb_register_callback() will be called,
* This function can block for a while, and will most probably schedule additional
* tasklets. The architecture should ensure that no softlockup can occur.
*
* IMPORTANT: NO SENDING WHATSOEVER IS ALLOWED ON THIS VPID UNTIL THE CALLBACK HAS BEEN CALLED!
*/
void kapi_velo2_wcb_fix(VELO2_Handle* handle);

/* see description for corresponding velo function */
void kapi_rma2_wcb_register_callback(RMA2_Handle *handle,kapi_replay_callback_t f);
/* see description for corresponding velo function */
int kapi_rma2_wcb_check(RMA2_Handle* handle,int us_timeout);
/* see description for corresponding velo function */
int kapi_rma2_wcb_check_notfull(RMA2_Handle* handle);
/* see description for corresponding velo function */
void kapi_rma2_wcb_fix(RMA2_Handle* handle);


#ifdef _KAPI_INTERNAL
static int _kapi_wcb_init(kapi_wcb_info_t *wcb, unsigned int vpid, const kapi_wcb_type_t function);
static void _kapi_wcb_release(kapi_wcb_info_t *wcb);
static inline uint64_t _kapi_wcb_get_state(kapi_wcb_info_t *wcb, const kapi_wcb_type_t function);
static inline void _kapi_wcb_set_state(kapi_wcb_info_t *wcb, const kapi_wcb_type_t function,uint64_t value);
static inline uint64_t _kapi_wcb_get_decode_state(kapi_wcb_info_t *wcb, const kapi_wcb_type_t function);
static inline kapi_wcb_send_state_t _kapi_wcb_update_commited_state(kapi_wcb_info_t *wcb, const kapi_wcb_type_t function);
int _kapi_wcb_check(kapi_wcb_info_t* wcb,int us_timeout);
void wcb_tasklet(unsigned long data);
void _kapi_wcb_fix(kapi_wcb_info_t* wcb);

#endif


 #endif //_EXTOLL_KAPI_H_

