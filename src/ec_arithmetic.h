#pragma once

#include "utility.h"
#include "field_arithmetic.h"

curve_pt add(curve_pt p, curve_pt q);

curve_pt scalar_mul(curve_pt p, int_256 alpha);

bool pt_equal(curve_pt p, curve_pt q);