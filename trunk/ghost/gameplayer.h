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

#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include <list>
using namespace std;

class CTCPSocket;
class CCommandPacket;
class CGameProtocol;
class CGame;
class CIncomingJoinPlayer;
class CIncomingGarenaUser;

//
// CPotentialPlayer
//

class CPotentialPlayer
{
public:
	CGameProtocol *m_Protocol;
	CBaseGame *m_Game;

protected:
	// note: we permit m_Socket to be NULL in this class to allow for the virtual host player which doesn't really exist
	// it also allows us to convert CPotentialPlayers to CGamePlayers without the CPotentialPlayer's destructor closing the socket

	CTCPSocket *m_Socket;
	queue<CCommandPacket *> m_Packets;
	bool m_DeleteMe;
	bool m_Error;
	bool m_LANSet;
	bool m_LAN;
	string m_ErrorString;
	CIncomingJoinPlayer *m_IncomingJoinPlayer;
	CIncomingGarenaUser *m_IncomingGarenaUser;
	
	uint32_t m_ConnectionState;	// zero if no packets received (wait REQJOIN), one if only REQJOIN received (wait MAPSIZE), two otherwise
	uint32_t m_ConnectionTime;	// last time the player did something relating to connection state

public:
	CPotentialPlayer( CGameProtocol *nProtocol, CBaseGame *nGame, CTCPSocket *nSocket );
	virtual ~CPotentialPlayer( );

	virtual CTCPSocket *GetSocket( )				{ return m_Socket; }
	virtual BYTEARRAY GetExternalIP( );
	virtual string GetExternalIPString( );
	virtual queue<CCommandPacket *> GetPackets( )	{ return m_Packets; }
	virtual bool IsLAN( )							{ if (m_LANSet) return m_LAN; else {GetExternalIPString(); return m_LAN;}}
	virtual bool GetDeleteMe( )						{ return m_DeleteMe; }
	virtual bool GetError( )						{ return m_Error; }
	virtual string GetErrorString( )				{ return m_ErrorString; }
	virtual CIncomingJoinPlayer *GetJoinPlayer( )	{ return m_IncomingJoinPlayer; }
	virtual CIncomingGarenaUser *GetGarenaUser( )	{ return m_IncomingGarenaUser; }
 	virtual BYTEARRAY GetGarenaIP( );

	virtual void SetSocket( CTCPSocket *nSocket )	{ m_Socket = nSocket; }
	virtual void SetDeleteMe( bool nDeleteMe )		{ m_DeleteMe = nDeleteMe; }
	virtual void SetGarenaUser( CIncomingGarenaUser *nIncomingGarenaUser ) { m_IncomingGarenaUser = nIncomingGarenaUser; }
	
	// processing functions

	virtual bool Update( void *fd );
	virtual void ExtractPackets( );
	virtual void ProcessPackets( );

	// other functions

	virtual void Send( BYTEARRAY data );
};

//
// CGamePlayer
//

