/* SCTP kernel Implementation: User API extensions.
 *__
 * sctp.h
 *
 * Distributed under the terms of the LGPL v2.1 as described in
 *    http://www.gnu.org/copyleft/lesser.txt 
 *
 * This file is part of the user library that offers support for the
 * Linux Kernel SCTP Implementation. The main purpose of this
 * code is to provide the SCTP Socket API mappings for user
 * application to interface with SCTP in kernel.
 *
 * This header represents the structures and constants needed to support
 * the SCTP Extension to the Sockets API.
 *
 * (C) Copyright IBM Corp. 2001, 2004
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 *
 * Written or modified by:
 *    La Monte H.P. Yarroll    <piggy@acm.org>
 *    R. Stewart               <randall@sctp.chicago.il.us>
 *    K. Morneau               <kmorneau@cisco.com>
 *    Q. Xie                   <qxie1@email.mot.com>
 *    Karl Knutson             <karl@athena.chicago.il.us>
 *    Jon Grimm                <jgrimm@austin.ibm.com>
 *    Daisy Chang              <daisyc@us.ibm.com>
 *    Inaky Perez-Gonzalez     <inaky.gonzalez@intel.com>
 *    Sridhar Samudrala        <sri@us.ibm.com>
 *    Vlad Yasevich		<vladislav.yasevich@hp.com>
 */

#ifndef __windows_sctp_h__
#define __windows_sctp_h__

#include <stdint.h>
#include <sys/types.h>
#include <windows.h>

#if (defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)) && defined(_MSC_VER)
# include <ws2tcpip.h>
#else
# include <winsock.h>
#endif

__BEGIN_DECLS

typedef Int32 sctp_assoc_t;

/* Socket option layer for SCTP */
#ifndef SOL_SCTP
#define SOL_SCTP	132
#endif

#ifndef IPPROTO_SCTP
#define IPPROTO_SCTP    132
#endif

/* 9. Preprocessor constants */
#define HAVE_SCTP
#define HAVE_KERNEL_SCTP
#define HAVE_SCTP_MULTIBUF
#define HAVE_SCTP_NOCONNECT
#define HAVE_SCTP_PRSCTP
#define HAVE_SCTP_ADDIP
#define HAVE_SCTP_CANSET_PRIMARY

/* The following symbols come from the Sockets API Extensions for
 * SCTP <draft-ietf-tsvwg-sctpsocket-07.txt>.
 */
#define SCTP_RTOINFO	0
#define SCTP_ASSOCINFO  1
#define SCTP_INITMSG	2
#define SCTP_NODELAY	3		/* Get/set nodelay option. */
#define SCTP_AUTOCLOSE	4
#define SCTP_SET_PEER_PRIMARY_ADDR 5
#define SCTP_PRIMARY_ADDR	6
#define SCTP_ADAPTATION_LAYER	7
#define SCTP_DISABLE_FRAGMENTS	8
#define SCTP_PEER_ADDR_PARAMS	9
#define SCTP_DEFAULT_SEND_PARAM	10
#define SCTP_EVENTS	11
#define SCTP_I_WANT_MAPPED_V4_ADDR 12	/* Turn on/off mapped v4 addresses  */
#define SCTP_MAXSEG	13		/* Get/set maximum fragment. */
#define SCTP_STATUS	14
#define SCTP_GET_PEER_ADDR_INFO	15
#define SCTP_DELAYED_ACK_TIME	16
#define SCTP_DELAYED_ACK SCTP_DELAYED_ACK_TIME
#define SCTP_DELAYED_SACK SCTP_DELAYED_ACK_TIME
#define SCTP_CONTEXT	17
#define SCTP_FRAGMENT_INTERLEAVE	18
#define SCTP_PARTIAL_DELIVERY_POINT	19 /* Set/Get partial delivery point */
#define SCTP_MAX_BURST	20		/* Set/Get max burst */
#define SCTP_AUTH_CHUNK	21	/* Set only: add a chunk type to authenticate */
#define SCTP_HMAC_IDENT	22
#define SCTP_AUTH_KEY	23
#define SCTP_AUTH_ACTIVE_KEY	24
#define SCTP_AUTH_DELETE_KEY	25
#define SCTP_PEER_AUTH_CHUNKS	26	/* Read only */
#define SCTP_LOCAL_AUTH_CHUNKS	27	/* Read only */
#define SCTP_GET_ASSOC_NUMBER	28	/* Read only */

