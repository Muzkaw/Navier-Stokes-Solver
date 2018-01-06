//This file is part of Navier Stokes Solver (GNU GPL) - https://www.youtube.com/user/Muzkaw).

template<typename T>
Field<T>::Field()
{
	col = 0;
	row = 0;
	c.clear();
	dx = 1;
}
template<typename T>
Field<T>::Field(int const& _col, int const& _row, T const& val0, double const &_dx)
{
	col = _col;
	row = _row;
	resize(col, row, val0);
	dx = _dx;
}
template<typename T>
void Field<T>::resize(int const& _col, int const& _row, T const& val0)
{
	col = _col;
	row = _row;
	c.resize(col*row,val0);
}
template<typename T>
T& Field<T>::operator() (int i, int j)
{
	return c[i + j*col];
}
template<typename T>
T Field<T>::operator() (int i, int j) const
{
	return c[i + j*col];
}
template<typename T>
T& Field<T>::operator() (Vec2<int> el)
{
	return c[el.x + el.y*col];
}
template<typename T>
T Field<T>::operator() (Vec2<int> el) const
{
	return c[el.x + el.y*col];
}

template<typename T>
int Field<T>::getRow() const
{
	return row;
}
template<typename T>
int Field<T>::getCol() const
{
	return col;
}
template<typename T>
void Field<T>::setDx(double const& _dx)
{
	dx = _dx;
}
template<typename T>
double Field<T>::getDx() const
{
	return dx;
}

/////////////////////////////////////////////////////////////////////////////////////

template<typename T>
Field<T> operator-=(Field<T> &m1, Field<T> const& m2)
{
	for (int i(0); i < m1.getCol(); i++)
		for (int j(0); j < m1.getRow(); j++)
			m1(i, j) -= m2(i, j);
	return m1;
}

template<typename T>
void rot(Field<T> &rotF, Field<Vec2<T>> const& F)
{
	for (int i(1); i < F.getCol() - 1; i++)
		for (int j(1); j < F.getRow() - 1; j++)
			rotF(i, j) = (F(i + 1, j).y - F(i - 1, j).y - F(i, j + 1).x + F(i, j - 1).x) / (2 * F.getDx());
}
template<typename T>
void grad(Field<Vec2<T>> &gradF, Field<T> const& F)
{
	for (int i(1); i < F.getCol() - 1; i++)
		for (int j(1); j < F.getRow() - 1; j++)
			gradF(i, j) = Vec2<T>(F(i+1, j) - F(i-1, j), F(i, j+1) - F(i, j-1)) / (2 * F.getDx());
}
template<typename T>
void div(Field<T> &divF, Field<Vec2<T>> const& F)
{
	for (int i(1); i < F.getCol() - 1; i++)
		for (int j(1); j < F.getRow() - 1; j++)
			divF(i, j) = (F(i + 1, j).x - F(i - 1, j).x + F(i, j + 1).y - F(i, j - 1).y) / (2 * F.getDx());
}

template<typename T>
void gradT(Field<Vec2<T>> &gradF, Field<T> const& F)
{
	for (int i(1); i < F.getCol() - 1; i++)
		for (int j(1); j < F.getRow() - 1; j++)
			gradF(i, j) = Vec2<T>(F(i, j + 1) - F(i, j - 1), -F(i + 1, j) + F(i - 1, j)) / (2 * F.getDx());
}

template<typename T>
T bilerp(Field<T> const& F, Vec2d &X)
{
	Vec2d X0, X1;
	Vec2d w0, w1;

	clamp(X, Vec2d(1, 1), Vec2d(F.getCol() - 2, F.getRow() - 2));

	X0 = Vec2d((int)X.x, (int)X.y);
	X1 = X0 + Vec2d(1, 1);

	w0 = X - X0;
	w1 = X1 - X;

	return w1.y*(F(X0.x, X0.y)*w1.x + F(X1.x, X0.y)*w0.x) + w0.y*(F(X0.x, X1.y)*w1.x + F(X1.x, X1.y)*w0.x);
}

template<typename T>
void advect(Field<Vec2<T>> &v, Field<T> &d, Field<Wall> const& wall, double const& dt)
{
	Field<Vec2<T>> vbuf = v;
	Field<T> dbuf = d;

	Vec2<T> X, X0, X1, w0, w1;
	for (int i(1); i < v.getCol() - 1; i++)
	{
		for (int j(1); j < v.getRow() - 1; j++)
		{
			if (wall(i, j).bnd == FLUID)
			{
				X = Vec2<T>(i, j) - v(i, j)*dt / v.getDx();

				clamp(X, Vec2<T>(1, 1), Vec2<T>(v.getCol() - 2, v.getRow() - 2));

				X0 = Vec2<T>((int)X.x, (int)X.y);
				X1 = X0 + Vec2<T>(1, 1);

				w0 = X - X0;
				w1 = X1 - X;

				vbuf(i, j) = w1.y*(v(X0.x, X0.y)*w1.x + v(X1.x, X0.y)*w0.x) + w0.y*(v(X0.x, X1.y)*w1.x + v(X1.x, X1.y)*w0.x);
				dbuf(i, j) = w1.y*(d(X0.x, X0.y)*w1.x + d(X1.x, X0.y)*w0.x) + w0.y*(d(X0.x, X1.y)*w1.x + d(X1.x, X1.y)*w0.x);
			}
		}
	}
	v = vbuf;
	d = dbuf;
}

template<typename T>
void relaxation(Field<T> &x, Field<T> const& b, Field<Wall> const& wall, double const& alpha, double const& beta, int const& kmax)
{
	Field<T> xbuf=x;
	for (int k(0); k < kmax; k++)
	{
		for (int i(1); i < x.getCol() - 1; i++)
		{
			for (int j(1); j < x.getRow() - 1; j++)
			{
				if (wall(i, j).bnd != NSLP) xbuf(i, j) = (x(i - 1, j) + x(i + 1, j) + x(i, j - 1) + x(i, j + 1) + alpha*b(i,j)) / beta;
				else xbuf(i, j) = T();
			}
		}
		x = xbuf;
	}
}

