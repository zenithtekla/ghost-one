/*

   Copyright [2008] [Trevor Hogan]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

   CODE PORTED FROM THE ORIGINAL GHOST PROJECT: http://ghost.pwner.org/

*/

#include "ghost.h"
#include "util.h"
#include "crc32.h"
#include "sha1.h"
#include "config.h"
#include "map.h"

#define __STORMLIB_SELF__
#include <stormlib/StormLib.h>

#define ROTL(x,n) ((x)<<(n))|((x)>>(32-(n)))	// this won't work with signed types
#define ROTR(x,n) ((x)>>(n))|((x)<<(32-(n)))	// this won't work with signed types

//
// CMap
//

CMap :: CMap( CGHost *nGHost )
{
	CONSOLE_Print( "[MAP] using hardcoded Emerald Gardens map data for Warcraft 3 version 1.24 & 1.24b" );
	m_GHost = nGHost;
	m_Valid = true;
	m_MapPath = "Maps\\FrozenThrone\\(12)EmeraldGardens.w3x";
	m_MapSize = UTIL_ExtractNumbers( "174 221 4 0", 4 );
	m_MapInfo = UTIL_ExtractNumbers( "251 57 68 98", 4 );
	m_MapCRC = UTIL_ExtractNumbers( "108 250 204 59", 4 );
	m_MapSHA1 = UTIL_ExtractNumbers( "35 81 104 182 223 63 204 215 1 17 87 234 220 66 3 185 82 99 6 13", 20 );
	if (m_GHost->m_LANWar3Version == 23 )
	{
		m_MapCRC = UTIL_ExtractNumbers( "112 185 65 97", 4 );
		m_MapSHA1 = UTIL_ExtractNumbers( "187 28 143 4 97 223 210 52 218 28 95 52 217 203 121 202 24 120 59 213", 20 );
	}
	m_MapSpeed = MAPSPEED_FAST;
	m_MapVisibility = MAPVIS_DEFAULT;
	m_MapObservers = MAPOBS_NONE;
	m_MapFlags = MAPFLAG_TEAMSTOGETHER | MAPFLAG_FIXEDTEAMS;
	m_MapGameType = 9;
	m_MapWidth = UTIL_ExtractNumbers( "172 0", 2 );
	m_MapHeight = UTIL_ExtractNumbers( "172 0", 2 );
	m_MapLoadInGame = false;
	m_MapNumPlayers = 12;
	m_MapNumTeams = 12;
	m_MapOnlyAutoWarnIfMoreThanXPlayers = 0;
	m_AutoWarnMarks.push_back( 0 );
	m_LogAll = false;
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 0, 0, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 1, 1, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 2, 2, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 3, 3, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 4, 4, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 5, 5, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 6, 6, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 7, 7, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 8, 8, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 9, 9, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 10, 10, SLOTRACE_RANDOM ) );
	m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 11, 11, SLOTRACE_RANDOM ) );
}

CMap :: CMap( CGHost *nGHost, CConfig *CFG, string nCFGFile )
{
	m_GHost = nGHost;
	m_LogAll = false;
	Load( CFG, nCFGFile );
}

CMap :: ~CMap( )
{

}

BYTEARRAY CMap :: GetMapGameFlags( )
{
	/*

	Speed: (mask 0x00000003) cannot be combined
		0x00000000 - Slow game speed
		0x00000001 - Normal game speed
		0x00000002 - Fast game speed
	Visibility: (mask 0x00000F00) cannot be combined
		0x00000100 - Hide terrain
		0x00000200 - Map explored
		0x00000400 - Always visible (no fog of war)
		0x00000800 - Default
	Observers/Referees: (mask 0x40003000) cannot be combined
		0x00000000 - No Observers
		0x00002000 - Observers on Defeat
		0x00003000 - Additional players as observer allowed
		0x40000000 - Referees
	Teams/Units/Hero/Race: (mask 0x07064000) can be combined
		0x00004000 - Teams Together (team members are placed at neighbored starting locations)
		0x00060000 - Fixed teams
		0x01000000 - Unit share
		0x02000000 - Random hero
		0x04000000 - Random races

	*/

	uint32_t GameFlags = 0;

	// speed

	if( m_MapSpeed == MAPSPEED_SLOW )
		GameFlags = 0x00000000;
	else if( m_MapSpeed == MAPSPEED_NORMAL )
		GameFlags = 0x00000001;
	else
		GameFlags = 0x00000002;

	// visibility

	if( m_MapVisibility == MAPVIS_HIDETERRAIN )
		GameFlags |= 0x00000100;
	else if( m_MapVisibility == MAPVIS_EXPLORED )
		GameFlags |= 0x00000200;
	else if( m_MapVisibility == MAPVIS_ALWAYSVISIBLE )
		GameFlags |= 0x00000400;
	else
		GameFlags |= 0x00000800;

	// observers

	if( m_MapObservers == MAPOBS_ONDEFEAT )
		GameFlags |= 0x00002000;
	else if( m_MapObservers == MAPOBS_ALLOWED )
		GameFlags |= 0x00003000;
	else if( m_MapObservers == MAPOBS_REFEREES )
		GameFlags |= 0x40000000;

	// teams/units/hero/race

	if( m_MapFlags & MAPFLAG_TEAMSTOGETHER )
		GameFlags |= 0x00004000;
	if( m_MapFlags & MAPFLAG_FIXEDTEAMS )
		GameFlags |= 0x00060000;
	if( m_MapFlags & MAPFLAG_UNITSHARE )
		GameFlags |= 0x01000000;
	if( m_MapFlags & MAPFLAG_RANDOMHERO )
		GameFlags |= 0x02000000;
	if( m_MapFlags & MAPFLAG_RANDOMRACES )
		GameFlags |= 0x04000000;

	return UTIL_CreateByteArray( GameFlags, false );
}