/* Internal Socket Options. Some of the sctp library functions are
 * implemented using these socket options.
 */
#define SCTP_SOCKOPT_BINDX_ADD	100	/* BINDX requests for adding addrs */
#define SCTP_SOCKOPT_BINDX_REM	101	/* BINDX requests for removing addrs. */
#define SCTP_SOCKOPT_PEELOFF	102	/* peel off association. */
/* Options 104-106 are deprecated and removed. Do not use this space */
#define SCTP_SOCKOPT_CONNECTX_OLD	107	/* CONNECTX old requests. */
#define SC-TP_GET_PEER_ADDRS	108		/* Get all peer addresss. */
#define SCTP_GET_LOCAL_ADDRS	109		/* Get all local addresss. */
#define SCTP_SOCKOPT_CONNECTX	110		/* CONNECTX requests. */
#define SCTP_SOCKOPT_CONNECTX3	111	/* CONNECTX requests (updated) */

/*
 * 5.2.1 SCTP Initiation Structure (SCTP_INIT)
 *
 *   This cmsghdr structure provides information for initializing new
 *   SCTP associations with sendmsg().  The SCTP_INITMSG socket option
 *   uses this same data structure.  This structure is not used for
 *   recvmsg().
 *
 *   cmsg_level    cmsg_type      cmsg_data[]
 *   ------------  ------------   ----------------------
 *   IPPROTO_SCTP  SCTP_INIT      struct sctp_initmsg
 *
 */
struct sctp_initmsg {
	UInt16 sinit_num_ostreams;
	UInt16 sinit_max_instreams;
	UInt16 sinit_max_attempts;
	UInt16 sinit_max_init_timeo;
};

/*
 * 5.2.2 SCTP Header Information Structure (SCTP_SNDRCV)
 *
 *   This cmsghdr structure specifies SCTP options for sendmsg() and
 *   describes SCTP header information about a received message through
 *   recvmsg().
 *
 *   cmsg_level    cmsg_type      cmsg_data[]
 *   ------------  ------------   ----------------------
 *   IPPROTO_SCTP  SCTP_SNDRCV    struct sctp_sndrcvinfo
 *
 */
struct sctp_sndrcvinfo {
	UInt16 sinfo_stream;
	UInt16 sinfo_ssn;
	UInt16 sinfo_flags;
	UInt32 sinfo_ppid;
	UInt32 sinfo_context;
	UInt32 sinfo_timetolive;
	UInt32 sinfo_tsn;
	UInt32 sinfo_cumtsn;
	sctp_assoc_t sinfo_assoc_id;
};

/*
 *  sinfo_flags: 16 bits (unsigned integer)
 *
 *   This field may contain any of the following flags and is composed of
 *   a bitwise OR of these values.
 */

enum sctp_sinfo_flags {
	SCTP_UNORDERED = 1,  /* Send/receive message unordered. */
	SCTP_ADDR_OVER = 2,  /* Override the primary destination. */
	SCTP_ABORT=4,        /* Send an ABORT message to the peer. */
	SCTP_SACK_IMMEDIATELY = 8,      /* SACK should be sent without delay */
	SCTP_EOF=MSG_FIN,    /* Initiate graceful shutdown process. */
};


typedef union {
	UInt8   			raw;
	struct sctp_initmsg	init;
	struct sctp_sndrcvinfo	sndrcv;
} sctp_cmsg_data_t;

