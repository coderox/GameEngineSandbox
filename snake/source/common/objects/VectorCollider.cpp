#include "VectorCollider.h"
#include "MathHelper.h"

using std::shared_ptr;
using Utilities::Vector2;

bool VectorCollider::Collides(Utilities::Vector2 vector1, Utilities::Vector2 vector2) const
{
	int x1 = static_cast<int>(vector1.m[0]);
	int x2 = static_cast<int>(vector2.m[0]);
	int y1 = static_cast<int>(vector1.m[1]);
	int y2 = static_cast<int>(vector2.m[1]);
    return ( x1 == x2 && y1 == y2);
}