# Decision Log

This file records architectural and implementation decisions using a list format.
2025-10-29 20:21:06 - Initial memory bank creation

*

## Decision

*

## Rationale

*

## Implementation Details

*
2025-11-23 14:35:00 - Modified acceleration/deceleration smoothing logic in longcontrol.py to implement urgency-based rate limiting

## Decision
Updated the longitudinal control smoothing logic to dynamically adjust the rate of acceleration change based on deceleration urgency.

## Rationale
The previous implementation used a fixed rate limit of 1.0 m/s^3 for both acceleration and deceleration. The new implementation provides more responsive braking by increasing the rate limit during urgent deceleration scenarios while maintaining smooth acceleration.

## Implementation Details
- Added urgency calculation based on required deceleration vs. maximum vehicle deceleration capability
- Implemented dynamic rate limiting: 1.0 m/s^3 for low urgency, up to 4.0 m/s^3 for high urgency
- Preserved smooth acceleration behavior with fixed rate limiting
- Added safety check to prevent division by zero if ACCEL_MIN is not available