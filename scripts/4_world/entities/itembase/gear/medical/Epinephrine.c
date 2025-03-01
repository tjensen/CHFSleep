// TODO: Make the epi give you a delayed tiredness effect as it gives you more stamina first?
modded class Epinephrine
{
    override void OnApply(PlayerBase player)
    {
        super.OnApply(player);

        float penalty = (float)player.MAX_TIREDNESS * -0.25;

        if (GetCHFSleepConfig().DebugOn)
        {
            player.CHFSleep_SendMessage("Giving tiredness penalty: " + penalty);
        }

        player.InsertAgent(CHFSleep_Agents.TIREDNESS, penalty);
    }
};

// vim:ft=enforce