class CGamePlayer : public CPotentialPlayer
{
private:
	unsigned char m_PID;
	unsigned char m_SID;
	string m_Name;								// the player's name
	BYTEARRAY m_InternalIP;						// the player's internal IP address as reported by the player when connecting
	vector<uint32_t> m_Pings;					// store the last few (20) pings received so we can take an average
	queue<uint32_t> m_CheckSums;				// the last few checksums the player has sent (for detecting desyncs)
	string m_LeftReason;						// the reason the player left the game
	string m_SpoofedRealm;						// the realm the player last spoof checked on
	string m_JoinedRealm;						// the realm the player joined on (probable, can be spoofed)
	uint32_t m_TotalPacketsSent;
	uint32_t m_TotalPacketsReceived;
	string m_Provider;							// the internet provider of this player
	string m_Country;							// the country of this player
	uint32_t m_LeftCode;						// the code to be sent in W3GS_PLAYERLEAVE_OTHERS for why this player left the game
	uint32_t m_LoginAttempts;					// the number of attempts to login (used with CAdminGame only)
	uint32_t m_SyncCounter;						// the number of keepalive packets received from this player
	uint32_t m_JoinTime;						// GetTime when the player joined the game (used to delay sending the /whois a few seconds to allow for some lag)
	uint32_t m_LastMapPartSent;					// the last mappart sent to the player (for sending more than one part at a time)
	uint32_t m_LastMapPartAcked;				// the last mappart acknowledged by the player
	uint32_t m_StartedDownloadingTicks;			// GetTicks when the player started downloading the map
	uint32_t m_FinishedDownloadingTime;			// GetTime when the player finished downloading the map
	uint32_t m_FinishedLoadingTicks;			// GetTicks when the player finished loading the game
	uint32_t m_StartedLaggingTicks;				// GetTicks when the player started lagging
	uint32_t m_TotalLaggingTicks;				// total ticks that the player has been lagging in the game
	uint32_t m_StatsSentTime;					// GetTime when we sent this player's stats to the chat (to prevent players from spamming !stats)
	uint32_t m_StatsDotASentTime;				// GetTime when we sent this player's dota stats to the chat (to prevent players from spamming !statsdota)
	uint32_t m_LastGProxyWaitNoticeSentTime;
	queue<BYTEARRAY> m_LoadInGameData;			// queued data to be sent when the player finishes loading when using "load in game"
	uint32_t m_DOTAKills;
	uint32_t m_DOTADeaths;
	uint32_t m_DOTAAssists;
	uint32_t m_Censors;
	bool m_Silence;
	string m_DownloadInfo;                      // Download info
	double m_Score;								// the player's generic "score" for the matchmaking algorithm
	bool m_LoggedIn;							// if the player has logged in or not (used with CAdminGame only)
	bool m_Spoofed;								// if the player has spoof checked or not
	bool m_Reserved;							// if the player is reserved (VIP) or not
	bool m_WhoisShouldBeSent;					// if a battle.net /whois should be sent for this player or not
	bool m_WhoisSent;							// if we've sent a battle.net /whois for this player yet (for spoof checking)
	bool m_DownloadAllowed;						// if we're allowed to download the map or not (used with permission based map downloads)
	bool m_DownloadStarted;						// if we've started downloading the map or not
	bool m_DownloadFinished;					// if we've finished downloading the map or not
	bool m_FinishedLoading;						// if the player has finished loading or not
	bool m_Lagging;								// if the player is lagging or not (on the lag screen)
	bool m_DropVote;							// if the player voted to drop the laggers or not (on the lag screen)
	bool m_KickVote;							// if the player voted to kick a player or not	
	bool m_StartVote;						                    // if the player !ready or not
	bool m_HasFFed;		
	uint32_t m_TimeOfFF;       
	bool m_CanFF; 
	bool m_HasRMKed;		
	uint32_t m_TimeOfRMK;       
	bool m_CanRMK;
	bool m_RmkVote;								// if the player voted to rmk or not
	bool m_Muted;								// if the player is muted or not
	bool m_LeftMessageSent;						// if the playerleave message has been sent or not
	bool m_GProxy;								// if the player is using GProxy++
	bool m_GProxyDisconnectNoticeSent;			// if a disconnection notice has been sent or not when using GProxy++
	queue<BYTEARRAY> m_GProxyBuffer;
	uint32_t m_GProxyReconnectKey;
	uint32_t m_LastGProxyAckTime;
	bool m_ScoreSet;
	bool m_RankSet;
	string m_ScoreS;
	string m_RankS;
	list<string> m_LastMessages;				// store the last messages sent for spam prevention

public:
	CGamePlayer( CGameProtocol *nProtocol, CBaseGame *nGame, CTCPSocket *nSocket, unsigned char nPID, string nJoinedRealm, string nName, BYTEARRAY nInternalIP, bool nReserved );
	CGamePlayer( CPotentialPlayer *potential, unsigned char nPID, string nJoinedRealm, string nName, BYTEARRAY nInternalIP, bool nReserved );
	virtual ~CGamePlayer( );

