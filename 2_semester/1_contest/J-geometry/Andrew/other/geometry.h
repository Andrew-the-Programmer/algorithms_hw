// Andrew was here :3

#pragma once

#include <boost/type.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <cmath>
#include <sstream>
#include <vector>
#include <functional>

template <class T>
T Squared(const T& value) {
  return value * value;
}

template <class... T>
void Output(const T&... args) {
  ((std::cout << args << ' '), ...);
  std::cout << '\n';
}

template <class... T>
void Input(T&... args) {
  ((std::cin >> args), ...);
}

template <class T, class IStream = std::istream>
T InputResult(IStream& stream = std::cin) {
  T value;
  stream >> value;
  return value;
}

namespace geometry {

using namespace std::literals;

using T = int64_t;

// declarations
template <class T>
class Point;
template <class T>
class Vector;
template <class T>
class Segment;
template <class T>
class Line;
template <class T>
class Ray;
template <class T>
class Polygon;

// ishape.h

template <class T>
struct IShape {
  using PointType = Point<T>;
  using VectorType = Vector<T>;
  using SegmentType = Segment<T>;

  virtual ~IShape() = default;

  virtual IShape& Move(const VectorType&) = 0;
  virtual bool ContainsPoint(const PointType&) const = 0;
  virtual bool CrossesSegment(const SegmentType&) const = 0;
  virtual std::shared_ptr<IShape> Clone() const = 0;
  virtual std::string ToString() const = 0;

  friend std::ostream& operator<<(std::ostream& stream, const IShape& shape) {
    stream << shape.ToString();
    return stream;
  }
};

// point.h
template <class T>
struct Point : public IShape<T> {
 public:
  using IShapeType = IShape<T>;
  using VectorType = Vector<T>;
  using SegmentType = Segment<T>;

 public:
  Point() = default;

  Point(const T& x, const T& y);

  Point& Move(const VectorType&) override;

  bool ContainsPoint(const Point&) const override;

  bool CrossesSegment(const SegmentType&) const override;

  std::shared_ptr<IShapeType> Clone() const override;

  std::string ToString() const override;

  VectorType operator-(const Point&) const;

  bool operator==(const Point&) const;

  bool operator!=(const Point&) const;

  friend std::istream& operator>>(std::istream&, Point&);

 public:
  T x;
  T y;
};

template <class T>
T SquaredDistance(const Point<T>&, const Point<T>&);

template <class T>
double Distance(const Point<T>&, const Point<T>&);

// vector.h

template <class T>
struct Vector {
  T x = 0;
  T y = 0;

  using PointType = Point<T>;

  Vector() = default;

  Vector(const T& x, const T& y);

  Vector(const PointType&);  // NOLINT

  Vector(const PointType& begin, const PointType& end);

  operator PointType() const;  // NOLINT

  bool IsZero() const;

  T SquaredLength() const;

  double Length() const;

  static T ScalarProduct(const Vector&, const Vector&);

  static T SignedArea(const Vector&, const Vector&);

  static bool Parallel(const Vector&, const Vector&);

  bool PointsTo(const PointType&) const;

  static double Sin(const Vector&, const Vector&);

  T VectorProduct(const Vector&) const;

  Vector& operator+=(const Vector&);

  Vector operator+(const Vector&) const;

  Vector& operator-=(const Vector&);

  Vector operator-(const Vector&) const;

  Vector operator-() const;

  bool operator==(const Vector&) const;

  std::string ToString() const;

  friend std::ostream& operator<<(std::ostream&, const Vector&);

  friend std::istream& operator>>(std::istream&, Vector&);
};

// segment.h
template <class T>
struct Segment : public IShape<T> {
  using IShapeType = IShape<T>;
  using PointType = Point<T>;
  using VectorType = Vector<T>;
  using LineType = Line<T>;

  PointType first_point = PointType();
  PointType second_point = PointType();

  Segment() = default;

  Segment(const PointType&, const PointType&);

  auto GetDirectingVector() const;

  auto SquaredLength() const;

  auto Length() const;

  bool IsPoint() const;

 protected:
  bool ContainsPointOnSameLine(const PointType&) const;

  static bool OverlapOnSameLine(const Segment&, const Segment&);

 public:
  IShapeType& Move(const VectorType&) override;

  bool ContainsPoint(const PointType&) const override;

  bool CrossesSegment(const Segment&) const override;

