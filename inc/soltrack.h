/*
 *  SolarOptimize: Library to calculate the direction of the sun
 *  Copyright (C) 2016 Tino Gfroerer
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * This file contains the declaration and documentation of lib func
 *
 * @author Tino Gfroerer
 * @version 0.1
 
 * Versioning:
 * 0.x are alpha versions, which do not implement the full task yet
 * 1.x are beta version, which implement the task, but are untested
 * 1.x.x are tested versions
 */

#ifndef SOLTRACK_H
#define SOLTRACK_H

int soltrack_init(double deg_beta, double deg_gamma);

void print_tilt();

void print_orth_with_spin();

#endif /* SOLTRACK_H */
