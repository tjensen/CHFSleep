modded class Morphine
{
    override void OnApply(PlayerBase player)
    {
        super.OnApply(player);

        float penalty = (float)player.MAX_TIREDNESS * 0.2;

        if (GetCHFSleepConfig().DebugOn)
        {
            player.CHFSleep_SendMessage("Giving tiredness penalty: " + penalty);
        }

        player.InsertAgent(CHFSleep_Agents.TIREDNESS, penalty);
    }
};

// vim:ft=enforce
