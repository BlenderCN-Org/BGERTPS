/*
 * $Id$
 *
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version. 
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2006 Blender Foundation.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file blender/nodes/intern/CMP_nodes/CMP_value.c
 *  \ingroup cmpnodes
 */


#include "../CMP_util.h"

/* **************** VALUE ******************** */
static bNodeSocketType cmp_node_value_out[]= {
	{	SOCK_VALUE, 0, "Value",		0.5f, 0.0f, 0.0f, 0.0f, -10000.0f, 10000.0f},
	{	-1, 0, ""	}
};

static void node_composit_exec_value(void *UNUSED(data), bNode *node, bNodeStack **UNUSED(in), bNodeStack **out)
{
	bNodeSocket *sock= node->outputs.first;
	
	out[0]->vec[0]= sock->ns.vec[0];
}

void register_node_type_cmp_value(ListBase *lb)
{
	static bNodeType ntype;

	node_type_base(&ntype, CMP_NODE_VALUE, "Value", NODE_CLASS_INPUT, NODE_OPTIONS,
		NULL, cmp_node_value_out);
	node_type_size(&ntype, 80, 40, 120);
	node_type_exec(&ntype, node_composit_exec_value);

	nodeRegisterType(lb, &ntype);
}


