#include "time_bounds.h"

bool time_bounds_to_xdr_object(const struct TimeBounds *in,
                               stellarxdr_TimeBounds *out) {
  out->maxTime = in->max_time;
  out->minTime = in->min_time;
  return true;
}

bool time_bounds_from_xdr_object(const stellarxdr_TimeBounds *in,
                                 struct TimeBounds *out) {
  out->min_time = in->minTime;
  out->max_time = in->maxTime;
  return true;
}