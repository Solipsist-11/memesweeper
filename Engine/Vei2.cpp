#include "Vei2.h"
#include "SpriteCodex.h"
#include <cmath>

Vei2::Vei2( int x_in,int y_in )
	:
	x( x_in ),
	y( y_in )
{
}

Vei2 Vei2::operator+( const Vei2& rhs ) const
{
	return Vei2( x + rhs.x,y + rhs.y );
}

Vei2& Vei2::operator+=( const Vei2& rhs )
{
	return *this = *this + rhs;
}

Vei2 Vei2::operator*( int rhs ) const
{
	return Vei2( x * rhs,y * rhs );
}

Vei2& Vei2::operator*=( int rhs )
{
	return *this = *this * rhs;
}

Vei2 Vei2::operator-( const Vei2& rhs ) const
{
	return Vei2( x - rhs.x,y - rhs.y );
}

Vei2& Vei2::operator-=( const Vei2& rhs )
{
	return *this = *this - rhs;
}

Vei2 Vei2::operator/( int rhs ) const
{
	return Vei2( x / rhs,y / rhs );
}

Vei2& Vei2::operator/=( int rhs )
{
	return *this = *this / rhs;
}

float Vei2::GetLength() const
{
	return std::sqrt( float( GetLengthSq() ) );
}

int Vei2::GetLengthSq() const
{
	return x * x + y * y;
}

const Vei2 Vei2::GridtoScreenPos() const
{
	int new_x = x * SpriteCodex::tileSize;
	int new_y = y * SpriteCodex::tileSize;
	return Vei2(new_x, new_y);
}

const Vei2 Vei2::ScreentoGridPos() const
{
	int new_x = x / SpriteCodex::tileSize;
	int new_y = y / SpriteCodex::tileSize;
	return Vei2(new_x, new_y);
}
