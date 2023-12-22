// Copyright 2015-2019 Autoware Foundation. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Authors: Simon Thompson, Ryohsuke Mitsudome

#ifndef LANELET2_EXTENSION__PROJECTION__WGS84_PROJECTOR_HPP_
#define LANELET2_EXTENSION__PROJECTION__WGS84_PROJECTOR_HPP_

// NOLINTBEGIN(readability-identifier-naming)

#include <GeographicLib/MGRS.hpp>
#include <GeographicLib/UTMUPS.hpp>

#include <lanelet2_io/Exceptions.h>
#include <lanelet2_io/Projection.h>

#include <string>
#include <utility>

namespace lanelet::projection
{
class WGS84Projector : public Projector
{
public:
  explicit WGS84Projector(Origin origin = Origin({0.0, 0.0}));

  /**
   * [WGS84Projector::forward projects gps lat/lon to Local Plane]
   * @param  gps [point with latitude longitude information]
   * @return     [projected point in Cartesian Coordinates]
   */
  BasicPoint3d forward(const GPSPoint & gps) const override;

  /**
   * [MGRSProjector::reverse projects point within MGRS 100km grid into gps
   * lat/lon (WGS84)]
   * @param  mgrs_point [3d point in MGRS 100km grid]
   * @return            [projected point in WGS84]
   */
  GPSPoint reverse(const BasicPoint3d & mgrs) const override;

private:
  Origin origin_point;
};

}  // namespace lanelet::projection

// NOLINTEND(readability-identifier-naming)

#endif  // LANELET2_EXTENSION__PROJECTION__WGS84_PROJECTOR_HPP_