/* These are cmsg_types.  */
typedef enum sctp_cmsg_type {
	SCTP_INIT,              /* 5.2.1 SCTP Initiation Structure */
#define SCTP_INIT SCTP_INIT
	SCTP_SNDRCV,            /* 5.2.2 SCTP Header Information Structure */
#define SCTP_SNDRCV SCTP_SNDRCV
} sctp_cmsg_t;


/*
 * 5.3.1.1 SCTP_ASSOC_CHANGE
 *
 *   Communication notifications inform the ULP that an SCTP association
 *   has either begun or ended. The identifier for a new association is
 *   provided by this notificaion. The notification information has the
 *   following format:
 *
 */
struct sctp_assoc_change {
	UInt16 sac_type;
	UInt16 sac_flags;
	UInt32 sac_length;
	UInt16 sac_state;
	UInt16 sac_error;
	UInt16 sac_outbound_streams;
	UInt16 sac_inbound_streams;
	sctp_assoc_t sac_assoc_id;
	UInt8 sac_info[0];
};

/*
 *   sac_state: 32 bits (signed integer)
 *
 *   This field holds one of a number of values that communicate the
 *   event that happened to the association.  They include:
 *
 *   Note:  The following state names deviate from the API draft as
 *   the names clash too easily with other kernel symbols.
 */
enum sctp_sac_state {
	SCTP_COMM_UP,
	SCTP_COMM_LOST,
	SCTP_RESTART,
	SCTP_SHUTDOWN_COMP,
	SCTP_CANT_STR_ASSOC,
};

/*
 * 5.3.1.2 SCTP_PEER_ADDR_CHANGE
 *
 *   When a destination address on a multi-homed peer encounters a change
 *   an interface details event is sent.  The information has the
 *   following structure:
 */
struct sctp_paddr_change {
	UInt16 spc_type;
	UInt16 spc_flags;
	UInt32 spc_length;
	struct sockaddr_storage spc_aaddr;
	int spc_state;
	int spc_error;
	sctp_assoc_t spc_assoc_id;
} __attribute__((packed, aligned(4)));

/*
 *    spc_state:  32 bits (signed integer)
 *
 *   This field holds one of a number of values that communicate the
 *   event that happened to the address.  They include:
 */
enum sctp_spc_state {
	SCTP_ADDR_AVAILABLE,
	SCTP_ADDR_UNREACHABLE,
	SCTP_ADDR_REMOVED,
	SCTP_ADDR_ADDED,
	SCTP_ADDR_MADE_PRIM,
	SCTP_ADDR_CONFIRMED,
};


/*
 * 5.3.1.3 SCTP_REMOTE_ERROR
 *
 *   A remote peer may send an Operational Error message to its peer.
 *   This message indicates a variety of error conditions on an
 *   association. The entire error TLV as it appears on the wire is
 *   included in a SCTP_REMOTE_ERROR event.  Please refer to the SCTP
 *   specification [SCTP] and any extensions for a list of possible
 *   error formats. SCTP error TLVs have the format:
 */
struct sctp_remote_error {
	UInt16 sre_type;
	UInt16 sre_flags;
	UInt32 sre_length;
	UInt16 sre_error;
	sctp_assoc_t sre_assoc_id;
	UInt8 sre_data[0];
};


/*
 * 5.3.1.4 SCTP_SEND_FAILED
 *
 *   If SCTP cannot deliver a message it may return the message as a
 *   notification.
 */
struct sctp_send_failed {
	UInt16 ssf_type;
	UInt16 ssf_flags;
	UInt32 ssf_length;
	UInt32 ssf_error;
	struct sctp_sndrcvinfo ssf_info;
	sctp_assoc_t ssf_assoc_id;
	UInt8 ssf_data[0];
};

