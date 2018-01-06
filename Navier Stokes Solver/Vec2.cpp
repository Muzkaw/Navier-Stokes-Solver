//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

template<typename T>
Vec2<T>::Vec2() :x(0), y(0) {}
template<typename T>
Vec2<T>::Vec2(T const& _x, T const& _y) : x(_x), y(_y) {}
template <typename T> template <typename U>
Vec2<T>::Vec2(Vec2<U> const& u) : x(static_cast<T>(u.x)), y(static_cast<T>(u.y)) {}

template<typename T>
Vec2<T> operator-(Vec2<T> const& u)
{
	return Vec2<T>(-u.x, -u.y);
}

template<typename T>
Vec2<T> operator+=(Vec2<T> &u, Vec2<T> const& v)
{
	u.x += v.x;
	u.y += v.y;
	return u;
}
template<typename T>
Vec2<T> operator-=(Vec2<T> &u, Vec2<T> const& v)
{
	u.x -= v.x;
	u.y -= v.y;
	return u;
}
template<typename T>
Vec2<T> operator*=(Vec2<T> &u, T const& k)
{
	u.x *= k;
	u.y *= k;
	return u;
}
template<typename T>
Vec2<T> operator/=(Vec2<T> &u, T const& k)
{
	u.x /= k;
	u.y /= k;
	return u;
}

template<typename T>
Vec2<T> operator+(Vec2<T> u, Vec2<T> const& v)
{
	u += v;
	return u;
}
template<typename T>
Vec2<T> operator-(Vec2<T> u, Vec2<T> const& v)
{
	u -= v;
	return u;
}
template<typename T>
Vec2<T> operator*(Vec2<T> u, T const& k)
{
	u *= k;
	return u;
}
template<typename T>
Vec2<T> operator*(T const& k, Vec2<T> u)
{
	u *= k;
	return u;
}
template<typename T>
Vec2<T> operator/(Vec2<T> u, T const& k)
{
	u /= k;
	return u;
}

template<typename T>
bool operator==(Vec2<T> const& u, Vec2<T> const& v)
{
	return (u.x == v.x) && (u.y == v.y);
}
template<typename T>
bool operator!=(Vec2<T> const& u, Vec2<T> const& v)
{
	return (u.x != v.x) || (u.y != v.y);
}

template<typename T>
ostream& operator<<(ostream &stream, Vec2<T> const& u)
{
	stream << u.x << " ; " << u.y << endl;
	return stream;
}

template<typename T>
double norm(Vec2<T> const& u)
{
	return sqrt(u.x*u.x + u.y*u.y);
}
template<typename T>
Vec2<T> unitN(Vec2<T> const& u)
{
	return u / norm(u);
}
template<typename T>
Vec2<T> unitT(Vec2<T> const& u)
{
	return Vec2<T>(u.y, -u.x) / norm(u);
}

template<typename T>
double dot(Vec2<T> const& u, Vec2<T> const& v)
{
	return u.x*v.x + u.y*v.y;
}
template<typename T>
double cross(Vec2<T> const& u, Vec2<T> const& v)
{
	return u.x*v.y - u.y*v.x;
}

template<typename T>
Vec2<T> clamp(Vec2<T> &u, Vec2<T> const& mini, Vec2<T> const& maxi)
{
	u.x = std::max(std::min(u.x, maxi.x), mini.x);
	u.y = std::max(std::min(u.y, maxi.y), mini.y);
	return u;
}