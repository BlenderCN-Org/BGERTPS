# ##### BEGIN GPL LICENSE BLOCK #####
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
# ##### END GPL LICENSE BLOCK #####

# <pep8 compliant>

import bpy
from rna_prop_ui import rna_idprop_ui_prop_get
from math import acos
from Mathutils import Vector
from rigify import get_layer_dict
from rigify_utils import bone_class_instance, copy_bone_simple

#METARIG_NAMES = ("cpy",)
RIG_TYPE = "eye_balls"

def mark_actions():
    for action in bpy.data.actions:
        action.tag = True

def get_unmarked_action():
    for action in bpy.data.actions:
        if action.tag != True:
            return action
    return None
    
def add_action(name=None):
    mark_actions()
    bpy.ops.action.new()
    action = get_unmarked_action()
    if name is not None:
        action.name = name
    return action


def metarig_template():
    # generated by rigify.write_meta_rig
    bpy.ops.object.mode_set(mode='EDIT')
    obj = bpy.context.active_object
    arm = obj.data
    bone = arm.edit_bones.new('Bone')
    bone.head[:] = 0.0000, 0.0000, 0.0000
    bone.tail[:] = 0.0000, 0.0000, 1.0000
    bone.roll = 0.0000
    bone.connected = False

    bpy.ops.object.mode_set(mode='OBJECT')
    pbone = obj.pose.bones['Bone']
    pbone['type'] = 'copy'


def metarig_definition(obj, orig_bone_name):
    bone = obj.data.bones[orig_bone_name]
    chain = []
    
    try:
        chain += [bone.parent.name, bone.name]
    except AttributeError:
        raise RigifyError("'%s' rig type requires a parent (bone: %s)" % (RIG_TYPE, base_names[0]))
    
    return chain


def deform(obj, definitions, base_names, options):
    bpy.ops.object.mode_set(mode='EDIT')
    
    eb = obj.data.edit_bones
    pb = obj.pose.bones
    
    # Get list of eyes
    if "eyes" in options:
        eye_base_names = options["eyes"].replace(" ", "").split(",")
    else:
        eye_base_names = []
    
    # Get their ORG- names
    eyes = []
    for name in eye_base_names:
        eyes += ["ORG-"+name]
    
    # Duplicate the eyes to make deformation bones
    def_eyes = [] # def/org pairs
    for eye in eyes:
        def_eyes += [(copy_bone_simple(obj.data, eye, "DEF-"+base_names[eye], parent=True).name, eye)]
    
    
    bpy.ops.object.mode_set(mode='OBJECT')
        
    # Constraints
    for eye in def_eyes:
        con = pb[eye[0]].constraints.new('COPY_TRANSFORMS')
        con.target = obj
        con.subtarget = eye[1]
    
    return (None,)