/*
 *   ssf_flags: 16 bits (unsigned integer)
 *
 *   The flag value will take one of the following values
 *
 *   SCTP_DATA_UNSENT  - Indicates that the data was never put on
 *                       the wire.
 *
 *   SCTP_DATA_SENT    - Indicates that the data was put on the wire.
 *                       Note that this does not necessarily mean that the
 *                       data was (or was not) successfully delivered.
 */
enum sctp_ssf_flags {
	SCTP_DATA_UNSENT,
	SCTP_DATA_SENT,
};

/*
 * 5.3.1.5 SCTP_SHUTDOWN_EVENT
 *
 *   When a peer sends a SHUTDOWN, SCTP delivers this notification to
 *   inform the application that it should cease sending data.
 */
struct sctp_shutdown_event {
	UInt16 sse_type;
	UInt16 sse_flags;
	UInt32 sse_length;
	sctp_assoc_t sse_assoc_id;
};

/*
 * 5.3.1.6 SCTP_ADAPTATION_INDICATION
 *
 *   When a peer sends a Adaptation Layer Indication parameter , SCTP
 *   delivers this notification to inform the application
 *   that of the peers requested adaptation layer.
 */
struct sctp_adaptation_event {
	UInt16 sai_type;
	UInt16 sai_flags;
	UInt32 sai_length;
	UInt32 sai_adaptation_ind;
	sctp_assoc_t sai_assoc_id;
};

/*
 * 5.3.1.7 SCTP_PARTIAL_DELIVERY_EVENT
 *
 *   When a receiver is engaged in a partial delivery of a
 *   message this notification will be used to indicate
 *   various events.
 */
struct sctp_pdapi_event {
	UInt16 pdapi_type;
	UInt16 pdapi_flags;
	UInt32 pdapi_length;
	UInt32 pdapi_indication;
	sctp_assoc_t pdapi_assoc_id;
};

enum { SCTP_PARTIAL_DELIVERY_ABORTED=0, };

/*
* 5.3.1.8.  SCTP_AUTHENTICATION_EVENT
*
*  When a receiver is using authentication this message will provide
*  notifications regarding new keys being made active as well as errors.
*/

struct sctp_authkey_event {
	UInt16 auth_type;
	UInt16 auth_flags;
	UInt32 auth_length;
	UInt16 auth_keynumber;
	UInt16 auth_altkeynumber;
	UInt32 auth_indication;
	sctp_assoc_t auth_assoc_id;
};

enum { SCTP_AUTH_NEWKEY = 0, };


/*
 * Described in Section 7.3
 *   Ancillary Data and Notification Interest Options
 */
struct sctp_event_subscribe {
	UInt8 sctp_data_io_event;
	UInt8 sctp_association_event;
	UInt8 sctp_address_event;
	UInt8 sctp_send_failure_event;
	UInt8 sctp_peer_error_event;
	UInt8 sctp_shutdown_event;
	UInt8 sctp_partial_delivery_event;
	UInt8 sctp_adaptation_layer_event;
	UInt8 sctp_authentication_event;
};

/*
 * 5.3.1 SCTP Notification Structure
 *
 *   The notification structure is defined as the union of all
 *   notification types.
 *
 */
union sctp_notification {
	struct {
		UInt16 sn_type;             /* Notification type. */
		UInt16 sn_flags;
		UInt32 sn_length;
	} sn_header;
	struct sctp_assoc_change sn_assoc_change;
	struct sctp_paddr_change sn_paddr_change;
	struct sctp_remote_error sn_remote_error;
	struct sctp_send_failed sn_send_failed;
	struct sctp_shutdown_event sn_shutdown_event;
	struct sctp_adaptation_event sn_adaptation_event;
	struct sctp_pdapi_event sn_pdapi_event;
	struct sctp_authkey_event sn_authkey_event;
};

/* Section 5.3.1
 * All standard values for sn_type flags are greater than 2^15.
 * Values from 2^15 and down are reserved.
 */