  std::shared_ptr<IShapeType> Clone() const override;

  std::string ToString() const override;

  friend std::istream& operator>>(std::istream&, Segment&);
};

template <class T>
double Distance(const Point<T>&, const Segment<T>&);

// ray.h
template <class T>
struct Ray : public IShape<T> {
  using IShapeType = IShape<T>;
  using PointType = Point<T>;
  using VectorType = Vector<T>;
  using LineType = Line<T>;
  using SegmentType = Segment<T>;

  PointType start_point = PointType();
  VectorType directing_vector = VectorType();

  Ray() = default;

  Ray(const PointType& start_point, const VectorType& directing_vector);

  Ray(const PointType& start_point, const PointType& end_point);

  explicit Ray(const SegmentType&);

  explicit operator LineType();

  bool IsUndefined() const;

  bool IsDefined() const;

  IShapeType& Move(const VectorType&) override;

  bool ContainsPoint(const PointType&) const override;

  bool CrossesSegment(const SegmentType&) const override;

  std::shared_ptr<IShapeType> Clone() const override;

  std::string ToString() const override;

  bool PointsTo(const PointType&) const;

  friend std::istream& operator>>(std::istream&, Ray&);
};

// line.h
template <class T>
struct Line : public IShape<T> {
 public:
  using IShapeType = IShape<T>;
  using PointType = Point<T>;
  using VectorType = Vector<T>;
  using LineType = Line<T>;
  using SegmentType = Segment<T>;
  using RayType = Ray<T>;

 protected:
  /*
    Suppose line is determined by equation ax + by + c = 0 (a^2 + b^2 > 0).
    Finds any point of this line.
  */
  template <class R>
  static PointType FindAnyPoint(const R& a, const R& b, const R& c);

 public:
  Line() = default;

  Line(const PointType&, const PointType&);

  Line(const PointType& point, const VectorType& directing_vector);

  template <class R>
  Line(const R& a, const R& b, const R& c);

  Line(const Line&) = default;

  explicit Line(const RayType&);

  explicit Line(const SegmentType&);

  Line& operator=(const Line&) = default;

  bool IsUndefined() const;

  bool IsDefined() const;

  IShapeType& Move(const VectorType&) override;

  bool ContainsPoint(const PointType&) const override;

  bool CrossesSegment(const SegmentType&) const override;

  std::shared_ptr<IShapeType> Clone() const override;

  const VectorType& GetDirectingVector() const;

  VectorType& GetDirectingVector();

  void SetDirectingVector(const VectorType&);

  const PointType& GetPoint() const;

  PointType& GetPoint();

  void SetPoint(const PointType&);

  // return (a,b,c): ax + by + c = 0
  auto GetPolynomialReprArgs() const;

  std::string PolynomialRepr() const;

  std::string PointAndVectorRepr() const;

  std::string ToString() const override;

  static bool Parallel(const Line& first, const Line& second);

  template <class R = T>
  void InputAsPolynom(std::istream& stream);

  void InputAsPointAndVector(std::istream& stream);

  friend std::istream& operator>>(std::istream& stream, Line& line);

 public:
  PointType point = PointType();
  VectorType directing_vector = VectorType();
};

// circle.h
template <class T, class R = T>
struct Circle : public IShape<T> {
 public:
  using IShapeType = IShape<T>;
  using PointType = Point<T>;
  using VectorType = Vector<T>;
  using LineType = Line<T>;
  using SegmentType = Segment<T>;
  using RayType = Ray<T>;
  using RadiusType = R;

 public:
  Circle() = default;

  Circle(const RadiusType&, const PointType&);

  Circle(const PointType&, const RadiusType&);

  Circle(const Circle&) = default;

 protected:
  template <typename Cmp>
  bool CompareDistanceToPointAndRadius(const PointType&, const Cmp& cmp = Cmp()) const;

 public:
  IShapeType& Move(const VectorType&) override;

  bool ContainsPoint(const PointType&) const override;

  bool StrictlyContainsPoint(const PointType&) const;

  bool CrossesSegment(const SegmentType&) const override;

  std::shared_ptr<IShapeType> Clone() const override;

  std::string ToString() const override;

  friend std::istream& operator>>(std::istream&, Circle&);

