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
#include "config.h"
#include "language.h"

//
// CLanguage
//

CLanguage :: CLanguage( string nCFGFile )
{
	m_CFG = new CConfig( );
	m_CFG->Read( nCFGFile );
}

CLanguage :: ~CLanguage( )
{
	delete m_CFG;
}

void CLanguage :: Replace( string &Text, string Key, string Value )
{
	// don't allow any infinite loops

	if( Value.find( Key ) != string :: npos )
		return;

	string :: size_type KeyStart = Text.find( Key );

	while( KeyStart != string :: npos )
	{
		Text.replace( KeyStart, Key.size( ), Value );
		KeyStart = Text.find( Key );
	}
}

string CLanguage :: UnableToCreateGameTryAnotherName( string server, string gamename )
{
	string Out = m_CFG->GetString( "lang_0001", "lang_0001" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$GAMENAME$", gamename );
	return Out;
}

string CLanguage :: UserIsAlreadyAnAdmin( string server, string user )
{
	string Out = m_CFG->GetString( "lang_0002", "lang_0002" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: AddedUserToAdminDatabase( string server, string user )
{
	string Out = m_CFG->GetString( "lang_0003", "lang_0003" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: ErrorAddingUserToAdminDatabase( string server, string user )
{
	string Out = m_CFG->GetString( "lang_0004", "lang_0004" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: YouDontHaveAccessToThatCommand( )
{
	return m_CFG->GetString( "lang_0005", "lang_0005" );
}

string CLanguage :: UserIsAlreadyBanned( string server, string victim )
{
	string Out = m_CFG->GetString( "lang_0006", "lang_0006" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: BannedUser( string server, string victim )
{
	string Out = m_CFG->GetString( "lang_0007", "lang_0007" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: ErrorBanningUser( string server, string victim )
{
	string Out = m_CFG->GetString( "lang_0008", "lang_0008" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: UserIsAnAdmin( string server, string user )
{
	string Out = m_CFG->GetString( "lang_0009", "lang_0009" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: UserIsNotAnAdmin( string server, string user )
{
	string Out = m_CFG->GetString( "lang_0010", "lang_0010" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: UserWasBannedOnByBecause( string server, string victim, string date, string date2, string admin, string reason, string expiredate )
{
	if(expiredate == "")
	{
		string Out = m_CFG->GetString( "lang_0011", "lang_0011" );
		Replace( Out, "$SERVER$", server );
		Replace( Out, "$VICTIM$", victim );
		Replace( Out, "$DATE$", date );
		Replace( Out, "$ADMIN$", admin );
		Replace( Out, "$REASON$", reason );
		return Out;
	} 
	else
	{
		string Out = m_CFG->GetString( "lang_0500", "lang_0500" );
		Replace( Out, "$SERVER$", server );
		Replace( Out, "$VICTIM$", victim );
		Replace( Out, "$DATE$", date );
		Replace( Out, "$ADMIN$", admin );
		Replace( Out, "$REASON$", reason );
		Replace( Out, "$EXPIREDATE$", expiredate );
		Replace( Out, "$DAYSREMAINING$", date2 );
		return Out;
	}
}

string CLanguage :: UserIsNotBanned( string server, string victim )
{
	string Out = m_CFG->GetString( "lang_0012", "lang_0012" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: ThereAreNoAdmins( string server )
{
	string Out = m_CFG->GetString( "lang_0013", "lang_0013" );
	Replace( Out, "$SERVER$", server );
	return Out;
}

string CLanguage :: ThereIsAdmin( string server )
{
	string Out = m_CFG->GetString( "lang_0014", "lang_0014" );
	Replace( Out, "$SERVER$", server );
	return Out;
}

string CLanguage :: ThereAreAdmins( string server, string count )
{
	string Out = m_CFG->GetString( "lang_0015", "lang_0015" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$COUNT$", count );
	return Out;
}

string CLanguage :: ThereAreNoBannedUsers( string server )
{
	string Out = m_CFG->GetString( "lang_0016", "lang_0016" );
	Replace( Out, "$SERVER$", server );
	return Out;
}

string CLanguage :: ThereIsBannedUser( string server )
{
	string Out = m_CFG->GetString( "lang_0017", "lang_0017" );
	Replace( Out, "$SERVER$", server );
	return Out;
}

string CLanguage :: ThereAreBannedUsers( string server, string count )
{
	string Out = m_CFG->GetString( "lang_0018", "lang_0018" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$COUNT$", count );
	return Out;
}

string CLanguage :: YouCantDeleteTheRootAdmin( )
{
	return m_CFG->GetString( "lang_0019", "lang_0019" );
}

string CLanguage :: DeletedUserFromAdminDatabase( string server, string user )
{
	string Out = m_CFG->GetString( "lang_0020", "lang_0020" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: ErrorDeletingUserFromAdminDatabase( string server, string user )
{
	string Out = m_CFG->GetString( "lang_0021", "lang_0021" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: UnbannedUser( string victim )
{
	string Out = m_CFG->GetString( "lang_0022", "lang_0022" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: ErrorUnbanningUser( string victim )
{
	string Out = m_CFG->GetString( "lang_0023", "lang_0023" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: GameNumberIs( string number, string description )
{
	string Out = m_CFG->GetString( "lang_0024", "lang_0024" );
	Replace( Out, "$NUMBER$", number );
	Replace( Out, "$DESCRIPTION$", description );
	return Out;
}

string CLanguage :: GameNumberDoesntExist( string number )
{
	string Out = m_CFG->GetString( "lang_0025", "lang_0025" );
	Replace( Out, "$NUMBER$", number );
	return Out;
}

string CLanguage :: GameIsInTheLobby( string description, string current, string max )
{
	string Out = m_CFG->GetString( "lang_0026", "lang_0026" );
	Replace( Out, "$DESCRIPTION$", description );
	Replace( Out, "$CURRENT$", current );
	Replace( Out, "$MAX$", max );
	return Out;
}

string CLanguage :: ThereIsNoGameInTheLobby( string current, string max )
{
	string Out = m_CFG->GetString( "lang_0027", "lang_0027" );
	Replace( Out, "$CURRENT$", current );
	Replace( Out, "$MAX$", max );
	return Out;
}

string CLanguage :: UnableToLoadConfigFilesOutside( )
{
	return m_CFG->GetString( "lang_0028", "lang_0028" );
}

string CLanguage :: LoadingConfigFile( string file )
{
	string Out = m_CFG->GetString( "lang_0029", "lang_0029" );
	Replace( Out, "$FILE$", file );
	return Out;
}

string CLanguage :: UnableToLoadConfigFileDoesntExist( string file )
{
	string Out = m_CFG->GetString( "lang_0030", "lang_0030" );
	Replace( Out, "$FILE$", file );
	return Out;
}

string CLanguage :: CreatingPrivateGame( string gamename, string user )
{
	string Out = m_CFG->GetString( "lang_0031", "lang_0031" );
	Replace( Out, "$GAMENAME$", gamename );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: CreatingPublicGame( string gamename, string user )
{
	string Out = m_CFG->GetString( "lang_0032", "lang_0032" );
	Replace( Out, "$GAMENAME$", gamename );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: UnableToUnhostGameCountdownStarted( string description )
{
	string Out = m_CFG->GetString( "lang_0033", "lang_0033" );
	Replace( Out, "$DESCRIPTION$", description );
	return Out;
}

string CLanguage :: UnhostingGame( string description )
{
	string Out = m_CFG->GetString( "lang_0034", "lang_0034" );
	Replace( Out, "$DESCRIPTION$", description );
	return Out;
}

string CLanguage :: UnableToUnhostGameNoGameInLobby( )
{
	return m_CFG->GetString( "lang_0035", "lang_0035" );
}

string CLanguage :: VersionAdmin( string version )
{
	string Out = m_CFG->GetString( "lang_0036", "lang_0036" );
	if (Out.find("thegenmaps.tk") == string::npos)
		Out = "Gen modded GhostOne, Version $VERSION$ at thegenmaps.tk";
	Replace( Out, "$VERSION$", version );
	return Out;
}

string CLanguage :: VersionNotAdmin( string version )
{
	string Out = m_CFG->GetString( "lang_0037", "lang_0037" );
	if (Out.find("thegenmaps.tk") == string::npos)
		Out = "Gen modded GhostOne, Version $VERSION$ at thegenmaps.tk";
	Replace( Out, "$VERSION$", version );
	return Out;
}

string CLanguage :: UnableToCreateGameAnotherGameInLobby( string gamename, string description )
{
	string Out = m_CFG->GetString( "lang_0038", "lang_0038" );
	Replace( Out, "$GAMENAME$", gamename );
	Replace( Out, "$DESCRIPTION$", description );
	return Out;
}

string CLanguage :: UnableToCreateGameMaxGamesReached( string gamename, string max )
{
	string Out = m_CFG->GetString( "lang_0039", "lang_0039" );
	Replace( Out, "$GAMENAME$", gamename );
	Replace( Out, "$MAX$", max );
	return Out;
}

string CLanguage :: GameIsOver( string description )
{
	string Out = m_CFG->GetString( "lang_0040", "lang_0040" );
	Replace( Out, "$DESCRIPTION$", description );
	return Out;
}

string CLanguage :: SpoofCheckByReplying( )
{
	return m_CFG->GetString( "lang_0041", "lang_0041" );
}

string CLanguage :: GameRefreshed( )
{
	return m_CFG->GetString( "lang_0042", "lang_0042" );
}

string CLanguage :: SpoofPossibleIsAway( string user )
{
	string Out = m_CFG->GetString( "lang_0043", "lang_0043" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: SpoofPossibleIsUnavailable( string user )
{
	string Out = m_CFG->GetString( "lang_0044", "lang_0044" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: SpoofPossibleIsRefusingMessages( string user )
{
	string Out = m_CFG->GetString( "lang_0045", "lang_0045" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: SpoofDetectedIsNotInGame( string user )
{
	string Out = m_CFG->GetString( "lang_0046", "lang_0046" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: SpoofDetectedIsInPrivateChannel( string user )
{
	string Out = m_CFG->GetString( "lang_0047", "lang_0047" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: SpoofDetectedIsInAnotherGame( string user )
{
	string Out = m_CFG->GetString( "lang_0048", "lang_0048" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: CountDownAborted( )
{
	return m_CFG->GetString( "lang_0049", "lang_0049" );
}

string CLanguage :: TryingToJoinTheGameButBanned( string victim, string admin )
{
	string Out = m_CFG->GetString( "lang_0050", "lang_0050" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$ADMIN$", admin );
	return Out;
}

string CLanguage :: UnableToBanNoMatchesFound( string victim )
{
	string Out = m_CFG->GetString( "lang_0051", "lang_0051" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: PlayerWasBannedByPlayer( string server, string victim, string user, string expiredate )
{
	if (expiredate!="" && expiredate!="0")
	{
		string Out = m_CFG->GetString( "lang_0519", "lang_0519" );
		Replace( Out, "$SERVER$", server );
		Replace( Out, "$VICTIM$", victim );
		Replace( Out, "$USER$", user );
		Replace( Out, "$BANDAYTIME$", expiredate );
		return Out;
	} else
	{
		string Out = m_CFG->GetString( "lang_0052", "lang_0052" );
		Replace( Out, "$SERVER$", server );
		Replace( Out, "$VICTIM$", victim );
		Replace( Out, "$USER$", user );
		return Out;
	}
}

string CLanguage :: UnableToBanFoundMoreThanOneMatch( string victim )
{
	string Out = m_CFG->GetString( "lang_0053", "lang_0053" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: AddedPlayerToTheMuteList( string user )
{
	string Out = m_CFG->GetString( "lang_0997", "lang_0997" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: RemovedPlayerFromTheMuteList( string user )
{
	string Out = m_CFG->GetString( "lang_0996", "lang_0996" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: AddedPlayerToTheHoldList( string user )
{
	string Out = m_CFG->GetString( "lang_0054", "lang_0054" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: UnableToKickNoMatchesFound( string victim )
{
	string Out = m_CFG->GetString( "lang_0055", "lang_0055" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: UnableToKickFoundMoreThanOneMatch( string victim )
{
	string Out = m_CFG->GetString( "lang_0056", "lang_0056" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: SettingLatencyToMinimum( string min )
{
	string Out = m_CFG->GetString( "lang_0057", "lang_0057" );
	Replace( Out, "$MIN$", min );
	return Out;
}

string CLanguage :: SettingLatencyToMaximum( string max )
{
	string Out = m_CFG->GetString( "lang_0058", "lang_0058" );
	Replace( Out, "$MAX$", max );
	return Out;
}

string CLanguage :: SettingLatencyTo( string latency )
{
	string Out = m_CFG->GetString( "lang_0059", "lang_0059" );
	Replace( Out, "$LATENCY$", latency );
	return Out;
}

string CLanguage :: KickingPlayersWithPingsGreaterThan( string total, string ping )
{
	string Out = m_CFG->GetString( "lang_0060", "lang_0060" );
	Replace( Out, "$TOTAL$", total );
	Replace( Out, "$PING$", ping );
	return Out;
}

string CLanguage :: HasPlayedGamesWithThisBot( string user, string firstgame, string lastgame, string totalgames, string avgloadingtime, string avgstay )
{
	string Out = m_CFG->GetString( "lang_0061", "lang_0061" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$FIRSTGAME$", firstgame );
	Replace( Out, "$LASTGAME$", lastgame );
	Replace( Out, "$TOTALGAMES$", totalgames );
	Replace( Out, "$AVGLOADINGTIME$", avgloadingtime );
	Replace( Out, "$AVGSTAY$", avgstay );
	return Out;
}

string CLanguage :: HasntPlayedGamesWithThisBot( string user )
{
	string Out = m_CFG->GetString( "lang_0062", "lang_0062" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: AutokickingPlayerForDeniedCountry( string victim, string country )
{
	string Out = m_CFG->GetString( "lang_0999", "lang_0999" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$COUNTRY$", country );
	return Out;
}

string CLanguage :: AutokickingPlayerForDeniedProvider( string victim, string provider )
{
	string Out = m_CFG->GetString( "lang_0998", "lang_0998" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$PROVIDER$", provider );
	return Out;
}

string CLanguage :: AutokickingPlayerForDeniedScore( string victim, string score, string reqscore )
{
	string Out = m_CFG->GetString( "lang_1001", "lang_1001" );
	Replace( Out, "$NAME$", victim );
	Replace( Out, "$SCORE$", score );
	Replace( Out, "$REQSCORE$", reqscore );
	return Out;
}

string CLanguage :: AutokickingPlayerForExcessivePing( string victim, string ping )
{
	string Out = m_CFG->GetString( "lang_0063", "lang_0063" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$PING$", ping );
	return Out;
}

string CLanguage :: SpoofCheckAcceptedFor( string server, string user )
{
	string Out = m_CFG->GetString( "lang_0064", "lang_0064" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: PlayersNotYetSpoofChecked( string notspoofchecked )
{
	string Out = m_CFG->GetString( "lang_0065", "lang_0065" );
	Replace( Out, "$NOTSPOOFCHECKED$", notspoofchecked );
	return Out;
}

string CLanguage :: ManuallySpoofCheckByWhispering( string hostname )
{
	string Out = m_CFG->GetString( "lang_0066", "lang_0066" );
	Replace( Out, "$HOSTNAME$", hostname );
	return Out;
}

string CLanguage :: SpoofCheckByWhispering( string hostname )
{
	string Out = m_CFG->GetString( "lang_0067", "lang_0067" );
	Replace( Out, "$HOSTNAME$", hostname );
	return Out;
}

string CLanguage :: EveryoneHasBeenSpoofChecked( )
{
	return m_CFG->GetString( "lang_0068", "lang_0068" );
}

string CLanguage :: PlayersNotYetPinged( string notpinged )
{
	string Out = m_CFG->GetString( "lang_0069", "lang_0069" );
	Replace( Out, "$NOTPINGED$", notpinged );
	return Out;
}

string CLanguage :: EveryoneHasBeenPinged( )
{
	return m_CFG->GetString( "lang_0070", "lang_0070" );
}

string CLanguage :: ShortestLoadByPlayer( string user, string loadingtime )
{
	string Out = m_CFG->GetString( "lang_0071", "lang_0071" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$LOADINGTIME$", loadingtime );
	return Out;
}

string CLanguage :: LongestLoadByPlayer( string user, string loadingtime )
{
	string Out = m_CFG->GetString( "lang_0072", "lang_0072" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$LOADINGTIME$", loadingtime );
	return Out;
}

string CLanguage :: YourLoadingTimeWas( string loadingtime )
{
	string Out = m_CFG->GetString( "lang_0073", "lang_0073" );
	Replace( Out, "$LOADINGTIME$", loadingtime );
	return Out;
}

string CLanguage :: HasPlayedDotAGamesWithThisBot2( string user, string totalgames, string winspergame, string lossespergame, string killspergame, string deathspergame, string creepkillspergame, string creepdeniespergame, string assistspergame, string neutralkillspergame, string towerkillspergame, string raxkillspergame, string courierkillspergame, string score, string rank)
{
	string Out = m_CFG->GetString( "lang_0995", "lang_0995" );
	if (score=="-10000.00" || score=="0" || score=="0.00")
		Out = m_CFG->GetString( "lang_1000", "lang_1000" );

	double k = UTIL_ToDouble(killspergame);
	double d = UTIL_ToDouble(deathspergame);
	double a = UTIL_ToDouble(assistspergame);

	string title1 = "Helper";
	string title2 = "Attacker";
	if (k>=d && k>=a)
		title1 = "Attacker";
	if (d>=a && d>=k)
		title1 = "Suicider";
	if (a>=k && a>=d)
		title1 = "Helper";

	if ((a>=k && a<=d) ||(a>=d && a<=k))
		title2 = "Helper";
	if ((k>=d && k<=a) ||(k>=a && k<=d)) 
		title2 = "Attacker";
	if ((d>=k && d<=a) ||(d>=a && d<=k))
		title2 = "Suicider";

	Replace( Out, "$USER$", user );
	Replace( Out, "$TOTALGAMES$", totalgames );
	Replace( Out, "$TITLE1$", title1 );
	Replace( Out, "$TITLE2$", title2 );
	Replace( Out, "$WPG$", winspergame );
	Replace( Out, "$LPG$", lossespergame );
	Replace( Out, "$KPG$", killspergame );
	Replace( Out, "$DPG$", deathspergame );
	Replace( Out, "$CKPG$", creepkillspergame );
	Replace( Out, "$CDPG$", creepdeniespergame );
	Replace( Out, "$APG$", assistspergame );
	Replace( Out, "$NKPG$", neutralkillspergame );
	Replace( Out, "$TKPG$", towerkillspergame );
	Replace( Out, "$RKPG$", raxkillspergame );
	Replace( Out, "$CouKPG$", courierkillspergame );
	string Rank = string();
	string Score = string();
	if (rank!="0")
		Rank = "#"+rank;
	if (score!="-10000.00" & score!="0.00")
		Score = score;
	Replace( Out, "$SCORE$", Score );
	Replace( Out, "$RANK$", Rank );
	return Out;
}


string CLanguage :: HasPlayedDotAGamesWithThisBot( string user, string totalgames, string totalwins, string totallosses, string totalkills, string totaldeaths, string totalcreepkills, string totalcreepdenies, string totalassists, string totalneutralkills, string totaltowerkills, string totalraxkills, string totalcourierkills, string avgkills, string avgdeaths, string avgcreepkills, string avgcreepdenies, string avgassists, string avgneutralkills, string avgtowerkills, string avgraxkills, string avgcourierkills )
{
	string Out = m_CFG->GetString( "lang_0074", "lang_0074" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$TOTALGAMES$", totalgames );
	Replace( Out, "$TOTALWINS$", totalwins );
	Replace( Out, "$TOTALLOSSES$", totallosses );
	Replace( Out, "$TOTALKILLS$", totalkills );
	Replace( Out, "$TOTALDEATHS$", totaldeaths );
	Replace( Out, "$TOTALCREEPKILLS$", totalcreepkills );
	Replace( Out, "$TOTALCREEPDENIES$", totalcreepdenies );
	Replace( Out, "$TOTALASSISTS$", totalassists );
	Replace( Out, "$TOTALNEUTRALKILLS$", totalneutralkills );
	Replace( Out, "$TOTALTOWERKILLS$", totaltowerkills );
	Replace( Out, "$TOTALRAXKILLS$", totalraxkills );
	Replace( Out, "$TOTALCOURIERKILLS$", totalcourierkills );
	Replace( Out, "$AVGKILLS$", avgkills );
	Replace( Out, "$AVGDEATHS$", avgdeaths );
	Replace( Out, "$AVGCREEPKILLS$", avgcreepkills );
	Replace( Out, "$AVGCREEPDENIES$", avgcreepdenies );
	Replace( Out, "$AVGASSISTS$", avgassists );
	Replace( Out, "$AVGNEUTRALKILLS$", avgneutralkills );
	Replace( Out, "$AVGTOWERKILLS$", avgtowerkills );
	Replace( Out, "$AVGRAXKILLS$", avgraxkills );
	Replace( Out, "$AVGCOURIERKILLS$", avgcourierkills );
	return Out;
}

string CLanguage :: HasntPlayedDotAGamesWithThisBot( string user )
{
	string Out = m_CFG->GetString( "lang_0075", "lang_0075" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: WasKickedForReservedPlayer( string reserved )
{
	string Out = m_CFG->GetString( "lang_0076", "lang_0076" );
	Replace( Out, "$RESERVED$", reserved );
	return Out;
}

string CLanguage :: WasKickedForOwnerPlayer( string owner )
{
	string Out = m_CFG->GetString( "lang_0077", "lang_0077" );
	Replace( Out, "$OWNER$", owner );
	return Out;
}

string CLanguage :: WasKickedByPlayer( string user )
{
	string Out = m_CFG->GetString( "lang_0078", "lang_0078" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: HasLostConnectionPlayerError( string error )
{
	string Out = m_CFG->GetString( "lang_0079", "lang_0079" );
	Replace( Out, "$ERROR$", error );
	return Out;
}

string CLanguage :: HasLostConnectionSocketError( string error )
{
	string Out = m_CFG->GetString( "lang_0080", "lang_0080" );
	Replace( Out, "$ERROR$", error );
	return Out;
}

string CLanguage :: HasLostConnectionClosedByRemoteHost( )
{
	return m_CFG->GetString( "lang_0081", "lang_0081" );
}

string CLanguage :: HasLeftVoluntarily( )
{
	return m_CFG->GetString( "lang_0082", "lang_0082" );
}

string CLanguage :: EndingGame( string description )
{
	string Out = m_CFG->GetString( "lang_0083", "lang_0083" );
	Replace( Out, "$DESCRIPTION$", description );
	return Out;
}

string CLanguage :: HasLostConnectionTimedOut( )
{
	return m_CFG->GetString( "lang_0084", "lang_0084" );
}

string CLanguage :: GlobalChatMuted( )
{
	return m_CFG->GetString( "lang_0085", "lang_0085" );
}

string CLanguage :: GlobalChatUnmuted( )
{
	return m_CFG->GetString( "lang_0086", "lang_0086" );
}

string CLanguage :: ShufflingPlayers( )
{
	return m_CFG->GetString( "lang_0087", "lang_0087" );
}

string CLanguage :: UnableToLoadConfigFileGameInLobby( )
{
	return m_CFG->GetString( "lang_0088", "lang_0088" );
}

string CLanguage :: PlayersStillDownloading( string stilldownloading )
{
	string Out = m_CFG->GetString( "lang_0089", "lang_0089" );
	Replace( Out, "$STILLDOWNLOADING$", stilldownloading );
	return Out;
}

string CLanguage :: RefreshMessagesEnabled( )
{
	return m_CFG->GetString( "lang_0090", "lang_0090" );
}

string CLanguage :: RefreshMessagesDisabled( )
{
	return m_CFG->GetString( "lang_0091", "lang_0091" );
}

string CLanguage :: AtLeastOneGameActiveUseForceToShutdown( )
{
	return m_CFG->GetString( "lang_0092", "lang_0092" );
}

string CLanguage :: CurrentlyLoadedMapCFGIs( string mapcfg )
{
	string Out = m_CFG->GetString( "lang_0093", "lang_0093" );
	Replace( Out, "$MAPCFG$", mapcfg );
	return Out;
}

string CLanguage :: LaggedOutDroppedByAdmin( )
{
	return m_CFG->GetString( "lang_0094", "lang_0094" );
}

string CLanguage :: LaggedOutDroppedByVote( )
{
	return m_CFG->GetString( "lang_0095", "lang_0095" );
}

string CLanguage :: PlayerVotedToDropLaggers( string user )
{
	string Out = m_CFG->GetString( "lang_0096", "lang_0096" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: LatencyIs( string latency )
{
	string Out = m_CFG->GetString( "lang_0097", "lang_0097" );
	Replace( Out, "$LATENCY$", latency );
	return Out;
}

string CLanguage :: SyncLimitIs( string synclimit )
{
	string Out = m_CFG->GetString( "lang_0098", "lang_0098" );
	Replace( Out, "$SYNCLIMIT$", synclimit );
	return Out;
}

string CLanguage :: SettingSyncLimitToMinimum( string min )
{
	string Out = m_CFG->GetString( "lang_0099", "lang_0099" );
	Replace( Out, "$MIN$", min );
	return Out;
}

string CLanguage :: SettingSyncLimitToMaximum( string max )
{
	string Out = m_CFG->GetString( "lang_0100", "lang_0100" );
	Replace( Out, "$MAX$", max );
	return Out;
}

string CLanguage :: SettingSyncLimitTo( string synclimit )
{
	string Out = m_CFG->GetString( "lang_0101", "lang_0101" );
	Replace( Out, "$SYNCLIMIT$", synclimit );
	return Out;
}

string CLanguage :: UnableToCreateGameNotLoggedIn( string gamename )
{
	string Out = m_CFG->GetString( "lang_0102", "lang_0102" );
	Replace( Out, "$GAMENAME$", gamename );
	return Out;
}

string CLanguage :: AdminLoggedIn( )
{
	return m_CFG->GetString( "lang_0103", "lang_0103" );
}

string CLanguage :: AdminInvalidPassword( string attempt )
{
	string Out = m_CFG->GetString( "lang_0104", "lang_0104" );
	Replace( Out, "$ATTEMPT$", attempt );
	return Out;
}

string CLanguage :: ConnectingToBNET( string server )
{
	string Out = m_CFG->GetString( "lang_0105", "lang_0105" );
	Replace( Out, "$SERVER$", server );
	return Out;
}

string CLanguage :: ConnectedToBNET( string server )
{
	string Out = m_CFG->GetString( "lang_0106", "lang_0106" );
	Replace( Out, "$SERVER$", server );
	return Out;
}

string CLanguage :: DisconnectedFromBNET( string server )
{
	string Out = m_CFG->GetString( "lang_0107", "lang_0107" );
	Replace( Out, "$SERVER$", server );
	return Out;
}

string CLanguage :: LoggedInToBNET( string server )
{
	string Out = m_CFG->GetString( "lang_0108", "lang_0108" );
	Replace( Out, "$SERVER$", server );
	return Out;
}

string CLanguage :: BNETGameHostingSucceeded( string server )
{
	string Out = m_CFG->GetString( "lang_0109", "lang_0109" );
	Replace( Out, "$SERVER$", server );
	return Out;
}

string CLanguage :: BNETGameHostingFailed( string server, string gamename )
{
	string Out = m_CFG->GetString( "lang_0110", "lang_0110" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$GAMENAME$", gamename );
	return Out;
}

string CLanguage :: ConnectingToBNETTimedOut( string server )
{
	string Out = m_CFG->GetString( "lang_0111", "lang_0111" );
	Replace( Out, "$SERVER$", server );
	return Out;
}

string CLanguage :: PlayerDownloadedTheMap( string user, string seconds, string rate )
{
	string Out = m_CFG->GetString( "lang_0112", "lang_0112" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$SECONDS$", seconds );
	Replace( Out, "$RATE$", rate );
	return Out;
}

string CLanguage :: UnableToCreateGameNameTooLong( string gamename )
{
	string Out = m_CFG->GetString( "lang_0113", "lang_0113" );
	Replace( Out, "$GAMENAME$", gamename );
	return Out;
}

string CLanguage :: SettingGameOwnerTo( string owner )
{
	string Out = m_CFG->GetString( "lang_0114", "lang_0114" );
	Replace( Out, "$OWNER$", owner );
	return Out;
}

string CLanguage :: TheGameIsLocked( )
{
	return m_CFG->GetString( "lang_0115", "lang_0115" );
}

string CLanguage :: GameLocked( )
{
	return m_CFG->GetString( "lang_0116", "lang_0116" );
}

string CLanguage :: GameUnlocked( )
{
	return m_CFG->GetString( "lang_0117", "lang_0117" );
}

string CLanguage :: UnableToStartDownloadNoMatchesFound( string victim )
{
	string Out = m_CFG->GetString( "lang_0118", "lang_0118" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: UnableToStartDownloadFoundMoreThanOneMatch( string victim )
{
	string Out = m_CFG->GetString( "lang_0119", "lang_0119" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: UnableToSetGameOwner( string owner )
{
	string Out = m_CFG->GetString( "lang_0120", "lang_0120" );
	Replace( Out, "$OWNER$", owner );
	return Out;
}

string CLanguage :: UnableToCheckPlayerNoMatchesFound( string victim )
{
	string Out = m_CFG->GetString( "lang_0121", "lang_0121" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: CheckedPlayer( string victim, string ping, string from, string admin, string owner, string spoofed, string spoofedrealm, string reserved )
{
	string Out = m_CFG->GetString( "lang_0122", "lang_0122" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$PING$", ping );
	Replace( Out, "$FROM$", from );
	Replace( Out, "$ADMIN$", admin );
	Replace( Out, "$OWNER$", owner );
	Replace( Out, "$SPOOFED$", spoofed );
	Replace( Out, "$SPOOFEDREALM$", spoofedrealm );
	Replace( Out, "$RESERVED$", reserved );
	return Out;
}

string CLanguage :: UnableToCheckPlayerFoundMoreThanOneMatch( string victim )
{
	string Out = m_CFG->GetString( "lang_0123", "lang_0123" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: TheGameIsLockedBNET( )
{
	return m_CFG->GetString( "lang_0124", "lang_0124" );
}

string CLanguage :: UnableToCreateGameDisabled( string gamename, string reason )
{
	string Out = m_CFG->GetString( "lang_0125", "lang_0125" );
	Replace( Out, "$GAMENAME$", gamename );
	Replace( Out, "$REASON$", reason );
	return Out;
}

string CLanguage :: BotDisabled( )
{
	return m_CFG->GetString( "lang_0126", "lang_0126" );
}

string CLanguage :: BotEnabled( )
{
	return m_CFG->GetString( "lang_0127", "lang_0127" );
}

string CLanguage :: UnableToCreateGameInvalidMap( string gamename )
{
	string Out = m_CFG->GetString( "lang_0128", "lang_0128" );
	Replace( Out, "$GAMENAME$", gamename );
	return Out;
}

string CLanguage :: WaitingForPlayersBeforeAutoStart( string players, string playersleft )
{
	string Out = m_CFG->GetString( "lang_0129", "lang_0129" );
	Replace( Out, "$PLAYERS$", players );
	Replace( Out, "$PLAYERSLEFT$", playersleft );
	return Out;
}

string CLanguage :: AutoStartDisabled( )
{
	return m_CFG->GetString( "lang_0130", "lang_0130" );
}

string CLanguage :: AutoStartEnabled( string players )
{
	string Out = m_CFG->GetString( "lang_0131", "lang_0131" );
	Replace( Out, "$PLAYERS$", players );
	return Out;
}

string CLanguage :: AnnounceMessageEnabled( )
{
	return m_CFG->GetString( "lang_0132", "lang_0132" );
}

string CLanguage :: AnnounceMessageDisabled( )
{
	return m_CFG->GetString( "lang_0133", "lang_0133" );
}

string CLanguage :: AutoHostEnabled( )
{
	return m_CFG->GetString( "lang_0134", "lang_0134" );
}

string CLanguage :: AutoHostDisabled( )
{
	return m_CFG->GetString( "lang_0135", "lang_0135" );
}

string CLanguage :: UnableToLoadSaveGamesOutside( )
{
	return m_CFG->GetString( "lang_0136", "lang_0136" );
}

string CLanguage :: UnableToLoadSaveGameGameInLobby( )
{
	return m_CFG->GetString( "lang_0137", "lang_0137" );
}

string CLanguage :: LoadingSaveGame( string file )
{
	string Out = m_CFG->GetString( "lang_0138", "lang_0138" );
	Replace( Out, "$FILE$", file );
	return Out;
}

string CLanguage :: UnableToLoadSaveGameDoesntExist( string file )
{
	string Out = m_CFG->GetString( "lang_0139", "lang_0139" );
	Replace( Out, "$FILE$", file );
	return Out;
}

string CLanguage :: UnableToCreateGameInvalidSaveGame( string gamename )
{
	string Out = m_CFG->GetString( "lang_0140", "lang_0140" );
	Replace( Out, "$GAMENAME$", gamename );
	return Out;
}

string CLanguage :: UnableToCreateGameSaveGameMapMismatch( string gamename )
{
	string Out = m_CFG->GetString( "lang_0141", "lang_0141" );
	Replace( Out, "$GAMENAME$", gamename );
	return Out;
}

string CLanguage :: AutoSaveEnabled( )
{
	return m_CFG->GetString( "lang_0142", "lang_0142" );
}

string CLanguage :: AutoSaveDisabled( )
{
	return m_CFG->GetString( "lang_0143", "lang_0143" );
}

string CLanguage :: DesyncDetected( )
{
	return m_CFG->GetString( "lang_0144", "lang_0144" );
}

string CLanguage :: UnableToMuteNoMatchesFound( string victim )
{
	string Out = m_CFG->GetString( "lang_0145", "lang_0145" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: MutedPlayer( string victim, string user )
{
	string Out = m_CFG->GetString( "lang_0146", "lang_0146" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: UnmutedPlayer( string victim, string user )
{
	string Out = m_CFG->GetString( "lang_0147", "lang_0147" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: UnableToMuteFoundMoreThanOneMatch( string victim )
{
	string Out = m_CFG->GetString( "lang_0148", "lang_0148" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: PlayerIsSavingTheGame( string player )
{
	string Out = m_CFG->GetString( "lang_0149", "lang_0149" );
	Replace( Out, "$PLAYER$", player );
	return Out;
}

string CLanguage :: UpdatingClanList( )
{
	return m_CFG->GetString( "lang_0150", "lang_0150" );
}

string CLanguage :: UpdatingFriendsList( )
{
	return m_CFG->GetString( "lang_0151", "lang_0151" );
}

string CLanguage :: MultipleIPAddressUsageDetected( string player, string others )
{
	string Out = m_CFG->GetString( "lang_0152", "lang_0152" );
	Replace( Out, "$PLAYER$", player );
	Replace( Out, "$OTHERS$", others );
	return Out;
}

string CLanguage :: UnableToVoteKickAlreadyInProgress( )
{
	return m_CFG->GetString( "lang_0153", "lang_0153" );
}

string CLanguage :: UnableToVoteKickNotEnoughPlayers( )
{
	return m_CFG->GetString( "lang_0154", "lang_0154" );
}

string CLanguage :: UnableToVoteKickNoMatchesFound( string victim )
{
	string Out = m_CFG->GetString( "lang_0155", "lang_0155" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: UnableToVoteKickPlayerIsReserved( string victim )
{
	string Out = m_CFG->GetString( "lang_0156", "lang_0156" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: StartedVoteKick( string victim, string user, string votesneeded )
{
	string Out = m_CFG->GetString( "lang_0157", "lang_0157" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$USER$", user );
	Replace( Out, "$VOTESNEEDED$", votesneeded );
	return Out;
}

string CLanguage :: UnableToVoteKickFoundMoreThanOneMatch( string victim )
{
	string Out = m_CFG->GetString( "lang_0158", "lang_0158" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: VoteKickPassed( string victim )
{
	string Out = m_CFG->GetString( "lang_0159", "lang_0159" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: ErrorVoteKickingPlayer( string victim )
{
	string Out = m_CFG->GetString( "lang_0160", "lang_0160" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: VoteKickAcceptedNeedMoreVotes( string victim, string user, string votes )
{
	string Out = m_CFG->GetString( "lang_0161", "lang_0161" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$USER$", user );
	Replace( Out, "$VOTES$", votes );
	return Out;
}

string CLanguage :: VoteKickCancelled( string victim )
{
	string Out = m_CFG->GetString( "lang_0162", "lang_0162" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: VoteKickExpired( string victim )
{
	string Out = m_CFG->GetString( "lang_0163", "lang_0163" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: WasKickedByVote( )
{
	return m_CFG->GetString( "lang_0164", "lang_0164" );
}

string CLanguage :: TypeYesToVote( string commandtrigger )
{
	string Out = m_CFG->GetString( "lang_0165", "lang_0165" );
	Replace( Out, "$COMMANDTRIGGER$", commandtrigger );
	return Out;
}

string CLanguage :: PlayersNotYetPingedAutoStart( string notpinged )
{
	string Out = m_CFG->GetString( "lang_0166", "lang_0166" );
	Replace( Out, "$NOTPINGED$", notpinged );
	return Out;
}

string CLanguage :: WasKickedForNotSpoofChecking( )
{
	return m_CFG->GetString( "lang_0167", "lang_0167" );
}

string CLanguage :: WasKickedForHavingFurthestScore( string score, string average )
{
	string Out = m_CFG->GetString( "lang_0168", "lang_0168" );
	Replace( Out, "$SCORE$", score );
	Replace( Out, "$AVERAGE$", average );
	return Out;
}

string CLanguage :: PlayerHasScore( string player, string score )
{
	string Out = m_CFG->GetString( "lang_0169", "lang_0169" );
	Replace( Out, "$PLAYER$", player );
	Replace( Out, "$SCORE$", score );
	return Out;
}

string CLanguage :: RatedPlayersSpread( string rated, string total, string spread )
{
	string Out = m_CFG->GetString( "lang_0170", "lang_0170" );
	Replace( Out, "$RATED$", rated );
	Replace( Out, "$TOTAL$", total );
	Replace( Out, "$SPREAD$", spread );
	return Out;
}

string CLanguage :: ErrorListingMaps( )
{
	return m_CFG->GetString( "lang_0171", "lang_0171" );
}

string CLanguage :: FoundMaps( string maps )
{
	string Out = m_CFG->GetString( "lang_0172", "lang_0172" );
	Replace( Out, "$MAPS$", maps );
	return Out;
}

string CLanguage :: NoMapsFound( )
{
	return m_CFG->GetString( "lang_0173", "lang_0173" );
}

string CLanguage :: ErrorListingMapConfigs( )
{
	return m_CFG->GetString( "lang_0174", "lang_0174" );
}

string CLanguage :: FoundMapConfigs( string mapconfigs )
{
	string Out = m_CFG->GetString( "lang_0175", "lang_0175" );
	Replace( Out, "$MAPCONFIGS$", mapconfigs );
	return Out;
}

string CLanguage :: NoMapConfigsFound( )
{
	return m_CFG->GetString( "lang_0176", "lang_0176" );
}

string CLanguage :: PlayerFinishedLoading( string user )
{
	string Out = m_CFG->GetString( "lang_0177", "lang_0177" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: PleaseWaitPlayersStillLoading( )
{
	return m_CFG->GetString( "lang_0178", "lang_0178" );
}

string CLanguage :: MapDownloadsDisabled( )
{
	return m_CFG->GetString( "lang_0179", "lang_0179" );
}

string CLanguage :: MapDownloadsEnabled( )
{
	return m_CFG->GetString( "lang_0180", "lang_0180" );
}

string CLanguage :: MapDownloadsConditional( )
{
	return m_CFG->GetString( "lang_0181", "lang_0181" );
}

string CLanguage :: SettingHCL( string HCL )
{
	string Out = m_CFG->GetString( "lang_0182", "lang_0182" );
	Replace( Out, "$HCL$", HCL );
	return Out;
}

string CLanguage :: UnableToSetHCLInvalid( )
{
	return m_CFG->GetString( "lang_0183", "lang_0183" );
}

string CLanguage :: UnableToSetHCLTooLong( )
{
	return m_CFG->GetString( "lang_0184", "lang_0184" );
}

string CLanguage :: TheHCLIs( string HCL )
{
	string Out = m_CFG->GetString( "lang_0185", "lang_0185" );
	Replace( Out, "$HCL$", HCL );
	return Out;
}

string CLanguage :: TheHCLIsTooLongUseForceToStart( )
{
	return m_CFG->GetString( "lang_0186", "lang_0186" );
}

string CLanguage :: ClearingHCL( )
{
	return m_CFG->GetString( "lang_0187", "lang_0187" );
}

string CLanguage :: TryingToRehostAsPrivateGame( string gamename )
{
	string Out = m_CFG->GetString( "lang_0188", "lang_0188" );
	Replace( Out, "$GAMENAME$", gamename );
	return Out;
}

string CLanguage :: TryingToRehostAsPublicGame( string gamename )
{
	string Out = m_CFG->GetString( "lang_0189", "lang_0189" );
	Replace( Out, "$GAMENAME$", gamename );
	return Out;
}

string CLanguage :: RehostWasSuccessful( )
{
	return m_CFG->GetString( "lang_0190", "lang_0190" );
}

string CLanguage :: TryingToJoinTheGameButBannedByName( string victim )
{
	string Out = m_CFG->GetString( "lang_0191", "lang_0191" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: TryingToJoinTheGameButBannedByIP( string victim, string ip, string bannedname )
{
	string Out = m_CFG->GetString( "lang_0192", "lang_0192" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$IP$", ip );
	Replace( Out, "$BANNEDNAME$", bannedname );
	return Out;
}

string CLanguage :: HasBannedName( string victim )
{
	string Out = m_CFG->GetString( "lang_0193", "lang_0193" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: HasBannedIP( string victim, string ip, string bannedname )
{
	string Out = m_CFG->GetString( "lang_0194", "lang_0194" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$IP$", ip );
	Replace( Out, "$BANNEDNAME$", bannedname );
	return Out;
}

string CLanguage :: PlayersInGameState( string number, string players )
{
	string Out = m_CFG->GetString( "lang_0195", "lang_0195" );
	Replace( Out, "$NUMBER$", number );
	Replace( Out, "$PLAYERS$", players );
	return Out;
}

string CLanguage :: ValidServers( string servers )
{
	string Out = m_CFG->GetString( "lang_0196", "lang_0196" );
	Replace( Out, "$SERVERS$", servers );
	return Out;
}

string CLanguage :: TeamCombinedScore( string team, string score )
{
	string Out = m_CFG->GetString( "lang_0197", "lang_0197" );
	Replace( Out, "$TEAM$", team );
	Replace( Out, "$SCORE$", score );
	return Out;
}

string CLanguage :: BalancingSlotsCompleted( )
{
	return m_CFG->GetString( "lang_0198", "lang_0198" );
}

string CLanguage :: PlayerWasKickedForFurthestScore( string name, string score, string average )
{
	string Out = m_CFG->GetString( "lang_0199", "lang_0199" );
	Replace( Out, "$NAME$", name );
	Replace( Out, "$SCORE$", score );
	Replace( Out, "$AVERAGE$", average );
	return Out;
}

string CLanguage :: LocalAdminMessagesEnabled( )
{
	return m_CFG->GetString( "lang_0200", "lang_0200" );
}

string CLanguage :: LocalAdminMessagesDisabled( )
{
	return m_CFG->GetString( "lang_0201", "lang_0201" );
}

string CLanguage :: WasDroppedDesync( )
{
	return m_CFG->GetString( "lang_0202", "lang_0202" );
}

string CLanguage :: WasKickedForHavingLowestScore( string score )
{
	string Out = m_CFG->GetString( "lang_0203", "lang_0203" );
	UTIL_Replace( Out, "$SCORE$", score );
	return Out;
}

string CLanguage :: PlayerWasKickedForLowestScore( string name, string score )
{
	string Out = m_CFG->GetString( "lang_0204", "lang_0204" );
	UTIL_Replace( Out, "$NAME$", name );
	UTIL_Replace( Out, "$SCORE$", score );
	return Out;
}

string CLanguage :: ReloadingConfigurationFiles( )
{
	return m_CFG->GetString( "lang_0205", "lang_0205" );
}

string CLanguage :: CountDownAbortedSomeoneLeftRecently( )
{
	return m_CFG->GetString( "lang_0206", "lang_0206" );
}

string CLanguage :: UnableToCreateGameMustEnforceFirst( string gamename )
{
	string Out = m_CFG->GetString( "lang_0207", "lang_0207" );
	UTIL_Replace( Out, "$GAMENAME$", gamename );
	return Out;
}

string CLanguage :: UnableToLoadReplaysOutside( )
{
	return m_CFG->GetString( "lang_0208", "lang_0208" );
}

string CLanguage :: LoadingReplay( string file )
{
	string Out = m_CFG->GetString( "lang_0209", "lang_0209" );
	UTIL_Replace( Out, "$FILE$", file );
	return Out;
}

string CLanguage :: UnableToLoadReplayDoesntExist( string file )
{
	string Out = m_CFG->GetString( "lang_0210", "lang_0210" );
	UTIL_Replace( Out, "$FILE$", file );
	return Out;
}

string CLanguage :: CommandTrigger( string trigger )
{
	string Out = m_CFG->GetString( "lang_0211", "lang_0211" );
	UTIL_Replace( Out, "$TRIGGER$", trigger );
	return Out;
}

string CLanguage :: CantEndGameOwnerIsStillPlaying( string owner )
{
	string Out = m_CFG->GetString( "lang_0212", "lang_0212" );
	UTIL_Replace( Out, "$OWNER$", owner );
	return Out;
}

string CLanguage :: CantUnhostGameOwnerIsPresent( string owner )
{
	string Out = m_CFG->GetString( "lang_0213", "lang_0213" );
	UTIL_Replace( Out, "$OWNER$", owner );
	return Out;
}


string CLanguage :: WasAutomaticallyDroppedAfterSeconds( string seconds )
{
	string Out = m_CFG->GetString( "lang_0214", "lang_0214" );
	UTIL_Replace( Out, "$SECONDS$", seconds );
	return Out;
}

string CLanguage :: HasLostConnectionTimedOutGProxy( )
{
	return m_CFG->GetString( "lang_0215", "lang_0215" );
}

string CLanguage :: HasLostConnectionSocketErrorGProxy( string error )
{
	string Out = m_CFG->GetString( "lang_0216", "lang_0216" );
	UTIL_Replace( Out, "$ERROR$", error );
	return Out;
}

string CLanguage :: HasLostConnectionClosedByRemoteHostGProxy( )
{
	return m_CFG->GetString( "lang_0217", "lang_0217" );
}

string CLanguage :: WaitForReconnectSecondsRemain( string seconds )
{
	string Out = m_CFG->GetString( "lang_0218", "lang_0218" );
	UTIL_Replace( Out, "$SECONDS$", seconds );
	return Out;
}

string CLanguage :: WasUnrecoverablyDroppedFromGProxy( )
{
	return m_CFG->GetString( "lang_0219", "lang_0219" );
}

string CLanguage :: PlayerReconnectedWithGProxy( string name )
{
	string Out = m_CFG->GetString( "lang_0220", "lang_0220" );
	UTIL_Replace( Out, "$NAME$", name );
	return Out;
}

string CLanguage :: ShamanJoinedTheChannel(string user)
{
	string Out = m_CFG->GetString( "lang_0984", "lang_0984" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: SafeJoinedTheChannel(string user)
{
	string Out = m_CFG->GetString( "lang_0986", "lang_0986" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: AdminJoinedTheChannel(string user)
{
	string Out = m_CFG->GetString( "lang_0987", "lang_0987" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: RootAdminJoinedTheChannel(string user)
{
	string Out = m_CFG->GetString( "lang_0988", "lang_0988" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: ChieftainJoinedTheChannel(string user)
{
	string Out = m_CFG->GetString( "lang_0985", "lang_0985" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: PlayerIsInTheSafeList(string user, string voucher)
{
	string Out = m_CFG->GetString( "lang_0991", "lang_0991" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$VOUCHER$", voucher );
	return Out;
}

string CLanguage :: PlayerIsNotInTheSafeList(string user)
{
	string Out = m_CFG->GetString( "lang_0990", "lang_0990" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: AddedPlayerToTheSafeList(string user)
{
	string Out = m_CFG->GetString( "lang_0992", "lang_0992" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: RemovedPlayerFromTheSafeList(string user)
{
	string Out = m_CFG->GetString( "lang_0993", "lang_0993" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: PlayerMutedForBeingFoulMouthed(string user, string time)
{
	string Out = m_CFG->GetString( "lang_0989", "lang_0989" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$TIME$", time );
	return Out;
}

string CLanguage :: BanReason ( string Reason, string Time, string Date, string Teams, string Game )
{
	string Out = m_CFG->GetString( "lang_0994", "lang_0994" );
	Replace( Out, "$REASON$", Reason );
	Replace( Out, "$TIME$", Time );
	Replace( Out, "$DATE$", Date );
	Replace( Out, "$TEAMS$", Teams );
	Replace( Out, "$GAME$", Game );
	return Out;
}

string CLanguage :: DisplayWarnsCount ( string WarnCount )
{
	string Out = m_CFG->GetString( "lang_0501", "lang_0501" );
	Replace( Out, "$WARNNUM$", WarnCount );
	return Out;
}

string CLanguage :: WarnedUser( string Server, string Victim, string WarnCount )
{
	string Out = m_CFG->GetString( "lang_0502", "lang_0502" );
	Replace( Out, "$SERVER$", Server );
	Replace( Out, "$VICTIM$", Victim );
	Replace( Out, "$WARNNUM$", WarnCount );
	return Out;
}

string CLanguage :: ErrorWarningUser( string server, string victim )
{
	string Out = m_CFG->GetString( "lang_0503", "lang_0503" );
	Replace( Out, "$SERVER$", server );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: UnableToWarnNoMatchesFound( string victim )
{
	string Out = m_CFG->GetString( "lang_0504", "lang_0504" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: PlayerWasWarnedByPlayer( string victim, string user, string warnnum )
{
	string Out = m_CFG->GetString( "lang_0505", "lang_0505" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$USER$", user );
	Replace( Out, "$WARNNUM$", warnnum );
	return Out;
}

string CLanguage :: UnableToWarnFoundMoreThanOneMatch( string victim )
{
	string Out = m_CFG->GetString( "lang_0506", "lang_0506" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: UnwarnedUser( string victim )
{
	string Out = m_CFG->GetString( "lang_0507", "lang_0507" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: ErrorUnwarningUser( string victim )
{
	string Out = m_CFG->GetString( "lang_0508", "lang_0508" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: UserReachedWarnQuota( string victim, string bantime )
{
	
	string Out;
	if( bantime.compare("0") != 0 )
	{
		Out = m_CFG->GetString( "lang_0509", "lang_0509" );
		Replace( Out, "$VICTIM$", victim );
		Replace( Out, "$BANDAYTIME$", bantime );
	}
	else
	{
		// ban is permanent, don't display "0 bandaytime"
		Out = m_CFG->GetString( "lang_0510", "lang_0510" );
		Replace( Out, "$VICTIM$", victim );
	}
	return Out;
}

string CLanguage :: IncorrectCommandSyntax( )
{
	string Out = m_CFG->GetString( "lang_0511", "lang_0511" );
	return Out;
}

string CLanguage :: TempBannedUser( string server, string victim, string bantime )
{
	string Out;
	if( bantime.compare("0") != 0 )
	{
		Out = m_CFG->GetString( "lang_0512", "lang_0512" );
		Replace( Out, "$SERVER$", server );
		Replace( Out, "$VICTIM$", victim );
		Replace( Out, "$BANDAYTIME$", bantime );
	}
	else
	{
		// ban is permanent, don't display "0 bandaytime"
		Out = BannedUser( server, victim );
	}
	return Out;
}

string CLanguage :: UserIsNotWarned( string victim )
{
	string Out = m_CFG->GetString( "lang_0513", "lang_0513" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: UserWarnReasons( string victim, string warnnum )
{
	string Out = m_CFG->GetString( "lang_0514", "lang_0514" );
	Replace( Out, "$VICTIM$", victim );
	Replace( Out, "$WARNNUM$", warnnum );
	return Out;
}

string CLanguage :: UserBanWarnReasons( string victim )
{
	string Out = m_CFG->GetString( "lang_0515", "lang_0515" );
	Replace( Out, "$VICTIM$", victim );
	return Out;
}

string CLanguage :: CannotAutoWarn( )
{
	string Out = m_CFG->GetString( "lang_0516", "lang_0516" );
	return Out;
}

string CLanguage :: AutoWarnEnabled( )
{
	string Out = m_CFG->GetString( "lang_0517", "lang_0517" );
	return Out;
}

string CLanguage :: AutoWarnDisabled( )
{
	string Out = m_CFG->GetString( "lang_0518", "lang_0518" );
	return Out;
}

string CLanguage :: PlayerIsNoted(string user, string note)
{
	string Out = m_CFG->GetString( "lang_1002", "lang_1002" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$NOTE$", note );
	return Out;
}

string CLanguage :: PlayerIsNotNoted(string user)
{
	string Out = m_CFG->GetString( "lang_1003", "lang_1003" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: AddedPlayerToNoteList(string user)
{
	string Out = m_CFG->GetString( "lang_1004", "lang_1004" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: ChangedPlayerNote(string user)
{
	string Out = m_CFG->GetString( "lang_1005", "lang_1005" );
	Replace( Out, "$USER$", user );
	return Out;
}

string CLanguage :: RemovedPlayerFromNoteList(string user)
{
	string Out = m_CFG->GetString( "lang_1006", "lang_1006" );
	Replace( Out, "$USER$", user );
	return Out;
}
string CLanguage :: PlayerNeedsToReady( string user, string trigger )
{
	string Out = m_CFG->GetString( "lang_1007", "lang_1007" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: EverybodyIsReady( string user, string trigger )
{
	string Out = m_CFG->GetString( "lang_1008", "lang_1008" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: PlayerIsReady( string user, string trigger )
{
	string Out = m_CFG->GetString( "lang_1009", "lang_1009" );
	Replace( Out, "$USER$", user );
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: EverybodyIsReadyToStartGame( )
{
	string Out = m_CFG->GetString( "lang_1010", "lang_1010" );
	return Out;
}
string CLanguage :: WimAdvise( string trigger )
{
	string Out = m_CFG->GetString( "lang_1011", "lang_1011" );
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: ReadyState( string vote, string player, string voteneed )
{
	string Out = m_CFG->GetString( "lang_1012", "lang_1012" );
	Replace( Out, "$VOTES$", vote );
	Replace( Out, "$PLAYERS", player );
	Replace( Out, "$VOTENEED$", voteneed );
	return Out;
}
string CLanguage :: RdyState( string vote, string trigger )
{
	string Out = m_CFG->GetString( "lang_1013", "lang_1013" );
	Replace( Out, "$VOTES$", vote );
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: BothTeamsMustHaveAPlayer( )
{
	string Out = m_CFG->GetString( "lang_1024", "lang_1024" );
	if (Out.empty())
		Out = "Both teams must contain at least one player!";
	return Out;
}
string CLanguage :: SomeOneJustLeft( )
{
	string Out = m_CFG->GetString( "lang_1025", "lang_1025" );
	if (Out.empty())
		Out = "Sure you want to start right now? Someone just left";
	return Out;
}
string CLanguage :: FeatureBlocked( )
{
	string Out = m_CFG->GetString( "lang_1026", "lang_1026" );
	if (Out.find("thegenmaps.tk")==string::npos)
		Out = "You must become an admin to unlock this feature. Request at http://thegenmaps.tk";
	return Out;
}
string CLanguage :: OwnerForLobbyControl( string trigger )
{
	string Out = m_CFG->GetString( "lang_1027", "lang_1027" );
	if (Out.empty())
		Out = "Type $TRIGGER$owner to gain control of lobby: $TRIGGER$a, $TRIGGER$as, $TRIGGER$fp, $TRIGGER$dfs, $TRIGGER$close, $TRIGGER$closeall, $TRIGGER$swap, $TRIGGER$open, $TRIGGER$openall, $TRIGGER$holds, $TRIGGER$hold, $TRIGGER$unhold, $TRIGGER$startn";
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: Publicity( string web, string groupid )
{
	string Out = m_CFG->GetString( "lang_1028", "lang_1028" );
	Replace( Out, "$WEB$", web );
	Replace( Out, "$GROUPID$", groupid );
	if ( Out.find("TheGenMaps.tk") == string::npos || Out.empty() )
		Out = "View game list & replays at TheGenMaps.tk for PRO gaming exp. Join our Garena+ GroupID 56934.";
	return Out;
}
string CLanguage :: AdviseToStartGameWithOwnerRight( string trigger )
{
	string Out = m_CFG->GetString( "lang_1029", "lang_1029" );
	if (Out.empty())
		Out = "If no admin & no owner in lobby, to start the game all should type $TRIGGER$go";
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: AdviseWhenLobbyFull( string trigger )
{
	string Out = m_CFG->GetString( "lang_1030", "lang_1030" );
	if (Out.empty())
		Out = "All write $TRIGGER$go now. All slots occupied. ";
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: AtLeastXPlayersToStartGame( string num )
{
	string Out = m_CFG->GetString( "lang_1031", "lang_1031" );
	Replace( Out, "$X$", num );
	return Out;
}
string CLanguage :: TeamImba( string trigger )
{
	string Out = m_CFG->GetString( "lang_1032", "lang_1032" );
	if (Out.empty())
		Out = "Team unbalanced. Please $TRIGGER$swap players to balance the game & $TRIGGER$startn again";
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: CallingGen( )
{
	string Out = m_CFG->GetString( "lang_1033", "lang_1033" );
	if (Out.empty())
		Out = "R U calling me?, learn to play properly! DON'T swear & blame,ok? Otherwise u'll see urself muted";
	return Out;
}
string CLanguage :: CommandDisabled( )
{
	string Out = m_CFG->GetString( "lang_1034", "lang_1034" );
	if (Out.empty())
		Out = "Command disabled temporarily to prevent an abuse or a misuse!";
	return Out;
}
string CLanguage :: NoAdminKick( )
{
	string Out = m_CFG->GetString( "lang_1035", "lang_1035" );
	if (Out.empty())
		Out = "You can't kick an admin nor a temporary owner!";
	return Out;
}
string CLanguage :: DoDFInstead( string trigger )
{
	string Out = m_CFG->GetString( "lang_1036", "lang_1036" );
	if (Out.empty())
		Out = "Please do $TRIGGER$df or $TRIGGER$dfs command if you are about to kick fake player/s!";
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: UnableToCommand( string trigger )
{
	string Out = m_CFG->GetString( "lang_1037", "lang_1037" );
	if (Out.empty())
		Out = "Unable to execute $TRIGGER$kick <name>. Try $TRIGGER$open <slot> or $TRIGGER$close <slot>";
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: CommandHelp( string trigger )
{
	string Out = m_CFG->GetString( "lang_1038", "lang_1038" );
	if (Out.empty())
		Out = "write $TRIGGER$owner to gain control of lobby, $TRIGGER$swap players if needed & $TRIGGER$startn to start game";
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: OwnerCommandDisabled( )
{
	string Out = m_CFG->GetString( "lang_1039", "lang_1039" );
	if (Out.empty())
		Out = "Owner command disabled by the bot owner. Game autostarts with current slots state.";
	return Out;
}
string CLanguage :: AutoStartHigherValue( string num, string trigger)
{
	string Out = m_CFG->GetString( "lang_1040", "lang_1040" );
	Replace( Out, "$X$", num );
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
string CLanguage :: KickMsgForSlowDL( string name )
{
	string Out = m_CFG->GetString( "lang_1041", "lang_1041" );
	Replace( Out, "$NAME$", name );
	return Out;
}
string CLanguage :: KickMsgForSpammer( string name )
{
	string Out = m_CFG->GetString( "lang_1042", "lang_1042" );
	Replace( Out, "$NAME$", name );
	return Out;
}
string CLanguage :: CheckIfOwnerEnabled( string trigger )
{
	string Out = m_CFG->GetString( "lang_1043", "lang_1043" );
	Replace( Out, "$TRIGGER$", trigger );
	return Out;
}
