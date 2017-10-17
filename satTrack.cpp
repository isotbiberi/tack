/*
 * Copyright 2013 Daniel Warner <contact@danrw.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <CoordTopocentric.h>
#include <CoordGeodetic.h>
#include <Observer.h>
#include <SGP4.h>

#include <iostream>

int main()
{
    Observer obs( 39.96972,33.07389,1167);
   /*
    Tle tle = Tle("UK-DMC 2                ",
        "1 35683U 09041C   12289.23158813  .00000484  00000-0  89219-4 0  5863",
        "2 35683  98.0221 185.3682 0001499 100.5295 259.6088 14.69819587172294");
    */
     Tle tle = Tle("UK-DMC 2                ",
            "1 23728U 95066A   08323.69802823 0.00000600  00000-0  31670-4 0    02",
            "2 23728  97.9290 101.5081 0307000 194.3756 165.6243 14.83044340    09");


    SGP4 sgp4(tle);

    std::cout << tle << std::endl;

    for (int i = 0; i < 1000; ++i)
    {
        /*
         * current time
         */
        DateTime now = DateTime::Now(true);
        /*
         * calculate satellite position
         */
        Eci eci = sgp4.FindPosition(now);
        /*
         * get look angle for observer to satellite
         */
        CoordTopocentric topo = obs.GetLookAngle(eci);
        /*
         * convert satellite position to geodetic coordinates
         */
        CoordGeodetic geo = eci.ToGeodetic();

        std::cout << now << " " << topo << " " << geo << std::endl;
    };

    return 0;
}
