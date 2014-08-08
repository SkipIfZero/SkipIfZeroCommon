namespace sfz {

	// Static constants
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	const HorizontalAlign Rectangle<T>::DEFAULT_HORIZONTAL_ALIGN = HorizontalAlign::CENTER;

	template<typename T>
	const VerticalAlign Rectangle<T>::DEFAULT_VERTICAL_ALIGN = VerticalAlign::MIDDLE;

	// Constructors and destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	Rectangle<T>::Rectangle(const Rectangle<T>& rect) :
		position{rect.position}, 
		dimensions{rect.dimensions},
		horizontalAlign{rect.horizontalAlign},
		verticalAlign{rect.verticalAlign} {
			// Initialization done.
	}

	template<typename T>
	Rectangle<T>::Rectangle(const vec2<T>& position, const vec2<T>& dimensions, 
		                    HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) :
		position{position}, 
		dimensions{requireNonNegative(dimensions[0]), requireNonNegative(dimensions[1])},
		horizontalAlign{horizontalAlign},
		verticalAlign{verticalAlign} {
			// Initialization done.
	}
	
	template<typename T>
	Rectangle<T>::Rectangle(const vec2<T>& position, T width, T height,
		                    HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) :
		position{position},
		dimensions{requireNonNegative(width), requireNonNegative(height)},
		horizontalAlign{horizontalAlign},
		verticalAlign{verticalAlign} {
			// Initialization done.
	}

	template<typename T>
	Rectangle<T>::Rectangle(T x, T y, T width, T height,
	                        HorizontalAlign horizontalAlign, VerticalAlign verticalAlign) :
		position{x, y},
		dimensions{requireNonNegative(width), requireNonNegative(height)},
		horizontalAlign{horizontalAlign},
		verticalAlign{verticalAlign} {
			// Initialization done.
	}

	// Public member functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	bool Rectangle<T>::overlap(const vec2<T>& point) const {
		Rectangle<T> leftBottomAlignRect{*this};
		leftBottomAlignRect.changeHorizontalAlign(HorizontalAlign::LEFT);
		leftBottomAlignRect.changeVerticalAlign(VerticalAlign::BOTTOM);

		T rectXLeft = leftBottomAlignRect.getXPosition();
		T rectXRight = rectXLeft + leftBottomAlignRect.getWidth();
		T rectYBottom = leftBottomAlignRect.getYPosition();
		T rectYTop = rectYBottom + leftBottomAlignRect.getHeight();
		T vecX = point[0];
		T vecY = point[1];

		return rectXLeft <= vecX && rectXRight >= vecX &&
		       rectYBottom <= vecY && rectYTop>= vecY;
	}

	template<typename T>
	bool Rectangle<T>::overlap(const Rectangle<T>& rect) const {
		Rectangle<T> leftBottomAlignRectThis{*this};
		leftBottomAlignRectThis.changeHorizontalAlign(HorizontalAlign::LEFT);
		leftBottomAlignRectThis.changeVerticalAlign(VerticalAlign::BOTTOM);

		Rectangle<T> leftBottomAlignRectOther{rect};
		leftBottomAlignRectOther.changeHorizontalAlign(HorizontalAlign::LEFT);
		leftBottomAlignRectOther.changeVerticalAlign(VerticalAlign::BOTTOM);

		T thisXLeft = leftBottomAlignRectThis.getXPosition();
		T thisXRight = thisXLeft + leftBottomAlignRectThis.getWidth();
		T thisYBottom = leftBottomAlignRectThis.getYPosition();
		T thisYTop = thisYBottom + leftBottomAlignRectThis.getHeight();

		T otherXLeft = leftBottomAlignRectOther.getXPosition();
		T otherXRight = otherXLeft + leftBottomAlignRectOther.getWidth();
		T otherYBottom = leftBottomAlignRectOther.getYPosition();
		T otherYTop = otherYBottom + leftBottomAlignRectOther.getHeight();

		return thisXLeft   <= otherXRight &&
		       thisXRight  >= otherXLeft &&
		       thisYBottom <= otherYTop &&
		       thisYTop    >= otherYBottom;
	}

	template<typename T>
	bool Rectangle<T>::overlap(const Circle<T>& circle) const {
		Rectangle<T> leftBottomAlignRect{*this};
		leftBottomAlignRect.changeHorizontalAlign(HorizontalAlign::LEFT);
		leftBottomAlignRect.changeVerticalAlign(VerticalAlign::BOTTOM);

		Circle<T> centerAlignCircle{circle};
		centerAlignCircle.changeHorizontalAlign(HorizontalAlign::CENTER);
		centerAlignCircle.changeVerticalAlign(VerticalAlign::MIDDLE);

		T rectXLeft = leftBottomAlignRect.getXPosition();
		T rectXRight = rectXLeft + leftBottomAlignRect.getWidth();
		T rectYBottom = leftBottomAlignRect.getYPosition();
		T rectYTop = rectYBottom + leftBottomAlignRect.getHeight();

		T circleX = centerAlignCircle.getXPosition();
		T circleY = centerAlignCircle.getYPosition();
		T radius = centerAlignCircle.getRadius();


		T closestX = circleX;
		T closestY = circleY;
		
		if(circleX <= rectXLeft) {
			closestX = rectXLeft;
		} 
		else if(circleX >= rectXRight) {
			closestX = rectXRight;
		}
		
		if(circleY <= rectYBottom) {
			closestY = rectYBottom;
		}
		else if(circleY >= rectYTop) {
			closestY = rectYTop;
		}
		
		return (sfz::vec2<T>{closestX, closestY} - centerAlignCircle.getPosition()).squaredNorm() /*getPosition().distanceSquared(closestX, closestY)*/ <= radius*radius;
	}

	// Getters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	vec2<T> Rectangle<T>::getPosition() const {
		return position;
	}

	template<typename T>
	T Rectangle<T>::getXPosition() const {
		return position[0];
	}

	template<typename T>
	T Rectangle<T>::getYPosition() const {
		return position[1];
	}

	template<typename T>
	vec2<T> Rectangle<T>::getDimensions() const {
		return dimensions;
	}

	template<typename T>
	T Rectangle<T>::getWidth() const {
		return dimensions[0];
	}

	template<typename T>
	T Rectangle<T>::getHeight() const {
		return dimensions[1];
	}

	template<typename T>
	HorizontalAlign Rectangle<T>::getHorizontalAlign() const {
		return horizontalAlign;
	}
	
	template<typename T>
	VerticalAlign Rectangle<T>::getVerticalAlign() const {
		return verticalAlign;
	}

	// Setters
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	void Rectangle<T>::setPosition(const vec2<T>& position) {
		this->position = position;
	}

	template<typename T>
	void Rectangle<T>::setPosition(T x, T y) {
		position[0] = x;
		position[1] = y;
	}

	template<typename T>
	void Rectangle<T>::setXPosition(T x) {
		position[0] = x;
	}

	template<typename T>
	void Rectangle<T>::setYPosition(T y) {
		position[1] = y;
	}

	template<typename T>
	void Rectangle<T>::setDimensions(const vec2<T>& dimensions) {
		this->dimensions[0] = requireNonNegative(dimensions[0]);
		this->dimensions[1] = requireNonNegative(dimensions[1]);
	}

	template<typename T>
	void Rectangle<T>::setDimensions(T width, T height) {
		dimensions[0] = requireNonNegative(width);
		dimensions[1] = requireNonNegative(height);
	}

	template<typename T>
	void Rectangle<T>::setWidth(T width) {
		dimensions[0] = requireNonNegative(width);
	}

	template<typename T>
	void Rectangle<T>::setHeight(T height) {
		dimensions[1] = requireNonNegative(height);
	}

	template<typename T>
	void Rectangle<T>::setHorizontalAlign(HorizontalAlign horizontalAlign) {
		this->horizontalAlign = horizontalAlign;
	}

	template<typename T>
	void Rectangle<T>::setVerticalAlign(VerticalAlign verticalAlign) {
		this->verticalAlign = verticalAlign;
	}

	template<typename T>
	void Rectangle<T>::changeHorizontalAlign(HorizontalAlign horizontalAlign) {
		position[0] = calculateNewPosition(position[0], dimensions[0], this->horizontalAlign, horizontalAlign);
		this->horizontalAlign = horizontalAlign;
	}

	template<typename T>
	void Rectangle<T>::changeVerticalAlign(VerticalAlign verticalAlign) {
		position[1] = calculateNewPosition(position[1], dimensions[1], this->verticalAlign, verticalAlign);
		this->verticalAlign = verticalAlign;
	}

	// Private helper functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	template<typename T>
	T Rectangle<T>::requireNonNegative(T value) const {
		if(value < 0) {
			throw std::invalid_argument{"Negative dimensions not allowed."};
		}
		return value;
	}
}