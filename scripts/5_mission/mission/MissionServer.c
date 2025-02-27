modded class MissionServer
{
	override void OnInit()
	{
		GetCHFSleepConfig();
		super.OnInit();
		Print("[CHFSleep] OnInit - Loaded config successfully.");
	}
};

// vim:ft=enforce
