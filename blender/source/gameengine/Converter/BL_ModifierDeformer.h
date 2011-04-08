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
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** \file BL_ModifierDeformer.h
 *  \ingroup bgeconv
 */

#ifndef BL_MODIFIERDEFORMER
#define BL_MODIFIERDEFORMER

#if defined(WIN32) && !defined(FREE_WINDOWS)
#pragma warning (disable:4786) // get rid of stupid stl-visual compiler debug warning
#endif //WIN32

#include "BL_ShapeDeformer.h"
#include "BL_DeformableGameObject.h"
#include <vector>

//#include "timege.h"

struct DerivedMesh;
struct Object;

class BL_ModifierDeformer : public BL_ShapeDeformer  
{
public:
	static bool HasCompatibleDeformer(Object *ob);
	static bool HasArmatureDeformer(Object *ob);
    static bool HasRTPSDeformer(Object *ob);

    enum {TI_UPDATE=0, TI_EMIT, TI_RTPSUP }; //2
    //GE::Time* timers[3];


	BL_ModifierDeformer(BL_DeformableGameObject *gameobj,
						Scene *scene,
						Object *bmeshobj,
						RAS_MeshObject *mesh,
                        bool bIsRTPS = false)
						:	
						BL_ShapeDeformer(gameobj,bmeshobj, mesh),
						m_lastModifierUpdate(-1),
						m_scene(scene),
						m_dm(NULL),
                        m_bIsRTPS(bIsRTPS)
	{
		m_recalcNormal = false;
        int print_freq = 100;
        int offset = 5;
        //timers[TI_UPDATE] = new GE::Time("modifier update", offset, print_freq);
        //timers[TI_EMIT] = new GE::Time("emit", offset, print_freq);
        //timers[TI_RTPSUP] = new GE::Time("rtps update:", offset, print_freq);
	};

	/* this second constructor is needed for making a mesh deformable on the fly. */
	BL_ModifierDeformer(BL_DeformableGameObject *gameobj,
						struct Scene *scene,
						struct Object *bmeshobj_old,
						struct Object *bmeshobj_new,
						class RAS_MeshObject *mesh,
						bool release_object,
						BL_ArmatureObject* arma = NULL,
                        bool bIsRTPS = false)
						:
						BL_ShapeDeformer(gameobj, bmeshobj_old, bmeshobj_new, mesh, release_object, false, arma),
						m_lastModifierUpdate(-1),
						m_scene(scene),
						m_dm(NULL),
                        m_bIsRTPS(bIsRTPS)
	{
        int print_freq = 100;
        int offset = 5;
        //timers[TI_UPDATE] = new GE::Time("modifier update", offset, print_freq);
        //timers[TI_EMIT] = new GE::Time("emit", offset, print_freq);
        //timers[TI_RTPSUP] = new GE::Time("rtps update:", offset, print_freq);
	};

	virtual void ProcessReplica();
	virtual RAS_Deformer *GetReplica();
	virtual ~BL_ModifierDeformer();
	virtual bool UseVertexArray()
	{
		return false;
	}

	bool Update (void);
	bool Apply(RAS_IPolyMaterial *mat);
	void ForceUpdate()
	{
		m_lastModifierUpdate = -1.0;
	};
	virtual struct DerivedMesh* GetFinalMesh()
	{
		return m_dm;
	}
    
	// The derived mesh returned by this function must be released!
	virtual struct DerivedMesh* GetPhysicsMesh();

protected:
	double					 m_lastModifierUpdate;
	Scene					*m_scene;
	DerivedMesh				*m_dm;
    bool                     m_bIsRTPS; //different from the RAS_MaterialBucket flag but used to set it.


#ifdef WITH_CXX_GUARDEDALLOC
public:
	void *operator new(size_t num_bytes) { return MEM_mallocN(num_bytes, "GE:BL_ModifierDeformer"); }
	void operator delete( void *mem ) { MEM_freeN(mem); }
#endif
};

#endif