 public:
  RadiusType radius = 0;
  PointType center = PointType();
};

// polygon.h
template <class T>
struct Polygon : public IShape<T> {
 public:
  using IShapeType = IShape<T>;
  using PointType = Point<T>;
  using VectorType = Vector<T>;
  using LineType = Line<T>;
  using SegmentType = Segment<T>;
  using RayType = Ray<T>;
  using RadiusType = T;

 public:
  Polygon() = default;

  Polygon(const std::initializer_list<PointType>&);

  explicit Polygon(const std::vector<PointType>&);

  auto Segments() const;

  IShapeType& Move(const VectorType&) override;

  bool ContainsPoint(const PointType&) const override;

  bool CrossesSegment(const SegmentType&) const override;

  std::shared_ptr<IShapeType> Clone() const override;

  std::string ToString() const override;

  friend std::istream& operator>>(std::istream&, Polygon&);

 public:
  std::vector<PointType> points;
};

// point.cpp
template <class T>
Point<T>::Point(const T& x, const T& y) : x(x), y(y) {
}

template <class T>
Point<T>& Point<T>::Move(const VectorType& vector) {
  x += vector.x;
  y += vector.y;
  return *this;
}

template <class T>
bool Point<T>::ContainsPoint(const Point<T>& other) const {
  return (*this) == other;
}

template <class T>
std::shared_ptr<IShape<T>> Point<T>::Clone() const {
  return std::make_shared<Point>(x, y);
}

template <class T>
std::string Point<T>::ToString() const {
  // return (boost::format("Point(%1%, %2%)") % x % y).str();
  std::stringstream ss;
  ss << "Point(" << x << ", " << y << ")";
  return ss.str();
}

template <class T>
typename Point<T>::VectorType Point<T>::operator-(const Point& other) const {
  return {other, *this};
}

template <class T>
bool Point<T>::operator==(const Point& other) const {
  return x == other.x && y == other.y;
}

template <class T>
bool Point<T>::operator!=(const Point& other) const {
  return !(*this == other);
}

template <class T>
std::istream& operator>>(std::istream& stream, Point<T>& point) {
  stream >> point.x >> point.y;
  return stream;
}

template <class T>
T SquaredDistance(const Point<T>& first, const Point<T>& second) {
  return Vector(first, second).SquaredLength();
}

template <class T>
double Distance(const Point<T>& first, const Point<T>& second) {
  return Vector(first, second).Length();
}

// vector.cpp
template <class T>
Vector<T>::Vector(const T& x, const T& y) : x(x), y(y) {
}

template <class T>
Vector<T>::Vector(const PointType& point) : Vector(point.x, point.y) {  // NOLINT
}

template <class T>
Vector<T>::Vector(const PointType& begin, const PointType& end) : Vector(end.x - begin.x, end.y - begin.y) {
}

template <class T>
Vector<T>::operator PointType() const {
  return {x, y};
}

template <class T>
bool Vector<T>::IsZero() const {
  return x == 0 && y == 0;
}

template <class T>
T Vector<T>::SquaredLength() const {
  return ScalarProduct(*this, *this);
}

template <class T>
double Vector<T>::Length() const {
  return std::sqrt(SquaredLength());
}

template <class T>
T Vector<T>::ScalarProduct(const Vector& first, const Vector& second) {
  return first.x * second.x + first.y * second.y;
}

template <class T>
T Vector<T>::SignedArea(const Vector& first, const Vector& second) {
  return first.x * second.y - first.y * second.x;
}

template <class T>
bool Vector<T>::Parallel(const Vector& first, const Vector& second) {
  if (first.IsZero() || second.IsZero()) {
    throw std::logic_error("Method 'Vector::Parallel' for zero-vector is undefined.");
  }
  return SignedArea(first, second) == 0;
}

template <class T>
bool Vector<T>::PointsTo(const PointType& point) const {
  if (this->IsZero()) {
    throw std::logic_error("Method 'Vector::PointsTo' for zero-vector is undefined.");
  }
  return ScalarProduct(Vector(point), *this) >= 0;
}

template <class T>
double Vector<T>::Sin(const Vector& first, const Vector& second) {
  return static_cast<double>(SignedArea(first, second)) / (first.Length() * second.Length());
}

template <class T>
T Vector<T>::VectorProduct(const Vector& other) const {
  return SignedArea(*this, other);
}

template <class T>
Vector<T>& Vector<T>::operator+=(const Vector& other) {
  x += other.x;
  y += other.y;
  return *this;
}

template <class T>
Vector<T> Vector<T>::operator+(const Vector& other) const {
  auto result = *this;
  result += other;
  return result;
}

template <class T>
Vector<T>& Vector<T>::operator-=(const Vector& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

template <class T>
Vector<T> Vector<T>::operator-(const Vector& other) const {
  auto result = *this;
  result -= other;
  return result;
}

template <class T>
Vector<T> Vector<T>::operator-() const {
  return {-x, -y};
}

template <class T>
bool Vector<T>::operator==(const Vector& other) const {
  return x == other.x && y == other.y;
}

template <class T>
std::string Vector<T>::ToString() const {
  // return (boost::format("Vector(%1%, %2%)") % x % y).str();
  std::stringstream ss;
  ss << "Vector(" << x << ", " << y << ")";
  return ss.str();
}

template <class T>
std::ostream& operator<<(std::ostream& stream, const Vector<T>& vector) {
  stream << vector.ToString();
  return stream;
}

template <class T>
std::istream& operator>>(std::istream& stream, Vector<T>& vector) {
  stream >> vector.x >> vector.y;
  return stream;
}

// segment.cpp
template <class T>
bool Point<T>::CrossesSegment(const Segment<T>& segment) const {
  return segment.ContainsPoint(*this);
}

template <class T>
Segment<T>::Segment(const PointType& first, const PointType& second) : first_point(first), second_point(second) {
}

template <class T>
auto Segment<T>::GetDirectingVector() const {
  return VectorType(first_point, second_point);
}

template <class T>
auto Segment<T>::SquaredLength() const {
  return GetDirectingVector().SquaredLength();
}

template <class T>
auto Segment<T>::Length() const {
  return GetDirectingVector().Length();
}

template <class T>
bool Segment<T>::IsPoint() const {
  return first_point == second_point;
}

// Assume point is on the line (first_point, second_point).
// Return true if segment contains point.
template <class T>
bool Segment<T>::ContainsPointOnSameLine(const PointType& point) const {
  auto vec = VectorType(first_point, point);
  auto prod = VectorType::ScalarProduct(vec, VectorType(first_point, second_point));
  return 0 <= prod && prod <= SquaredLength();
}

// Assume first_segment and second_segment are on the same line.
// Return true if first_segment and second_segment overlap.
template <class T>
bool Segment<T>::OverlapOnSameLine(const Segment& first_segment, const Segment& second_segment) {
  return first_segment.ContainsPointOnSameLine(second_segment.first_point) ||
         first_segment.ContainsPointOnSameLine(second_segment.second_point);
}

template <class T>
typename Segment<T>::IShapeType& Segment<T>::Move(const Vector<T>& vector) {
  first_point.Move(vector);
  second_point.Move(vector);
  return *this;
}

template <class T>
bool Segment<T>::ContainsPoint(const Point<T>& point) const {
  if (this->IsPoint()) {
    return point == first_point;
  }
  bool on_the_line = Line(*this).ContainsPoint(point);
  return on_the_line && ContainsPointOnSameLine(point);
}

template <class T>
bool Segment<T>::CrossesSegment(const Segment& segment) const {
  if (this->IsPoint()) {
    return segment.ContainsPoint(first_point);
  }
  if (segment.IsPoint()) {
    return this->ContainsPoint(segment.first_point);
  }
  Line first_line(*this);
  Line second_line(segment);
  if (!(first_line.CrossesSegment(segment) && second_line.CrossesSegment(*this))) {
    return false;
  }
  if (LineType::Parallel(first_line, second_line)) {  // first_line == second_line
    return OverlapOnSameLine(*this, segment);
  }
  return true;
}

template <class T>
std::shared_ptr<typename Segment<T>::IShapeType> Segment<T>::Clone() const {
  return std::make_shared<Segment>(first_point, second_point);
}

template <class T>
std::string Segment<T>::ToString() const {
  // return (boost::format("Segment(%1%, %2%)") % first_point % second_point).str();
  std::stringstream ss;
  ss << "Segment(" << first_point << ", " << second_point << ")";
  return ss.str();
}

template <class T>
std::istream& operator>>(std::istream& stream, Segment<T>& section) {
  stream >> section.first_point >> section.second_point;
  return stream;
}

template <class T>
double Distance(const Point<T>& point, const Segment<T>& segment) {
  if (segment.IsPoint()) {
    return Distance(point, segment.first_point);
  }
  auto section_vector = segment.GetDirectingVector();
  auto ray1 = Ray<T>(segment.second_point, section_vector);
  if (ray1.PointsTo(point)) {
    return Vector<T>(segment.second_point, point).Length();
  }
  auto ray2 = Ray<T>(segment.first_point, -section_vector);
  if (ray2.PointsTo(point)) {
    return Vector<T>(segment.first_point, point).Length();
  }
  auto vec_first_point = Vector<T>(segment.first_point, point);
  auto sin_angle = std::abs(Vector<T>::Sin(section_vector, vec_first_point));
  return sin_angle * vec_first_point.Length();
}

// ray.cpp
template <class T>
Ray<T>::Ray(const PointType& start_point, const VectorType& directing_vector)
    : start_point(start_point), directing_vector(directing_vector) {
}

template <class T>
Ray<T>::Ray(const PointType& start_point, const PointType& end_point)
    : start_point(start_point), directing_vector(VectorType(start_point, end_point)) {
}

template <class T>
Ray<T>::Ray(const SegmentType& segment)
    : Ray(segment.first_point, VectorType(segment.first_point, segment.second_point)) {
}

template <class T>
Ray<T>::operator LineType() {
  return {start_point, directing_vector};
}

template <class T>
bool Ray<T>::IsUndefined() const {
  return directing_vector.IsZero();
}

template <class T>
bool Ray<T>::IsDefined() const {
  return !IsUndefined();
}

template <class T>
typename Ray<T>::IShapeType& Ray<T>::Move(const Vector<T>& vector) {
  start_point.Move(vector);
  return *this;
}

template <class T>
bool Ray<T>::ContainsPoint(const PointType& point) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Ray::ContainsPoint(): ray is undefined.");
  }
  bool on_the_line = Line(*this).ContainsPoint(point);
  return on_the_line && PointsTo(point);
}