	bool m_Switched;
	bool m_Switching;
	bool m_Switchok;
	bool m_WarnChecked;
	unsigned char GetSID( )						{ return m_SID; }
	unsigned char GetPID( )						{ return m_PID; }
	string GetName( )							{ return m_Name; }
	BYTEARRAY GetInternalIP( )					{ return m_InternalIP; }
	unsigned int GetNumPings( )					{ return m_Pings.size( ); }
	unsigned int GetNumCheckSums( )				{ return m_CheckSums.size( ); }
	queue<uint32_t> *GetCheckSums( )			{ return &m_CheckSums; }
	string GetLeftReason( )						{ return m_LeftReason; }
	string GetSpoofedRealm( )					{ return m_SpoofedRealm; }
	string GetJoinedRealm( )					{ return m_JoinedRealm; }
	uint32_t GetLeftCode( )						{ return m_LeftCode; }
	uint32_t GetLoginAttempts( )				{ return m_LoginAttempts; }
	uint32_t GetSyncCounter( )					{ return m_SyncCounter; }
	uint32_t GetJoinTime( )						{ return m_JoinTime; }
	uint32_t GetLastMapPartSent( )				{ return m_LastMapPartSent; }
	uint32_t GetLastMapPartAcked( )				{ return m_LastMapPartAcked; }
	uint32_t GetStartedDownloadingTicks( )		{ return m_StartedDownloadingTicks; }
	uint32_t GetFinishedDownloadingTime( )		{ return m_FinishedDownloadingTime; }
	uint32_t GetFinishedLoadingTicks( )			{ return m_FinishedLoadingTicks; }
	uint32_t GetStartedLaggingTicks( )			{ return m_StartedLaggingTicks; }
	uint32_t GetTotalLaggingTicks( )			{ return m_TotalLaggingTicks; }
	uint32_t GetStatsSentTime( )				{ return m_StatsSentTime; }
	uint32_t GetStatsDotASentTime( )			{ return m_StatsDotASentTime; }
	uint32_t GetLastGProxyWaitNoticeSentTime( )	{ return m_LastGProxyWaitNoticeSentTime; }
	queue<BYTEARRAY> *GetLoadInGameData( )		{ return &m_LoadInGameData; }
	bool GetWarnChecked( )						{ return m_WarnChecked; }
	string GetDownloadInfo ( )					{ return m_DownloadInfo; }
	double GetScore( )							{ return m_Score; }
	bool GetLoggedIn( )							{ return m_LoggedIn; }
	bool GetSpoofed( )							{ return m_Spoofed; }
	bool GetReserved( )							{ return m_Reserved; }
	bool GetWhoisShouldBeSent( )				{ return m_WhoisShouldBeSent; }
	bool GetWhoisSent( )						{ return m_WhoisSent; }
	bool GetDownloadAllowed( )					{ return m_DownloadAllowed; }
	bool GetDownloadStarted( )					{ return m_DownloadStarted; }
	bool GetDownloadFinished( )					{ return m_DownloadFinished; }
	bool GetFinishedLoading( )					{ return m_FinishedLoading; }
	bool GetLagging( )							{ return m_Lagging; }
	bool GetDropVote( )							{ return m_DropVote; }
	bool GetKickVote( )							{ return m_KickVote; }
	bool GetStartVote( )                        { return m_StartVote; }
	bool GetHasFFed( )							{ return m_HasFFed; }
	void SetHadFFed( bool nHasFFed )			{ m_HasFFed = nHasFFed; }
	void SetTimeFFed(uint32_t set_time) { m_TimeOfFF = set_time; }
	uint32_t GetTimeOfFF() { return m_TimeOfFF;}
	void SetCanFF( bool nCanFF )	{ m_CanFF = nCanFF; }
	bool CanFF()    { return m_CanFF;}
	bool GetHasRMKed( )							{ return m_HasRMKed; }
	void SetHadRMKed( bool nHasRMKed )			{ m_HasRMKed = nHasRMKed; }
	void SetTimeRMKed(uint32_t set_time) { m_TimeOfRMK = set_time; }
	uint32_t GetTimeOfRMK() { return m_TimeOfRMK;}
	void SetCanRMK( bool nCanRMK )	{ m_CanRMK = nCanRMK; }
	bool CanRMK()    { return m_CanRMK;}
	bool GetRmkVote( )							{ return m_RmkVote; }
	bool GetMuted( )							{ return m_Muted; }
	bool GetLeftMessageSent( )					{ return m_LeftMessageSent; }
	bool GetScoreSet( )						{ return m_ScoreSet; }
	bool GetRankSet( )						{ return m_RankSet; }
	uint32_t GetDOTAKills( )				{ return m_DOTAKills; }
	uint32_t GetDOTADeaths( )				{ return m_DOTADeaths; }
	uint32_t GetDOTAAssists( )				{ return m_DOTAAssists; }
	uint32_t GetCensors( )					{ return m_Censors; }
	bool GetSilence( )						{ return m_Silence; }
	string GetScoreS ( )					{ return m_ScoreS; }
	string GetRanksS ( )					{ return m_RankS; }
	bool GetGProxy( )							{ return m_GProxy; }
	bool GetGProxyDisconnectNoticeSent( )		{ return m_GProxyDisconnectNoticeSent; }
	uint32_t GetGProxyReconnectKey( )			{ return m_GProxyReconnectKey; }

