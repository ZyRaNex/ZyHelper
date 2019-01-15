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

	bool CastIp() { return ElementAt(1, 3); };
	bool WarCryOnCooldown() { return ElementAt(2, 3); };
	bool NecroInWCRange() { return ElementAt(3, 3); };
	bool CastFalter() { return ElementAt(4, 3); };
	bool CastBerserker() { return ElementAt(5, 3); };
	bool CastSprint() { return ElementAt(6, 3); };
	bool EpiphanyOnCooldown() { return ElementAt(7, 3); };
	
	bool EpiphanyBuffActive() { return ElementAt(1, 4); };
	bool CastMantraHealing() { return ElementAt(2, 4); };
	bool CastSweepingWind() { return ElementAt(3, 4); };
	bool BohOnCooldown() { return ElementAt(4, 4); };
	bool CastMantraConviction() { return ElementAt(5, 4); };
	bool CastLotd() { return ElementAt(6, 4); };
	bool CastBoneArmor() { return ElementAt(7, 4); };

	bool CastPotion() { return ElementAt(1, 5); };
	bool CastStormArmor() { return ElementAt(2, 5); };
	bool CastMagicWeapon() { return ElementAt(3, 5); };
	bool CastVengeance() { return ElementAt(4, 5); };
	bool CastRainOfVengeance() { return ElementAt(5, 5); };
	bool CastPreparation() { return ElementAt(6, 5); };

	/*bool IPWizInRange() { return ElementAt(1, 0); };
	bool IPOnCooldown() { return ElementAt(2, 0); };
	bool WarCryOnCooldown() { return ElementAt(3, 0); };
	bool NecroInWCRange() { return ElementAt(4, 0); };
	bool IsActive() { return ElementAt(5, 0); };
	bool FalterOnCooldown() { return ElementAt(6, 0); };
	bool WizInRange() { return ElementAt(7, 0); };
	
	bool BerserkerOnCooldown() { return ElementAt(1, 1); };
	bool ImBarb() { return ElementAt(2, 1); };
	bool ImWizard() { return ElementAt(3, 1); };
	bool ImMonk() { return ElementAt(4, 1); };
	bool ImNecro() { return ElementAt(5, 1); };
	bool EpiphanyOnCooldown() { return ElementAt(6, 1); };
	bool MantraOfHealingOnCooldown() { return ElementAt(7, 1); };

	bool EnoughSpirit() { return ElementAt(1, 2); };
	bool WarCryBuffActive() { return ElementAt(2, 2); };
	bool BerserkerBuffActive() { return ElementAt(3, 2); };
	bool EpiphanyBuffActive() { return ElementAt(4, 2); };
	bool LotDOnCooldown() { return ElementAt(5, 2); };
	bool LotDBuffActive() { return ElementAt(6, 2); };
	bool EnoughFury() { return ElementAt(7, 2); };

	bool SprintOnCooldown() { return ElementAt(1, 3); };
	bool SprintBuffActive() { return ElementAt(2, 3); };
	bool RecastSweepingWind() { return ElementAt(3, 3); };
	bool BohOnCooldown() { return ElementAt(4, 3); };
	bool BoneArmorAlmostRunningOut() { return ElementAt(5, 3); };
	bool BoneArmorOnCooldown() { return ElementAt(6, 3); };
	bool Range25Enemies1() { return ElementAt(7, 3); };

	bool Range25Enemies5() { return ElementAt(1, 4); };
	bool UsePotion() { return ElementAt(2, 4); };
	bool PotionIsOnCooldown() { return ElementAt(3, 4); };
	bool ConventionLight() { return ElementAt(4, 4); };
	bool ConventionArcane() { return ElementAt(5, 4); };
	bool ConventionCold() { return ElementAt(6, 4); };
	bool ConventionFire() { return ElementAt(7, 4); };

	bool BlackholeBuffActive() { return ElementAt(1, 5); };
	bool StormArmorOnCooldown() { return ElementAt(2, 5); };
	bool StormArmorBuffActive() { return ElementAt(3, 5); };
	bool MagicWeaponOnCooldown() { return ElementAt(4, 5); };
	bool MagicWeaponBuffActive() { return ElementAt(5, 5); };
	bool BossIsSpawned() { return ElementAt(6, 5); };
	bool NecroInIPRange() { return ElementAt(7, 5); };

	bool NatBuffActive() { return ElementAt(1, 6); };
	bool ImDh() { return ElementAt(2, 6); };
	bool ImSader() { return ElementAt(3, 6); };
	bool VengeanceOnCooldown() { return ElementAt(4, 6); };
	bool VengeanceBuffActive() { return ElementAt(5, 6); };
	bool RainOfVengeanceOnCooldown() { return ElementAt(6, 6); };
	bool PreparationOnCooldown() { return ElementAt(7, 6); };

	bool PreparationDisciplineThreshold() { return ElementAt(1, 7); };*/

		

	bool ElementAt(unsigned  i, unsigned j);
	std::string content;
	std::mutex tcpmutex;

private:
	
	char text[256];
	int error_code;
	SOCKET acceptSocket;
	SOCKET connectedSocket;
	SOCKADDR_IN addr;
};


#endif  // TCP_CONNECTION_H_