#pragma once

#include "../Libraries/GlobalDefines.h"

#include "IDisplay.h"

NS_ARI_START

class Display;

typedef std::shared_ptr<Display> Display_p;

class Display: public IDisplay
{
private:

	NS_CORE eColor								m_fontColor;
	NS_CORE eColor								m_backColor;

	Display();

	void cursorPositionSet( const Cordinate & cord ) const;

public:

	static Display_p							create();


	virtual void								print( const Cordinate& cord, const char c ) const override;
	virtual void								setColors( NS_CORE eColor font, NS_CORE eColor background ) override;
	virtual void								resetColors() override;
};

NS_ARI_END