template <class T>
bool Ray<T>::CrossesSegment(const SegmentType& segment) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Ray::CrossesSegment(): ray is undefined.");
  }
  if (!LineType(*this).CrossesSegment(segment)) {
    return false;
  }
  VectorType a(start_point, segment.first_point);
  VectorType b(start_point, segment.second_point);
  VectorType c = directing_vector;
  auto vp_ac = VectorType::SignedArea(a, c);
  auto vp_bc = VectorType::SignedArea(b, c);
  auto sp_bc = VectorType::ScalarProduct(b, c);
  auto sp_ac = VectorType::ScalarProduct(a, c);
  return std::abs(vp_ac) * sp_bc + std::abs(vp_bc) * sp_ac >= 0;
}

template <class T>
std::shared_ptr<typename Ray<T>::IShapeType> Ray<T>::Clone() const {
  return std::make_shared<Ray>(start_point, directing_vector);
}

template <class T>
std::string Ray<T>::ToString() const {
  // return (boost::format("Ray(%1%, %2%)") % start_point % directing_vector).str();
  std::stringstream ss;
  ss << "Ray(" << start_point << ", " << directing_vector << ")";
  return ss.str();
}

template <class T>
bool Ray<T>::PointsTo(const PointType& point) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Ray::PointsTo(): ray is undefined.");
  }
  return directing_vector.PointsTo(VectorType(start_point, point));
}

