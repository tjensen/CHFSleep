modded class AntiChemInjector
{
    override void OnApply(PlayerBase player)
    {
        super.OnApply(player);

        float penalty = (float)player.MAX_TIREDNESS;

        if (GetCHFSleepConfig().DebugOn)
        {
            player.CHFSleep_SendMessage("Giving tiredness penalty: " + penalty);
        }

        player.InsertAgent(CHFSleep_Agents.TIREDNESS, penalty);
    }
};

// vim:ft=enforce
