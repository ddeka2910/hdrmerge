/*
 *  HDRMerge - HDR exposure merging software.
 *  Copyright 2012 Javier Celaya
 *  jcelaya@gmail.com
 *
 *  This file is part of HDRMerge.
 *
 *  HDRMerge is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  HDRMerge is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with HDRMerge. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _METADATA_H_
#define _METADATA_H_

#include <string>
#include <libraw/libraw.h>


namespace hdrmerge {

class MetaData {
public:
    MetaData(const char * f, const LibRaw & rawData);

    // From LibRaw
    int FC(int row, int col) const {
        return (filter >> (((row << 1 & 14) | (col & 1)) << 1) & 3);
    }

    bool isSameFormat(const MetaData & r) {
        return width == r.width && height == r.height && filter == r.filter && cdesc == r.cdesc;
    }

    uint16_t blackAt(size_t row, size_t col) {
        return black + cblack[FC(row, col)];
    }

    float logExp() const;

    void dumpInfo() const;

    std::string fileName;
    size_t width, height;
    std::string cdesc;
    uint32_t filter;
    uint16_t max;
    uint16_t black;
    uint16_t cblack[4];
    float isoSpeed;
    float shutter;
    float aperture;
    std::string maker, model;
    int colors;
};

} // namespace hdrmerge

#endif // _METADATA_H_