template <class T>
std::istream& operator>>(std::istream& stream, Ray<T>& ray) {
  stream >> ray.start_point >> ray.directing_vector;
  return stream;
}

// line.cpp
template <class T>
template <class R>
typename Line<T>::PointType Line<T>::FindAnyPoint(const R& a, const R& b, const R& c) {
  if (a == 0) {
    if (b == 0) {
      throw std::invalid_argument("a and b cannot be zero");
    }
    return {0, -static_cast<T>(c) / static_cast<T>(b)};
  }
  return {-static_cast<T>(c) / static_cast<T>(a), 0};
}

template <class T>
Line<T>::Line(const PointType& point, const VectorType& directing_vector)
    : point(point), directing_vector(directing_vector) {
}

template <class T>
Line<T>::Line(const PointType& first, const PointType& second) : Line(first, VectorType(first, second)) {
}

template <class T>
template <class R>
Line<T>::Line(const R& a, const R& b, const R& c) : Line(FindAnyPoint(a, b, c), VectorType(b, -a)) {
}

template <class T>
Line<T>::Line(const Ray<T>& ray) : Line(ray.start_point, ray.directing_vector) {
}
template <class T>
Line<T>::Line(const SegmentType& segment) : Line(segment.first_point, segment.second_point) {
}

template <class T>
bool Line<T>::IsUndefined() const {
  return GetDirectingVector().IsZero();
}

