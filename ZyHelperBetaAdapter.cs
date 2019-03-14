using System.Globalization;
using Turbo.Plugins.Default;
using System.Linq;
using SharpDX.DirectInput;

using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Collections.Generic;

namespace Turbo.Plugins.Zy
{
    public class ZyHelperBetaAdapter : BasePlugin, IInGameTopPainter, IKeyEventHandler
    {

        public TopLabelDecorator logoDecorator { get; set; }
        TcpClient client;
        NetworkStream stream;
        private readonly int[] _skillOrder = { 2, 3, 4, 5, 0, 1 };
        public bool Show { get; set; }
        public IKeyEvent ToggleKeyEvent { get; set; }
        public Key HotKey
        {
            get { return ToggleKeyEvent.Key; }
            set { ToggleKeyEvent = Hud.Input.CreateKeyEvent(true, value, false, false, false); }
        }
        private StringBuilder textBuilder;
        private IFont Font;
        public ZyHelperBetaAdapter()
        {
            Enabled = true;
        }

        public override void Load(IController hud)
        {
            base.Load(hud);

            string textFunc() => "ZH";
            logoDecorator = new TopLabelDecorator(Hud)
            {
                TextFont = Hud.Render.CreateFont("tahoma", 8, 255, 146, 99, 6, true, false, false),
                TextFunc = textFunc,
            };

            HotKey = Key.F11;
            Show = false;
            Font = Hud.Render.CreateFont("tahoma", 8, 255, 146, 99, 6, true, false, false);
            textBuilder = new StringBuilder();

            int port = 2206;
            client = new TcpClient("localhost", port);
            if (Enabled) stream = client.GetStream();


            byte[] myWriteBuffer = Encoding.ASCII.GetBytes("Starting connection");
            if (Enabled) stream.Write(myWriteBuffer, 0, myWriteBuffer.Length);
            if (Enabled) stream.Flush();
        }

        public void OnKeyEvent(IKeyEvent keyEvent)
        {
            if (keyEvent.IsPressed && ToggleKeyEvent.Matches(keyEvent))
            {
                Show = !Show;
            }
        }

        public static Byte Set(byte input, int pos, bool value)
        {
            Byte result = input;
            if (value)
            {
                result = (byte)(input | (1 << pos));
            }
            else
            {
                result = (byte)(input & ~(1 << pos));
            }
            return result;
        }


