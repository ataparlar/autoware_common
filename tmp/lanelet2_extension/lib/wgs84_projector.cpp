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

// NOLINTBEGIN(readability-identifier-naming)

#include "lanelet2_extension/projection/wgs84_projector.hpp"

#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace lanelet::projection
{

WGS84Projector::WGS84Projector(Origin origin) : Projector(origin)
{
  origin_point = origin;
}

BasicPoint3d WGS84Projector::forward(const lanelet::GPSPoint & gps) const
{
  BasicPoint3d point3d;

  try {
    float lon_difference = gps.lon - origin_point.position.lon;
    float lat_difference = gps.lat - origin_point.position.lat;

    double lon_constant = (111312.84*std::cos(M_PI*gps.lat/180)) - (93.5*std::cos(3*(M_PI*gps.lat/180)))
                          + (0.118*std::cos(5*(M_PI*gps.lat/180)));
    double lat_constant = 111132.92 - (559.82*std::cos(2*(M_PI*gps.lat/180))) + (1.175*std::cos(4*(M_PI*gps.lat/180)))
                          - (0.0023*std::cos(6*(M_PI*gps.lat/180)));

     point3d.x() = lon_difference * lon_constant;
     point3d.y() = lat_difference * lat_constant;
     point3d.z() = gps.ele - origin_point.position.ele;
  } catch (const GeographicLib::GeographicErr & err) {
    std::cerr << err.what() << std::endl;
    return point3d;
  }

  return point3d;
}

GPSPoint WGS84Projector::reverse(const BasicPoint3d & mgrs_point) const
{
  GPSPoint gps{0., 0., 0.};
  std::cout << mgrs_point.x();
  return gps;
}


}  // namespace lanelet::projection

// NOLINTEND(readability-identifier-naming)
