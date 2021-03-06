/* $Id$ 
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
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */
#ifndef BKE_SUBSURF_H
#define BKE_SUBSURF_H

/** \file BKE_subsurf.h
 *  \ingroup bke
 */

struct DMGridAdjacency;
struct DMGridData;
struct DerivedMesh;
struct EditMesh;
struct IndexNode;
struct ListBase;
struct Mesh;
struct MultiresSubsurf;
struct Object;
struct PBVH;
struct SubsurfModifierData;
struct _CCGEdge;
struct _CCGFace;
struct _CCGSubsurf;
struct _CCGVert;

/**************************** External *****************************/

struct DerivedMesh *subsurf_make_derived_from_derived(
						struct DerivedMesh *dm,
						struct SubsurfModifierData *smd,
						int useRenderParams, float (*vertCos)[3],
						int isFinalCalc, int forEditMode, int inEditMode);

void subsurf_calculate_limit_positions(struct Mesh *me, float (*positions_r)[3]);

/**************************** Internal *****************************/

typedef struct CCGDerivedMesh {
	DerivedMesh dm;

	struct _CCGSubSurf *ss;
	int freeSS;
	int drawInteriorEdges, useSubsurfUv;

	struct {int startVert; struct _CCGVert *vert;} *vertMap;
	struct {int startVert; int startEdge; struct _CCGEdge *edge;} *edgeMap;
	struct {int startVert; int startEdge;
			int startFace; struct _CCGFace *face;} *faceMap;

	short *edgeFlags;
	char *faceFlags;

	struct PBVH *pbvh;
	struct ListBase *fmap;
	struct IndexNode *fmap_mem;

	struct DMGridData **gridData;
	struct DMGridAdjacency *gridAdjacency;
	int *gridOffset;
	struct _CCGFace **gridFaces;

	struct {
		struct MultiresModifierData *mmd;
		int local_mmd;

		int lvl, totlvl;
		float (*orco)[3];

		struct Object *ob;
		int modified;

		void (*update)(DerivedMesh*);
	} multires;
} CCGDerivedMesh;

#endif

