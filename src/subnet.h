/*
    subnet.h -- header for subnet.c
    Copyright (C) 2000,2001 Guus Sliepen <guus@sliepen.warande.net>,
                  2000,2001 Ivo Timmermans <itimmermans@bigfoot.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    $Id: subnet.h,v 1.1.2.10 2001/01/08 21:32:30 guus Exp $
*/

#ifndef __TINC_SUBNET_H__
#define __TINC_SUBNET_H__

#include "net.h"

enum
{
  SUBNET_MAC = 0,
  SUBNET_IPV4,
  SUBNET_IPV6,
  SUBNET_TYPES				/* Guardian */
};

typedef struct subnet_mac_t
{
  mac_t address;
} subnet_mac_t;

typedef struct subnet_ipv4_t
{
  ipv4_t address;
  ipv4_t mask;
} subnet_ipv4_t;

typedef struct subnet_ipv6_t
{
  ipv6_t address;
  ipv6_t mask;
} subnet_ipv6_t;

typedef struct subnet_t {
  struct connection_t *owner;		/* the owner of this subnet */
  struct connection_t *uplink;		/* the uplink which we should send packets to for this subnet */

  int type;				/* subnet type (IPv4? IPv6? MAC? something even weirder?) */

  /* And now for the actual subnet: */

  union net
    {
      subnet_mac_t mac;
      subnet_ipv4_t ipv4;
      subnet_ipv6_t ipv6;
    } net;
    
} subnet_t;  

#include "connection.h"

extern subnet_t *new_subnet(void);
extern void free_subnet(subnet_t *);
extern void init_subnets(void);
extern void subnet_add(struct connection_t *, subnet_t *);
extern void subnet_del(subnet_t *);
extern char *net2str(subnet_t *);
extern subnet_t *str2net(char *);
extern int subnet_compare(subnet_t *, subnet_t *);
extern subnet_t *lookup_subnet_mac(mac_t *);
extern subnet_t *lookup_subnet_ipv4(ipv4_t *);
extern subnet_t *lookup_subnet_ipv6(ipv6_t *);
extern void dump_subnet_list(void);

#endif /* __TINC_SUBNET_H__ */
