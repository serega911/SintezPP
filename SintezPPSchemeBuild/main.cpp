#include "KinematicSchemeBuilder.h"

int main()
{
	setlocale( LC_ALL, "Russian" );
	NS_CORE Log::log( "====  ������ ����������� ������� � ����� ��������� �������. ��������.  ====\n\n" );

	ari::KinematicSchemeBuilder schemeBuilder;
	schemeBuilder.readUIGeneralData();
	schemeBuilder.run();
	system( "pause" );
}