template <class T>
bool Line<T>::IsDefined() const {
  return !IsUndefined();
}

template <class T>
typename Line<T>::IShapeType& Line<T>::Move(const VectorType& vector) {
  point.Move(vector);
  return *this;
}

template <class T>
bool Line<T>::ContainsPoint(const PointType& p) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Line::ContainsPoint: Line is undefined.");
  }
  VectorType to_p(GetPoint(), p);
  if (to_p.IsZero()) {
    return true;
  }
  return VectorType::Parallel(VectorType(GetPoint(), p), GetDirectingVector());
}

template <class T>
bool Line<T>::CrossesSegment(const SegmentType& segment) const {
  if (this->IsUndefined()) {
    throw std::logic_error("Line::CrossesSegment: Line is undefined.");
  }
  // v := VectorType::SignedArea(VectorType(point, p), directing_vector)
  // if (v > 0): p is to the left of line, if (v < 0): - to the right.
  // if (segment.first_point and segment.second_point are on the same side of the line): line does not cross segment.
  // else: line crosses segment.
  VectorType to_first(GetPoint(), segment.first_point);
  VectorType to_second(GetPoint(), segment.second_point);
  auto first_point_info = VectorType::SignedArea(to_first, GetDirectingVector());
  auto second_point_info = VectorType::SignedArea(to_second, GetDirectingVector());
  return first_point_info * second_point_info <= 0;
}

template <class T>
std::shared_ptr<typename Line<T>::IShapeType> Line<T>::Clone() const {
  return std::make_shared<Line>(*this);
}

template <class T>
const typename Line<T>::VectorType& Line<T>::GetDirectingVector() const {
  return directing_vector;
}

template <class T>
typename Line<T>::VectorType& Line<T>::GetDirectingVector() {
  return directing_vector;
}

template <class T>
void Line<T>::SetDirectingVector(const VectorType& vector) {
  this->directing_vector = vector;
}

template <class T>
const typename Line<T>::PointType& Line<T>::GetPoint() const {
  return point;
}

template <class T>
typename Line<T>::PointType& Line<T>::GetPoint() {
  return point;
}

template <class T>
void Line<T>::SetPoint(const PointType& point) {
  this->point = point;
}

// return (a,b,c): ax + by + c = 0
template <class T>
auto Line<T>::GetPolynomialReprArgs() const {
  auto a = GetDirectingVector().y;
  auto b = -GetDirectingVector().x;
  auto c = -(a * GetPoint().x + b * GetPoint().y);
  return std::make_tuple(a, b, c);
}

template <class T>
std::string Line<T>::PolynomialRepr() const {
  auto args = GetPolynomialReprArgs();
  // return (boost::format("Line(%1%, %2%, %3%)") % std::get<0>(args) %
  // std::get<1>(args) % std::get<2>(args)).str();
  std::stringstream ss;
  ss << "Line(" << std::get<0>(args) << ", " << std::get<1>(args) << ", " << std::get<2>(args) << ")";
  return ss.str();
}

template <class T>
std::string Line<T>::PointAndVectorRepr() const {
  // return (boost::format("Line(%1%, %2%)") % GetPoint() %
  // GetDirectingVector()).str();
  std::stringstream ss;
  ss << "Line(" << GetPoint() << ", " << GetDirectingVector() << ")";
  return ss.str();
}

template <class T>
std::string Line<T>::ToString() const {
  return PolynomialRepr();
}

template <class T>
bool Line<T>::Parallel(const Line& first, const Line& second) {
  if (first.IsUndefined() || second.IsUndefined()) {
    throw std::logic_error("Method 'Line::Parallel' for undefined lines is undefined.");
  }
  return VectorType::Parallel(first.GetDirectingVector(), second.GetDirectingVector());
}

template <class T>
template <class R>
void Line<T>::InputAsPolynom(std::istream& stream) {
  R a;
  R b;
  R c;
  stream >> a >> b >> c;
  *this = Line(a, b, c);
}

template <class T>
void Line<T>::InputAsPointAndVector(std::istream& stream) {
  SetPoint(InputResult<PointType>(stream));
  SetDirectingVector(InputResult<VectorType>(stream));
}

