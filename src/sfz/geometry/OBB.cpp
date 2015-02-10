#include "sfz/geometry/OBB.hpp"

#include "sfz/MSVC12HackON.hpp"

namespace sfz {

// Anonymous functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace {

bool approxEqual(float lhs, float rhs) noexcept
{
	static const float EPSILON = 0.001f;
	return lhs <= rhs + EPSILON && lhs >= rhs - EPSILON;
}

} // anonymous namespace

// Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

OBB::OBB(const vec3f& center, const vec3f& xAxis, const vec3f& yAxis, const vec3f& zAxis,
         float xExtent, float yExtent, float zExtent) noexcept
:
	mCenter{center},
	mExtents{xExtent, yExtent, zExtent}
{
	mAxes[0] = xAxis;
	mAxes[1] = yAxis;
	mAxes[2] = zAxis;
	ensureCorrectState();
}

// Public member functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

size_t OBB::hash() const noexcept
{
	std::hash<vec3f> hasher;
	size_t hash = 0;
	// hash_combine algorithm from boost
	hash ^= hasher(mCenter) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mAxes[0]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mAxes[1]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mAxes[2]) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	hash ^= hasher(mExtents) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
	return hash;
}

std::string OBB::to_string() const noexcept
{
	std::string str{"Center: "};
	str += mCenter.to_string();
	str += "\nX-axis: ";
	str += mAxes[0].to_string();
	str += "\nY-axis: ";
	str += mAxes[1].to_string();
	str += "\nZ-axis: ";
	str += mAxes[2].to_string();
	str += "\nExtents: ";
	str += mExtents.to_string();
	return std::move(str);
}

// Public getters/setters
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

// Private functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void OBB::ensureCorrectState() noexcept
{
	// Check if axes are orthogonal
	assert(approxEqual(mAxes[0].dot(mAxes[1]), 0.0f));
	assert(approxEqual(mAxes[0].dot(mAxes[2]), 0.0f));
	assert(approxEqual(mAxes[1].dot(mAxes[2]), 0.0f));

	// Extents are non-negative
	assert(0.0f < mExtents[0]);
	assert(0.0f < mExtents[1]);
	assert(0.0f < mExtents[2]);
}

// Non-member operators
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

std::ostream& operator<< (std::ostream& ostream, const OBB& obb) noexcept
{
	return ostream << obb.to_string();
}

} // namespace sfz

// Specializations of standard library for sfz::OBB
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

namespace std {

size_t hash<sfz::OBB>::operator() (const sfz::OBB& obb) const noexcept
{
	return obb.hash();
}

} // namespace std

#include "sfz/MSVC12HackOFF.hpp"