void CMap :: Load( CConfig *CFG, string nCFGFile )
{
	m_Valid = true;
	m_CFGFile = nCFGFile;
	m_GHost->UDPChatSend("|cfg "+nCFGFile);

	// load the map data

	m_MapLocalPath = CFG->GetString( "map_localpath", string( ) );
	m_MapData.clear( );

	if( !m_MapLocalPath.empty( ) )
		m_MapData = UTIL_FileRead( m_GHost->m_MapPath + m_MapLocalPath );

	// load the map MPQ

	string MapMPQFileName = m_GHost->m_MapPath + m_MapLocalPath;
	HANDLE MapMPQ;
	bool MapMPQReady = false;

	if( SFileOpenArchive( MapMPQFileName.c_str( ), 0, MPQ_OPEN_FORCE_MPQ_V1, &MapMPQ ) )
	{
		CONSOLE_Print( "[MAP] loading MPQ file [" + MapMPQFileName + "]" );
		MapMPQReady = true;
	}
	else
		CONSOLE_Print( "[MAP] warning - unable to load MPQ file [" + MapMPQFileName + "]" );

	// try to calculate map_size, map_info, map_crc, map_sha1

	BYTEARRAY MapSize;
	BYTEARRAY MapInfo;
	BYTEARRAY MapCRC;
	BYTEARRAY MapSHA1;

	if( !m_MapData.empty( ) )
	{
		m_GHost->m_SHA->Reset( );

		// calculate map_size

		MapSize = UTIL_CreateByteArray( (uint32_t)m_MapData.size( ), false );
		CONSOLE_Print( "[MAP] calculated map_size = " + UTIL_ToString( MapSize[0] ) + " " + UTIL_ToString( MapSize[1] ) + " " + UTIL_ToString( MapSize[2] ) + " " + UTIL_ToString( MapSize[3] ) );

		// calculate map_info (this is actually the CRC)

		MapInfo = UTIL_CreateByteArray( (uint32_t)m_GHost->m_CRC->FullCRC( (unsigned char *)m_MapData.c_str( ), m_MapData.size( ) ), false );
		CONSOLE_Print( "[MAP] calculated map_info = " + UTIL_ToString( MapInfo[0] ) + " " + UTIL_ToString( MapInfo[1] ) + " " + UTIL_ToString( MapInfo[2] ) + " " + UTIL_ToString( MapInfo[3] ) );

		// calculate map_crc (this is not the CRC) and map_sha1
		// a big thank you to Strilanc for figuring the map_crc algorithm out

		string CommonJ = UTIL_FileRead( m_GHost->m_MapCFGPath + "common.j" );

		if( CommonJ.empty( ) )
			CONSOLE_Print( "[MAP] unable to calculate map_crc/sha1 - unable to read file [" + m_GHost->m_MapCFGPath + "common.j]" );
		else
		{
			string BlizzardJ = UTIL_FileRead( m_GHost->m_MapCFGPath + "blizzard.j" );

			if( BlizzardJ.empty( ) )
				CONSOLE_Print( "[MAP] unable to calculate map_crc/sha1 - unable to read file [" + m_GHost->m_MapCFGPath + "blizzard.j]" );
			else
			{
				uint32_t Val = 0;

				// update: it's possible for maps to include their own copies of common.j and/or blizzard.j
				// this code now overrides the default copies if required

				bool OverrodeCommonJ = false;
				bool OverrodeBlizzardJ = false;

				if( MapMPQReady )
				{
					HANDLE SubFile;

					// override common.j

					if( SFileOpenFileEx( MapMPQ, "Scripts\\common.j", 0, &SubFile ) )
					{
						uint32_t FileLength = SFileGetFileSize( SubFile, NULL );

						if( FileLength > 0 && FileLength != 0xFFFFFFFF )
						{
							char *SubFileData = new char[FileLength];
							DWORD BytesRead = 0;

							if( SFileReadFile( SubFile, SubFileData, FileLength, &BytesRead ) )
							{
								CONSOLE_Print( "[MAP] overriding default common.j with map copy while calculating map_crc/sha1" );
								OverrodeCommonJ = true;
								Val = Val ^ XORRotateLeft( (unsigned char *)SubFileData, BytesRead );
								m_GHost->m_SHA->Update( (unsigned char *)SubFileData, BytesRead );
							}

							delete [] SubFileData;
						}

						SFileCloseFile( SubFile );
					}
				}

				if( !OverrodeCommonJ )
				{
					Val = Val ^ XORRotateLeft( (unsigned char *)CommonJ.c_str( ), CommonJ.size( ) );
					m_GHost->m_SHA->Update( (unsigned char *)CommonJ.c_str( ), CommonJ.size( ) );
				}

				if( MapMPQReady )
				{
					HANDLE SubFile;

					// override blizzard.j

					if( SFileOpenFileEx( MapMPQ, "Scripts\\blizzard.j", 0, &SubFile ) )
					{
						uint32_t FileLength = SFileGetFileSize( SubFile, NULL );

						if( FileLength > 0 && FileLength != 0xFFFFFFFF )
						{
							char *SubFileData = new char[FileLength];
							DWORD BytesRead = 0;

							if( SFileReadFile( SubFile, SubFileData, FileLength, &BytesRead ) )
							{
								CONSOLE_Print( "[MAP] overriding default blizzard.j with map copy while calculating map_crc/sha1" );
								OverrodeBlizzardJ = true;
								Val = Val ^ XORRotateLeft( (unsigned char *)SubFileData, BytesRead );
								m_GHost->m_SHA->Update( (unsigned char *)SubFileData, BytesRead );
							}

							delete [] SubFileData;
						}

						SFileCloseFile( SubFile );
					}
				}

				if( !OverrodeBlizzardJ )
				{
					Val = Val ^ XORRotateLeft( (unsigned char *)BlizzardJ.c_str( ), BlizzardJ.size( ) );
					m_GHost->m_SHA->Update( (unsigned char *)BlizzardJ.c_str( ), BlizzardJ.size( ) );
				}

				Val = ROTL( Val, 3 );
				Val = ROTL( Val ^ 0x03F1379E, 3 );
				m_GHost->m_SHA->Update( (unsigned char *)"\x9E\x37\xF1\x03", 4 );

				if( MapMPQReady )
				{
					vector<string> FileList;
					FileList.push_back( "war3map.j" );
					FileList.push_back( "scripts\\war3map.j" );
					FileList.push_back( "war3map.w3e" );
					FileList.push_back( "war3map.wpm" );
					FileList.push_back( "war3map.doo" );
					FileList.push_back( "war3map.w3u" );
					FileList.push_back( "war3map.w3b" );
					FileList.push_back( "war3map.w3d" );
					FileList.push_back( "war3map.w3a" );
					FileList.push_back( "war3map.w3q" );
					bool FoundScript = false;

					for( vector<string> :: iterator i = FileList.begin( ); i != FileList.end( ); i++ )
					{
						// don't use scripts\war3map.j if we've already used war3map.j (yes, some maps have both but only war3map.j is used)

						if( FoundScript && *i == "scripts\\war3map.j" )
							continue;

						HANDLE SubFile;

						if( SFileOpenFileEx( MapMPQ, (*i).c_str( ), 0, &SubFile ) )
						{
							uint32_t FileLength = SFileGetFileSize( SubFile, NULL );

							if( FileLength > 0 && FileLength != 0xFFFFFFFF )
							{
								char *SubFileData = new char[FileLength];
								DWORD BytesRead = 0;

								if( SFileReadFile( SubFile, SubFileData, FileLength, &BytesRead ) )
								{
									if( *i == "war3map.j" || *i == "scripts\\war3map.j" )
										FoundScript = true;

									Val = ROTL( Val ^ XORRotateLeft( (unsigned char *)SubFileData, BytesRead ), 3 );
									m_GHost->m_SHA->Update( (unsigned char *)SubFileData, BytesRead );
									// DEBUG_Print( "*** found: " + *i );
								}

								delete [] SubFileData;
							}

							SFileCloseFile( SubFile );
						}
						else
						{
							// DEBUG_Print( "*** not found: " + *i );
						}
					}

					if( !FoundScript )
						CONSOLE_Print( "[MAP] couldn't find war3map.j or scripts\\war3map.j in MPQ file, calculated map_crc/sha1 is probably wrong" );

					MapCRC = UTIL_CreateByteArray( Val, false );
					CONSOLE_Print( "[MAP] calculated map_crc = " + UTIL_ToString( MapCRC[0] ) + " " + UTIL_ToString( MapCRC[1] ) + " " + UTIL_ToString( MapCRC[2] ) + " " + UTIL_ToString( MapCRC[3] ) );
					m_GHost->m_SHA->Final( );
					unsigned char SHA1[20];
					memset( SHA1, 0, sizeof( unsigned char ) * 20 );
					m_GHost->m_SHA->GetHash( SHA1 );
					MapSHA1 = UTIL_CreateByteArray( SHA1, 20 );
					CONSOLE_Print( "[MAP] calculated map_sha1 = " + UTIL_ByteArrayToDecString( MapSHA1 ) );
				}
				else
					CONSOLE_Print( "[MAP] unable to calculate map_crc/sha1 - map MPQ file not loaded" );
			}
		}
	}
	else
		CONSOLE_Print( "[MAP] no map data available, using config file for map_size, map_info, map_crc, map_sha1" );

	// try to calculate map_width, map_height, map_slot<x>, map_numplayers, map_numteams

	BYTEARRAY MapWidth;
	BYTEARRAY MapHeight;
	uint32_t MapNumPlayers = 0;
	uint32_t MapNumTeams = 0;
	uint32_t MapFilterType = MAPFILTER_TYPE_SCENARIO;
	vector<CGameSlot> Slots;

	if( !m_MapData.empty( ) )
	{
		if( MapMPQReady )
		{
			HANDLE SubFile;

			if( SFileOpenFileEx( MapMPQ, "war3map.w3i", 0, &SubFile ) )
			{
				uint32_t FileLength = SFileGetFileSize( SubFile, NULL );

				if( FileLength > 0 && FileLength != 0xFFFFFFFF )
				{
					char *SubFileData = new char[FileLength];
					DWORD BytesRead = 0;

					if( SFileReadFile( SubFile, SubFileData, FileLength, &BytesRead ) )
					{
						istringstream ISS( string( SubFileData, BytesRead ) );

						// war3map.w3i format found at http://www.wc3campaigns.net/tools/specs/index.html by Zepir/PitzerMike

						string GarbageString;
						uint32_t FileFormat;
						uint32_t RawMapWidth;
						uint32_t RawMapHeight;
						uint32_t RawMapFlags;
						uint32_t RawMapNumPlayers;
						uint32_t RawMapNumTeams;

						ISS.read( (char *)&FileFormat, 4 );				// file format (18 = ROC, 25 = TFT)

						if( FileFormat == 18 || FileFormat == 25 )
						{
							ISS.seekg( 4, ios :: cur );					// number of saves
							ISS.seekg( 4, ios :: cur );					// editor version
							getline( ISS, GarbageString, '\0' );		// map name
							getline( ISS, GarbageString, '\0' );		// map author
							getline( ISS, GarbageString, '\0' );		// map description
							getline( ISS, GarbageString, '\0' );		// players recommended
							ISS.seekg( 32, ios :: cur );				// camera bounds
							ISS.seekg( 16, ios :: cur );				// camera bounds complements
							ISS.read( (char *)&RawMapWidth, 4 );		// map width
							ISS.read( (char *)&RawMapHeight, 4 );		// map height
							ISS.read( (char *)&RawMapFlags, 4 );		// flags
							ISS.seekg( 1, ios :: cur );					// map main ground type

							if( FileFormat == 18 )
								ISS.seekg( 4, ios :: cur );				// campaign background number
							else if( FileFormat == 25 )
							{
								ISS.seekg( 4, ios :: cur );				// loading screen background number
								getline( ISS, GarbageString, '\0' );	// path of custom loading screen model
							}

							getline( ISS, GarbageString, '\0' );		// map loading screen text
							getline( ISS, GarbageString, '\0' );		// map loading screen title
							getline( ISS, GarbageString, '\0' );		// map loading screen subtitle

							if( FileFormat == 18 )
								ISS.seekg( 4, ios :: cur );				// map loading screen number
							else if( FileFormat == 25 )
							{
								ISS.seekg( 4, ios :: cur );				// used game data set
								getline( ISS, GarbageString, '\0' );	// prologue screen path
							}

							getline( ISS, GarbageString, '\0' );		// prologue screen text
							getline( ISS, GarbageString, '\0' );		// prologue screen title
							getline( ISS, GarbageString, '\0' );		// prologue screen subtitle

							if( FileFormat == 25 )
							{
								ISS.seekg( 4, ios :: cur );				// uses terrain fog
								ISS.seekg( 4, ios :: cur );				// fog start z height
								ISS.seekg( 4, ios :: cur );				// fog end z height
								ISS.seekg( 4, ios :: cur );				// fog density
								ISS.seekg( 1, ios :: cur );				// fog red value
								ISS.seekg( 1, ios :: cur );				// fog green value
								ISS.seekg( 1, ios :: cur );				// fog blue value
								ISS.seekg( 1, ios :: cur );				// fog alpha value
								ISS.seekg( 4, ios :: cur );				// global weather id
								getline( ISS, GarbageString, '\0' );	// custom sound environment
								ISS.seekg( 1, ios :: cur );				// tileset id of the used custom light environment
								ISS.seekg( 1, ios :: cur );				// custom water tinting red value
								ISS.seekg( 1, ios :: cur );				// custom water tinting green value
								ISS.seekg( 1, ios :: cur );				// custom water tinting blue value
								ISS.seekg( 1, ios :: cur );				// custom water tinting alpha value
							}

							ISS.read( (char *)&RawMapNumPlayers, 4 );	// number of players
							uint32_t ClosedSlots = 0;

							for( uint32_t i = 0; i < RawMapNumPlayers; i++ )
							{
								CGameSlot Slot( 0, 255, SLOTSTATUS_OPEN, 0, 0, 1, SLOTRACE_RANDOM );
								uint32_t Colour;
								uint32_t Status;
								uint32_t Race;

								ISS.read( (char *)&Colour, 4 );			// colour
								Slot.SetColour( Colour );
								ISS.read( (char *)&Status, 4 );			// status

								if( Status == 1 )
									Slot.SetSlotStatus( SLOTSTATUS_OPEN );
								else if( Status == 2 )
								{
									Slot.SetSlotStatus( SLOTSTATUS_OCCUPIED );
									Slot.SetComputer( 1 );
									Slot.SetComputerType( SLOTCOMP_NORMAL );
								}
								else
								{
									Slot.SetSlotStatus( SLOTSTATUS_CLOSED );
									ClosedSlots++;
								}

								ISS.read( (char *)&Race, 4 );			// race

								if( Race == 1 )
									Slot.SetRace( SLOTRACE_HUMAN );
								else if( Race == 2 )
									Slot.SetRace( SLOTRACE_ORC );
								else if( Race == 3 )
									Slot.SetRace( SLOTRACE_UNDEAD );
								else if( Race == 4 )
									Slot.SetRace( SLOTRACE_NIGHTELF );
								else
									Slot.SetRace( SLOTRACE_RANDOM );

								ISS.seekg( 4, ios :: cur );				// fixed start position
								getline( ISS, GarbageString, '\0' );	// player name
								ISS.seekg( 4, ios :: cur );				// start position x
								ISS.seekg( 4, ios :: cur );				// start position y
								ISS.seekg( 4, ios :: cur );				// ally low priorities
								ISS.seekg( 4, ios :: cur );				// ally high priorities

								if( Slot.GetSlotStatus( ) != SLOTSTATUS_CLOSED )
									Slots.push_back( Slot );
							}

							ISS.read( (char *)&RawMapNumTeams, 4 );		// number of teams

							for( uint32_t i = 0; i < RawMapNumTeams; i++ )
							{
								uint32_t Flags;
								uint32_t PlayerMask;

								ISS.read( (char *)&Flags, 4 );			// flags
								ISS.read( (char *)&PlayerMask, 4 );		// player mask

								for( unsigned char j = 0; j < 12; j++ )
								{
									if( PlayerMask & 1 )
									{
										for( vector<CGameSlot> :: iterator k = Slots.begin( ); k != Slots.end( ); k++ )
										{
											if( (*k).GetColour( ) == j )
												(*k).SetTeam( i );
										}
									}

									PlayerMask >>= 1;
								}

								getline( ISS, GarbageString, '\0' );	// team name
							}

							MapWidth = UTIL_CreateByteArray( (uint16_t)RawMapWidth, false );
							CONSOLE_Print( "[MAP] calculated map_width = " + UTIL_ToString( MapWidth[0] ) + " " + UTIL_ToString( MapWidth[1] ) );
							MapHeight = UTIL_CreateByteArray( (uint16_t)RawMapHeight, false );
							CONSOLE_Print( "[MAP] calculated map_height = " + UTIL_ToString( MapHeight[0] ) + " " + UTIL_ToString( MapHeight[1] ) );
							MapNumPlayers = RawMapNumPlayers - ClosedSlots;
							CONSOLE_Print( "[MAP] calculated map_numplayers = " + UTIL_ToString( MapNumPlayers ) );
							MapNumTeams = RawMapNumTeams;
							CONSOLE_Print( "[MAP] calculated map_numteams = " + UTIL_ToString( MapNumTeams ) );
							CONSOLE_Print( "[MAP] found " + UTIL_ToString( Slots.size( ) ) + " slots" );

							BYTEARRAY b;
							string s;
							int k=0;
							if (false && m_LogAll)
								for( vector<CGameSlot> :: iterator i = Slots.begin( ); i != Slots.end( ); i++ )
								{
									k++;
									b =(*i).GetByteArray( );
									s = "map_slot"+UTIL_ToString(k)+" = ";
									for( unsigned int j = 0; j < b.size( ); j++ )
									{
										s= s+ UTIL_ToString((int)b[j]);
										if (j<b.size()-1)
											s=s+" ";
									}
									CONSOLE_Print( "[MAP] calculated " + s );
								}

							/* for( vector<CGameSlot> :: iterator i = Slots.begin( ); i != Slots.end( ); i++ )
								DEBUG_Print( (*i).GetByteArray( ) ); */

							// if it's a melee map...

							if( RawMapFlags & 4 )
							{
								CONSOLE_Print( "[MAP] found melee map, initializing slots" );

								// give each slot a different team and set the race to random

								unsigned char Team = 0;

								for( vector<CGameSlot> :: iterator i = Slots.begin( ); i != Slots.end( ); i++ )
								{
									(*i).SetTeam( Team++ );
									(*i).SetRace( SLOTRACE_RANDOM );
								}
								MapFilterType = MAPFILTER_TYPE_MELEE;
							}
						}
					}
					else
						CONSOLE_Print( "[MAP] unable to calculate map_width, map_height, map_slot<x>, map_numplayers, map_numteams - unable to extract war3map.w3i from MPQ file" );

					delete [] SubFileData;
				}

				SFileCloseFile( SubFile );
			}
			else
				CONSOLE_Print( "[MAP] unable to calculate map_width, map_height, map_slot<x>, map_numplayers, map_numteams - couldn't find war3map.w3i in MPQ file" );
		}
		else
			CONSOLE_Print( "[MAP] unable to calculate map_width, map_height, map_slot<x>, map_numplayers, map_numteams - map MPQ file not loaded" );
	}
	else
		CONSOLE_Print( "[MAP] no map data available, using config file for map_width, map_height, map_slot<x>, map_numplayers, map_numteams" );

	// write config
	if (m_LogAll)
	{
		string s = string();
		string spad = string();
		string fmap = m_MapLocalPath.substr(0,m_MapLocalPath.length()-4);
		string File = m_GHost->m_MapCFGPath+ fmap + ".cfg";
		ofstream tmpcfg;
		tmpcfg.open( File.c_str( ), ios :: trunc );
		s = "# map file for " + m_MapLocalPath+" #";
		spad = spad.insert(0,s.length(),'#');
		tmpcfg << spad << endl;
		tmpcfg << s << endl;
		tmpcfg << spad << endl;
		tmpcfg << endl;
		tmpcfg << "# the map path tells Warcraft III clients where to find the map on their system" << endl;
		tmpcfg << "# it is NOT the path to the map on the GHost++ system, in fact GHost++ doesn't need the map at all" << endl;
		tmpcfg << endl;
		tmpcfg << "map_path = " << "Maps\\Download\\"+ m_MapLocalPath << endl;
		tmpcfg << "map_size = " << UTIL_ToString( MapSize[0] ) + " " + UTIL_ToString( MapSize[1] ) + " " + UTIL_ToString( MapSize[2] ) + " " + UTIL_ToString( MapSize[3] ) << endl;
		tmpcfg << "map_info = " << UTIL_ToString( MapInfo[0] ) + " " + UTIL_ToString( MapInfo[1] ) + " " + UTIL_ToString( MapInfo[2] ) + " " + UTIL_ToString( MapInfo[3] ) << endl;
		tmpcfg << "map_crc = " << UTIL_ToString( MapCRC[0] ) + " " + UTIL_ToString( MapCRC[1] ) + " " + UTIL_ToString( MapCRC[2] ) + " " + UTIL_ToString( MapCRC[3] ) << endl;
		tmpcfg << "map_sha1 = " << UTIL_ByteArrayToDecString( MapSHA1 ) << endl;
		tmpcfg << endl;
		tmpcfg << "# map speed" << endl;
		tmpcfg << "# 1 = slow" << endl;
		tmpcfg << "# 2 = normal" << endl;
		tmpcfg << "# 3 = fast" << endl;
		tmpcfg << endl;
		tmpcfg << "map_speed = " << "3" << endl;
		tmpcfg << endl;
		tmpcfg << "# map visibility" << endl;
		tmpcfg << "# 1 = hide terrain" << endl;
		tmpcfg << "# 2 = explored" << endl;
		tmpcfg << "# 3 = always visible" << endl;
		tmpcfg << "# 4 = default" << endl;
		tmpcfg << endl;
		tmpcfg << "map_visibility = " << "4" << endl;
		tmpcfg << endl;
		tmpcfg << "# map observers" << endl;
		tmpcfg << "# 1 = none" << endl;
		tmpcfg << "# 2 = on defeat" << endl;
		tmpcfg << "# 3 = allowed" << endl;
		tmpcfg << "# 4 = referees" << endl;
		tmpcfg << endl;
		tmpcfg << "map_observers = " << "1" << endl;
		tmpcfg << endl;
		tmpcfg << "# map flags" << endl;
		tmpcfg << "#  - you can combine these flags by adding together all the options you want to use" << endl;
		tmpcfg << "#  - for example to have teams together and fixed teams you would use \"3\"" << endl;
		tmpcfg << "# 1 = teams together" << endl;
		tmpcfg << "# 2 = fixed teams" << endl;
		tmpcfg << "# 4 = unit share" << endl;
		tmpcfg << "# 8 = random hero" << endl;
		tmpcfg << "# 16 = random races" << endl;
		tmpcfg << endl;
		tmpcfg << "map_flags = " << "3" << endl;
		tmpcfg << endl;
		tmpcfg << "# map game type" << endl;
		tmpcfg << "# 1 = custom" << endl;
		tmpcfg << endl;
		tmpcfg << "map_gametype = " << "1" << endl;
		tmpcfg << endl;
		tmpcfg << "# map dimensions" << endl;
		tmpcfg << endl;
		tmpcfg << "map_width = " << UTIL_ToString( MapWidth[0] ) + " " + UTIL_ToString( MapWidth[1] ) << endl;
		tmpcfg << "map_height = " << UTIL_ToString( MapHeight[0] ) + " " + UTIL_ToString( MapHeight[1] ) << endl;
		tmpcfg << endl;
		tmpcfg << "# map players and teams" << endl;
		tmpcfg << endl;
		tmpcfg << "map_numplayers = " << UTIL_ToString(MapNumPlayers) << endl;
		tmpcfg << "map_numteams = " << UTIL_ToString(MapNumTeams) << endl;
		tmpcfg << endl;
		tmpcfg << "# " << endl;
		tmpcfg << "# slot structure" << endl;
		tmpcfg << "#  [PID] [Download Status] [Slot Status] [Computer] [Team] [Colour] [Race] [Skill] [Handicap]" << endl;
		tmpcfg << "#  - PID is always 0" << endl;
		tmpcfg << "#  - Download Status is always 255" << endl;
		tmpcfg << "#  - Slot Status is 0 for open, 1 for closed, 2 for occupied" << endl;
		tmpcfg << "#  - Computer is 0 for no, 1 for yes" << endl;
		tmpcfg << "#  - Team" << endl;
		tmpcfg << "#  - Colour" << endl;
		tmpcfg << "#  - Race is 1 for human, 2 for orc, 4 for night elf, 8 for undead, 32 for random (add 64 to any of these for fixed)" << endl;
		tmpcfg << "#  - Skill is 0 for easy computer, 1 for normal computer or human, 2 for hard computer" << endl;
		tmpcfg << "#  - Handicap is 50/60/70/80/90/100" << endl;
		tmpcfg << "# " << endl;
		tmpcfg << endl;
		BYTEARRAY b;
		string ss;
		int k=0;
		for( vector<CGameSlot> :: iterator i = Slots.begin( ); i != Slots.end( ); i++ )
		{
			k++;
			b =(*i).GetByteArray( );
			ss = "map_slot"+UTIL_ToString(k)+" = ";
			for( unsigned int j = 0; j < b.size( ); j++ )
			{
				ss= ss+ UTIL_ToString((int)b[j]);
				if (j<b.size()-1)
					ss=ss+" ";
			}
			tmpcfg << ss << endl;
		}
		tmpcfg << endl;
		tmpcfg << "# map type (for map specific stats)" << endl;
		tmpcfg << endl;
		s = "map_type = ";
		bool dota = false;
		if (m_MapLocalPath.find("Allstars")!=string::npos)
			dota = true;
		if (dota)
			s = s + "dota";
		tmpcfg << s << endl;
		s = "map_matchmakingcategory = ";
		if (dota)
			s = s + "dota_elo";
		tmpcfg << s << endl;
		tmpcfg << "map_statsw3mmdcategory = " << endl;
		tmpcfg << endl;
		tmpcfg << "# map local path (for map downloads)" << endl;
		tmpcfg << "#  GHost++ doesn't require map files but if it has access to them it can send them to players" << endl;
		tmpcfg << "#  GHost++ will search bot_mappath + map_localpath for the map file (bot_mappath is set in the main config file)" << endl;
		tmpcfg << endl;
		tmpcfg << "map_localpath = " << m_MapLocalPath << endl;
		tmpcfg.close( );
		CONSOLE_Print( "[MAP] wrote config file " + fmap + ".cfg" );
	}

	// close the map MPQ

	if( MapMPQReady )
		SFileCloseArchive( MapMPQ );

	m_MapPath = CFG->GetString( "map_path", string( ) );

	if( MapSize.empty( ) )
		MapSize = UTIL_ExtractNumbers( CFG->GetString( "map_size", string( ) ), 4 );
	else if( CFG->Exists( "map_size" ) )
	{
		CONSOLE_Print( "[MAP] overriding calculated map_size with config value map_size = " + CFG->GetString( "map_size", string( ) ) );
		MapSize = UTIL_ExtractNumbers( CFG->GetString( "map_size", string( ) ), 4 );
	}

	m_MapSize = MapSize;

	if( MapInfo.empty( ) )
		MapInfo = UTIL_ExtractNumbers( CFG->GetString( "map_info", string( ) ), 4 );
	else if( CFG->Exists( "map_info" ) )
	{
		CONSOLE_Print( "[MAP] overriding calculated map_info with config value map_info = " + CFG->GetString( "map_info", string( ) ) );
		MapInfo = UTIL_ExtractNumbers( CFG->GetString( "map_info", string( ) ), 4 );
	}

	m_MapInfo = MapInfo;

	if( MapCRC.empty( ) )
		MapCRC = UTIL_ExtractNumbers( CFG->GetString( "map_crc", string( ) ), 4 );
	else if( CFG->Exists( "map_crc" ) )
	{
		CONSOLE_Print( "[MAP] overriding calculated map_crc with config value map_crc = " + CFG->GetString( "map_crc", string( ) ) );
		MapCRC = UTIL_ExtractNumbers( CFG->GetString( "map_crc", string( ) ), 4 );
	}

	m_MapCRC = MapCRC;

	if( MapSHA1.empty( ) )
		MapSHA1 = UTIL_ExtractNumbers( CFG->GetString( "map_sha1", string( ) ), 20 );
	else if( CFG->Exists( "map_sha1" ) )
	{
		CONSOLE_Print( "[MAP] overriding calculated map_sha1 with config value map_sha1 = " + CFG->GetString( "map_sha1", string( ) ) );
		MapSHA1 = UTIL_ExtractNumbers( CFG->GetString( "map_sha1", string( ) ), 20 );
	}

	m_MapSHA1 = MapSHA1;
	m_MapSpeed = CFG->GetInt( "map_speed", MAPSPEED_FAST );
	m_MapVisibility = CFG->GetInt( "map_visibility", MAPVIS_DEFAULT );
	m_MapObservers = CFG->GetInt( "map_observers", MAPOBS_NONE );
	m_MapFlags = CFG->GetInt( "map_flags", MAPFLAG_TEAMSTOGETHER | MAPFLAG_FIXEDTEAMS );
	if( CFG->Exists( "map_filter_type" ) )
	{
		CONSOLE_Print( "[MAP] overriding calculated map_filter_type with config value map_filter_type = " + CFG->GetString( "map_filter_type", string( ) ) );
		MapFilterType = CFG->GetInt( "map_filter_type", MAPFILTER_TYPE_SCENARIO );
	}		
	m_MapFilterType = MapFilterType;
	m_MapGameType = CFG->GetInt( "map_gametype", 1 );

	if( MapWidth.empty( ) )
		MapWidth = UTIL_ExtractNumbers( CFG->GetString( "map_width", string( ) ), 2 );
	else if( CFG->Exists( "map_width" ) )
	{
		CONSOLE_Print( "[MAP] overriding calculated map_width with config value map_width = " + CFG->GetString( "map_width", string( ) ) );
		MapWidth = UTIL_ExtractNumbers( CFG->GetString( "map_width", string( ) ), 2 );
	}

	m_MapWidth = MapWidth;

	if( MapHeight.empty( ) )
		MapHeight = UTIL_ExtractNumbers( CFG->GetString( "map_height", string( ) ), 2 );
	else if( CFG->Exists( "map_height" ) )
	{
		CONSOLE_Print( "[MAP] overriding calculated map_height with config value map_height = " + CFG->GetString( "map_height", string( ) ) );
		MapHeight = UTIL_ExtractNumbers( CFG->GetString( "map_height", string( ) ), 2 );
	}

	m_MapHeight = MapHeight;
	m_MapType = CFG->GetString( "map_type", string( ) );
	m_MapMatchMakingCategory = CFG->GetString( "map_matchmakingcategory", string( ) );
	m_MapStatsW3MMDCategory = CFG->GetString( "map_statsw3mmdcategory", string( ) );
	m_MapDefaultHCL = CFG->GetString( "map_defaulthcl", string( ) );
	m_MapDefaultPlayerScore = CFG->GetInt( "map_defaultplayerscore", 1000 );
	m_MapLoadInGame = CFG->GetInt( "map_loadingame", 0 ) == 0 ? false : true;
	if (m_GHost->m_ForceLoadInGame)
		m_MapLoadInGame = true;

	if( MapNumPlayers == 0 )
		MapNumPlayers = CFG->GetInt( "map_numplayers", 0 );
	else if( CFG->Exists( "map_numplayers" ) )
	{
		CONSOLE_Print( "[MAP] overriding calculated map_numplayers with config value map_numplayers = " + CFG->GetString( "map_numplayers", string( ) ) );
		MapNumPlayers = CFG->GetInt( "map_numplayers", 0 );
	}

	m_MapNumPlayers = MapNumPlayers;

	if( MapNumTeams == 0 )
		MapNumTeams = CFG->GetInt( "map_numteams", 0 );
	else if( CFG->Exists( "map_numteams" ) )
	{
		CONSOLE_Print( "[MAP] overriding calculated map_numteams with config value map_numteams = " + CFG->GetString( "map_numteams", string( ) ) );
		MapNumTeams = CFG->GetInt( "map_numteams", 0 );
	}

	m_MapNumTeams = MapNumTeams;

	m_MapOnlyAutoWarnIfMoreThanXPlayers = CFG->GetInt( "map_onlyautowarnifmorethanxplayers", 0 );

	m_AutoWarnMarks.push_back( 0 );
	string mapmarks = CFG->GetString("map_marks", "");
	char * marks = new char[mapmarks.length() + 1];
	strcpy(marks, mapmarks.c_str());
	uint32_t mark = 9999;
	while( mark != 0)
	{
		mark = strtoul(marks, &marks , 10);
		if(mark > 0)
			m_AutoWarnMarks.push_back( mark );
	}

	if( Slots.empty( ) )
	{
		for( uint32_t Slot = 1; Slot <= 12; Slot++ )
		{
			string SlotString = CFG->GetString( "map_slot" + UTIL_ToString( Slot ), string( ) );

			if( SlotString.empty( ) )
				break;

			BYTEARRAY SlotData = UTIL_ExtractNumbers( SlotString, 9 );
			Slots.push_back( CGameSlot( SlotData ) );
		}
	}
	else if( CFG->Exists( "map_slot1" ) )
	{
		CONSOLE_Print( "[MAP] overriding slots" );
		Slots.clear( );

		for( uint32_t Slot = 1; Slot <= 12; Slot++ )
		{
			string SlotString = CFG->GetString( "map_slot" + UTIL_ToString( Slot ), string( ) );

			if( SlotString.empty( ) )
				break;

			BYTEARRAY SlotData = UTIL_ExtractNumbers( SlotString, 9 );
			Slots.push_back( CGameSlot( SlotData ) );
		}
	}

	m_Slots = Slots;

	// if random races is set force every slot's race to random + fixed

	if( m_MapFlags & MAPFLAG_RANDOMRACES )
	{
		CONSOLE_Print( "[MAP] forcing races to random" );

		for( vector<CGameSlot> :: iterator i = m_Slots.begin( ); i != m_Slots.end( ); i++ )
			(*i).SetRace( SLOTRACE_RANDOM | SLOTRACE_FIXED );
	}

	// add observer slots

	if( m_MapObservers == MAPOBS_ALLOWED || m_MapObservers == MAPOBS_REFEREES )
	{
		CONSOLE_Print( "[MAP] adding " + UTIL_ToString( 12 - m_Slots.size( ) ) + " observer slots" );

		while( m_Slots.size( ) < 12 )
			m_Slots.push_back( CGameSlot( 0, 255, SLOTSTATUS_OPEN, 0, 12, 12, SLOTRACE_RANDOM ) );
	}

	CheckValid( );
}

