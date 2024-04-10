////////////////////////////////////////////////////////////////////////////////////
///                                                                              ///
///    ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///    ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///      ░▒▓█▓▒░                                                                 ///
///       ░▒▓██▓▒░                                                               ///
///                                                                              ///
///     * QUIX LANG COMPILER - The official compiler for the Quix language.      ///
///     * Copyright (C) 2020-2024 Wesley C. Jones                                ///
///                                                                              ///
///     The QUIX Compiler Suite is free software; you can redistribute it and/or ///
///     modify it under the terms of the GNU Lesser General Public               ///
///     License as published by the Free Software Foundation; either             ///
///     version 2.1 of the License, or (at your option) any later version.       ///
///                                                                              ///
///     The QUIX Compiler Suite is distributed in the hope that it will be       ///
///     useful, but WITHOUT ANY WARRANTY; without even the implied warranty of   ///
///     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        ///
///     Lesser General Public License for more details.                          ///
///                                                                              ///
///     You should have received a copy of the GNU Lesser General Public         ///
///     License along with the QUIX Compiler Suite; if not, see                  ///
///     <https://www.gnu.org/licenses/>.                                         ///
///                                                                              ///
////////////////////////////////////////////////////////////////////////////////////

#ifndef __CODE_EXAMPLE_HPP__
#define __CODE_EXAMPLE_HPP__

#include <cstddef>

namespace libquixcc
{
    static const char benchmark_source[] = R"(

/* This is a simple program that does some basic stuff */

type EnginePoint = f32;     ~> The floating point type used for engine points
type EP = EnginePoint;      ~> Alias for EnginePoint

struct Point {              ~> A point in 2D space
    x: EP = 0.0,            ~> The x-coordinate
    y: EP = 0.0,            ~> The y-coordinate
}                           ~> End of Point struct

struct Line {               ~> A line in 2D space
    start: Point,           ~> The start point of the line
    end: Point,             ~> The end point of the line
} 

struct Circle {             ~> A circle in 2D space
    center: Point,          ~> The center of the circle
    radius: EP,             ~> The radius of the circle
}

struct Rectangle {          ~> A rectangle in 2D space
    top_left: Point,        ~> The top-left corner
    bottom_right: Point,    ~> The bottom-right corner
}

struct Triangle {           ~> A triangle in 2D space
    a: Point,               ~> The first point
    b: Point,               ~> The second point
    c: Point,               ~> The third point
}

let world_line: Line;       ~> A line in the world
let world_circle: Circle;   ~> A circle in the world
let world_rect: Rectangle;  ~> A rectangle in the world
let world_tri: Triangle;    ~> A triangle in the world

fn calculate_yada(): i8 {   ~> A function that calculates yada
    let x: i8 = 0;          ~> A variable x
    let y: i8 = 0;          ~> A variable y

    return (x+1) >> 2 & y;  ~> Return the result of some operations
}

fn main(): i8 {             ~> The main function
    return 0;               ~> Return 0
}
)";

    constexpr size_t benchmark_source_len = sizeof(benchmark_source) - 1;

}

#endif // __CODE_EXAMPLE_HPP__