enum sctp_sn_type {
	SCTP_SN_TYPE_BASE     = (1<<15),
	SCTP_ASSOC_CHANGE,
	SCTP_PEER_ADDR_CHANGE,
	SCTP_SEND_FAILED,
	SCTP_REMOTE_ERROR,
	SCTP_SHUTDOWN_EVENT,
	SCTP_PARTIAL_DELIVERY_EVENT,
	SCTP_ADAPTATION_INDICATION,
	SCTP_AUTHENTICATION_INDICATION,
};

/* Notification error codes used to fill up the error fields in some
 * notifications.
 * SCTP_PEER_ADDRESS_CHAGE 	: spc_error
 * SCTP_ASSOC_CHANGE		: sac_error
 * These names should be potentially included in the draft 04 of the SCTP
 * sockets API specification.
 */
typedef enum sctp_sn_error {
	SCTP_FAILED_THRESHOLD,
	SCTP_RECEIVED_SACK,
	SCTP_HEARTBEAT_SUCCESS,
	SCTP_RESPONSE_TO_USER_REQ,
	SCTP_INTERNAL_ERROR,
	SCTP_SHUTDOWN_GUARD_EXPIRES,
	SCTP_PEER_FAULTY,
} sctp_sn_error_t;

/*
 * 7.1.1 Retransmission Timeout Parameters (SCTP_RTOINFO)
 *
 *   The protocol parameters used to initialize and bound retransmission
 *   timeout (RTO) are tunable.  See [SCTP] for more information on how
 *   these parameters are used in RTO calculation. 
 */
struct sctp_rtoinfo {
	sctp_assoc_t	srto_assoc_id;
	UInt32		srto_initial;
	UInt32		srto_max;
	UInt32		srto_min;
};

/*
 * 7.1.2 Association Parameters (SCTP_ASSOCINFO)
 *
 *   This option is used to both examine and set various association and
 *   endpoint parameters.
 */
struct sctp_assocparams {
	sctp_assoc_t	sasoc_assoc_id;
	UInt16		sasoc_asocmaxrxt;
	UInt16		sasoc_number_peer_destinations;
	UInt32		sasoc_peer_rwnd;
	UInt32		sasoc_local_rwnd;
	UInt32		sasoc_cookie_life;
};

/*
 * 7.1.9 Set Peer Primary Address (SCTP_SET_PEER_PRIMARY_ADDR)
 *
 *  Requests that the peer mark the enclosed address as the association
 *  primary. The enclosed address must be one of the association's
 *  locally bound addresses. The following structure is used to make a
 *   set primary request:
 */
struct sctp_setpeerprim {
	sctp_assoc_t            sspp_assoc_id;
	struct sockaddr_storage sspp_addr;
} __attribute__((packed, aligned(4)));

/*
 * 7.1.10 Set Primary Address (SCTP_PRIMARY_ADDR)
 *
 *  Requests that the local SCTP stack use the enclosed peer address as
 *  the association primary. The enclosed address must be one of the
 *  association peer's addresses. The following structure is used to
 *  make a set peer primary request:
 */
struct sctp_setprim {
	sctp_assoc_t            ssp_assoc_id;
	struct sockaddr_storage ssp_addr;
} __attribute__((packed, aligned(4)));

/* For backward compatibility use, define the old name too */
#define sctp_prim sctp_setprim

/*
 * 7.1.11 Set Adaptation Layer Indicator (SCTP_ADAPTATION_LAYER)
 *
 * Requests that the local endpoint set the specified Adaptation Layer
 * Indication parameter for all future INIT and INIT-ACK exchanges.
 */
struct sctp_setadaptation {
	UInt32	ssb_adaptation_ind;
};

