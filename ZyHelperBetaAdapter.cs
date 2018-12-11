using System.Globalization;
using Turbo.Plugins.Default;
using System.Linq;
using SharpDX.DirectInput;

using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace Turbo.Plugins.Zy
{
    public class ZyHelperBetaAdapter : BasePlugin, IInGameTopPainter, IKeyEventHandler
    {


        TcpClient client;
        NetworkStream stream;
        private readonly int[] _skillOrder = { 2, 3, 4, 5, 0, 1 };

        bool ToggleOn;
        public IKeyEvent ToggleKeyEvent { get; set; }
        public Key HotKey
        {
            get { return ToggleKeyEvent.Key; }
            set { ToggleKeyEvent = Hud.Input.CreateKeyEvent(true, value, false, false, false); }
        }

        public ZyHelperBetaAdapter()
        {
            Enabled = true;
            ToggleOn = true;
        }

        public override void Load(IController hud)
        {
            base.Load(hud);

            HotKey = Key.F10;
            int port = 2206;
            client = new TcpClient("localhost", port);
            if (Enabled) stream = client.GetStream();


            byte[] myWriteBuffer = Encoding.ASCII.GetBytes("Are you receiving this message?");
            if (Enabled) stream.Write(myWriteBuffer, 0, myWriteBuffer.Length);
            if (Enabled) stream.Flush();
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

        public void OnKeyEvent(IKeyEvent keyEvent)
        {
            if (keyEvent.IsPressed && ToggleKeyEvent.Matches(keyEvent))
            {
                ToggleOn = !ToggleOn;
            }
        }

        public void PaintTopInGame(ClipState clipState)
        {
            if (Hud.Render.UiHidden) return;
            string send = "a";

            bool IPOnCooldown = false;
            bool WarCryOnCooldown = false;
            float NecroDistance = 0.0f;
            bool Active = false;
            bool FalterOnCooldown = false;
            float WizDistance = 0.0f;
            bool BerserkerOnCooldown = false;
            bool ImBarb = false;
            bool ImWizard = false;
            bool ImMonk = false;
            bool imNecro = false;
            bool EpiphanyOnCooldown = false;
            bool MantraOfHealingOnCooldown = false;
            bool WarCryBuffActive = false;
            bool BerserkerBuffActive = false;
            bool EpiphanyBuffActive = false;
            bool LotDOnCooldown = false;
            bool LotDBuffActive = false;
            bool SprintOnCooldown = false;
            bool SprintBuffActive = false;
            float MonkDistance = 0.0f;
            bool WizardIngame = false;
            bool MonkIngame = false;
            bool NecroIngame = false;
            bool RecastSweepingWind = false;
            bool BohOnCooldown = false;
            bool BoneArmorAlmostRunningOut = false;
            bool BoneArmorOnCooldown = false;
            bool Range25Enemies1 = false;
            bool Range25Enemies10 = false;

            IWorldCoordinate MyPosition = Hud.Game.Players.First().FloorCoordinate;
            IWorldCoordinate WizPosition = Hud.Game.Players.First().FloorCoordinate;
            IWorldCoordinate MonkPosition = Hud.Game.Players.First().FloorCoordinate;
            IWorldCoordinate NecroPosition = Hud.Game.Players.First().FloorCoordinate;

            int Range25Enemies = 0;

            var monsters2 = Hud.Game.AliveMonsters.Where(m => ((m.SummonerAcdDynamicId == 0 && m.IsElite) || !m.IsElite));
            foreach (var monster in monsters2)
            {
                if (monster.FloorCoordinate.XYDistanceTo(Hud.Game.Me.FloorCoordinate) <= 25) Range25Enemies++;
            }
            Range25Enemies1 = Range25Enemies >= 1;
            Range25Enemies10 = Range25Enemies >= 10;

            foreach (var player in Hud.Game.Players)//me
            {
                if (!player.IsMe) continue;
                MyPosition = player.FloorCoordinate;

                foreach (var i in _skillOrder)
                {
                    var skill = player.Powers.SkillSlots[i];
                    if (skill == null ) continue;

                    if (skill.SnoPower.Sno == 79528)//Barbarian_IgnorePain
                        IPOnCooldown = skill.IsOnCooldown;
                    if (skill.SnoPower.Sno == 375483)// Barbarian_WarCry
                    {
                        WarCryBuffActive = skill.BuffIsActive;
                        WarCryOnCooldown = skill.IsOnCooldown; 
                    }
                    if (skill.SnoPower.Sno == 79077)// Barbarian_ThreateningShout
                        FalterOnCooldown = skill.IsOnCooldown; 
                    if (skill.SnoPower.Sno == 79607)// Barbarian_WrathOfTheBerserker
                    {
                        BerserkerBuffActive = skill.BuffIsActive;
                        BerserkerOnCooldown = skill.IsOnCooldown; 
                    }
                    if (skill.SnoPower.Sno == 78551)// Barbarian_Sprint
                    {
                        SprintBuffActive = skill.BuffIsActive;
                        SprintOnCooldown = skill.IsOnCooldown;
                    }

                    if (skill.SnoPower.Sno == 312307)//Monk_Epiphany
                    {
                        EpiphanyBuffActive = skill.BuffIsActive;
                        EpiphanyOnCooldown = skill.IsOnCooldown;
                    }
                    if (skill.SnoPower.Sno == 373143)//Monk_MantraOfHealing
                        MantraOfHealingOnCooldown = skill.IsOnCooldown;

                    if (skill.SnoPower.Sno == 96090)//Monk_SweepingWind
                    {
                        if (skill.Buff != null)
                        {
                            RecastSweepingWind = skill.Buff.TimeLeftSeconds[0] < 1.0;
                        }
                    }

                    if (skill.SnoPower.Sno == 69130)//Monk_BreathOfHeaven
                        BohOnCooldown = skill.IsOnCooldown;

                    //NOT WORKING
                    //if (skill.SnoPower.Sno == 375088)//Monk_MantraOfConviction
                    //{
                    //}

                    if (skill.SnoPower.Sno == 465839)//Necromancer_LandOfTheDead
                    {
                        LotDBuffActive = skill.BuffIsActive;
                        LotDOnCooldown = skill.IsOnCooldown;
                    }

                    if (skill.SnoPower.Sno == 466857)//Necromancer_BoneArmor
                    {
                        BoneArmorOnCooldown = skill.IsOnCooldown;
                        if (skill.Buff != null)
                        {
                            BoneArmorAlmostRunningOut = skill.Buff.TimeLeftSeconds[0] < 15.0;
                        }
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
                }
                if (player.HeroClassDefinition.HeroClass == HeroClass.Wizard)
                {
                    if (player.IsMe)
                    {
                        ImWizard = true;
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
                        imNecro = true;
                    }
                    else
                    {
                        NecroPosition = player.FloorCoordinate;
                        NecroIngame = true;
                    }
                }
            }

            WizDistance = WizPosition.XYDistanceTo(MyPosition);
            MonkDistance = MonkPosition.XYDistanceTo(MyPosition);
            NecroDistance = NecroPosition.XYDistanceTo(MyPosition);

           



            Byte FirstByte = 0;
            FirstByte = Set(FirstByte, 0, true);
            FirstByte = Set(FirstByte, 1, Math.Max(WizDistance, MonkDistance) <= 45);
            if ((WizPosition.XYDistanceTo(MonkPosition) > 50) || !MonkIngame)
            {
                FirstByte = Set(FirstByte, 1, WizDistance<= 45);
            }
            else
            {
                FirstByte = Set(FirstByte, 1, Math.Max(WizDistance, MonkDistance) <= 45);
            }

            FirstByte = Set(FirstByte, 2, IPOnCooldown == true);
            FirstByte = Set(FirstByte, 3, WarCryOnCooldown == true);
            FirstByte = Set(FirstByte, 4, NecroIngame && (NecroDistance <= 95));
            Active = true;
            Active = Active && Hud.Game.IsInGame;
            Active = Active && !Hud.Game.IsPaused;
            Active = Active && !Hud.Game.IsLoading;
            Active = Active && (Hud.Game.SpecialArea == SpecialArea.Rift || Hud.Game.SpecialArea == SpecialArea.GreaterRift);
            Active = Active && ToggleOn;
            FirstByte = Set(FirstByte, 5, Active);
            FirstByte = Set(FirstByte, 6, FalterOnCooldown);
            FirstByte = Set(FirstByte, 7, WizDistance <= 20);
            send += "A";

            Byte SecondByte = 0;
            SecondByte = Set(SecondByte, 0, true);
            SecondByte = Set(SecondByte, 1, BerserkerOnCooldown);
            SecondByte = Set(SecondByte, 2, ImBarb);
            SecondByte = Set(SecondByte, 3, ImWizard);
            SecondByte = Set(SecondByte, 4, ImMonk);
            SecondByte = Set(SecondByte, 5, imNecro);
            SecondByte = Set(SecondByte, 6, EpiphanyOnCooldown);
            SecondByte = Set(SecondByte, 7, MantraOfHealingOnCooldown);
            send += "B";

            Byte ThirdByte = 0;
            ThirdByte = Set(ThirdByte, 0, true);
            ThirdByte = Set(ThirdByte, 1, Hud.Game.Me.Stats.ResourceCurSpirit >= (Hud.Game.Me.Stats.ResourceMaxSpirit / 2.0));
            ThirdByte = Set(ThirdByte, 2, WarCryBuffActive);
            ThirdByte = Set(ThirdByte, 3, BerserkerBuffActive);
            ThirdByte = Set(ThirdByte, 4, EpiphanyBuffActive);
            ThirdByte = Set(ThirdByte, 5, LotDOnCooldown);
            ThirdByte = Set(ThirdByte, 6, LotDBuffActive);
            ThirdByte = Set(ThirdByte, 7, Hud.Game.Me.Stats.ResourceCurFury >= (Hud.Game.Me.Stats.ResourceMaxFury / 2.0));
            send += "C";

            Byte FourthByte = 0;
            FourthByte = Set(FourthByte, 0, true);
            FourthByte = Set(FourthByte, 1, SprintOnCooldown);
            FourthByte = Set(FourthByte, 2, SprintBuffActive);
            FourthByte = Set(FourthByte, 3, RecastSweepingWind);
            FourthByte = Set(FourthByte, 4, BohOnCooldown);
            FourthByte = Set(FourthByte, 5, BoneArmorAlmostRunningOut);
            FourthByte = Set(FourthByte, 6, BoneArmorOnCooldown);
            FourthByte = Set(FourthByte, 7, Range25Enemies1);
            send += "D";

            Byte FifthByte = 0;
            FifthByte = Set(FifthByte, 0, true);
            FifthByte = Set(FifthByte, 1, Range25Enemies10);
            FifthByte = Set(FifthByte, 2, Hud.Game.Me.Defense.HealthCur <= (Hud.Game.Me.Defense.HealthMax *0.35));
            double Cooldown = (Hud.Game.Me.Powers.HealthPotionSkill.CooldownFinishTick - Hud.Game.CurrentGameTick) / 60d;
            bool PotionIsOnCooldown = Cooldown <= 30 && Cooldown >= 0 ? true : false;
            FifthByte = Set(FifthByte, 3, PotionIsOnCooldown);

            send += "E";

            byte[] myWriteBuffer = Encoding.ASCII.GetBytes(send);
            myWriteBuffer[1] = FirstByte;
            myWriteBuffer[2] = SecondByte;
            myWriteBuffer[3] = ThirdByte;
            myWriteBuffer[4] = FourthByte;
            myWriteBuffer[5] = FifthByte;
            if (Enabled) stream.Write(myWriteBuffer, 0, myWriteBuffer.Length);
            System.Threading.Thread.Sleep(2);
        }

    }

}