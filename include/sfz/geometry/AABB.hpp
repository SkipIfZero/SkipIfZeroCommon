#pragma once
#ifndef SFZ_GEOMETRY_AABB_HPP
#define SFZ_GEOMETRY_AABB_HPP

#include <string>
#include <array>
#include <iostream> // std::ostream
#include <functional> // std::hash

#include "sfz/Assert.hpp"
#include "sfz/math/Vector.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

/**
 * @brief Class representing an Axis-Aligned Bounding Box.
 * @author Peter Hillerström
 */
class AABB final {
public:
	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	inline AABB(const vec3f& min, const vec3f& max) noexcept;
	inline AABB(const vec3f& centerPos, float xExtent, float yExtent, float zExtent) noexcept;

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	inline std::array<vec3f,8> corners() const noexcept;
	inline void corners(vec3f* arrayOut) const noexcept;
	inline vec3f closestPoint(const vec3f& point) const noexcept;

	inline size_t hash() const noexcept;
	inline std::string to_string() const noexcept;

	// Public getters/setters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	inline vec3f min() const noexcept { return mMin; }
	inline vec3f max() const noexcept { return mMax; }
	inline vec3f position() const noexcept { return mMin + (extents()/2.0f); }
	inline vec3f extents() const noexcept { return mMax - mMin; }
	inline float xExtent() const noexcept { return mMax[0] - mMin[0]; }
	inline float yExtent() const noexcept { return mMax[1] - mMin[1]; }
	inline float zExtent() const noexcept { return mMax[2] - mMin[2]; }
	inline vec3f halfExtents() const noexcept { return extents() / 2.0f; }
	inline float halfXExtent() const noexcept { return xExtent() / 2.0f; }
	inline float halfYExtent() const noexcept { return yExtent() / 2.0f; }
	inline float halfZExtent() const noexcept { return zExtent() / 2.0f; }

	inline void min(const vec3f& newMin) noexcept { mMin = newMin; }
	inline void max(const vec3f& newMax) noexcept { mMax = newMax; }
	inline void position(const vec3f& newCenterPos) noexcept;
	inline void extents(const vec3f& newExtents) noexcept;
	inline void xExtent(float newXExtent) noexcept;
	inline void yExtent(float newYExtent) noexcept;
	inline void zExtent(float newZExtent) noexcept;

private:
	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	vec3f mMin, mMax;
};

// Non-member operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

inline std::ostream& operator<< (std::ostream& ostream, const AABB& aabb) noexcept;

} // namespace sfz

// Specializations of standard library for sfz::AABB
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

template<>
struct hash<sfz::AABB> {
	inline size_t operator() (const sfz::AABB& aabb) const noexcept;
};

} // namespace std

#include "sfz/MSVC12HackOFF.hpp"
#include "sfz/geometry/AABB.inl"
#endif