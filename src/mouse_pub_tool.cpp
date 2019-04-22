/*
 * Copyright (c) 2011, Willow Garage, Inc.
 * Copyright (c) 2019, Joydeep Biswas joydeepb@cs.umass.edu
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreEntity.h>

#include <ros/console.h>

#include <geometry_msgs/Point32.h>
#include <rviz/viewport_mouse_event.h>
#include <rviz/visualization_manager.h>
#include <rviz/mesh_loader.h>
#include <rviz/geometry.h>
#include <rviz/properties/vector_property.h>

#include "mouse_pub_tool.h"

namespace rviz_mouse_pub {

MousePub::MousePub() {
  shortcut_key_ = 'l';
  ros::NodeHandle n_;
  mouse_publisher_ = n_.advertise<geometry_msgs::Point32>("mouse_pub", 1);
}

MousePub::~MousePub() {
}

void MousePub::onInitialize() {
}

void MousePub::activate() {
}

void MousePub::deactivate() {
}

int MousePub::processMouseEvent(rviz::ViewportMouseEvent& event) {
  static const bool kDebug = false;
  Ogre::Vector3 intersection;
  Ogre::Plane ground_plane(Ogre::Vector3::UNIT_Z, 0.0f);
  if (rviz::getPointOnPlaneFromWindowXY(
        event.viewport, ground_plane, event.x, event.y, intersection)) {
    if (kDebug) printf("Loc: %f %f\n", intersection.x, intersection.y);
    if (event.leftDown()) {
      if (kDebug) printf("LeftDown\n");
      return Render | Finished;
    }
    geometry_msgs::Point32 p;
    p.x = intersection.x;
    p.y = intersection.y;
    p.z = 0;
    mouse_publisher_.publish(p);
  } else {
    if (kDebug) printf("Sky\n");
  }
  return Render;
}

}  // namespace rviz_mouse_pub

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_mouse_pub::MousePub, rviz::Tool)