	void SetLeftReason( string nLeftReason )										{ m_LeftReason = nLeftReason; }
	void SetSpoofedRealm( string nSpoofedRealm )									{ m_SpoofedRealm = nSpoofedRealm; }
	void SetLeftCode( uint32_t nLeftCode )											{ m_LeftCode = nLeftCode; }
	void SetLoginAttempts( uint32_t nLoginAttempts )								{ m_LoginAttempts = nLoginAttempts; }
	void SetSyncCounter( uint32_t nSyncCounter )									{ m_SyncCounter = nSyncCounter; }
	void SetLastMapPartSent( uint32_t nLastMapPartSent )							{ m_LastMapPartSent = nLastMapPartSent; }
	void SetLastMapPartAcked( uint32_t nLastMapPartAcked )							{ m_LastMapPartAcked = nLastMapPartAcked; }
	void SetStartedDownloadingTicks( uint32_t nStartedDownloadingTicks )			{ m_StartedDownloadingTicks = nStartedDownloadingTicks; }
	void SetFinishedDownloadingTime( uint32_t nFinishedDownloadingTime )			{ m_FinishedDownloadingTime = nFinishedDownloadingTime; }
	void SetStartedLaggingTicks( uint32_t nStartedLaggingTicks )					{ m_StartedLaggingTicks = nStartedLaggingTicks; }
	void SetTotalLaggingTicks( uint32_t nTotalLaggingTicks )						{ m_TotalLaggingTicks = nTotalLaggingTicks; }
	void SetStatsSentTime( uint32_t nStatsSentTime )								{ m_StatsSentTime = nStatsSentTime; }
	void SetStatsDotASentTime( uint32_t nStatsDotASentTime )						{ m_StatsDotASentTime = nStatsDotASentTime; }
	void SetLastGProxyWaitNoticeSentTime( uint32_t nLastGProxyWaitNoticeSentTime )	{ m_LastGProxyWaitNoticeSentTime = nLastGProxyWaitNoticeSentTime; }
	void SetScore( double nScore )													{ m_Score = nScore; }
	void SetLoggedIn( bool nLoggedIn )												{ m_LoggedIn = nLoggedIn; }
	void SetSpoofed( bool nSpoofed )												{ m_Spoofed = nSpoofed; }
	void SetReserved( bool nReserved )												{ m_Reserved = nReserved; }
	void SetWhoisShouldBeSent( bool nWhoisShouldBeSent )							{ m_WhoisShouldBeSent = nWhoisShouldBeSent; }
	void SetDownloadAllowed( bool nDownloadAllowed )								{ m_DownloadAllowed = nDownloadAllowed; }
	void SetDownloadStarted( bool nDownloadStarted )								{ m_DownloadStarted = nDownloadStarted; }
	void SetDownloadFinished( bool nDownloadFinished )								{ m_DownloadFinished = nDownloadFinished; }
	void SetDownloadInfo( string nDownloadInfo )							{ m_DownloadInfo = nDownloadInfo; }
	void SetLagging( bool nLagging )												{ m_Lagging = nLagging; }
	void SetDropVote( bool nDropVote )												{ m_DropVote = nDropVote; }
	void SetKickVote( bool nKickVote )												{ m_KickVote = nKickVote; }
	void SetStartVote( bool nStartVote ) 									{ m_StartVote = nStartVote; }
	void SetRmkVote( bool nRmkVote )										{ m_RmkVote = nRmkVote; }
	void SetMuted( bool nMuted )													{ m_Muted = nMuted; }
	void SetLeftMessageSent( bool nLeftMessageSent )								{ m_LeftMessageSent = nLeftMessageSent; }
	void SetGProxyDisconnectNoticeSent( bool nGProxyDisconnectNoticeSent )			{ m_GProxyDisconnectNoticeSent = nGProxyDisconnectNoticeSent; }
	void SetWarnChecked( bool nWarnChecked )								{ m_WarnChecked = nWarnChecked; }
	void SetName( string nName )											{ m_Name = nName; }
	virtual string GetProvider( );											
	virtual string GetCountry ( );
	void SetSID( unsigned char nSID )										{ m_SID = nSID; }
	void SetDOTAKills( uint32_t nKills )									{ m_DOTAKills = nKills; }
	void SetDOTADeaths( uint32_t nDeaths )									{ m_DOTADeaths = nDeaths; }
	void SetDOTAAssists( uint32_t nAssists )								{ m_DOTAAssists = nAssists; }
	void SetCensors( uint32_t nCensors )									{ m_Censors = nCensors; }
	void SetSilence( bool nSilence )										{ m_Silence = nSilence; }
	void SetScoreS( string nScore )											{ m_ScoreS = nScore; m_ScoreSet = true; }
	void SetRankS( string nRank )											{ m_RankS = nRank; m_RankSet = true; }
	void SetProvider( string nProvider )									{ m_Provider = nProvider;}
	void SetCountry( string nCountry )										{ m_Country = nCountry;}

	string GetNameTerminated( );
	uint32_t GetPing( bool LCPing );	
	bool IsSpammer( );
	void PushMessage( string message );

	void AddLoadInGameData( BYTEARRAY nLoadInGameData )								{ m_LoadInGameData.push( nLoadInGameData ); }

	// processing functions

	virtual bool Update( void *fd );
	virtual void ExtractPackets( );
	virtual void ProcessPackets( );

	// other functions

	virtual void Send( BYTEARRAY data );
	virtual void EventGProxyReconnect( CTCPSocket *NewSocket, uint32_t LastPacket );
};

#endif