/*
 * 7.1.13 Peer Address Parameters  (SCTP_PEER_ADDR_PARAMS)
 *
 *   Applications can enable or disable heartbeats for any peer address
 *   of an association, modify an address's heartbeat interval, force a
 *   heartbeat to be sent immediately, and adjust the address's maximum
 *   number of retransmissions sent before an address is considered
 *   unreachable. The following structure is used to access and modify an
 *   address's parameters:
 */
enum  sctp_spp_flags {
	SPP_HB_ENABLE = 1<<0,		/*Enable heartbeats*/
	SPP_HB_DISABLE = 1<<1,		/*Disable heartbeats*/
	SPP_HB = SPP_HB_ENABLE | SPP_HB_DISABLE,
	SPP_HB_DEMAND = 1<<2,		/*Send heartbeat immediately*/
	SPP_PMTUD_ENABLE = 1<<3,	/*Enable PMTU discovery*/
	SPP_PMTUD_DISABLE = 1<<4,	/*Disable PMTU discovery*/
	SPP_PMTUD = SPP_PMTUD_ENABLE | SPP_PMTUD_DISABLE,
	SPP_SACKDELAY_ENABLE = 1<<5,	/*Enable SACK*/
	SPP_SACKDELAY_DISABLE = 1<<6,	/*Disable SACK*/
	SPP_SACKDELAY = SPP_SACKDELAY_ENABLE | SPP_SACKDELAY_DISABLE,
	SPP_HB_TIME_IS_ZERO = 1<<7,	/* Set HB delay to 0 */
};

struct sctp_paddrparams {
	sctp_assoc_t		spp_assoc_id;
	struct sockaddr_storage	spp_address;
	UInt32			spp_hbinterval;
	UInt16			spp_pathmaxrxt;
	UInt32			spp_pathmtu;
	UInt32			spp_sackdelay;
	UInt32			spp_flags;
} __attribute__((packed, aligned(4)));

/*
 * 7.1.18.  Add a chunk that must be authenticated (SCTP_AUTH_CHUNK)
 *
 * This set option adds a chunk type that the user is requesting to be
 * received only in an authenticated way.  Changes to the list of chunks
 * will only effect future associations on the socket.
 */
struct sctp_authchunk {
	UInt8		sauth_chunk;
};

/*
 * 7.1.19.  Get or set the list of supported HMAC Identifiers (SCTP_HMAC_IDENT)
 *
 * This option gets or sets the list of HMAC algorithms that the local
 * endpoint requires the peer to use.
*/

enum {
	SCTP_AUTH_HMAC_ID_SHA1 = 1,
	SCTP_AUTH_HMAC_ID_SHA256 = 3,
};

struct sctp_hmacalgo {
	UInt32		shmac_number_of_idents;
	UInt16		shmac_idents[];
};

/*
 * 7.1.20.  Set a shared key (SCTP_AUTH_KEY)
 *
 * This option will set a shared secret key which is used to build an
 * association shared key.
 */
struct sctp_authkey {
	sctp_assoc_t	sca_assoc_id;
	UInt16		sca_keynumber;
	UInt16		sca_keylength;
	UInt8		sca_key[];
};

/*
 * 7.1.21.  Get or set the active shared key (SCTP_AUTH_ACTIVE_KEY)
 *
 * This option will get or set the active shared key to be used to build
 * the association shared key.
 */

struct sctp_authkeyid {
	sctp_assoc_t	scact_assoc_id;
	UInt16		scact_keynumber;
};


/*
 * 7.1.23.  Get or set delayed ack timer (SCTP_DELAYED_SACK)
 *
 * This option will effect the way delayed acks are performed.  This
 * option allows you to get or set the delayed ack time, in
 * milliseconds.  It also allows changing the delayed ack frequency.
 * Changing the frequency to 1 disables the delayed sack algorithm.  If
 * the assoc_id is 0, then this sets or gets the endpoints default
 * values.  If the assoc_id field is non-zero, then the set or get
 * effects the specified association for the one to many model (the
 * assoc_id field is ignored by the one to one model).  Note that if
 * sack_delay or sack_freq are 0 when setting this option, then the
 * current values will remain unchanged.
 */
