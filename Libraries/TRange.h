#pragma once

namespace pss
{
	class TRange
	{
	private:

		float									m_begin;
		float									m_end;

	public:

		TRange() = delete;
		TRange( const float beg, const float end );

		float									getBegin() const;
		float									getEnd() const;
		float									getMid() const;
		bool									isInRange( const float value ) const;

	};
}