void CMap :: CheckValid( )
{
	// todotodo: should this code fix any errors it sees rather than just warning the user?

	if( m_MapPath.empty( ) )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_path detected" );
	}
	else if( m_MapPath[0] == '\\' )
		CONSOLE_Print( "[MAP] warning - map_path starts with '\\', any replays saved by GHost++ will not be playable in Warcraft III" );

	if( m_MapPath.find( '/' ) != string :: npos )
		CONSOLE_Print( "[MAP] warning - map_path contains forward slashes '/' but it must use Windows style back slashes '\\'" );

	if( m_MapSize.size( ) != 4 )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_size detected" );
	}
	else if( !m_MapData.empty( ) && m_MapData.size( ) != UTIL_ByteArrayToUInt32( m_MapSize, false ) )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_size detected - size mismatch with actual map data" );
	}

	if( m_MapInfo.size( ) != 4 )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_info detected" );
	}

	if( m_MapCRC.size( ) != 4 )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_crc detected" );
	}

	if( m_MapSHA1.size( ) != 20 )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_sha1 detected" );
	}

	if( m_MapSpeed != MAPSPEED_SLOW && m_MapSpeed != MAPSPEED_NORMAL && m_MapSpeed != MAPSPEED_FAST )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_speed detected" );
	}

	if( m_MapVisibility != MAPVIS_HIDETERRAIN && m_MapVisibility != MAPVIS_EXPLORED && m_MapVisibility != MAPVIS_ALWAYSVISIBLE && m_MapVisibility != MAPVIS_DEFAULT )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_visibility detected" );
	}

	if( m_MapObservers != MAPOBS_NONE && m_MapObservers != MAPOBS_ONDEFEAT && m_MapObservers != MAPOBS_ALLOWED && m_MapObservers != MAPOBS_REFEREES )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_observers detected" );
	}

	// todotodo: m_MapFlags

	if( m_MapGameType != 1 && m_MapGameType != 2 && m_MapGameType != 9 )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_gametype detected" );
	}

	if( m_MapWidth.size( ) != 2 )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_width detected" );
	}

	if( m_MapHeight.size( ) != 2 )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_height detected" );
	}

	if( m_MapNumPlayers == 0 || m_MapNumPlayers > 12 )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_numplayers detected" );
	}

	if( m_MapNumTeams == 0 || m_MapNumTeams > 12 )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_numteams detected" );
	}

	if( m_Slots.empty( ) || m_Slots.size( ) > 12 )
	{
		m_Valid = false;
		CONSOLE_Print( "[MAP] invalid map_slot<x> detected" );
	}
}

uint32_t CMap :: XORRotateLeft( unsigned char *data, uint32_t length )
{
	// a big thank you to Strilanc for figuring this out

	uint32_t i = 0;
	uint32_t Val = 0;

	if( length > 3 )
	{
		while( i < length - 3 )
		{
			Val = ROTL( Val ^ ( (uint32_t)data[i] + (uint32_t)( data[i + 1] << 8 ) + (uint32_t)( data[i + 2] << 16 ) + (uint32_t)( data[i + 3] << 24 ) ), 3 );
			i += 4;
		}
	}

	while( i < length )
	{
		Val = ROTL( Val ^ data[i], 3 );
		i++;
	}

	return Val;
}