struct sctp_sack_info {
	sctp_assoc_t	sack_assoc_id;
	uint32_t	sack_delay;
	uint32_t	sack_freq;
};

struct sctp_assoc_value {
    sctp_assoc_t            assoc_id;
    uint32_t                assoc_value;
};

/*
 * 7.2.2 Peer Address Information
 *
 *   Applications can retrieve information about a specific peer address
 *   of an association, including its reachability state, congestion
 *   window, and retransmission timer values.  This information is
 *   read-only. The following structure is used to access this
 *   information:
 */
struct sctp_paddrinfo {
	sctp_assoc_t		spinfo_assoc_id;
	struct sockaddr_storage	spinfo_address;
	__s32			spinfo_state;
	UInt32			spinfo_cwnd;
	UInt32			spinfo_srtt;
	UInt32			spinfo_rto;
	UInt32			spinfo_mtu;
} __attribute__((packed, aligned(4)));

/* Peer addresses's state. */
/* UNKNOWN: Peer address passed by the upper layer in sendmsg or connect[x]
 * calls.
 * UNCONFIRMED: Peer address received in INIT/INIT-ACK address parameters.
 *              Not yet confirmed by a heartbeat and not available for data
 *		transfers.
 * ACTIVE : Peer address confirmed, active and available for data transfers.
 * INACTIVE: Peer address inactive and not available for data transfers.
 */
enum sctp_spinfo_state {
	SCTP_INACTIVE,
	SCTP_ACTIVE,
	SCTP_UNCONFIRMED
};

/*
 * 7.2.1 Association Status (SCTP_STATUS)
 *
 *   Applications can retrieve current status information about an
 *   association, including association state, peer receiver window size,
 *   number of unacked data chunks, and number of data chunks pending
 *   receipt.  This information is read-only.  The following structure is
 *   used to access this information:
 */
struct sctp_status {
	sctp_assoc_t		sstat_assoc_id;
	__s32			sstat_state;
	UInt32			sstat_rwnd;
	UInt16			sstat_unackdata;
	UInt16			sstat_penddata;
	UInt16			sstat_instrms;
	UInt16			sstat_outstrms;
	UInt32			sstat_fragmentation_point;
	struct sctp_paddrinfo	sstat_primary;
};

/*
 * 7.2.3.  Get the list of chunks the peer requires to be authenticated
 *         (SCTP_PEER_AUTH_CHUNKS)
 *
 * This option gets a list of chunks for a specified association that
 * the peer requires to be received authenticated only.
 */
struct sctp_authchunks {
	sctp_assoc_t	gauth_assoc_id;
	UInt32		gauth_number_of_chunks;
	uint8_t		gauth_chunks[];
};
/* The broken spelling has been released already,
 * so don't break anyone, now that it's fixed.
 */
#define guth_number_of_chunks gauth_number_of_chunks

/* Association states.  */
enum sctp_sstat_state {
	SCTP_EMPTY                = 0,
	SCTP_CLOSED               = 1,
	SCTP_COOKIE_WAIT          = 2,
	SCTP_COOKIE_ECHOED        = 3,
	SCTP_ESTABLISHED          = 4,
	SCTP_SHUTDOWN_PENDING     = 5,
	SCTP_SHUTDOWN_SENT        = 6,
	SCTP_SHUTDOWN_RECEIVED    = 7,
	SCTP_SHUTDOWN_ACK_SENT    = 8,
};

/*
 * 8.3, 8.5 get all peer/local addresses in an association.
 * This parameter struct is used by SCTP_GET_PEER_ADDRS and
 * SCTP_GET_LOCAL_ADDRS socket options used internally to implement
 * sctp_getpaddrs() and sctp_getladdrs() API. 
 */