        public void PaintTopInGame(ClipState clipState)
        {
            bool IPOnCooldown = false;
            bool WarCryOnCooldown = false;
            float NecroDistance = 0.0f;
            float WizDistance = 0.0f;
            float MonkDistance = 0.0f;
            float ChargeBarbDistance = 0.0f;
            bool Active = false;
            bool FalterOnCooldown = false;
            bool BerserkerOnCooldown = false;
            bool ImBarb = false;
            bool ImWizard = false;
            bool ImMonk = false;
            bool ImNecro = false;
            bool EpiphanyOnCooldown = false;
            bool MantraOfHealingOnCooldown = false;
            bool WarCryBuffActive = false;
            bool BerserkerBuffActive = false;
            bool EpiphanyBuffActive = false;
            bool LotDOnCooldown = false;
            bool LotDBuffActive = false;
            bool SprintOnCooldown = false;
            bool SprintBuffActive = false;
            bool WizardIngame = false;
            bool MonkIngame = false;
            bool NecroIngame = false;
            bool BarbIngame = false;
            bool RecastSweepingWind = false;
            bool BohOnCooldown = false;
            bool BoneArmorAlmostRunningOut = false;
            bool BoneArmorOnCooldown = false;
            bool ConventionLight = false;
            bool ConventionArcane = false;
            bool ConventionCold = false;
            bool ConventionFire = false;
            bool BlackholeBuffActive = false;
            bool StormArmorOnCooldown = false;
            bool StormArmorBuffActive = false;
            bool MagicWeaponOnCooldown = false;
            bool MagicWeaponBuffActive = false;
            bool BossIsSpawned = false;
            bool NatBuffActive = false;
            bool ImDh = false;
            bool ImSader = false;
            bool VengeanceBuffActive = false;
            bool VengeanceOnCooldown = false;
            bool RainOfVengeanceOnCooldown = false;
            bool PreparationOnCooldown = false;
            bool ChilanikBuff = false;
            bool BarbHasValidActor = false;
            int  NumberOfSkeleMages = 0;
            bool EliteInRange = false;
            bool SimBuffActive = false;
            bool SimOnCooldown = false;
            bool RiftJustStarted = false;
            bool ChannelingRunningOut = false;
            bool InARift = false;
            bool ImZnec = false;
            bool ArchonBuffActive = false;
            bool ArcaneBlastOnCooldown = false;

            bool CastIp = false;
            bool CastWc = false;
            bool CastFalter = false;
            bool CastBerserker = false;
            bool CastSprint = false;
            bool CastEpiphany = false;
            bool CastMantraHealing = false;
            bool CastSweepingWind = false;
            bool CastBoh = false;
            bool CastMantraConviction = false;
            bool CastLotd = false;
            bool CastBoneArmor = false;
            bool CastPotion = false;
            bool CastStormArmor = false;
            bool CastMagicWeapon = false;
            bool CastVengeance = false;
            bool CastRainOfVengeance = false;
            bool CastPreparation = false;
            bool CastSkeleMages = false;
            bool CastSim = false;
            bool ForceMove = false;
            bool CastArcaneBlast = false;


            bool IpEquipped = false;
            bool WcEquipped = false;
            bool FalterEquipped = false;
            bool BerserkerEquipped = false;
            bool SprintEquipped = false;
            bool EpiphanyEquipped = false;
            bool MantraHealingEquipped = false;
            bool SweepingWindEquipped = false;
            bool BohEquipped = false;
            bool MantraConvictionEquipped = false;
            bool LotdEquipped = false;
            bool BoneArmorEquipped = false;
            bool StormArmorEquipped = false;
            bool MagicWeaponEquipped = false;
            bool VengeanceEquipped = false;
            bool RainOfVengeanceEquipped = false;
            bool PreparationEquipped = false;
            bool SkeleMagesEquipped = false;
            bool SimEquipped = false;
            bool ArchonEquipped = false;


            IWorldCoordinate MyPosition = Hud.Game.Players.First().FloorCoordinate;
            IWorldCoordinate WizPosition = Hud.Game.Players.First().FloorCoordinate;
            IWorldCoordinate MonkPosition = Hud.Game.Players.First().FloorCoordinate;
            IWorldCoordinate NecroPosition = Hud.Game.Players.First().FloorCoordinate;
            IWorldCoordinate ChargeBarbPosition = Hud.Game.Players.First().FloorCoordinate;

            BossIsSpawned = (Hud.Game.AliveMonsters.Count(m => m.SnoMonster.Priority == MonsterPriority.boss) > 0);

            int Range15Enemies = 0;
            int Range25Enemies = 0;
            int Range75Enemies = 0;

            var monsters2 = Hud.Game.AliveMonsters.Where(m => ((m.SummonerAcdDynamicId == 0 && m.IsElite) || !m.IsElite));
            foreach (var monster in monsters2)
            {
                if (monster.FloorCoordinate.XYDistanceTo(Hud.Game.Me.FloorCoordinate) <= 15) Range15Enemies++;
                if (monster.FloorCoordinate.XYDistanceTo(Hud.Game.Me.FloorCoordinate) <= 25) Range25Enemies++;
                if (monster.FloorCoordinate.XYDistanceTo(Hud.Game.Me.FloorCoordinate) <= 75) Range75Enemies++;

                
                if ((monster.Rarity == ActorRarity.Unique) ||
                    (monster.Rarity == ActorRarity.Champion) ||
                    (monster.Rarity == ActorRarity.Rare) ||
                    (monster.SnoMonster.Priority == MonsterPriority.boss) ||
                    (monster.SnoActor.Sno == ActorSnoEnum._x1_pand_ext_ordnance_tower_shock_a))//shocktower
                {
                    if (monster.FloorCoordinate.XYDistanceTo(Hud.Game.Me.FloorCoordinate) <= 70)
                    {
                        EliteInRange = true;
                    }
                }
            }

            foreach (var player in Hud.Game.Players)//me
            {
                if (!player.IsMe) continue;
                MyPosition = player.FloorCoordinate;

                foreach (var i in _skillOrder)
                {
                    var skill = player.Powers.SkillSlots[i];
                    if (skill == null ) continue;
                    //barb
                    if (skill.SnoPower.Sno == 79528)//Barbarian_IgnorePain
                    {
                        IPOnCooldown = skill.IsOnCooldown;
                        IpEquipped = true;
                    }
                    if (skill.SnoPower.Sno == 375483)// Barbarian_WarCry
                    {
                        WarCryBuffActive = skill.BuffIsActive;
                        WarCryOnCooldown = skill.IsOnCooldown;
                        WcEquipped = true;
                        var buff = player.Powers.GetBuff(318821); //ChilaniksChain 318821 - ItemPassive_Unique_Ring_639_x1
                        if ((buff == null) || (buff.IconCounts[0] <= 0)) continue;
                        ChilanikBuff = buff.TimeLeftSeconds[1] > 0.0;
                        
                    }
                    if (skill.SnoPower.Sno == 79077)// Barbarian_ThreateningShout
                    {
                        FalterOnCooldown = skill.IsOnCooldown;
                        FalterEquipped = true;
                    }
                    if (skill.SnoPower.Sno == 79607)// Barbarian_WrathOfTheBerserker
                    {
                        BerserkerBuffActive = skill.BuffIsActive;
                        BerserkerOnCooldown = skill.IsOnCooldown;
                        BerserkerEquipped = true;
                    }
                    if (skill.SnoPower.Sno == 78551)// Barbarian_Sprint
                    {
                        SprintBuffActive = skill.BuffIsActive;
                        SprintOnCooldown = skill.IsOnCooldown;
                        SprintEquipped = true;
                    }

                    //monk
                    if (skill.SnoPower.Sno == 312307)//Monk_Epiphany
                    {
                        EpiphanyEquipped = true;
                        EpiphanyOnCooldown = skill.IsOnCooldown;
                        var buff = skill.Buff;
                        if ((buff == null) || (buff.IconCounts[0] <= 0)) continue;
                        EpiphanyBuffActive = buff.TimeLeftSeconds[0] > 0.5;
                    }
                    if (skill.SnoPower.Sno == 373143)//Monk_MantraOfHealing
                    {
                        MantraOfHealingOnCooldown = skill.IsOnCooldown;
                        MantraHealingEquipped = true;
                    }

                    if (skill.SnoPower.Sno == 96090)//Monk_SweepingWind
                    {
                        SweepingWindEquipped = true;
						var buff = skill.Buff;
						if ((buff == null) || (buff.IconCounts[0] <= 0)) 
						{
							RecastSweepingWind = true;
							continue;
						}
						RecastSweepingWind = skill.Buff.TimeLeftSeconds[0] < 1.0;
                        
                    }

                    if (skill.SnoPower.Sno == 69130)//Monk_BreathOfHeaven
                    {
                        BohOnCooldown = skill.IsOnCooldown;
                        BohEquipped = true;
                    }

                    if (skill.SnoPower.Sno == 375088)//Monk_MantraOfConviction
                    {
                        MantraConvictionEquipped = true;
                    }

                    //wizard
                    if (skill.SnoPower.Sno == 74499)//Wizard_StormArmor
                    {
                        StormArmorBuffActive = skill.BuffIsActive;
                        StormArmorOnCooldown = skill.IsOnCooldown;
                        StormArmorEquipped = true;
                    }

                    if (skill.SnoPower.Sno == 76108)//Wizard_MagicWeapon
                    {
                        MagicWeaponBuffActive = skill.BuffIsActive;
                        MagicWeaponOnCooldown = skill.IsOnCooldown;
                        MagicWeaponEquipped = true;
                    }

                    if (skill.SnoPower.Sno == 134872)//Wizard_Archon
                    {
                        var buff = player.Powers.GetBuff(Hud.Sno.SnoPowers.Wizard_Archon.Sno);
                        if (buff != null)
                        {
                            ArchonBuffActive = buff.TimeLeftSeconds[2] > 0.1;
                        }

                        var skill2 = player.Powers.SkillSlots[2];
                        ArcaneBlastOnCooldown = skill2.IsOnCooldown;
                        ArchonEquipped = true;
                    }
                    

                    //necro
                    if (skill.SnoPower.Sno == 466857)//Necromancer_BoneArmor
                    {
                        BoneArmorOnCooldown = skill.IsOnCooldown;
                        BoneArmorEquipped = true;
                        if (skill.Buff != null)
                        {
                            BoneArmorAlmostRunningOut = skill.Buff.TimeLeftSeconds[0] < 30.0;
                        }
                       
                    }
					if (skill.SnoPower.Sno == 465839)//Necromancer_LandOfTheDead { get; }
                    {
                        //LotDBuffActive = skill.BuffIsActive;
                        LotDOnCooldown = skill.IsOnCooldown;
                        LotdEquipped = true;
						var buff = skill.Buff;
                        if ((buff == null) || (buff.IconCounts[0] <= 0)) continue;
                        LotDBuffActive = buff.TimeLeftSeconds[0] > 0.5;
                    }
                    
                    if (skill.SnoPower.Sno == 462089)//Necromancer_SkeletalMage { get; }
                    {
                        SkeleMagesEquipped = true;
                        HashSet<ActorSnoEnum> SkeletonMageActorSNOs = new HashSet<ActorSnoEnum>
                        {
                            ActorSnoEnum._p6_necro_skeletonmage_a, // Skeleton Mage - No Rune
                            ActorSnoEnum._p6_necro_skeletonmage_b, // Skeleton Mage - Gift of Death
                            ActorSnoEnum._p6_necro_skeletonmage_e, // Skeleton Mage - Contamination
                            ActorSnoEnum._p6_necro_skeletonmage_f_archer, // Skeleton Mage - Archer
                            ActorSnoEnum._p6_necro_skeletonmage_c, // Skeleton Mage - Singularity
                           ActorSnoEnum. _p6_necro_skeletonmage_d  // Skeleton Mage - Life Support
                        };
                        var SkeletonMageActors = Hud.Game.Actors.Where(EachActor => SkeletonMageActorSNOs.Contains(EachActor.SnoActor.Sno) && // Find out which are skeleton mages actors
                                        EachActor.SummonerAcdDynamicId == Hud.Game.Me.SummonerId); // Then find out if they are summoned by the player
                        NumberOfSkeleMages = SkeletonMageActors.Count(); // And then count how many are found
                    }
                    
                    if (skill.SnoPower.Sno == 465350)//Necromancer_Simulacrum { get; }
                    {
                        SimOnCooldown = skill.IsOnCooldown;
                        SimEquipped = true;
                        var buff = skill.Buff;
                        if ((buff == null) || (buff.IconCounts[0] <= 0)) continue;
                        SimBuffActive = buff.TimeLeftSeconds[0] > 0.0;
                    }


                    //dh
                    if (skill.SnoPower.Sno == 302846)//DemonHunter_Vengeance { get; }
                    {
						VengeanceOnCooldown = skill.IsOnCooldown;
                        VengeanceEquipped = true;
                        var buff = skill.Buff;
                        if ((buff == null) || (buff.IconCounts[0] <= 0)) continue;
                        VengeanceBuffActive = buff.TimeLeftSeconds[0] > 0.5;
                        
                    }
                    if (skill.SnoPower.Sno == 130831)//DemonHunter_RainOfVengeance { get; }
                    {
                        RainOfVengeanceOnCooldown = skill.IsOnCooldown;
                        RainOfVengeanceEquipped = true;
                    }
                    if (skill.SnoPower.Sno == 129212)//DemonHunter_Preparation { get; }
                    {
                        PreparationOnCooldown = skill.IsOnCooldown;
                        PreparationEquipped = true;
                    }
                }
            }
        
            foreach (var player in Hud.Game.Players)//others
            {

                if (player.HeroClassDefinition.HeroClass == HeroClass.Barbarian)
                {
                    if (player.IsMe)
                    {
                        ImBarb = true;
                    }
                    else
                    {
                        BarbIngame = true;
                        BarbHasValidActor = player.HasValidActor;
                        var EfficaciousToxin = player.Powers.GetBuff(403461);
                        if (EfficaciousToxin == null || !EfficaciousToxin.Active)
                        {
                            //chargebarb
                            ChargeBarbPosition = player.FloorCoordinate;
                        }
                        else
                        {
                            //zbarb
                        }
                    }
                }
                if (player.HeroClassDefinition.HeroClass == HeroClass.Wizard)
                {
                    if (player.IsMe)
                    {
                        ImWizard = true;
                        IBuff ConventionBuff = player.Powers.GetBuff(430674);
                        if ((ConventionBuff == null) || (ConventionBuff.IconCounts[0] <= 0)) continue;

                        ConventionLight = ConventionBuff.IconCounts[5] != 0;
                        ConventionArcane = ConventionBuff.IconCounts[1] != 0;
                        ConventionCold = ConventionBuff.IconCounts[2] != 0;
                        ConventionFire = ConventionBuff.IconCounts[3] != 0;

                        IBuff BlackholeBuff = player.Powers.GetBuff(243141);
                        if (BlackholeBuff == null) continue;
                        if (BlackholeBuff.IconCounts[5] <= 0) continue;

                        BlackholeBuffActive = (BlackholeBuff.TimeLeftSeconds[5] > 3.5);
                    }
                    else
                    {
                        WizPosition = player.FloorCoordinate;
                        WizardIngame = true;
                    }
                }
                if (player.HeroClassDefinition.HeroClass == HeroClass.Monk)
                {
                    if (player.IsMe)
                    {
                        ImMonk = true;
                    }
                    else
                    {
                        MonkPosition = player.FloorCoordinate;
                        MonkIngame = true;
                    }
                }
                if (player.HeroClassDefinition.HeroClass == HeroClass.Necromancer)
                {
                    if (player.IsMe)
                    {
                        ImNecro = true;

                        var EfficaciousToxin = player.Powers.GetBuff(403461);
                        if (EfficaciousToxin == null || !EfficaciousToxin.Active)
                        {
                            //rat
                            ImZnec = false;
                        }
                        else
                        {
                            //znec
                            ImZnec = true;
                        }
                    }
                    else
                    {
                        NecroPosition = player.FloorCoordinate;
                        NecroIngame = player.HasValidActor;
                    }
                }
                if (player.HeroClassDefinition.HeroClass == HeroClass.DemonHunter)
                {
                    if (player.IsMe)
                    {
                        ImDh = true;
                        IBuff NatBuff = player.Powers.GetBuff(434964);
                        if (NatBuff == null) continue;
                        NatBuffActive = (NatBuff.TimeLeftSeconds[1] > 0.5);
                    }
                    else
                    {
                        //
                    }
                }
                if (player.HeroClassDefinition.HeroClass == HeroClass.Crusader)
                {
                    if (player.IsMe)
                    {
                        ImSader = true;
                    }
                    else
                    {
                        //
                    }
                }

                
            }

            WizDistance = WizPosition.XYDistanceTo(MyPosition);
            MonkDistance = MonkPosition.XYDistanceTo(MyPosition);
            NecroDistance = NecroPosition.XYDistanceTo(MyPosition);
            ChargeBarbDistance = ChargeBarbPosition.XYDistanceTo(MyPosition);

            var Channelingbuff = Hud.Game.Me.Powers.GetBuff(266258);
            if ((Channelingbuff != null) && (Channelingbuff.IconCounts[0] > 0))
            {
                ChannelingRunningOut = (Channelingbuff.TimeLeftSeconds[0] < 2.0d);
            }

            var TargetedMonster = Hud.Game.SelectedMonster2 ?? Hud.Game.SelectedMonster1;
            bool EliteTargeted = false;
            if (TargetedMonster != null)
            {
                //EliteTargeted = TargetedMonster.IsElite;
                EliteTargeted = (TargetedMonster.Rarity == ActorRarity.Unique) ||
                                (TargetedMonster.Rarity == ActorRarity.Champion) ||
                                (TargetedMonster.Rarity == ActorRarity.Rare) ||
                                (TargetedMonster.SnoMonster.Priority == MonsterPriority.boss) ||
                                (TargetedMonster.SnoActor.Sno == ActorSnoEnum._x1_pand_ext_ordnance_tower_shock_a);//shocktower
            }


            InARift = (Hud.Game.SpecialArea == SpecialArea.Rift || Hud.Game.SpecialArea == SpecialArea.GreaterRift);
            Active = true;
            Active = Active && Hud.Game.IsInGame;
            Active = Active && !Hud.Game.IsLoading;
            Active = Active && !Hud.Game.IsInTown;
            Active = Active && !Hud.Game.Me.IsDead;
            Active = Active && !Hud.Render.UiHidden;
            Active = Active && Hud.Game.MapMode == MapMode.Minimap;
            Active = Active && (Hud.Game.Me.AnimationState != AcdAnimationState.CastingPortal && Hud.Game.Me.AnimationState != AcdAnimationState.Dead);

            bool GRGuardianIsDead = false;
            var riftQuest = Hud.Game.Quests.FirstOrDefault(q => q.SnoQuest.Sno == 337492) ??
                            Hud.Game.Quests.FirstOrDefault(q => q.SnoQuest.Sno == 382695);
            if (riftQuest != null)
            {
                if (Hud.Game.Monsters.Any(m => m.Rarity == ActorRarity.Boss && !m.IsAlive))
                {
                    GRGuardianIsDead = true;
                }
                else
                {
                    GRGuardianIsDead = (riftQuest.QuestStepId == 34 || riftQuest.QuestStepId == 46);
                };
            }

            Active = Active && !GRGuardianIsDead;


            double Cooldown = (Hud.Game.Me.Powers.HealthPotionSkill.CooldownFinishTick - Hud.Game.CurrentGameTick) / 60d;
            bool PotionIsOnCooldown = Cooldown <= 30 && Cooldown >= 0 ? true : false;

            bool WizInIpRange;
            if (WizardIngame && MonkIngame)
            {
                if ((WizPosition.XYDistanceTo(MonkPosition) > 50) || !MonkIngame)
                {
                    WizInIpRange = (WizDistance <= 45);
                }
                else
                {
                    WizInIpRange = (Math.Max(WizDistance, MonkDistance) <= 45);
                }

                CastIp = !IPOnCooldown && IpEquipped && (!BossIsSpawned && WizInIpRange  ||
                           BossIsSpawned && (NecroDistance <= 45));
                CastFalter = FalterEquipped && !FalterOnCooldown && (!BossIsSpawned && (WizDistance <= 20)  ||
                           BossIsSpawned);
                CastWc = WcEquipped && !WarCryOnCooldown && (!ChilanikBuff || NecroDistance <= 100);
            }
            else
            {
                CastIp = !IPOnCooldown && IpEquipped && (Hud.Game.NumberOfPlayersInGame == (Hud.Game.Players.Where(p => p.CentralXyDistanceToMe <= 45)).Count());
                CastFalter = FalterEquipped && !FalterOnCooldown;
                CastWc = (WcEquipped && !WarCryOnCooldown && (!ChilanikBuff || (Hud.Game.NumberOfPlayersInGame == (Hud.Game.Players.Where(p => p.CentralXyDistanceToMe <= 45)).Count())));
            }
            
            


            CastBerserker = BerserkerEquipped && !BerserkerOnCooldown && !BerserkerBuffActive;
            CastSprint = SprintEquipped && !SprintOnCooldown && Hud.Game.Me.Stats.ResourceCurFury >= (Hud.Game.Me.Stats.ResourceMaxFury / 2.0) && !SprintBuffActive;
            CastEpiphany = EpiphanyEquipped && !EpiphanyOnCooldown && !EpiphanyBuffActive;
            CastMantraHealing = MantraHealingEquipped && !MantraOfHealingOnCooldown && Hud.Game.Me.Stats.ResourceCurSpirit >= (Hud.Game.Me.Stats.ResourceMaxSpirit / 2.0);
            CastSweepingWind = SweepingWindEquipped && RecastSweepingWind && Hud.Game.Me.Stats.ResourceCurSpirit >= (Hud.Game.Me.Stats.ResourceMaxSpirit / 2.0);
            CastBoh = BohEquipped && !BohOnCooldown && ((Hud.Game.SpecialArea == SpecialArea.Rift) || BarbIngame && (ChargeBarbDistance <= 12) && BarbHasValidActor);
            CastMantraConviction = MantraConvictionEquipped && Hud.Game.Me.Stats.ResourceCurSpirit >= (Hud.Game.Me.Stats.ResourceMaxSpirit / 2.0);
            CastLotd = LotdEquipped && !LotDOnCooldown && !LotDBuffActive && (Range75Enemies >= 1);
            //CastBoneArmor = BoneArmorEquipped && (((BoneArmorAlmostRunningOut && (Range25Enemies >= 1)) ||
            //                  (!BoneArmorAlmostRunningOut && (Range25Enemies >= 5))) &&
            //                  !BoneArmorOnCooldown);
            CastBoneArmor = BoneArmorEquipped && (Range25Enemies >= 1) && !BoneArmorOnCooldown;
            RiftJustStarted = (((Hud.Game.CurrentTimedEventEndTick - (double)Hud.Game.CurrentGameTick) / 60.0d) > 890.0d);
            CastSim = InARift && SimEquipped && !SimOnCooldown && (!(Hud.Game.Me.Stats.ResourceMaxEssence > 450) || ChannelingRunningOut);//have sim because of reservoir
            CastPotion = Hud.Game.Me.Defense.HealthCur <= (Hud.Game.Me.Defense.HealthMax * 0.35) && !PotionIsOnCooldown;
            CastStormArmor = StormArmorEquipped && !StormArmorOnCooldown && !StormArmorBuffActive;
            CastMagicWeapon = MagicWeaponEquipped && !MagicWeaponOnCooldown && !MagicWeaponBuffActive;
            CastVengeance = VengeanceEquipped && !VengeanceOnCooldown && !VengeanceBuffActive;
            CastRainOfVengeance = RainOfVengeanceEquipped && !RainOfVengeanceOnCooldown && !NatBuffActive;
            CastPreparation = PreparationEquipped && !PreparationOnCooldown && !(Hud.Game.Me.Stats.ResourceCurDiscipline >= (Hud.Game.Me.Stats.ResourceMaxDiscipline - 30));
            ForceMove = InARift && !ImZnec && (Hud.Game.Me.AnimationState == AcdAnimationState.Idle || Hud.Game.Me.AnimationState == AcdAnimationState.Casting);
            CastArcaneBlast = ArchonBuffActive && ArchonEquipped && !ArcaneBlastOnCooldown && (Range15Enemies > 0);

            CastSkeleMages = InARift && SkeleMagesEquipped && (Hud.Game.Me.Stats.ResourceCurEssence >= Hud.Game.Me.Stats.ResourceMaxEssence*0.95) && (EliteInRange && EliteTargeted || !EliteInRange && (NumberOfSkeleMages < 10));
            Byte[] Bytes = new Byte[8];

            Bytes[0] = Set(Bytes[0], 0, true);
            Bytes[0] = Set(Bytes[0], 1, Active);
            Bytes[0] = Set(Bytes[0], 2, ImBarb);
            Bytes[0] = Set(Bytes[0], 3, ImMonk);
            Bytes[0] = Set(Bytes[0], 4, ImWizard);
            Bytes[0] = Set(Bytes[0], 5, ImNecro);
            Bytes[0] = Set(Bytes[0], 6, ImDh);
            Bytes[0] = Set(Bytes[0], 7, ImSader);

            Bytes[1] = Set(Bytes[1], 0, true);
            Bytes[1] = Set(Bytes[1], 1, ConventionLight);
            Bytes[1] = Set(Bytes[1], 2, ConventionArcane);
            Bytes[1] = Set(Bytes[1], 3, ConventionCold);
            Bytes[1] = Set(Bytes[1], 4, ConventionFire);
            Bytes[1] = Set(Bytes[1], 5, BlackholeBuffActive);
            Bytes[1] = Set(Bytes[1], 6, CastArcaneBlast);
            Bytes[1] = Set(Bytes[1], 7, false);

            Bytes[2] = Set(Bytes[2], 0, true);
            Bytes[2] = Set(Bytes[2], 1, CastIp);
            Bytes[2] = Set(Bytes[2], 2, WarCryBuffActive);
            Bytes[2] = Set(Bytes[2], 3, BerserkerBuffActive);
            Bytes[2] = Set(Bytes[2], 4, EpiphanyBuffActive);
            Bytes[2] = Set(Bytes[2], 5, LotDOnCooldown);
            Bytes[2] = Set(Bytes[2], 6, LotDBuffActive);
            Bytes[2] = Set(Bytes[2], 7, Hud.Game.Me.Stats.ResourceCurFury >= (Hud.Game.Me.Stats.ResourceMaxFury / 2.0));

            Bytes[3] = Set(Bytes[3], 0, true);
            Bytes[3] = Set(Bytes[3], 1, CastIp);
            Bytes[3] = Set(Bytes[3], 2, CastSim);
            Bytes[3] = Set(Bytes[3], 3, RiftJustStarted);
            Bytes[3] = Set(Bytes[3], 4, CastFalter);
            Bytes[3] = Set(Bytes[3], 5, CastBerserker);
            Bytes[3] = Set(Bytes[3], 6, CastSprint);
            Bytes[3] = Set(Bytes[3], 7, CastEpiphany);

            Bytes[4] = Set(Bytes[4], 0, true);
            Bytes[4] = Set(Bytes[4], 1, CastWc); 
            Bytes[4] = Set(Bytes[4], 2, CastMantraHealing);
            Bytes[4] = Set(Bytes[4], 3, CastSweepingWind);
            Bytes[4] = Set(Bytes[4], 4, CastBoh);
            Bytes[4] = Set(Bytes[4], 5, CastMantraConviction);
            Bytes[4] = Set(Bytes[4], 6, CastLotd);
            Bytes[4] = Set(Bytes[4], 7, CastBoneArmor);

            Bytes[5] = Set(Bytes[5], 0, true);
            Bytes[5] = Set(Bytes[5], 1, CastPotion);
            Bytes[5] = Set(Bytes[5], 2, CastStormArmor);
            Bytes[5] = Set(Bytes[5], 3, CastMagicWeapon);
            Bytes[5] = Set(Bytes[5], 4, CastVengeance);
            Bytes[5] = Set(Bytes[5], 5, CastRainOfVengeance);
            Bytes[5] = Set(Bytes[5], 6, CastPreparation);
            Bytes[5] = Set(Bytes[5], 7, CastSkeleMages);

            Bytes[6] = Set(Bytes[6], 0, true);
            Bytes[6] = Set(Bytes[6], 1, ForceMove);

            Bytes[7] = Set(Bytes[7], 0, true);

            if (Enabled) stream.Write(Bytes, 0, Bytes.Length);
            System.Threading.Thread.Sleep(2);

            if (Hud.Render.UiHidden) return;
            float x = -Hud.Window.Size.Width * 0.001f;
            float y = Hud.Window.Size.Height * 0.965f;

            logoDecorator.Paint(x, y, 30.0f, 30.0f, HorizontalAlign.Center);

            if (Show)
            {
                float XPos = Hud.Window.Size.Width * 0.01f;
                float YPos = Hud.Window.Size.Height * 0.665f;
                textBuilder.Clear();

                Active = true;
                Active = Active && Hud.Game.IsInGame;
                Active = Active && !Hud.Game.IsPaused;
                Active = Active && !Hud.Game.IsLoading;
                Active = Active && !Hud.Game.IsInTown;
                Active = Active && !Hud.Game.Me.IsDead;
                Active = Active && !Hud.Render.UiHidden;
                Active = Active && Hud.Game.MapMode == MapMode.Minimap;
                Active = Active && (Hud.Game.Me.AnimationState != AcdAnimationState.CastingPortal && Hud.Game.Me.AnimationState != AcdAnimationState.Dead);
                Active = Active && (Hud.Game.SpecialArea == SpecialArea.Rift || Hud.Game.SpecialArea == SpecialArea.GreaterRift);

                textBuilder.AppendFormat("IsInGame: {0}", Hud.Game.IsInGame);
                textBuilder.AppendLine();
                textBuilder.AppendFormat("IsPaused: {0}", Hud.Game.IsPaused);
                textBuilder.AppendLine();
                textBuilder.AppendFormat("IsLoading: {0}", Hud.Game.IsLoading);
                textBuilder.AppendLine();
                textBuilder.AppendFormat("IsDead: {0}", Hud.Game.Me.IsDead);
                textBuilder.AppendLine();
                textBuilder.AppendFormat("UiHidden: {0}", Hud.Render.UiHidden);
                textBuilder.AppendLine();
                textBuilder.AppendFormat("Minimap: {0}", Hud.Game.MapMode == MapMode.Minimap);
                textBuilder.AppendLine();
                textBuilder.AppendFormat("dead or portal: {0}", (Hud.Game.Me.AnimationState != AcdAnimationState.CastingPortal && Hud.Game.Me.AnimationState != AcdAnimationState.Dead));
                textBuilder.AppendLine();
                textBuilder.AppendFormat("in rift: {0}", (Hud.Game.SpecialArea == SpecialArea.Rift || Hud.Game.SpecialArea == SpecialArea.GreaterRift));
                textBuilder.AppendLine();
                
                

                var layout = Font.GetTextLayout(textBuilder.ToString());
                Font.DrawText(layout, XPos, YPos);
            }
        }

    }

}