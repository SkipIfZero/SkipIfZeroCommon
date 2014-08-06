#pragma once
#ifndef SFZ_MATH_RECTANGLE_HPP
#define SFZ_MATH_RECTANGLE_HPP

#include <stdexcept>
#include "sfz/math/Vector.hpp"
#include "sfz/math/Alignment.hpp"

namespace sfz {

	template<typename T>
	class Circle;

	template<typename T>
	class Rectangle final {
	public:
		// Static constants
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		static const HorizontalAlign DEFAULT_HORIZONTAL_ALIGN;
		static const VerticalAlign DEFAULT_VERTICAL_ALIGN;

		// Constructors and destructors
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		Rectangle() = delete;

		Rectangle(const Rectangle<T>& rect);

		Rectangle(const vec2<T>& position, const vec2<T>& dimensions, 
		          HorizontalAlign horizontalAlign = DEFAULT_HORIZONTAL_ALIGN, 
		          VerticalAlign verticalAlign = DEFAULT_VERTICAL_ALIGN);

		Rectangle(const vec2<T>& position, T width, T height, 
		          HorizontalAlign horizontalAlign = DEFAULT_HORIZONTAL_ALIGN, 
		          VerticalAlign verticalAlign = DEFAULT_VERTICAL_ALIGN);

		Rectangle(T x, T y, T width, T height, 
		          HorizontalAlign horizontalAlign = DEFAULT_HORIZONTAL_ALIGN, 
		          VerticalAlign verticalAlign = DEFAULT_VERTICAL_ALIGN);

		~Rectangle() = default;

		// Public member functions
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		bool overlap(const Rectangle<T>& rect) const;
		bool overlap(const Circle<T>& circle) const;
		bool overlap(const vec2<T>& vector) const;

		// Getters
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		vec2<T> getPosition() const;
		T getXPosition() const;
		T getYPosition() const;
		vec2<T> getDimensions() const;
		T getWidth() const;
		T getHeight() const;
		HorizontalAlign getHorizontalAlign() const;
		VerticalAlign getVerticalAlign() const;

		// Setters
		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

		void setPosition(const vec2<T>& position);
		void setPosition(T x, T y);
		void setXPosition(T x);
		void setYPosition(T y);
		void setDimensions(const vec2<T>& dimensions);
		void setDimensions(T width, T height);
		void setWidth(T width);
		void setHeight(T height);
		void setHorizontalAlign(HorizontalAlign horizontalAlign);
		void setVerticalAlign(VerticalAlign verticalAlign);
		void changeHorizontalAlign(HorizontalAlign horizontalAlign);
		void changeVerticalAlign(VerticalAlign verticalAlign);

	private:
		vec2<T> position;
		vec2<T> dimensions;
		HorizontalAlign horizontalAlign;
		VerticalAlign verticalAlign;
	};
}
#include "Rectangle.inl"
#endif