template <class T>
std::istream& operator>>(std::istream& stream, Line<T>& line) {
  line.InputAsPolynom(stream);
  return stream;
}

// circle.cpp
template <class T, class R>
Circle<T, R>::Circle(const RadiusType& radius, const PointType& center) : radius(radius), center(center) {
}

template <class T, class R>
Circle<T, R>::Circle(const PointType& center, const RadiusType& radius) : Circle(radius, center) {
}

template <class T, class R>
typename Circle<T, R>::IShapeType& Circle<T, R>::Move(const VectorType& vector) {
  center.Move(vector);
  return *this;
}

template <class T, class R>
template <typename Cmp>
bool Circle<T, R>::CompareDistanceToPointAndRadius(const PointType& point, const Cmp& cmp) const {
  return cmp(static_cast<RadiusType>(SquaredDistance(center, point)), Squared(radius));
}

template <class T, class R>
bool Circle<T, R>::ContainsPoint(const PointType& point) const {
  return CompareDistanceToPointAndRadius<std::less_equal<RadiusType>>(point);
}

template <class T, class R>
bool Circle<T, R>::StrictlyContainsPoint(const PointType& point) const {
  return CompareDistanceToPointAndRadius<std::less<RadiusType>>(point);
}

template <class T, class R>
bool Circle<T, R>::CrossesSegment(const SegmentType& segment) const {
  if (StrictlyContainsPoint(segment.first_point) && StrictlyContainsPoint(segment.second_point)) {
    return false;
  }
  return Distance(center, segment) <= static_cast<double>(radius);
}

template <class T, class R>
std::shared_ptr<typename Circle<T, R>::IShapeType> Circle<T, R>::Clone() const {
  return std::make_shared<Circle>(*this);
}

template <class T, class R>
std::string Circle<T, R>::ToString() const {
  // return (boost::format("Circle(%1%, %2%)") % center % radius).str();
  std::stringstream ss;
  ss << "Circle(" << center << ", " << radius << ")";
  return ss.str();
}

template <class T, class R>
std::istream& operator>>(std::istream& stream, Circle<T, R>& circle) {
  stream >> circle.center >> circle.radius;
  return stream;
}

// polygon.cpp
template <class T>
Polygon<T>::Polygon(const std::initializer_list<PointType>& list) : points(list) {
}

template <class T>
Polygon<T>::Polygon(const std::vector<PointType>& points) : points(points) {
}

template <class T>
auto Polygon<T>::Segments() const {
  std::vector<SegmentType> segments;
  for (size_t i = 0; i < points.size() - 1; ++i) {
    segments.emplace_back(points[i], points[i + 1]);
  }
  segments.emplace_back(points.back(), points.front());
  return segments;
}

template <class T>
typename Polygon<T>::IShapeType& Polygon<T>::Move(const VectorType& vector) {
  for (PointType& point : points) {
    point.Move(vector);
  }
  return *this;
}

template <class T>
bool Polygon<T>::ContainsPoint(const PointType& point) const {
  // T max = std::numeric_limits<T>::max();
  T max = 200000;
  auto ray = Ray(point, Vector(max, 1));
  size_t count = 0;
  for (const auto& segment : Segments()) {
    if (segment.ContainsPoint(point)) {
      return true;
    }
    if (ray.CrossesSegment(segment)) {
      ++count;
    }
  }
  return count % 2 == 1;
}

template <class T>
bool Polygon<T>::CrossesSegment(const SegmentType& segment) const {
  for (const auto& s : Segments()) {
    if (segment.CrossesSegment(s)) {
      return true;
    }
  }
  return false;
}

template <class T>
std::shared_ptr<typename Polygon<T>::IShapeType> Polygon<T>::Clone() const {
  return std::make_shared<Polygon>(points);
}

template <class T>
std::string Polygon<T>::ToString() const {
  std::stringstream ss;
  ss << "Polygon(";
  for (size_t i = 0; i < points.size(); ++i) {
    if (i != 0) {
      ss << ", ";
    }
    ss << points[i];
  }
  ss << ")";
  return ss.str();
}

template <class T>
std::istream& operator>>(std::istream& stream, Polygon<T>& poly) {
  size_t count = 0;
  stream >> count;
  for (size_t i = 0; i < count; ++i) {
    poly.points.push_back(InputResult<typename Polygon<T>::PointType>());
  }
  return stream;
}

}  // namespace geometry
