#include "TMake.h"



TMake::TMake( void )
{
	iKombi[0] = 1;
	iKombi[1] = 2;
	NUM = 0;
}

TMake::~TMake( void )
{

}

int TMake::Run( const std::vector<size_t> &Input, size_t first_frict_pos )
{
	CountPlanRyad = Input[0];
	ari::TPlanetaryGearSet PlanRyad;
	MasPlanRyad.resize( CountPlanRyad );
	for ( size_t i = 0; i < MasPlanRyad.size(); i++ ){
		PlanRyad.Create( i + 1 );
		MasPlanRyad[i] = PlanRyad;
	}
	YmaxPlanRyad = PlanRyad.getYMAX();
	YmaxGearBox = CountPlanRyad * YmaxPlanRyad + 2;
	for ( size_t j = 2; j < Input.size(); j++ ){
		AllLinks.push_back( Input[j] );
	}
	iIn = AllLinks[0];
	int iKombi[] = { 1, 2 };
	TWave Wave;
	int ret;
	CreateMas( V, 0 );
	CreateMas( Field, 0 );
	for ( size_t j = 0; j < AllLinks.size(); j++ ){
		Wave.Run( Field, YmaxGearBox, AllLinks[j] / 100, AllLinks[j] % 100 );
		LinksForPaint.push_back( Wave.Road );

		if ( j >= first_frict_pos && AllLinks[j] % 100 != 66 && first_frict_pos != 0 )
			for ( size_t k = 4; k < Wave.Road.size() - 2; k = k + 2 )
			{
				Field[Wave.Road[k] * YmaxGearBox + Wave.Road[k + 1]] = 7777;
				if ( k > 2 && k < Wave.Road.size() - 2 )
					k += 2;
			}
		else
		{
			for ( size_t k = 0; k < Wave.Road.size(); k = k + 2 )
			{
				Field[Wave.Road[k] * YmaxGearBox + Wave.Road[k + 1]] = AllLinks[j];
				if ( k > 2 && k < Wave.Road.size() - 2 )
					k += 2;
			}
		}
	}
	//std::sort(LinksForPaint.begin(), LinksForPaint.end(), pred);
	return 0;
}

int TMake::getCountPlanRyad()
{
	return CountPlanRyad;
}

size_t TMake::getYmaxGearBox()
{
	return YmaxGearBox;
}

int TMake::getCellV( size_t i )
{
	if ( !( i < 0 ) && !( i > V.size() - 1 ) )
		return V[i];
	else
		return -1;
}

int TMake::getCellLinksForPaint( size_t i, size_t j )
{
	if ( ( i >= 0 ) && ( i < LinksForPaint.size() ) && ( j >= 0 ) && ( j < LinksForPaint[i].size() ) )
		return LinksForPaint[i][j];
	else
		return -1;
}

size_t TMake::getSizeV()
{
	return V.size();
}

size_t TMake::getSizeLinksForPaint()
{
	return LinksForPaint.size();
}

size_t TMake::getSizeLinksForPaint( size_t i )
{
	return LinksForPaint[i].size();
}

bool TMake::GenNext( std::vector<size_t> &v, size_t MaxLen /*= 4*/ )
{
	if ( v.size() == 1 )
		return false;
	for ( int i = v.size() - 1; i > -1; i-- ){
		if ( v[i] != 0 && v[i] < MaxLen ){
			v[i]++;
			for ( size_t j = i + 1; j < v.size(); j++ ){
				if ( v[j] == MaxLen ){
					v[j] = 1;
				}
			}
			return true;
		}
	}
	return false;
}

ari::TPlanetaryGearSet::ePlanetarySetType TMake::GetType( size_t Num )
{
	switch ( Num ){
	case 0:
		return ari::TPlanetaryGearSet::DEFAULT;
	case 1:
		return ari::TPlanetaryGearSet::P_NORMAL;
		break;
	case 2:
		return ari::TPlanetaryGearSet::U_NORMAL;
		break;
	case 3:
		return ari::TPlanetaryGearSet::P_INVERSE;
		break;
	case 4:
		return ari::TPlanetaryGearSet::U_INVERSE;
		break;
	}
	return ari::TPlanetaryGearSet::DEFAULT;
}

void TMake::CreateMas( std::vector <int> & v, int a )
{
	//построчная запись поля из массивов планетарных рядов
	v.clear();
	TPlanetaryGearSet PlanRyad;
	PlanRyad.Create( 0 );
	int In = ( iIn - 44 ) / 100 % 10;
	for ( int i = 0; i < YmaxGearBox; i++ )
		v.push_back( 9999 );
	for ( size_t i = 0; i < PlanRyad.getXMAX(); i++ ){
		v.push_back( 9999 );
		for ( size_t k = 0; k < MasPlanRyad.size(); k++ ){
			for ( int j = 0; j < YmaxPlanRyad; j++ ){
				if ( ( k + 1 ) == In ) v.push_back( MasPlanRyad[k].getCellMas( a, i*YmaxPlanRyad + j ) );
				if ( ( k + 1 ) != In ) v.push_back( MasPlanRyad[k].getCellMas( 0, i*YmaxPlanRyad + j ) );
			}
		}
		v.push_back( 9999 );
	}
	for ( int i = 0; i < YmaxGearBox; i++ )
		v.push_back( 9999 );
	for ( int i = 1; i < YmaxGearBox - 1; i++ )
		v[YmaxGearBox + i] = 6600;														//корпус
	v[YmaxGearBox*PlanRyad.getXMAX() + 1] = 4400;										//вход
	v[YmaxGearBox*PlanRyad.getXMAX() + MasPlanRyad.size()*PlanRyad.getYMAX()] = 5500;			//выход
}
