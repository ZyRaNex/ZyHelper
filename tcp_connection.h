#pragma once

#ifndef TCP_CONNECTION_H_
#define TCP_CONNECTION_H_

#include <Windows.h>
#include <string>
#include <mutex>

#define PORT_STR "2206"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


class TCPConnection
{
public:
	TCPConnection();

	int Init();
	int Listen();
	int Exit();
	
	bool IsReady();
	DWORD StartupTime;
	~TCPConnection();

	//bool () { return ElementAt(, 4); };


	bool Active() { return ElementAt(1, 0); };
	bool ImBarb() { return ElementAt(2, 0); };
	bool ImMonk() { return ElementAt(3, 0); };
	bool ImWizard() { return ElementAt(4, 0); };
	bool ImNecro() { return ElementAt(5, 0); };
	bool ImDh() { return ElementAt(6, 0); };
	bool ImSader() { return ElementAt(7, 0); };

	bool ConventionLight() { return ElementAt(1, 1); };
	bool ConventionArcane() { return ElementAt(2, 1); };
	bool ConventionCold() { return ElementAt(3, 1); };
	bool ConventionFire() { return ElementAt(4, 1); };
	bool BlackholeBuffActive() { return ElementAt(5, 1); };
	bool CastArcaneBlast() { return ElementAt(6, 1); };

	bool InARift() { return ElementAt(1, 2); };
	bool DontCastLand() { return ElementAt(2, 2); };
	bool CastBlindingFlash() { return ElementAt(3, 2); };
	bool CastCommandSkeletons() { return ElementAt(4, 2); };

	bool CastIp() { return ElementAt(1, 3); };
	bool CastSim() { return ElementAt(2, 3); };
	bool DontCastSim() { return ElementAt(3, 3); };
	bool CastFalter() { return ElementAt(4, 3); };
	bool CastBerserker() { return ElementAt(5, 3); };
	bool CastSprint() { return ElementAt(6, 3); };
	bool CastEpiphany() { return ElementAt(7, 3); };
	
	bool CastWc() { return ElementAt(1, 4); };
	bool CastMantraHealing() { return ElementAt(2, 4); };
	bool CastSweepingWind() { return ElementAt(3, 4); };
	bool CastBoh() { return ElementAt(4, 4); };
	bool CastMantraConviction() { return ElementAt(5, 4); };
	bool CastLotd() { return ElementAt(6, 4); };
	bool CastBoneArmor() { return ElementAt(7, 4); };

	bool CastPotion() { return ElementAt(1, 5); };
	bool CastStormArmor() { return ElementAt(2, 5); };
	bool CastMagicWeapon() { return ElementAt(3, 5); };
	bool CastVengeance() { return ElementAt(4, 5); };
	bool CastRainOfVengeance() { return ElementAt(5, 5); };
	bool CastPreparation() { return ElementAt(6, 5); };
	bool CastSkeleMages() { return ElementAt(7, 5); };

	bool NeedToMove() { return ElementAt(1, 6); };
	bool CastExplosiveBlast() { return ElementAt(2, 6); };
	bool CastBloodNova() { return ElementAt(3, 6); };

	bool ElementAt(unsigned  i, unsigned j);
	std::string content;
	std::mutex tcpmutex;
	bool Running;

private:
	
	char text[256];
	int error_code;
	SOCKET acceptSocket;
	SOCKET connectedSocket;
	SOCKADDR_IN addr;
};


#endif  // TCP_CONNECTION_H_