struct sctp_getaddrs_old {
	sctp_assoc_t            assoc_id;
	int			addr_num;
	struct sockaddr		*addrs;
};
struct sctp_getaddrs {
	sctp_assoc_t		assoc_id; /*input*/
	UInt32			addr_num; /*output*/
	UInt8			addrs[0]; /*output, variable size*/
};

/* These are bit fields for msghdr->msg_flags.  See section 5.1.  */
/* On user space Linux, these live in <bits/socket.h> as an enum.  */
enum sctp_msg_flags {
	MSG_NOTIFICATION = 0x8000,
#define MSG_NOTIFICATION MSG_NOTIFICATION
};

/*
 * 8.1 sctp_bindx()
 *
 * The flags parameter is formed from the bitwise OR of zero or more of the
 * following currently defined flags:
 */
#define SCTP_BINDX_ADD_ADDR 0x01
#define SCTP_BINDX_REM_ADDR 0x02

/* This is the structure that is passed as an argument(optval) to
 * getsockopt(SCTP_SOCKOPT_PEELOFF).
 */
typedef struct {
	sctp_assoc_t associd;
	int sd;
} sctp_peeloff_arg_t;


int sctp_bindx(int sd, struct sockaddr *addrs, int addrcnt, int flags);

int sctp_connectx(int sd, struct sockaddr *addrs, int addrcnt,
		  sctp_assoc_t *id);

int sctp_peeloff(int sd, sctp_assoc_t assoc_id);

/* Prototype for the library function sctp_opt_info defined in
 * API 7. Socket Options.
 */
int sctp_opt_info(int sd, sctp_assoc_t id, int opt, void *arg, socklen_t *size);

/* Get all peer address on a socket.  This is a new SCTP API
 * described in the section 8.3 of the Sockets API Extensions for SCTP.
 * This is implemented using the getsockopt() interface.
 */
int sctp_getpaddrs(int sd, sctp_assoc_t id, struct sockaddr **addrs);

/* Frees all resources allocated by sctp_getpaddrs().  This is a new SCTP API
 * described in the section 8.4 of the Sockets API Extensions for SCTP.
 */
int sctp_freepaddrs(struct sockaddr *addrs);

/* Get all locally bound address on a socket.  This is a new SCTP API
 * described in the section 8.5 of the Sockets API Extensions for SCTP.
 * This is implemented using the getsockopt() interface.
 */
int sctp_getladdrs(int sd, sctp_assoc_t id, struct sockaddr **addrs);

/* Frees all resources allocated by sctp_getladdrs().  This is a new SCTP API
 * described in the section 8.6 of the Sockets API Extensions for SCTP.
 */
int sctp_freeladdrs(struct sockaddr *addrs);

/* This library function assists the user with the advanced features
 * of SCTP.  This is a new SCTP API described in the section 8.7 of the
 * Sockets API Extensions for SCTP. This is implemented using the
 * sendmsg() interface.
 */
int sctp_sendmsg(int s, const void *msg, size_t len, struct sockaddr *to,
		 socklen_t tolen, uint32_t ppid, uint32_t flags,
		 uint16_t stream_no, uint32_t timetolive, uint32_t context);

/* This library function assist the user with sending a message without
 * dealing directly with the CMSG header.
 */
int sctp_send(int s, const void *msg, size_t len,
              const struct sctp_sndrcvinfo *sinfo, int flags);

/* This library function assists the user with the advanced features
 * of SCTP.  This is a new SCTP API described in the section 8.8 of the
 * Sockets API Extensions for SCTP. This is implemented using the
 * recvmsg() interface.
 */
int sctp_recvmsg(int s, void *msg, size_t len, struct sockaddr *from,
		 socklen_t *fromlen, struct sctp_sndrcvinfo *sinfo,
		 int *msg_flags);

/* Return the address length for an address family. */
int sctp_getaddrlen(sa_family_t family);

__END_DECLS

#endif /* __windows_sctp_h__*/