def control(obj, definitions, base_names, options):
    bpy.ops.object.mode_set(mode='EDIT')
    
    eb = obj.data.edit_bones
    bb = obj.data.bones
    pb = obj.pose.bones
    
    head = definitions[0]
    eye_target = definitions[1]
    
    # Get list of eyes
    if "eyes" in options:
        eye_base_names = options["eyes"].replace(" ", "").split(",")
    else:
        eye_base_names = []
    
    # Get their ORG- names
    eyes = []
    for name in eye_base_names:
        eyes += ["ORG-"+name]
        
    # Get the average position of the eyes
    center = Vector(0,0,0)
    for eye in eyes:
        center += eb[eye].head
    if len(eyes) != 0:
        center /= len(eyes)
        
    # Get the average length of the eyes
    length = 0.0
    for eye in eyes:
        length += eb[eye].length
    if len(eyes) == 0:
        length = 1.0
    else:
        length /= len(eyes)
    
    
    # Make the mind's eye
    minds_eye = copy_bone_simple(obj.data, eye_target, "MCH-"+base_names[eye_target]+".mind", parent=True).name
    eb[minds_eye].head = center
    eb[minds_eye].tail = eb[eye_target].head
    eb[minds_eye].roll = 0.0
    eb[minds_eye].length = length
    
    # Create org/copy/control eye sets
    eye_sets = []
    for eye in eyes:
        copy = copy_bone_simple(obj.data, minds_eye, "MCH-"+base_names[eye]+".cpy", parent=True).name
        eb[copy].translate(eb[eye].head - eb[copy].head)
        eb[copy].parent = eb[eye].parent
        
        control = copy_bone_simple(obj.data, eye, base_names[eye], parent=True).name
        eb[control].parent = eb[copy]
    
        eye_sets += [(eye, copy, control)]
    
    # Bones for parent/free switch for eye target
    target_ctrl = copy_bone_simple(obj.data, eye_target, base_names[eye_target], parent=True).name
    parent = copy_bone_simple(obj.data, head, "MCH-eye_target_parent", parent=False).name
    
    eb[target_ctrl].parent = eb[parent]
    
    
    
    
    bpy.ops.object.mode_set(mode='OBJECT')
    
    # Axis locks
    pb[target_ctrl].lock_scale = False, True, True
    
    # Add eye_spread action if it doesn't already exist
    action_name = "eye_spread"
    if action_name in bpy.data.actions:
        spread_action = bpy.data.actions[action_name]
    else:
        spread_action = add_action(name=action_name)
    
    # Add free property
    prop_name = "free"
    prop = rna_idprop_ui_prop_get(pb[target_ctrl], prop_name, create=True)
    pb[target_ctrl][prop_name] = 0.0
    prop["soft_min"] = 0.0
    prop["soft_max"] = 1.0
    prop["min"] = 0.0
    prop["max"] = 1.0
    
    free_driver_path = pb[target_ctrl].path_to_id() + '["free"]'
    
    # Constraints
    # Mind's eye tracks eye target control
    con = pb[minds_eye].constraints.new('DAMPED_TRACK')
    con.target = obj
    con.subtarget = target_ctrl
    
    # Parent copies transforms of head
    con = pb[parent].constraints.new('COPY_TRANSFORMS')
    con.target = obj
    con.subtarget = head
    
    fcurve = con.driver_add("influence", 0)
    driver = fcurve.driver
    driver.type = 'AVERAGE'
    mod = fcurve.modifiers[0]
    mod.coefficients[0] = 1.0
    mod.coefficients[1] = -1.0
    
    var = driver.variables.new()
    var.name = "free"
    var.targets[0].id_type = 'OBJECT'
    var.targets[0].id = obj
    var.targets[0].data_path = free_driver_path
    
    # Eye set's constraints
    for eye in eye_sets:
        # Org copies transforms of control
        con = pb[eye[0]].constraints.new('COPY_TRANSFORMS')
        con.target = obj
        con.subtarget = eye[2]
        
        # Copy copies rotation of mind's eye
        con = pb[eye[1]].constraints.new('COPY_ROTATION')
        con.target = obj
        con.subtarget = minds_eye
        
        # Control gets action constraint for eye spread
        con = pb[eye[2]].constraints.new('ACTION')
        con.target = obj
        con.subtarget = target_ctrl
        con.action = spread_action
        con.transform_channel = 'SCALE_X'
        con.start_frame = -20
        con.end_frame = 20
        con.minimum = 0.0
        con.maximum = 2.0
        con.target_space = 'LOCAL'
        
    
    
    # Set layers
    #layer = list(bb[definitions[2]].layer)
    #bb[lid1].layer = layer
    #bb[lid2].layer = layer
    #bb[lid3].layer = layer
    #bb[lid4].layer = layer
    #bb[lid5].layer = layer
    #bb[lid6].layer = layer
    #bb[lid7].layer = layer
    #bb[lid8].layer = layer
    
    
    return (None,)




def main(obj, bone_definition, base_names, options):
    # Create control rig
    control(obj, bone_definition, base_names, options)
    # Create deform rig
    deform(obj, bone_definition, base_names, options)

    return (None,)
