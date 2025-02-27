modded class MissionServer
{
	override void OnInit()
	{
		GetZenSleepConfig();
		super.OnInit();
		Print("[CHFSleep] OnInit - Loaded config successfully.");
	}
};

// vim:ft=enforce
