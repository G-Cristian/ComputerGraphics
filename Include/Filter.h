#ifndef _FILTER_H_
#define _FILTER_H_

namespace K9 {
	class Filter {
	public:
		virtual ~Filter() {}

		float getRadius() const { return _radius; }

		virtual float execute(float x) const = 0;
		inline float executeScaled(float x, float scale) const {
			return execute(x / scale) / scale;
		}
	protected:
		Filter(float radius):
			_radius(radius) {
		}

		float _radius;
	};
}

#endif // !_FILTER_H_

